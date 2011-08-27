/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 * 
 * 
 * NAME:
 *      main.c -- Copyright (C) 2011
 *
 * DESCRIPTION:
 *      This provides utilitis for display LCD16x2
 * 
 * AUTHOR:
 *		Edgardo Vaz, Melina Rabinovich & Daniel Aicardi
 */

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
