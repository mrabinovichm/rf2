/*** Test para probar los leds, buzzer, y backlight sobre la Beagleboard ***/

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
 *      This provides utilitis for GPIO
 * 
 * AUTHOR:
 *		Edgardo Vaz, Melina Rabinovich & Daniel Aicardi
 */

#include "gpio.h"
#include "beagle_gpio.h"


int main(void){

	status_gpio status_pin_ledR;
	status_gpio status_pin_ledA;
	status_gpio status_pin_ledV;
	status_gpio status_pin_buzzer;
	status_gpio status_pin_bkl;
	status_gpio status_pin_rstSC;
	status_gpio status_pin_rstRF;

	reset_status_gpio(status_pin_ledR);
	reset_status_gpio(status_pin_ledA);
	reset_status_gpio(status_pin_ledV);
	reset_status_gpio(status_pin_buzzer);
	reset_status_gpio(status_pin_bkl);
	reset_status_gpio(status_pin_rstSC);
	reset_status_gpio(status_pin_rstRF);

	config_gpio_pin(&status_pin_ledR, OUT, PIN5);
	config_gpio_pin(&status_pin_ledA, OUT, PIN10);
	config_gpio_pin(&status_pin_ledV, OUT, PIN3);
	config_gpio_pin(&status_pin_buzzer, OUT, PIN12);
	config_gpio_pin(&status_pin_bkl, OUT, PIN14);

	printf("Export del pin %s: %c\n", PIN5, status_pin_ledR.export);
	printf("Export del pin %s: %c\n", PIN10, status_pin_ledA.export);
	printf("Export del pin %s: %c\n", PIN3, status_pin_ledV.export);
	printf("Export del pin %s: %c\n", PIN12, status_pin_buzzer.export);
	printf("Export del pin %s: %c\n", PIN14, status_pin_bkl.export);

	clear_gpio_pin(&status_pin_ledR, PIN5);
	clear_gpio_pin(&status_pin_ledA, PIN10);
	clear_gpio_pin(&status_pin_ledV, PIN3);
	clear_gpio_pin(&status_pin_buzzer, PIN12);
	clear_gpio_pin(&status_pin_bkl, PIN14);

	while(1)
	{
		set_gpio_pin(&status_pin_ledR, PIN5);
		sleep(1);
		set_gpio_pin(&status_pin_ledA, PIN10);
		sleep(1);
		set_gpio_pin(&status_pin_ledV, PIN3);
		sleep(1);
		set_gpio_pin(&status_pin_bkl, PIN14);
		sleep(1);	
		set_gpio_pin(&status_pin_buzzer, PIN12);
		usleep(200000);
		clear_gpio_pin(&status_pin_buzzer, PIN12);			
		clear_gpio_pin(&status_pin_ledR, PIN5);
		clear_gpio_pin(&status_pin_ledA, PIN10);
		clear_gpio_pin(&status_pin_ledV, PIN3);
		clear_gpio_pin(&status_pin_bkl, PIN14);
		sleep(1);		
	}
	return 0;
}
