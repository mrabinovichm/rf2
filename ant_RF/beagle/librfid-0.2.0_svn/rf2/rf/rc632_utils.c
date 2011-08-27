//      rc632_utils.c
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
/*
 * NAME:
 *      rc632_utils.c -- Copyright (C) 2011
 *
 * DESCRIPTION:
 *      This provides utilitis to initialize CL-RC632 of rf2_RFID reader
 * 
 * AUTHOR:
 *		Daniel Aicardi, Edgardo Vaz & Melina Rabinovich
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../gpio/beagle_gpio.h"
#include "../gpio/gpio.h"
#include "rc632_utils.h"

status_gpio status_rst_RF;

/*La pata del reset en 1 impide el uso del rc632*/

int init_rc632(void)
{
	return config_gpio_pin(&status_rst_RF, OUT, PIN24);
}

int encender_rc632(void)
{
	return clear_gpio_pin(&status_rst_RF, PIN24);
}

int apagar_rc632(void)
{
	return set_gpio_pin(&status_rst_RF, PIN24);
}
