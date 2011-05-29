/*
 * NAME:
 * 	serial.c -- Copyright (C) 1998 David Corcoran
 *
 * DESCRIPTION:
 *      This provides Unix serial driver support for RF2_SC reader
 * 
 * AUTHOR:
 *	David Corcoran, 7/22/98
 *
 *	Modified by Mark Hartman for Macintosh support, 7/15/98
 *
 *      Modified by James Rose to work with Litronic Argus 210 reader, 12/18/98
 *
 *         This version has no Mac support; the Mac portions of the code have
 *         been removed to avoid confusion.  This used to be a rather generic serial 
 *         driver, but due to the quirks of the Litronic Argus 210, it has been modified 
 *         specifically for the Argus CT-API driver.  Any other projects should use 
 *         a previous version of this file.
 *
 * 		Modified by Edgardo Vaz to work with RF2_SC reader, 05/29/2011
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
#include "../gpio/gpio.h"
#include "../gpio/beagle_gpio.h"

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
 *	This functions opens the serial port specified and sets the
 *	line parameters baudrate, bits per byte and parity according to the
 *	parameters.  If no serial port is specified, the Communications
 *	Manager's dialog is invoked to permit the user to select not only
 *	the port, but all the other (baud/bits/parity) details as well.
 *	Selections made by the user in this case will override the
 *	parameters passed.
 */

/*  Note:  Only the "port" parameter is used in this version.  Everything else
           is fixed for the Litronic Argus 210.  Most of this code is taken from
	       Litronics' sample code for Solaris.  
 */
bool
IO_InitializePort(int baud, int bits, char parity, char* port)
{
	/* UNIX SERIAL SUPPORT */
	
#ifdef CPU_ICAP_PC
	
	int handle; 
	struct termios tstr;
	int status;
	char buf[10];
	
	handle = open(port, O_RDWR | O_NOCTTY);	
	
	if (handle < 0) {	/* Problems with /dev/smartcard  */
	  return FALSE;
	}
	
	memset ((void*) &tstr, 0, sizeof (tstr)); 

	/* 
	   PARMRK Mark parity errors. 
	   INPCK  Enable input parity check. 
	*/
	tstr.c_iflag = PARMRK | INPCK;
	tstr.c_oflag = (tcflag_t) NULL;
	
	/* 
	   B9600   9600 baud 
	   PARENB  Parity enable   (even by default) 
	   CS8     8 bits          (one stop bit by default) 
	   CREAD   Enable receiver 
	   CLOCAL  Local line, else dial-up 
	*/
	tstr.c_cflag = B9600 | PARENB | CS8 | CREAD | CLOCAL;
	tstr.c_lflag = NOFLSH;
	tstr.c_cc[VMIN] = 0;		/* Minimum number of characters = 0 */
	tstr.c_cc[VTIME] = 5;		/* Timeout value in .1 sec intervals = 5 */
	
	/* Set the serial port parameters */
	status = ioctl (handle, TCSETS, &tstr);
	if (status)
	  perror ("Set params:");
	
	/* Write and read one test byte.  This seems to help the Zilog 8530 
	   sync up the framing. */
#define TEST_BYTE 55
	buf[0] = TEST_BYTE;
	status = write (handle, &buf[0], 1);
	if (status == -1)
	  {
	    perror ("Error syncing initial byte");
	  }
	Delay ();
	status = read (handle, &buf[0], 1);
	if ((status == 0) || (buf[0] != TEST_BYTE))
	  {
	    printf ("Error syncing initial byte/n");
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
	status_gpio status_XOE;
	
	handle = IO_ReturnHandle ();

	if (status)
		err = set_gpio_pin(&status_XOE, PIN7);
	else
		err = clear_gpio_pin(&status_XOE, PIN7);
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
	status_gpio status_XOE;
	
	handle = IO_ReturnHandle ();
	
	status = read_gpio_pin(&status_XOE, PIN7);
	
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
*/

bool 
IO_RF2SC_Reset () {

	int handle;
	int status;
	status_gpio status_RST_SC;
	
	handle = IO_ReturnHandle ();
	
	status = set_gpio_pin(&status_RST_SC, PIN4);	/* Reset High */
	if (status) {
		perror ("Reset High:");
		return FALSE;
	}
	
	Delay ();
	
	status = clear_gpio_pin(&status_RST_SC, PIN4);	/* Reset Low */
       	if (status) {
		perror ("Reset Low:");
		return FALSE;
	}
	
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

/* Reads a string of bytes of unknown length, reading repeatedly
   until the processes times out.  Returns number of bytes read. */
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

  Delay ();			/* The litronic reader needs this delay or there */
				/* will be a bunch of framing/parity errors */

  tcflush(handle, TCIFLUSH);	/* Flush the port.  We sure do a lot of flushing.. */
  
  if (write(handle, &c, 1) == 1) {            /* Write one byte   */
	  if (read (handle, &test, 1) == 1)   	  /* Now read it back */ 
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
