#include "gpio.h"

int main(void){

	config_gpio_pin(OUT, "144");
	config_gpio_pin(OUT, "168");

	read_gpio_pin("144");
	read_gpio_pin("168");

	while(1)
	{
		set_gpio_pin("144");
		clear_gpio_pin("168");
		sleep(1);
		set_gpio_pin("168");
		clear_gpio_pin("144");
		sleep(1);
	}
	return 0;
}
