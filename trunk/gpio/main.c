/*** Test para probar los leds, buzzer, y backlight sobre la Beagleboard ***/

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
