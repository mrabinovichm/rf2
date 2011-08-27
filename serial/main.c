/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 * 
 * 
 * NAME:
 *      main.c -- Copyright (C) 2011
 *
 * DESCRIPTION:
 *      This provides utilitis for serial port
 * 
 * AUTHOR:
 *		Edgardo Vaz, Melina Rabinovich & Daniel Aicardi
 */

#include "serialcomm.h"

void printHexa(unsigned char *data, int length)
{
   int i;
   for (i=0; i<length; i++) {
       printf("%02X", data[i]);
   }
   printf("\n");
}


int main(void){

	int fd, wr, rd, cerrar;
	//unsigned char wstr[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5};
	unsigned char wstr[] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
	unsigned char* rstr;
	int baud = 115200;
	int len = 12;
	int tout = 100;	

	fd = serialport_init(DEVICE, baud);
	if (fd==-1)
	{
		printf("no se pudo abrir el puerto %s\n",DEVICE);
		return -1;
	}
	printf("se pudo abrir el puerto %s correctamente\n",DEVICE);

	wr = serialport_write_len(fd, wstr, len);
	if (wr == -1)
	{
		printf("no se pudo escribir\n");
		return -1;
	}
	printf("Bytes transmitidos: ");
	printHexa(wstr, len);

	//se leen "len" caracteres
	rstr = (unsigned char*) malloc(len);
	rd = serialport_read(fd, rstr, len, tout);
	switch(rd)
	{
    		case -1:   {printf("error al leer\n"); return -1; break;}
        	case -2:   {printf("timeout\n"); return -1; break;}
    	}
	printf("Bytes recibidos:    ");	
	printHexa(rstr, len);

	free(rstr);
	//se cierra el puerto
	cerrar = serialport_close(fd);
	if(cerrar == 0)
	{
		printf("se cierra el puerto %s correctamente\n", DEVICE);	
	}
	return 0;
}
