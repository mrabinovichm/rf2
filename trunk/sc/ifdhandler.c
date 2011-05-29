/*****************************************************************
/
/ File   :   ifdhandler.c
/ Author :   David Corcoran
/ Date   :   November 7, 1998
/ Purpose:   This provides reader specific low-level calls.
/            Alot of the functionality listed in the specs is
/            not done.  I've done a minimum to get started.
/            See http://www.linuxnet.com for more information.
/ License:   See file LICENSE
/
******************************************************************/

#include "ctapi.h"
#include "ctbcs.h"
#include "ifdhandler.h"
#include <string.h>

RESPONSECODE IO_Create_Channel ( DWORD ChannelId ) {

  RESPONSECODE lRetVal = IFD_SUCCESS;

  int iPort;
  unsigned int iTerm = 0;

  unsigned short Unibble;         /* Upper 16bits of DWORD. (DDDD) */
  unsigned short Lnibble;         /* Lower 16bits of DWORD. (CCCC) */

  Unibble = ChannelId >> 16;                 /* Shift right 16 bits.     */
  Lnibble = ChannelId - ( Unibble << 16 );   /* Shift left and subtract. */

  switch ( Unibble ) {

    case 0x01:                               /* Serial Port.             */

      switch ( Lnibble ) {

        case 0x3F8:
          iPort = PORT_COM1;
          break;

        case 0x2F8:
          iPort = PORT_COM2;
          break;

        case 0x3E8:
          iPort = PORT_COM3;
          break;

        case 0x2E8:
          iPort = PORT_COM4;
          break;
    
        default:
          lRetVal = IFD_NOT_SUPPORTED;
          break;
      }


      break;

    case 0x02:                               /* Parallel Port.     */
      lRetVal = IFD_NOT_SUPPORTED;
      break;

    case 0x04:                               /* PS 2 Port.         */
      lRetVal = IFD_NOT_SUPPORTED;
      break;

    case 0x08:                               /* SCSI Port.         */
      lRetVal = IFD_NOT_SUPPORTED;
      break;

    case 0x10:                               /* IDE Port.          */
      lRetVal = IFD_NOT_SUPPORTED;
      break;

    case 0x20:                               /* USB Port.          */
      lRetVal = IFD_NOT_SUPPORTED;
      break;

    /* case 0xFy where y is vendor defined 0 - F is NOT implemented */

    default:                                 /* Port Not Found.    */
      lRetVal = IFD_NOT_SUPPORTED;
      break;

  }


  if ( lRetVal == IFD_SUCCESS ) {
    
    if ( CT_init( iTerm, iPort ) == OK ) {
      lRetVal = IFD_SUCCESS;

     } else {
      lRetVal = IFD_COMMUNICATION_ERROR;
     }
  }

  return lRetVal;
}

RESPONSECODE IO_Close_Channel () {

  RESPONSECODE lRetVal = IFD_SUCCESS;

  unsigned int iTerm = 0;

  if ( CT_close( iTerm ) == OK ) {
    lRetVal = IFD_SUCCESS;

  } else {
    lRetVal = IFD_COMMUNICATION_ERROR;
  }

  return lRetVal;

}


RESPONSECODE IFD_Get_Capabilities ( DWORD Tag, BYTE Value[] ) {

  RESPONSECODE lRetVal;
  DWORD HighNibble;
  DWORD LowNibble;
  int i;
  HighNibble = Tag >> 8;
  LowNibble  = Tag - ( HighNibble << 8 );   /* Shift left and subtract. */

  if ( HighNibble == 0x02 ) {

    switch( LowNibble ) {
      case 0x01:
        lRetVal = IFD_SUCCESS;  
        break;

    }

  } else if ( HighNibble == 0x03 ) {      /* This is the ICC_STATE */

    switch( LowNibble ) {
   
      case 0x00:
	break;
      case 0x01:

        if ( IFD_Is_ICC_Present() == IFD_SUCCESS ) {
          *(DWORD*)Value = IFD_ICC_PRESENT;
        } else {
          *(DWORD*)Value = IFD_ICC_NOT_PRESENT;
        }

        lRetVal = IFD_SUCCESS;  
	break;
      case 0x03:
        memcpy(Value, ICC.ATR, MAX_ATR_SIZE);
        lRetVal = IFD_SUCCESS;  
	break;
      case 0x04:
	break;
      default:
 	break;

    }

  }

  return lRetVal;
}

RESPONSECODE IFD_Set_Capabilities ( DWORD Tag, BYTE Value[] ) {

  RESPONSECODE lRetVal;
  DWORD HighNibble;
  DWORD LowNibble;

  HighNibble = Tag >> 8;
  LowNibble  = Tag - ( HighNibble << 8 );   /* Shift left and subtract. */

  if ( HighNibble == 0x03 ) {      /* This is the ICC_STATE */

    switch( LowNibble ) {
   
      case 0x00:
	break;
      case 0x01:
	break;
      case 0x03:
	break;
      case 0x04:
	break;
      default:
 	break;

    }

  }
  
  return lRetVal;
}

RESPONSECODE IFD_Set_Protocol_Parameters ( DWORD ProtocolType, 
					   BYTE SelectionFlags,
					   BYTE PTS1, BYTE PTS2,
					   BYTE PTS3 ) {

  RESPONSECODE lRetVal;
  lRetVal = IFD_NOT_SUPPORTED;
  return lRetVal;

}

RESPONSECODE IFD_Power_ICC ( DWORD ActionRequested ) {
  
  RESPONSECODE lRetVal;
  RESPONSECODE TestRsp;
  
  int i;
  int lc;
  unsigned int lr;
  unsigned int iTerm;
  
  BYTE sad;
  BYTE dad;
  BYTE Response[MAX_RESPONSE_SIZE];
  BYTE pcPowerUp[]   = {0x20, 0x12, 0x00, 0x00, 0x00};
  BYTE pcPowerDown[] = {0x20, 0x15, 0x00, 0x00, 0x00};
  BYTE pcReset[]     = {0x20, 0x11, 0x00, 0x01, 0x00}; 

  iTerm = 1;
  sad = 2;
  dad = 1;

  lc = 5;
  lr = 2;

  if ( ActionRequested == IFD_POWER_UP ) {
    
    if ( CT_data( iTerm, &dad, &sad, lc, pcPowerUp, &lr, Response ) ==
	 OK ) {

       sad = 2;
       dad = 1;
       lr = MAX_ATR_SIZE;

      TestRsp = CT_data( iTerm, &dad, &sad, lc, pcReset, &lr, Response );

      if (TestRsp == OK ) {

        memcpy( ICC.ATR, Response, lr );          /* Copies the ATR.       */
            
        for ( i=lr-2; i < MAX_ATR_SIZE; i++ ) {   /* Copies zeros to rest. */
	  ICC.ATR[i] = 0x00;
        }

        lRetVal = IFD_SUCCESS;
      
      } else {
        lRetVal = IFD_ERROR_POWER_ACTION;
      }

    } else {
      lRetVal = IFD_ERROR_POWER_ACTION;
    }
    
  } else if ( ActionRequested == IFD_POWER_DOWN ) {
    
    if ( CT_data( iTerm, &dad, &sad, lc, pcPowerDown, &lr, Response ) == 
	 OK ) {
     
      lRetVal = IFD_SUCCESS;
      
    } else {
      lRetVal = IFD_ERROR_POWER_ACTION;
    }
    
  } else if ( ActionRequested == IFD_RESET ) {

    if ( CT_data( iTerm, &dad, &sad, lc, pcReset, &lr, Response ) == 
	 OK ) {
     
      memcpy( ICC.ATR, Response, lr );         /* Copies the ATR.       */
      
      for ( i=lr; i < sizeof(ICC.ATR); i++ ) { /* Copies zeros to rest. */
	ICC.ATR[i] = 0x00;
      }

      lRetVal = IFD_SUCCESS;
      
    } else {
      lRetVal = IFD_ERROR_POWER_ACTION;
    }
    
  } else {
    lRetVal = IFD_NOT_SUPPORTED;
  }

  return lRetVal;
  
}

RESPONSECODE IFD_Swallow_ICC() {
  
  RESPONSECODE lRetVal;
  lRetVal = IFD_ERROR_NOT_SUPPORTED;        /* This is not supported. */
  return lRetVal;

}

RESPONSECODE IFD_Eject_ICC() {
  
  RESPONSECODE lRetVal;
  lRetVal = IFD_ERROR_NOT_SUPPORTED;        /* This is not supported. */
  return lRetVal;

}

RESPONSECODE IFD_Confiscate_ICC() {
  
  RESPONSECODE lRetVal;
  lRetVal = IFD_ERROR_NOT_SUPPORTED;        /* This is not supported. */
  return lRetVal;

}

RESPONSECODE IFD_Transmit_to_ICC ( struct SCARD_IO_HEADER SendPci,
                                   BYTE CommandData[], DWORD CommandSize, 
                                   BYTE ResponseData[], DWORD *ResponseSize, 
                                   struct SCARD_IO_HEADER *RecvPci ) {

  RESPONSECODE lRetVal;
  int i;
  DWORD lc;
  DWORD Protocol;
  unsigned int lr;
  unsigned int iTerm;
  
  BYTE sad;
  BYTE dad;
  
  iTerm = 1;

  sad = 2;
  dad = 0;

  lc = CommandSize;

/* Print Transmit Error Messaging */

#ifdef PCSC_DEBUG
  printf("[%04x] -> ", lc );

  for ( i=0; i < lc; i++ ) {
    printf("%02x ", CommandData[i]);
  } printf("\n");
#endif  


    if ( lc > 5 ) {
      lr = 2;
    } else {
      lr = CommandData[4] + 2;
    }

    if ( CT_data( iTerm, &dad, &sad, lc, CommandData, &lr, ResponseData ) ==
         OK ) {
    
      *ResponseSize = lr;      
      lRetVal = IFD_SUCCESS;

/* Print Receive Error Messaging */

#ifdef PCSC_DEBUG
  printf("[%04x] <- ", lr );

  for ( i=0; i < lr; i++ ) {
    printf("%02x ", ResponseData[i]);
  } printf("\n");
#endif  

    } else {
      lRetVal = IFD_COMMUNICATION_ERROR;
    }
    
  return lRetVal;    
}
    
RESPONSECODE IFD_Is_ICC_Present() {

  RESPONSECODE lRetVal;
  RESPONSECODE TestRsp;
  
  int lc;
  unsigned int lr;
  unsigned int iTerm;  
  int i;
  BYTE sad;
  BYTE dad;
  BYTE Response[MAX_RESPONSE_SIZE];
  BYTE pcStatus[5] = {0x20, 0x13, 0x00, 0x00, 0x00};

  iTerm = 0;

  i=0;

  sad = 2;
  dad = 1;
  lc = 5;
  lr = 7;

    TestRsp = CT_data( iTerm, &dad, &sad, lc, pcStatus, &lr, Response );
 
     if ( TestRsp == OK ) {

	 if ( Response[0] & CTBCS_DATA_STATUS_CARD ) {  /* Card Inserted */
	   return IFD_ICC_PRESENT;

	 } else {
	   return IFD_ICC_NOT_PRESENT;
	 }
     }   

  return IFD_COMMUNICATION_ERROR;

}

RESPONSECODE IFD_Is_ICC_Absent() {

  RESPONSECODE lRetVal;

  int lc;
  unsigned int lr;
  unsigned int iTerm;  

  BYTE sad;
  BYTE dad;
  BYTE Response[MAX_RESPONSE_SIZE];
  BYTE pcStatus[5] = {0x20, 0x13, 0x00, 0x00, 0x00};

  iTerm = 0;

  sad = 2;
  dad = 1;

  lc = 5;
  lr = 7; 
   
    if ( CT_data( iTerm, &dad, &sad, lc, pcStatus, &lr, Response ) ==
	 OK ) {

	 if ( ! Response[0] & CTBCS_DATA_STATUS_CARD ) {  /* Card Removed */
	   lRetVal = IFD_ICC_NOT_PRESENT;

	 } else {
	   lRetVal = IFD_ICC_PRESENT;
	 }
     }   
  
  return lRetVal;
  
}
