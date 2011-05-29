/*****************************************************************
/
/ File   :   ifdhandler.h
/ Author :   David Corcoran
/ Date   :   November 7, 1998
/ Purpose:   This provides reader specific low-level calls.
/            See http://www.linuxnet.com for more information.
/ License:   See file LICENSE
/
******************************************************************/

#ifndef _IFD_Handler_h_
#define _IFD_Handler_h_

#include "pcscdefines.h"
#include "defines.h"

/* List of Data Structures available to IFD_Handler */

struct SCARD_IO_HEADER {
  DWORD Protocol;
  DWORD Length;
};

struct DEVICE_CAPABILITIES {
  
  STR Vendor_Name;          	/* Tag 0x0100        */
  STR IFD_Type;					/* Tag 0x0101        */
  DWORD IFD_Version;			/* Tag 0x0102        */
  STR IFD_Serial;				/* Tag 0x0103        */
  DWORD IFD_Channel_ID;  		/* Tag 0x0110        */
  
  
  DWORD Asynch_Supported;		/* Tag 0x0120        */
  DWORD Default_Clock;			/* Tag 0x0121        */
  DWORD Max_Clock;				/* Tag 0x0122        */
  DWORD Default_Data_Rate;		/* Tag 0x0123        */
  DWORD Max_Data_Rate;			/* Tag 0x0124        */
  DWORD Max_IFSD;				/* Tag 0x0125        */
  DWORD Synch_Supported;		/* Tag 0x0126        */
  DWORD Power_Mgmt;				/* Tag 0x0131        */
  DWORD Card_Auth_Devices;		/* Tag 0x0140        */
  DWORD User_Auth_Device;		/* Tag 0x0142        */
  DWORD Mechanics_Supported;	/* Tag 0x0150        */
  DWORD Vendor_Features;		/* Tag 0x0180 - 0x01F0   User Defined. */
  
} Device;

struct ICC_STATE {

  BYTE ICC_Presence;			/* Tag 0x0300        */
  BYTE ICC_Interface_Status;	/* Tag 0x0301        */
  BYTE ATR[32];					/* Tag 0x0303        */
  BYTE ICC_Type;				/* Tag 0x0304        */

} ICC;

struct PROTOCOL_OPTIONS {
  
  DWORD Protocol_Type;			/* Tag 0x0201        */
  DWORD Current_Clock;			/* Tag 0x0202        */
  DWORD Current_F;				/* Tag 0x0203        */
  DWORD Current_D;				/* Tag 0x0204        */
  DWORD Current_N;				/* Tag 0x0205        */
  DWORD Current_W;				/* Tag 0x0206        */
  DWORD Current_IFSC;			/* Tag 0x0207        */
  DWORD Current_IFSD;			/* Tag 0x0208        */
  DWORD Current_BWT;			/* Tag 0x0209        */
  DWORD Current_CWT;			/* Tag 0x020A        */
  DWORD Current_EBC;			/* Tag 0x020B        */
} Protocol;


/* The list of tags should be alot more but
   this is all I use in the meantime        */

#define TAG_IFD_ATR					0x0303

/* List of Defines available to IFD_Handler */

#define IFD_POWER_UP				500
#define IFD_POWER_DOWN				501
#define IFD_RESET					502

#define	IFD_SUCCESS					0
#define IFD_ERROR_TAG				600
#define IFD_ERROR_SET_FAILURE		601
#define IFD_ERROR_VALUE_READ_ONLY	602
#define IFD_NEGOTIATE_PTS11			603
#define IFD_NEGOTIATE_PTS22			604
#define IFD_ERROR_PTS_FAILURE		605
#define IFD_ERROR_NOT_SUPPORTED		606
#define IFD_PROTOCOL_NOT_SUPPORTED	607
#define IFD_ERROR_POWER_ACTION		608
#define IFD_ERROR_SWALLOW			609
#define IFD_ERROR_EJECT				610
#define IFD_ERROR_CONFISCATE		611
#define IFD_COMMUNICATION_ERROR		612
#define IFD_RESPONSE_TIMEOUT		613
#define IFD_NOT_SUPPORTED			614

/* Extension of the Specification */

#define IFD_ICC_PRESENT				615
#define IFD_ICC_NOT_PRESENT			616

/* List of Defined Functions Available to IFD_Handler */


RESPONSECODE IO_Create_Channel (
				DWORD ChannelID
				);

RESPONSECODE IO_Close_Channel ();


RESPONSECODE IFD_Get_Capabilities (
				   DWORD Tag,
				   BYTE Value[]
				   );


RESPONSECODE IFD_Set_Capabilities (
				   DWORD Tag,
				   BYTE Value[]
				   );

RESPONSECODE IFD_Set_Protocol_Parameters (
					  DWORD ProtocolType,
					  BYTE SelectionFlags,
					  BYTE PTS1,
					  BYTE PTS2,
					  BYTE PTS3
					  );

RESPONSECODE IFD_Power_ICC (
			    DWORD ActionRequested
			    );

RESPONSECODE IFD_Swallow_ICC();

RESPONSECODE IFD_Eject_ICC();

RESPONSECODE IFD_Confiscate_ICC();

/* Added to make life much easier */

RESPONSECODE IFD_Transmit_to_ICC ( 
                                   struct SCARD_IO_HEADER SendPci,
                                   BYTE CommandData[], 
                                   DWORD CommandSize,
                                   BYTE ResponseData[], 
                                   DWORD *ResponseSize,
                                   struct SCARD_IO_HEADER *RecvPci 
                                 );

RESPONSECODE IFD_Is_ICC_Present();

RESPONSECODE IFD_Is_ICC_Absent();

#endif

