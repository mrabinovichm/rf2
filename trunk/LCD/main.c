#include "lcd16x2.h"
#include "mensajes.h"

int main(void){

	//unsigned char es[] = "Esto funciona sin problemas, P3R";	/* esto se escribe al display */
	
	init_gpio();												/* inicialización de GPIO en beagleboard */
	init_lcd();													/* inicialización del display 16x2 */
	
	//write_lcd(CLEAR, CTRL_WR);							 		/* por si el display ya tuviera algo escrito */
	//delay(2);											estas 2 lineas fueron para adentro de dato_lcd
	
	dato_lcd(prueba, sizeof(prueba)-1);
	delay(150000);												/* espera para poder leer el display */
	
	dato_lcd(inicio, sizeof(inicio)-1);
	delay(150000);					
	
	dato_lcd(tarjeta, sizeof(tarjeta)-1);
	delay(150000);					
	
	dato_lcd(quieto, sizeof(quieto)-1);
	delay(150000);					
	
	dato_lcd(err, sizeof(err)-1);
	delay(150000);					
	
	dato_lcd(esperar, sizeof(esperar)-1);
	delay(150000);					
	
	dato_lcd(saldoP, sizeof(saldoP)-1);
	delay(150000);					
	
	apagar_bl();
	apagar_lcd();													/* borra y apaga el display */
	
	return 0;		/* para evitar el warning */
}
