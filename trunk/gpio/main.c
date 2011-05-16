#include "gpio.h"
#include "beagle_gpio.h"

const char OUT[] = "out";
const char IN[] = "in";

int main(void){

	status_gpio status_pin4;
	status_gpio status_pin13;
	status_gpio status_pin24;

	reset_status_gpio(status_pin4);
	reset_status_gpio(status_pin13);
	reset_status_gpio(status_pin24);

	config_gpio_pin(&status_pin4, OUT, PIN4);
	config_gpio_pin(&status_pin13, IN, PIN13);
	config_gpio_pin(&status_pin24, OUT, PIN24);

	read_gpio_pin(&status_pin4, PIN4);
	read_gpio_pin(&status_pin4, PIN13);
	read_gpio_pin(&status_pin24, PIN24);
	
	printf("Dirección del pin %s: %c\n", PIN4, status_pin4.direction);
	printf("Dirección del pin %s: %c\n", PIN13, status_pin13.direction);
	printf("Dirección del pin %s: %c\n", PIN24, status_pin24.direction);

	set_gpio_pin(&status_pin13, PIN13);
	clear_gpio_pin(&status_pin13, PIN13);

	while(1)
	{
		set_gpio_pin(&status_pin4, PIN4);
		clear_gpio_pin(&status_pin24, PIN24);	
		sleep(1);
		set_gpio_pin(&status_pin24, PIN24);
		clear_gpio_pin(&status_pin4, PIN4);		
		sleep(1);
	}
	return 0;
}
