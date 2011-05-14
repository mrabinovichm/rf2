#ifndef GPIO_H
#define GPIO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define IN  "in"
#define OUT "out"

struct status_gpio{

		char status;
		char direction;
		char value;
		char power;
		char edge;
		char uevent;
};

int config_gpio_pin(char *dir, char *pinN);
int read_gpio_pin(char *pinN);
int set_gpio_pin(char *pinN);
int clear_gpio_pin(char *pinN);

#endif /*GPIO_H*/
