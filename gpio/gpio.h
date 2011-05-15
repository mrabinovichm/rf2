#ifndef GPIO_H
#define GPIO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {

		char status;
		char direction;
		char value;
		char power;
		char edge;
		char uevent;
}status_gpio;

int config_gpio_pin(status_gpio *status, const char *dir, char *pinN);
int read_gpio_pin(status_gpio *status, char *pinN);
int set_gpio_pin(status_gpio *status, char *pinN);
int clear_gpio_pin(status_gpio *status, char *pinN);

#endif /*GPIO_H*/
