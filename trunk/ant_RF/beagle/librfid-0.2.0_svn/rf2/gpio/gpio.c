//      gpio.c
//      
//      Copyright 2011 proyecto RF²
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
/*
 * NAME:
 *      gpio.c -- Copyright (C) 2011
 *
 * DESCRIPTION:
 *      This provides utilitis for GPIO
 * 
 * AUTHOR:
 *		Edgardo Vaz, Melina Rabinovich & Daniel Aicardi
 */


#include "gpio.h"

FILE *fp;

int config_gpio_pin(status_gpio *status, const char *dir, const char *pinN)
{
	char gpio_path[50];
	char len_dir = strlen(dir);
	char len_pinN = strlen(pinN);

	strcpy(gpio_path, "/sys/class/gpio/gpio");
	strcat(gpio_path, pinN); 
	strcat(gpio_path, "/direction");
	
	if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
		return -1;
	rewind(fp);	/*Set pointer to begining of the file*/
	fwrite(pinN, sizeof(char), len_pinN, fp); /*Write number pin to the file*/
	fclose(fp);	
	status->export = 'y';
	
	if ((fp = fopen(gpio_path, "rb+")) == NULL) /*file in binary for reading and writing*/
		return -1;
	rewind(fp);	/*Set pointer to begining of the file*/
	fwrite(dir, sizeof(char), len_dir, fp); /*Write "out" or "in" to the file*/
	fclose(fp);

	status->direction = *dir;
	return 0;		
}
	
int read_gpio_pin(status_gpio *status, const char *pinN)
{
	char gpio_value;
	char gpio_path[30];
	strcpy(gpio_path, "/sys/class/gpio/gpio");
	strcat(gpio_path, pinN); 
	strcat(gpio_path, "/value");
		
	if ((fp = fopen(gpio_path, "rb")) == NULL) /*file in binary for reading only*/
		return -1;
		
	rewind(fp);	/*Set pointer to begining of the file*/
	fread(&gpio_value, sizeof(char), 1, fp); /*Value read of the file*/
	fclose(fp);
	
	status->value = gpio_value;
	return 0;	
}
	
int set_gpio_pin(status_gpio *status, const char *pinN)
{
	char gpio_path[30];
	
	if(status->direction == 'i') {printf("Error: GPIO input can't be set\n"); return -1;}
	strcpy(gpio_path, "/sys/class/gpio/gpio");
	strcat(gpio_path, pinN); 
	strcat(gpio_path, "/value");
		
	if ((fp = fopen(gpio_path, "rb+")) == NULL) /*file in binary for reading and writing*/
		return -1;
		
	rewind(fp);	/*Set pointer to begining of the file*/
	fwrite("1", sizeof(char), 1, fp); /*Write "1" to the file*/
	fclose(fp);
	
	status->value = '1';
	return 0;
}
	
int clear_gpio_pin(status_gpio *status, const char *pinN)
{
	char gpio_path[30];
	
	if(status->direction == 'i') {printf("Error: GPIO input can't be cleaned\n"); return -1;}
	strcpy(gpio_path, "/sys/class/gpio/gpio");
	strcat(gpio_path, pinN); 
	strcat(gpio_path, "/value");
		
	if ((fp = fopen(gpio_path, "rb+")) == NULL) /*file in binary for reading and writing*/
		return -1;
		
	rewind(fp);	/*Set pointer to begining of the file*/
	fwrite("0", sizeof(char), 1, fp); /*Write "0" to the file*/
	fclose(fp);	
	
	status->value = '0';
	return 0;
}	
