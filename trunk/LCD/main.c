#include "gpio.h"
#include "lcd16x2.h"

int main(void){

	init_gpio();	/* inicialización de GPIO en beagleboard */
	init_lcd();		/* inicialización del display 16x2 */
	ppal();			/* programa prueba de display y leds */
}
