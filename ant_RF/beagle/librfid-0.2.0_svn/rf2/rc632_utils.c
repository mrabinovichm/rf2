/*funciones utiles para comunicacion con RC632*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rc632_utils.h"



/*La pata del reset en 1 impide el uso del rc632*/
int reset_rc632(int turn)
{
	FILE *fd_rst;
	
	/*create a variable to store whether we are sending a '1' or a '0'*/
	char set_value[4]; 
	
	/*Using sysfs we need to write "168" to /sys/class/gpio/export
	This will create the folder /sys/class/gpio/gpio168*/
	if ((fd_rst = fopen("/sys/class/gpio/export", "ab")) == NULL)
	{
		printf("Cannot open export file.\n");
		return -1;
	}
	/*Set pointer to begining of the file*/
	rewind(fd_rst);
	/*Write our value of "168" to the file*/
	strcpy(set_value,"168");
	fwrite(&set_value, sizeof(char), 3, fd_rst);
	fclose(fd_rst);
	
	/*SET DIRECTION*/
	/*Open the LED's sysfs file in binary for reading and writing, store file pointer in fp*/
	if ((fd_rst = fopen("/sys/class/gpio/gpio168/direction", "rb+")) == NULL)
	{
		printf("Cannot open direction file.\n");
		return -1;
	}
	/*Set pointer to begining of the file*/
	rewind(fd_rst);
	/*Write our value of "out" to the file*/
	strcpy(set_value,"out");
	fwrite(&set_value, sizeof(char), 3, fd_rst);
	fclose(fd_rst);
		
	/*SET VALUE*/
	/*Open the LED's sysfs file in binary for reading and writing, store file pointer in fp*/
	if ((fd_rst = fopen("/sys/class/gpio/gpio168/value", "rb+")) == NULL)
	{
		printf("Cannot open value file.\n");
		return -1;
	}
	/*Set pointer to begining of the file*/
	rewind(fd_rst);
	
	/*Write our value of "valor" to the file*/
	if (turn)
		strcpy(set_value, "1");
	else
		strcpy(set_value, "0");

	fwrite(&set_value, sizeof(char), 1, fd_rst);
	fclose(fd_rst);
				
	return 0;
}

int encender_rc632(void){

	return reset_rc632(0);
}

int apagar_rc632(void) {
	
	return reset_rc632(1);
}
