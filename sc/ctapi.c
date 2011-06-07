/*****************************************************************
/
/ File   :   ctapi.c
/ Authors:   Edgardo Vaz, Melina Rabinovich, Daniel Aicardi
/			 Based on code by James Rose
/ Date   :   June 6, 2011
/ Purpose:   Defines CT-API functions
/ License:   See file LICENSE
/
******************************************************************/

/* for Delay function */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "defines.h"
#include "ctapi.h"
#include "serial.h"

#include "../gpio/gpio.h"
#include "../gpio/beagle_gpio.h"

#ifdef SUN_SPARC
static char com1_path[] = "/dev/cua/a";
static char com2_path[] = "/dev/cua/b";
static char com3_path[] = "/dev/cua/c";
static char com4_path[] = "/dev/cua/d";
#endif

#ifndef SUN_SPARC
static char com1_path[] = "/dev/ttyS0";
static char com2_path[] = "/dev/ttyS1";
static char com3_path[] = "/dev/ttyS2";
static char com4_path[] = "/dev/ttyS3";
#endif



static void print_bytes (const BYTE* bytes, int len)
{
	int i;
	for (i=0; i<len; i++) {
		printf("%02x ", bytes[i]);
	}
	
	printf("\n");
}


/* Delay for 5 ms */

static void Delay ()
{
	/* tstruct contains the delay value (sec,usec); default 5ms */
	struct timeval tstruct =  {0, 5000};
	
	select (1, NULL, NULL, NULL, &tstruct);
}

/* Initializes the port on which the reader resides */

int  CT_init ( unsigned int Ctn,  unsigned int pn ) {
  
	bool BretVal;        /* Return value from IO_InitializePort() */
	int IretVal;         /* Return for this function */  
	
	switch( pn ) {
		
	case PORT_COM1:
		BretVal = IO_InitializePort (9600, 8, 'E', com1_path);
		break;
     
	case PORT_COM2:
		BretVal = IO_InitializePort (9600, 8, 'E', com2_path);
		break;
		
	case PORT_COM3:
		BretVal = IO_InitializePort (9600, 8, 'E', com3_path);
		break;

	case PORT_COM4:
		BretVal = IO_InitializePort (9600, 8, 'E', com4_path);
		break;
		
	case PORT_Printer:
		BretVal = IO_InitializePort(9600,8,'E',"Printer Port");
		break;
		
	case PORT_Modem:
		BretVal = IO_InitializePort(9600,8,'E',"Modem Port");
		break;
		
	default:
		BretVal = IO_InitializePort(9600,8,'E',"/dev/smartcard");
		break;
	}
	
	if (BretVal != TRUE) {
		IretVal = ERR_MEMORY;        /* Could not allocate port */
	} else {
		IretVal = OK;
	}

	IO_UpdateReturnBlock (100000);

	return IretVal;  
}


/* Closes the port in which the reader resides */

int  CT_close( unsigned int Ctn ) {
  
	if (IO_Close() == TRUE) {
		return OK;
		
	} else {
		return ERR_CT;
		
	}
}            

/* Sends/Receives Data to/from the Reader */

int CT_data( unsigned int ctn, unsigned char *dad, unsigned char *sad,
              unsigned int  lc, const unsigned char *cmd, unsigned int  *lr,
              unsigned char *rsp ) 
{
    int IretVal;
	unsigned char control_byte;
	status_gpio status_RST_SC;

	/* READER COMMAND */
	if (*dad == 1) { 	/* This command goes to the reader */

		*sad = 1;	/* Data is going from reader (1) to host (2) */
		*dad = 2;
		
		/*******************/
		/* CT-BCS Commands */
		/*******************/
		
		/* Reset - Reset the card and return ATR */
		if (cmd[0] == 0x20 && cmd[1] == 0x11) {
			if (IO_RF2SC_Reset () == FALSE)
				IretVal = ERR_TRANS;
			else {
				/* Read the ATR. */
				*lr = IO_Read2 (*lr, rsp);
				rsp[*lr] = 0x90;
				rsp[*lr+1] = 0x00;
				*lr += 2;
				IretVal = OK;
			}
		}

		/* Request ICC - Turn on reader/card */
		else if (cmd[0] == 0x20 && cmd[1] == 0x12) {
			/* Just turn on the clock */
			IO_RF2SC_EN_CLK (TRUE);
			*lr = 0;
			IretVal = OK;
		}

		/* Eject ICC - Turn off card's clock & Reset Low */
		else if (cmd[0] == 0x20 && cmd[1] == 0x15) {
			clear_gpio_pin(&status_RST_SC, PIN4);	/* Reset Low */
			IO_RF2SC_EN_CLK (FALSE);				/* Stop clock */
			*lr = 0;
			IretVal = OK;
		}

		/* Get Card Status, ICC status Data Object (DO) */
		else if (cmd[0] == 0x20 && cmd[1] == 0x13) {
			if (IO_RF2SC_IsCardInserted ())
				*rsp = 5; /* card is present and electrically connected */
			else 
				*rsp = 0; /* card not present */

			*lr = 1;
			IretVal = OK;
		}

		/* Command sent directly to the card */
		else {
			/* Don't do anything..  */
			*lr = 0;
			IretVal = OK;
		}
	}

	/* CARD COMMAND */
	else if (*dad == 0) {	/* This command goes to the card */

		char buf[MAX_BUFFER_SIZE];
		int i, max_len;

/*    		printf("sending command to card... len %d\n", lc);  */
		
		*sad = 0;	/* Card (0) --> Host (2) */
		*dad = 2;

		IretVal = OK;
		
		/* Send the command (first five bytes) */
		for (i = 0; i < 5; i++)
			if (!IO_Write (cmd[i])) {
				IretVal = ERR_TRANS;
				break;
			}

		max_len = *lr;

		/* Read the card's response */
		*lr = IO_Read (1, &control_byte);
		if ((control_byte == 0x90) ||
		    ((control_byte & 0x60) == 0x60)) {
		    /* Store 90 00 in rsp */
		    rsp[0] = control_byte;
		    IO_Read (1, &rsp[1]);
		    *lr = 2;
		}
		else {
		    *lr = IO_Read2 (max_len, rsp);
		}

		/* The card may have more data that it's trying to send.. 
		   Eat it up so that it doesn't sit there and mess up the
		   next read... */
		if (max_len == *lr) {
		    unsigned char trash[128];
		    int nr;
		    
		    nr = IO_Read2 (128, trash);
		    if (nr > 0) {
			/* Indicate that data was lost somehow.. */
			printf ("Uh-oh, your buffer was too small"
				" and you lost data.\n");
		    }

		    while (nr == 128)
			nr = IO_Read2 (128, trash);
		}

/*  		printf ("lr = %d\n", *lr); */
		
/*  		if ((cmd[1] ^ rsp[0]) == 0) { */
/*  			printf ("\nsend it all!\n"); */
/*  		} else if ((cmd[1] ^ rsp[0]) == 1 || */
/*  			   (cmd[1] ^ rsp[0]) == 0xFF){ */
/*  		  printf ("Big command.  buffering"); */
/*  		} else { */
/*  			  printf ("\nGot something unexpected:  (xor = %02x)  ", */
/*  				  rsp[0] ^ cmd[1]); */
/*  			  print_bytes (rsp, *lr); */
/*  		} */

		/* Send the rest of the command */
		for (i = 5; i < lc; i++) {
			if (!IO_Write (cmd[i])) {
				IretVal = ERR_TRANS;
				break;
			}
			
			if ((cmd[1] ^ control_byte) == 1 ||
			    (cmd[1] ^ control_byte) == 0xFF) {
				/* The buffer is full */
				/* Wait on a response from the card */
				*lr = IO_Read (1, &control_byte);
			} 
			 
		}

		/* Read the card's second response, if something was sent */
		/* CHECK:  can there be anything here more than two bytes if 
		   it was a long command above?  */
		if (lc > 5) {
			*lr = IO_Read2 (max_len, rsp);
		}

		/* Read back the echo */
/* 		if (!IO_Read (lc, rsp)) */
/* 	  		IretVal = ERR_TRANS; */
		
	}
	else {			/* This command goes nowhere because the dest. is invalid */
		IretVal = ERR_INVALID;  
	}
	
	if (IretVal != OK)
		*lr = 0;

	return IretVal;
}


