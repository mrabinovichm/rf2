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

#include "../gpio/gpio.h"
#include "../gpio/beagle_gpio.h"

void print_bytes (const BYTE* bytes, int len)
{
	int i;
	for (i=0; i<len; i++) {
		printf("%02x ", bytes[i]);
	}
	
	printf("\n");
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
  status_gpio status_pin_rstSC;
  status_gpio status_pin_XOE;
  
  /*Inicializa los gpio para usar XOE y RST_SC*/
  config_gpio_pin(&status_pin_rstSC, OUT, PIN4);
  config_gpio_pin(&status_pin_XOE, OUT, PIN7);
  clear_gpio_pin(&status_pin_rstSC, PIN4);
  clear_gpio_pin(&status_pin_XOE, PIN7);
  
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
 
  dad = 1;
  sad = 2;
  if ((Iret = CT_data(1,&dad,&sad,5,Eject,&lr,Brsp)) == OK ) {
    printf("Successful Eject \n");
  } else {
    printf("Error on Eject -> %d\n", Iret);
  }


  CT_close(1);
 
}
