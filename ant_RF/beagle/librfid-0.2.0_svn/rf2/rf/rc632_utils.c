/*funciones utiles para comunicacion con RC632*/

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
