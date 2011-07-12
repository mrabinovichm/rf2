/*
 * NAME:
 *      rf2_sc.c -- Copyright (C) 2011
 *
 * DESCRIPTION:
 *      This provides utilitis for RF2_SC reader
 * 
 * AUTHOR:
 *		Edgardo Vaz, Melina Rabinovich & Daniel Aicardi
 * 		to work with RF2_SC reader, 05/29/2011
 *
 * LICENSE: See file LICENSE.
 *
 */

#include "rf2_sc.h"


int init_rf2_sc(void)
{
  config_gpio_pin(&status_RST_SC, OUT, PIN4);
  config_gpio_pin(&status_XOE, OUT, PIN7);
  clear_gpio_pin(&status_RST_SC, PIN4);
  clear_gpio_pin(&status_XOE, PIN7);
  
  return 0;	
}

int enable_clock(void)
{	
	return set_gpio_pin(&status_XOE, PIN7);
}

int desable_clock(void)
{
	return clear_gpio_pin(&status_XOE, PIN7);	
}

int reset_high(void)
{
	return set_gpio_pin(&status_RST_SC, PIN4);
}

int reset_low(void)
{
	return clear_gpio_pin(&status_RST_SC, PIN4);
}

int status_card(void)
{
	return read_gpio_pin(&status_XOE, PIN7);
}
