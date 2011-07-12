/*
 * NAME:
 *      serial.c -- Copyright (C) 1998 David Corcoran
 *
 * DESCRIPTION:
 *      This provides Unix serial driver support for RF2_SC reader
 * 
 * AUTHOR:
 *      David Corcoran, 7/22/98
 *
 *      Modified by Mark Hartman for Macintosh support, 7/15/98
 *
 *      Modified by James Rose to work with Litronic Argus 210 reader, 12/18/98
 *
 *         This version has no Mac support; the Mac portions of the code have
 *         been removed to avoid confusion.  This used to be a rather generic serial 
 *         driver, but due to the quirks of the Litronic Argus 210, it has been modified 
 *         specifically for the Argus CT-API driver.  Any other projects should use 
 *         a previous version of this file.
 *
 *      Modified by Edgardo Vaz, Melina Rabinovich & Daniel Aicardi
 * 		to work with RF2_SC reader, 05/29/2011
 *
 * LICENSE: See file LICENSE.
 *
 */

#include <stdio.h>                       /* Standard Includes     */
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

#include "serial.h"
#include "rf2_sc.h"
                                        /* For Unix Support      */
#include <termios.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>


struct IO_Specs {
        int    handle;
        BYTE   baud;
        BYTE   bits;
        char   parity;
        long   blocktime;
} ioport;


static char _rcsid[] UNUSED = "$Id: serial.c,v 1.2 1999/06/07 22:37:30 corcoran Exp $";

/* Delay for 5 ms */
static void Delay ()
{
        /* tstruct contains the delay value (sec,usec); default 5ms */
        struct timeval tstruct;
        tstruct.tv_sec  = 0;
        tstruct.tv_usec = 5000;
        
        select (1, NULL, NULL, NULL, &tstruct);
}


/*
 * InititalizePort -- initialize a serial port
 *      This functions opens the serial port specified and sets the
 *      line parameters baudrate, bits per byte and parity according to the
 *      parameters.  If no serial port is specified, the Communications
 *      Manager's dialog is invoked to permit the user to select not only
 *      the port, but all the other (baud/bits/parity) details as well.
 *      Selections made by the user in this case will override the
 *      parameters passed.
 */


bool
IO_InitializePort(int baud, int bits, char parity, char* port)
{
        /* UNIX SERIAL SUPPORT */
        
#ifdef CPU_ICAP_PC
        
        int handle; 
        struct termios newtio;
        int status;
        
        handle = open(port, O_RDWR | O_NOCTTY); 
        
        if (handle < 0) {       /* Problems with /dev/smartcard  */
          return FALSE;
        }

		bzero(&newtio, sizeof(newtio)); /*Clear struct for new port settings */

  /*
   * Set the baudrate
   */
		switch (baud) {

		case 4800:                      	/* Baudrate 4800          */
			newtio.c_cflag |= B4800;
			break;
		case 9600:                      	/* Baudrate 9600          */
			newtio.c_cflag |= B9600;
			break;
		case 19200:                         /* Baudrate 19200         */
			newtio.c_cflag |= B19200;
			break;
		default:
			close(handle);
			return -1;
		}
  
  /*
   * Set the bits.
   */
		switch (bits) {
			
		case 5:                              /* Five bits             */
			newtio.c_cflag |= CS5;
			break;
		case 6:                              /* Six bits              */
			newtio.c_cflag |= CS6;
			break;
		case 7:                              /* Seven bits            */
			newtio.c_cflag |= CS7;
			break;
		case 8:                              /* Eight bits            */
			newtio.c_cflag |= CS8;
			break;
		default:
			close(handle);
			return -1;
		}
	
  /*
   * Set the parity (Odd Even None)
   */
		switch (parity) {

		case 'O':                                   /* Odd Parity     */
			newtio.c_cflag |= PARODD | PARENB;
			break;
	  	case 'E':                                   /* Even Parity    */ 
			newtio.c_cflag &= (~PARODD); 
			newtio.c_cflag |= PARENB;
			break;
		case 'N':                                   /* No Parity      */
			newtio.c_cflag &= ~PARENB;
			break;
	    default:
			close(handle);
			return -1;
		}	

  /*
   * Setting Raw Input and Defaults
   */
   
	/* Control settings
	* CREAD    Allow input to be received.
	* CLOCAL   Disable modem control signals.
	* ~CRTSCTS Desable RTS/CTS handshaking.
	*/
	newtio.c_cflag |= CREAD|CLOCAL;
    newtio.c_cflag &= ~CRTSCTS;
	
	/* 
	 * Input settings
	 */
	newtio.c_iflag &= ~(IXON|IXOFF|IXANY); /*Turn off s/w flow ctrl*/
	newtio.c_iflag |= IGNBRK|IGNCR;
	newtio.c_iflag &= ~(ISTRIP|IGNPAR);	
	
	/*Output settings
     *~OPOST  No postprocess output.
     */ 
	newtio.c_oflag  &= ~OPOST; /*Raw output*/
	
	/*Local settings
	 *~ICANON  No Canonical input mode.
	 *~ECHO    No echo input characters. 
	 *~ECHOE 
	 *~ECHONL  No echo newline even if not echoing other characters.
     *~ISIG    Desable `interrupt', `quit', and `suspend' special characters.
     *~IEXTEN  Desable non-POSIX special characters.
	 */
	newtio.c_lflag &= ~(ICANON|ECHO|ECHOE|ISIG); /*Raw input*/
	newtio.c_lflag &= ~(ECHONL|IEXTEN);
	
	/*Special settings*/
	newtio.c_cc[VMIN]  = 1;		  /* Minimum number of characters = 1 */
	newtio.c_cc[VTIME] = 0;  /* Timeout value in .1 sec intervals = 0 */

	
	if (tcflush(handle, TCIFLUSH) < 0)        /* Flush the serial port*/
	{  
	  close(handle);
	  return -1;
	}
	
	if (tcsetattr(handle, TCSANOW, &newtio) < 0) /* Set the parameters*/
	{  
	  close(handle);
	  return -1;
	}	
        
        ioport.handle = handle;                           /* Record the handle                 */
        ioport.baud   = baud;                             /* Record the baudrate               */
        ioport.bits   = bits;                             /* Record the bits                   */
        ioport.parity = parity;                           /* Record the parity                 */
        ioport.blocktime = 10;                            /* Default Beginning Blocktime       */
        
        return TRUE;

#endif

}

void
IO_RF2SC_EN_CLK (bool status)
{
        int handle;
        int err;

        handle = IO_ReturnHandle ();

        if (status)
                err = enable_clock();
        else
                err = desable_clock();
        if (err)
                perror ("XOE clock error");
}

/* IO_RF2SC_IsCardInserted:
   Checks if a card is inserted by looking at the Clock line.
*/

bool
IO_RF2SC_IsCardInserted () {
  
        int handle;
        int status;

        handle = IO_ReturnHandle ();

        status = status_card();
        
        if (status < 0) {
                perror ("Clock detect error");
                return FALSE;
        }
        
        if (status_XOE.value)
                return TRUE;
        return FALSE;
}


/* IO_RF2SC_Reset:
   Resets the smartcard currently inserted in the RF2_SC reader 
   by cycling the GPIO line.
   ISO7816-3 
*/

bool 
IO_RF2SC_Reset () {

        int handle;
        int status;

        handle = IO_ReturnHandle ();

        status = reset_low();				   /* Reset Low smart card*/
        
        if (status) {
                perror ("Reset Low:");
                return FALSE;
        }
        
        Delay ();

        status = reset_high();				  /* Reset High smart card*/
        
    if (status) {
                perror ("Reset High:");
                return FALSE;
        }
        usleep(2000); /*Equivale a 8000 ciclos de reloj a F = 4MHz*/
        return TRUE;
}


int
IO_ReturnHandle() {
  return ioport.handle;                                   /* Return the current used handle    */
}

int 
IO_UpdateReturnBlock(int blocktime) {                    /* Sets the blocking timeout value, 
                                                                                                                        in microseconds                     */
 #ifdef CPU_ICAP_PC
  ioport.blocktime = (long)blocktime;     
 #endif
  
  return ioport.blocktime;                               /* Return the current blocktime        */
}

int
IO_ReturnBaudRate() {
  return ioport.baud;                                    /* Return the current baudrate         */
}

bool
IO_FlushBuffer() {
  
#ifdef CPU_ICAP_PC

  int handle = ioport.handle;

  if (tcflush(handle, TCIFLUSH) == 0)
    return TRUE;
  return FALSE;

#endif

}


/* Reads a string of bytes of a known length. */
bool
IO_Read( int readsize, BYTE *response ) { 
  
#ifdef CPU_ICAP_PC

  fd_set rfds;
  struct timeval tv;
  int rval;
  BYTE c;
  int handle;
  int count = 0;
  
  handle = ioport.handle;

  tv.tv_sec = 0;
  tv.tv_usec = ioport.blocktime;

  FD_ZERO(&rfds);
  
  for (count=0; count < readsize; count++) {
    FD_SET(handle, &rfds);
    rval = select (handle+1, &rfds, NULL, NULL, &tv);
    
    if (FD_ISSET(handle, &rfds)) {
      read(handle, &c, 1);
      response[count] = c;
    }
    else {
      tcflush(handle, TCIFLUSH);
      return FALSE;
    }
  }
  return TRUE;
  
#endif
 
}

/* Reads a string of bytes of unknown length, until the 
 * processes times out.  Returns number of bytes read. */
int 
IO_Read2 (int readsize, BYTE* response)
{

#ifdef CPU_ICAP_PC

  fd_set rfds;
  struct timeval tv;
  int rval;
  BYTE c;
  int handle;
  int count = 0;
  
  handle = ioport.handle;

  tv.tv_sec = 0;
  tv.tv_usec = ioport.blocktime;
  
  FD_ZERO(&rfds);
  
  for (count=0; count < readsize; count++) {
    FD_SET(handle, &rfds);
    rval = select (handle+1, &rfds, NULL, NULL, &tv);
    
    if (FD_ISSET(handle, &rfds)) {
      read(handle, &c, 1);
      response[count] = c;
    }
    else {
      tcflush(handle, TCIFLUSH); /* Not sure why this needs to be here.  It was there before. */
      return count;
    }
  }
  return readsize;

#endif

}


bool
IO_Write(BYTE c) {

#ifdef CPU_ICAP_PC

  int handle = ioport.handle;
  BYTE test;

  tcflush(handle, TCIFLUSH);    /* Flush the port.  We sure do a lot of flushing.. */
  
  if (write(handle, &c, 1) == 1) {            /* Write one byte   */
          if (read (handle, &test, 1) == 1)       /* Now read it back */ 
                  if (test == c) 
                          return TRUE;
  }
  return FALSE;
  
#endif

}


bool
IO_Close() {

#ifdef CPU_ICAP_PC

  int handle = ioport.handle;

  if ( close (handle) == 0 ) {                /* Close the handle */
    return TRUE;
  } else {
    return FALSE;                             /* Done !            */
  }

#endif

}
