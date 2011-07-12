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

#include "rf2_sc.h"

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
	unsigned char ack_byte;

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
			reset_low();				   /* Reset Low smart card*/
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

		BYTE sw1, sw2;
		BYTE get_response[5];
		int i, max_len;

/*    		printf("sending command to card... len %d\n", lc);  */
		
		*sad = 0;	/* Card (0) --> Host (2) */
		*dad = 2;

		IretVal = OK;
		
		/* Algoritmo T = 0 implementado como indica el libro Smart Card Handbook 3rd edition, 
		 * Autores Rankl & Effing. Chapter 6, Smart Card data transmission, page 403
		 */ 
		
		/* Send the command (first five bytes) */
		for (i = 0; i < 5; i++)
			if (!IO_Write (cmd[i])) {
				IretVal = ERR_TRANS;
				break;
			}

		max_len = *lr;

		/* Read the card's ACK byte */
		*lr = IO_Read (1, &ack_byte);
		//printf("\nACK de la tarjeta: %02X\n", ack_byte);
		
		/*Si el byte ACK de la tarjeta es igual al byte INS mando el resto del comando*/		
		if (ack_byte == cmd[1]) {
		/* Send the rest of the command */
			for (i = 5; i < lc; i++) {
				if (!IO_Write (cmd[i])) {
					IretVal = ERR_TRANS;
					break;
				}
			}
			IO_Read (1, &sw1);
			IO_Read (1, &sw2);
		}
		else {
			sw1 = ack_byte;
			IO_Read (1, &sw2);						
		}
		//printf("SW1: %02X, SW2: %02X\n", sw1, sw2);			
		switch(sw1){
			
			case 0x90: 
				rsp[0] = sw1;
				rsp[1] = sw2;
				*lr = 2;
			break;
			case 0x6c:
				memcpy(get_response, cmd, 5);
				get_response[4] = sw2;
				for (i = 0; i < 5; i++)
					if (!IO_Write (get_response[i])) {
						IretVal = ERR_TRANS;
					break;
					}
				/* Read the card's second response, if something was sent */
				/* CHECK:  can there be anything here more than two bytes if 
				   it was a long command above?  */
				*lr = IO_Read (1, &ack_byte);
				//printf("\nACK de la tarjeta: %02X\n", ack_byte);
				*lr = IO_Read2 (max_len, rsp);
			break;
			default:
				rsp[0] = sw1;
				rsp[1] = sw2;
				*lr = 2;			
			break;			
		}
		
	}
	else {			/* This command goes nowhere because the dest. is invalid */
		IretVal = ERR_INVALID;  
	}
	
	if (IretVal != OK)
		*lr = 0;

	return IretVal;
}


