/****************************************************************
						  
   main.c:  CT-API test program.
            Tests the functions of the CT-API for 
	        the RF2 smartcard reader.

	    Authors: Edgardo Vaz, Melina Rabinovich, Danien Aicardi
	    Based on code by James Rose & David Corcoran

	    Date:    06/06/2011
	    License: See LICENSE

****************************************************************/

#include <stdio.h>
#include "ctapi.h"
#include "defines.h"
#include "pcscdefines.h"

#include "apdu_STM.h"
#include "rf2_sc.h"

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

	len = len - 1; /*Longitud de datos esperada no es enviada a la tarjeta*/
	*rlen = *(cmd + len) + 2; /*Adiciono 2 para SW1 y SW2*/

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

  BYTE Brsp[255];
  BYTE Act[5] = {0x20,0x12,0x00,0x00,0x00};
  BYTE Rst[5] = {0x20,0x11,0x00,0x00,0x00};
  BYTE Eject[5] = {0x20,0x15,0x00,0x00,0x00};
  BYTE GetStatus[] = {0x20,0x13,0x00,0x00,0x00};
  int i;
  int Iret;
  
  /*Inicializa los gpio para usar XOE y RST_SC*/
  init_rf2_sc();
  
  CT_init(1,PORT_COM2);
  
  if ((Iret = CT_data(1,&dad,&sad,5,Act,&lr,Brsp)) == OK ) {
    printf("Successful Initialize \n");
  } else {
    printf("Error on Initialization -> %d\n", Iret);
  }

  dad = 1;	 /*Destination Reader*/
  sad = 2;	 /*Source Host*/
  lr = 10;
  if (CT_data (1, &dad, &sad, 5, GetStatus, &lr, Brsp) != OK) {
	  printf ("Error on card status\n");
  }
  if (!Brsp[0]) 
	  printf ("Card not inserted.\n\n");
  else
	  printf ("Card inserted.\n\n");


  dad = 1;   /*Destination Reader*/
  sad = 2;   /*Source Host*/
  lr = MAX_ATR_SIZE;
  if ((Iret = CT_data(1,&dad,&sad,5,Rst,&lr,Brsp)) == OK ) {
    printf("Successful Reset/Set Mode \n");
  } else {
    printf("Error on Reset -> %d\n", Iret);
  }

  printf("ATR Response Size: %02x \n", lr);
  print_bytes (Brsp, lr);
  printf("\n");
  
  printf("Command: SELECT\n");
  do_card_command (SELECT, sizeof (SELECT), Brsp, &lr);
  
  printf("Command: GET_SAM_ID\n");
  do_card_command (GET_SAM_ID, sizeof (GET_SAM_ID), Brsp, &lr);
  
  printf("Command: GET_ROLE_RIGHTS\n");
  do_card_command (GET_ROLE_RIGHTS, sizeof (GET_ROLE_RIGHTS), Brsp, &lr);
 
  dad = 1;	 /*Destination Reader*/
  sad = 2;	 /*Source Host*/
  if ((Iret = CT_data(1,&dad,&sad,5,Eject,&lr,Brsp)) == OK ) {
    printf("Successful Eject \n");
  } else {
    printf("Error on Eject -> %d\n", Iret);
  }


  CT_close(1);
 
}
