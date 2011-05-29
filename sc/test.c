/**************************************************
						  
   main.c:  CT-API test program.
            Tests the functions of the CT-API for 
	    the Litronic Argus 210 smartcard reader
	    and a Schlumberger Cryptoflex card.

	    Author:  James Rose
	    Based on code by David Corcoran

	    Date:    12/22/98
	    License: See LICENSE

****************************************************/

#include <stdio.h>
#include "ctapi.h"
#include "defines.h"

void print_bytes (const BYTE* bytes, int len)
{
	int i;
	for (i=0; i<len; i++) {
		printf("%02x ", bytes[i]);
	}
	
	printf("\n");
}

void do_card_command (const BYTE* cmd, int len, BYTE* Resp, int* rlen)
{
	BYTE dad = 0;
	BYTE sad = 2;
	int Iret;

	*rlen = 500;
	if ((Iret = CT_data (1,&dad,&sad,len,cmd,rlen,Resp)) == OK ) {
		printf ("Command sent successfully: \n");
		print_bytes (cmd, len);
		printf ("Response: \n");
		print_bytes (Resp, *rlen);
		printf ("\n");
	} else {
		printf("Error sending command: %d \n", Iret);
		print_bytes (cmd, len);
	}
	
}

int main() {
  
  unsigned char dad=1;
  unsigned char sad=2;
  unsigned int lr = 3;
  BYTE Bcmd[50];
  BYTE Brsp[50];
  BYTE Act[5] = {0x20,0x12,0x00,0x00,0x00};
  BYTE Rst[5] = {0x20,0x11,0x00,0x00,0x00};
  BYTE Eject[5] = {0x20,0x15,0x00,0x00,0x00};
  BYTE GetStatus[] = {0x20,0x13,0x00,0x00,0x00};
  int i;
  int Iret;
  
  CT_init(1,PORT_COM2);
  
  if ((Iret = CT_data(1,&dad,&sad,5,Act,&lr,Brsp)) == OK ) {
    printf("Successful Initialize \n");
  } else {
    printf("Error on Initialization -> %d\n", Iret);
  }

  dad = 1;   // Reader
  sad = 2;   // Host

  lr = 10;

  if ((Iret = CT_data(1,&dad,&sad,5,Rst,&lr,Brsp)) == OK ) {
    printf("Successful Reset/Set Mode \n");
  } else {
    printf("Error on Reset -> %d\n", Iret);
  }

  printf("ATR Response Size: %02x \n", lr);
  
  for (i=0; i<lr; i++) {
	  printf("%02x ", Brsp[i]);
  }
  
  printf("\n\n");

  dad = 1;
  sad = 2;
  lr = 10;
  if (CT_data (1, &dad, &sad, 5, GetStatus, &lr, Brsp) != OK) {
	  printf ("Error on card status\n");
  }
  if (!Brsp[0]) 
	  printf ("Card not inserted.\n\n");
  else
	  printf ("Card inserted.\n\n");
  
  /* Start testing commands */
  {  
				/* get challenge (random number) */
      BYTE Brnd[]   = {0xC0,0x84,0x00,0x00,0x08};
      BYTE GetBigChallenge[] = {0xC0, 0x84, 0x00, 0x00, 0x26};

				/* authenticate to the card */
      BYTE Verify[] = {0xF0,0x2A,0x00,0x01,0x08,0x47,0x46,0x58,0x49,0x32,0x56,0x78,0x40};

      BYTE Select[] = {0xC0, 0xA4, 0x00, 0x00, 0x02, 0x3F, 0x00}; /* select root directory */

				/* create record  */
      BYTE Create[] = {0xC0, 0xE2, 0x00, 0x00, 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
      BYTE Dir[] = {0xF0, 0xA8, 0x00, 0x00, 0x00};
      BYTE GetResponse[] = {0xC0, 0xC0, 0x00, 0x00, 0x20}; /* last byte is length */

      BYTE Select1257[] = {0xC0, 0xA4, 0x00, 0x00, 0x02, 0x12, 0x57};
      BYTE Select0200[] = {0xC0, 0xA4, 0x00, 0x00, 0x02, 0x02, 0x00};
      BYTE Select1001[] = {0xC0, 0xA4, 0x00, 0x00, 0x02, 0x10, 0x01};
      // BYTE Seek[] = {0xF0, 0xA2, 0x00, 0x00, 0x40, /* seek for 64-byte pattern */
	
      BYTE Update[] = {0xC0, 0xD6, 0x00, 0x00, 0x40, /* update 64-byte pattern */
		     /* 8 by 8 pattern matrix */
		     0x00, 0x01, 0x02, 0x04, 0x08, 0x88, 0x02, 0x85,
		     0x00, 0x01, 0x02, 0x04, 0x08, 0x88, 0x02, 0x85,
		     0x00, 0x01, 0x02, 0x04, 0x08, 0x88, 0x02, 0x85,
		     0x00, 0x01, 0x02, 0x04, 0x08, 0x88, 0x02, 0x85,
		     0x00, 0x01, 0x02, 0x04, 0x08, 0x88, 0x02, 0x85,
		     0x00, 0x01, 0x02, 0x04, 0x08, 0x88, 0x02, 0x85,
		     0x00, 0x01, 0x02, 0x04, 0x08, 0x88, 0x02, 0x85,
		     0x00, 0x01, 0x02, 0x04, 0x08, 0x88, 0x02, 0x85
      };

      
/*        BYTE MakeBigFile = {0xF0, 0xE0, 0x00, 0x00, 0x10, */
/*  			  0x00, 0x00, /* RFU (reserved) */
/*  			  0x01, 0x00, /* 256 byte file */ 
/*  			  0x13, 0x48, /* File name */ 
/*  			  0x01,	      /* Transparent EF */ 
/*  			  0xFF, */
			  
      BYTE Resp[500];
      int RespLen;

      do_card_command (Select, sizeof (Select), Resp, &RespLen);
      do_card_command (Brnd, sizeof (Brnd), Resp, &RespLen);
      do_card_command (GetBigChallenge, sizeof (GetBigChallenge), Resp, &RespLen);
      do_card_command (Verify, sizeof (Verify), Resp, &RespLen);
      do_card_command (Dir, sizeof (Dir), Resp, &RespLen);
      GetResponse[4] = Resp[1];	  /* Get however many bytes the card told us to get */
      do_card_command (GetResponse, sizeof (GetResponse), Resp, &RespLen);
      do_card_command (Select1257, sizeof (Select1257), Resp, &RespLen);

      /* Change to 0x200 directory and list it */
      do_card_command (Select0200, sizeof (Select0200), Resp, &RespLen);
      do_card_command (Dir, sizeof (Dir), Resp, &RespLen);
      GetResponse[4] = Resp[1];	  /* Get however many bytes the card told us to get */
      do_card_command (GetResponse, sizeof (GetResponse), Resp, &RespLen);

      do_card_command (Select1001, sizeof (Select1001), Resp, &RespLen);
      do_card_command (Update, sizeof (Update), Resp, &RespLen);
      do_card_command (GetBigChallenge, sizeof (GetBigChallenge), Resp, &RespLen);
  }

  dad = 1;
  sad = 2;
  if ((Iret = CT_data(1,&dad,&sad,5,Eject,&lr,Brsp)) == OK ) {
    printf("Successful Eject \n");
  } else {
    printf("Error on Eject -> %d\n", Iret);
  }


  CT_close(1);
 
}
