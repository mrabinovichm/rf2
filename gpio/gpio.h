#ifndef GPIO_H
#define GPIO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const char OUT[] = "out";
static const char IN[] = "in";

typedef struct {

		char export;
		char direction;
		char value;
		char power;
		char edge;
		char uevent;
}status_gpio;

#define reset_status_gpio(status) \
            status.export    = 'n'; \
            status.direction = '0'; \
            status.value     = '0'; \
            status.power   	 = '0'; \
            status.edge 	 = '0'; \
            status.uevent  	 = '0'; 

int config_gpio_pin(status_gpio *status, const char *dir, const char *pinN);
int read_gpio_pin(status_gpio *status, const char *pinN);
int set_gpio_pin(status_gpio *status, const char *pinN);
int clear_gpio_pin(status_gpio *status, const char *pinN);


#endif /*GPIO_H*/
