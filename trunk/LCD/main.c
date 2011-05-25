//#include "gpio.h"
#include "lcd16x2.h"


int main(void){

	unsigned char es[] = "Esto funciona sin problemas, P3R";	/* esto se escribe al display */
	
	init_gpio();												/* inicialización de GPIO en beagleboard */
	init_lcd();													/* inicialización del display 16x2 */
	
	write_lcd(CLEAR, CTRL_WR);							 		/* por si el display ya tuviera algo escrito */
	delay(2);
	
	dato_lcd(es, 32);
	delay(150000);												/* espera para poder leer el display */
	
	apagar();													/* borra y apaga el display */
	
	return 0;		/* para evitar el warning */
}
