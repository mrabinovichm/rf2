#include "beagle_gpio.h"
#include "gpio.h"
#include "lcd16x2.h"

/*extern*/ status_gpio status_D7;
/*extern*/ status_gpio status_D6;
/*extern*/ status_gpio status_D5;
/*extern*/ status_gpio status_D4;
/*extern*/ status_gpio status_RW;
/*extern*/ status_gpio status_RS;
/*extern*/ status_gpio status_BL;
/*extern*/ status_gpio status_E;
/*extern*/ status_gpio status_LV;
/*extern*/ status_gpio status_LR;
/*extern*/ status_gpio status_LA;



/* ******************************************************************************************************* */
/* ******************************** Inicialización de pines en beagleboard *********************************/
/* ******************************************************************************************************* */

void init_gpio(void)
{
	config_gpio_pin(&status_D7, "out", PIN9);		/*D7*/
	config_gpio_pin(&status_D6, "out", PIN16);		/*D6*/
	config_gpio_pin(&status_D5, "out", PIN13);		/*D5*/
	config_gpio_pin(&status_D4, "out", PIN18);		/*D4*/
	config_gpio_pin(&status_RW, "out", PIN20);		/*RW*/
	config_gpio_pin(&status_RS, "out", PIN22);		/*RS*/
	config_gpio_pin(&status_BL, "out", PIN14);		/*BL*/
	config_gpio_pin(&status_E, "out", PIN15);		/*E*/
		
}
/* ******************************************************************************************************* */


/* ******************************************************************************************************* */
/* *********************** Escribe un cartacter en la memoria del display ******************************** */
/* ******************************************************************************************************* */

void write_lcd(unsigned char simbolo, short ctrl_dat)
{
	int i = 0;

	unsigned char aux = simbolo;
	
	set_gpio_pin(&status_E, PIN15); 	/* seteo E para luego poder ver la bajada */
	set_gpio_pin(&status_BL, PIN14);

	if ( (simbolo == FSE) | (simbolo == FSET) )
	{
		for (i = 0; i < 4; i++)
		{
			simbolo = simbolo << i;
			simbolo &= 0x80;
			if (simbolo)
			{
				switch (i)
				{
					case 0:		set_gpio_pin(&status_D7, PIN9);
								break;
					case 1:		set_gpio_pin(&status_D6, PIN16);
								break;
					case 2:		set_gpio_pin(&status_D5, PIN13);
								break;
					case 3:		set_gpio_pin(&status_D4, PIN18);
								break;
					case 4:		set_gpio_pin(&status_D7, PIN9);
								break;
					case 5:		set_gpio_pin(&status_D6, PIN16);
								break;
					case 6:		set_gpio_pin(&status_D5, PIN13);
								break;
					case 7:		set_gpio_pin(&status_D4, PIN18);
								break;
					default: 	break;
				}
			} else 
			{
				switch (i)
				{
					case 0:		clear_gpio_pin(&status_D7, PIN9);
								break;
					case 1:		clear_gpio_pin(&status_D6, PIN16);
								break;
					case 2:		clear_gpio_pin(&status_D5, PIN13);
								break;
					case 3:		clear_gpio_pin(&status_D4, PIN18);
								break;
					case 4:		clear_gpio_pin(&status_D7, PIN9);
								break;
					case 5:		clear_gpio_pin(&status_D6, PIN16);
								break;
					case 6:		clear_gpio_pin(&status_D5, PIN13);
								break;
					case 7:		clear_gpio_pin(&status_D4, PIN18);
								break;
					default: 	break;
				}			
			}
			
						
			if (i == 3)
			{
				clear_gpio_pin(&status_RS, PIN22);
				clear_gpio_pin(&status_RW, PIN20);
				
				clear_gpio_pin(&status_E, PIN15);
				set_gpio_pin(&status_E, PIN15);
			}
			
			simbolo = aux;
		}
	} else 
	{
			for (i = 0; i < 8; i++)
			{
				simbolo = simbolo << i;
				simbolo &= 0x80;
				if (simbolo)
				{
					switch (i)
					{
						case 0:		set_gpio_pin(&status_D7, PIN9);
									break;
						case 1:		set_gpio_pin(&status_D6, PIN16);
									break;
						case 2:		set_gpio_pin(&status_D5, PIN13);
									break;
						case 3:		set_gpio_pin(&status_D4, PIN18);
									break;
						case 4:		set_gpio_pin(&status_D7, PIN9);
									break;
						case 5:		set_gpio_pin(&status_D6, PIN16);
									break;
						case 6:		set_gpio_pin(&status_D5, PIN13);
									break;
						case 7:		set_gpio_pin(&status_D4, PIN18);
									break;
						default: 	break;
					}
			} else 
			{
				switch (i)
				{
					case 0:		clear_gpio_pin(&status_D7, PIN9);
								break;
					case 1:		clear_gpio_pin(&status_D6, PIN16);
								break;
					case 2:		clear_gpio_pin(&status_D5, PIN13);
								break;
					case 3:		clear_gpio_pin(&status_D4, PIN18);
								break;
					case 4:		clear_gpio_pin(&status_D7, PIN9);
								break;
					case 5:		clear_gpio_pin(&status_D6, PIN16);
								break;
					case 6:		clear_gpio_pin(&status_D5, PIN13);
								break;
					case 7:		clear_gpio_pin(&status_D4, PIN18);
								break;
					default: 	break;
				}
			}
		
			switch (ctrl_dat)
			{
				case CTRL_WR:	clear_gpio_pin(&status_RS, PIN22);
								clear_gpio_pin(&status_RW, PIN20);
								break;
				case CTRL_RD:	clear_gpio_pin(&status_RS, PIN22);
								set_gpio_pin(&status_RW, PIN20);
								break; 
				case DATO_WR: 	set_gpio_pin(&status_RS, PIN22);
								clear_gpio_pin(&status_RW, PIN20);
								break; 
				case DATO_RD:	set_gpio_pin(&status_RS, PIN22);
								set_gpio_pin(&status_RW, PIN20);
								break; 
				default:		break;
			}
				
		
			if ((i == 3) | (i == 7)){
				clear_gpio_pin(&status_E, PIN15);
				set_gpio_pin(&status_E, PIN15);
			}
				
			simbolo = aux;
		}
	}
}
/* ******************************************************************************************************* */
                                                                         
																		 
/* ******************************************************************************************************* */
/* **************************** Produce un retardo proporcional a 100us ********************************** */
/* ******************************************************************************************************* */

void delay(int factor)
{
	usleep(factor*100);
}
/* ******************************************************************************************************* */


/* ******************************************************************************************************* */
/* ********************** Inicializa el display LCD16x2, pag.46 HD44780U.pdf ***************************** */
/* ******************************************************************************************************* */

void init_lcd(void)
{
	delay(150);  						/* esperar 15ms */
	write_lcd(FSET, CTRL_WR);			/* comando Function set */
	delay(50);  						/* esperar 5ms */
	write_lcd(FSET, CTRL_WR);			/* comando Function set */
	delay(1);  				    		/* esperar 100us */
	write_lcd(FSET, CTRL_WR);			/* comando Function set */
	delay(1);  				    		/* esperar 100us */
	write_lcd(FSE, CTRL_WR);			/* comando Function set */
	delay(1);  				    		/* esperar 100us */
	write_lcd(FUN_SET, CTRL_WR);			/* comando Function set */
	delay(1);  				    		/* esperar 100us */
	write_lcd(DPLY_OFF, CTRL_WR);	    	/* comando Dply off */
	delay(1);  				    		/* esperar 100us */
	write_lcd(CLEAR, CTRL_WR);	    		/* comando Clear Dply */
	delay(1);  				    	/* esperar 10ms */
	write_lcd(ETY_MOD_SET, CTRL_WR);	    /* comando Entry mode set */
	delay(1);							/* esperar 100us */
	write_lcd(DPLY_ON, CTRL_WR);	    	/* comando Dply on */
	delay(1);  				    		/* esperar 100us */
}
/* ******************************************************************************************************* */                                                                                                                    


/* ******************************************************************************************************* */     
/* ************ Envia los datos que se escribiran en el display y la longitud de los mismos ************** */
/* ******************************************************************************************************* */
 
void dato_lcd(unsigned char *dato, int len)
{
	short i;

	if(len <= LCD_16)                                                  
  	{                                                                  
  		for(i=0; i<len; i++)                                           
  		{                                                              
  			write_lcd(dato[i], DATO_WR);                               
  			delay(1);  				    		/* esperar 100us */      
  		}                                                              
  	}                                                                  
  	else                                                               
  	{                                                                  
  		for(i=0; i<LCD_16; i++)                                        
  		{                                                              
 			write_lcd(dato[i], DATO_WR);                               
  			delay(1);  				    		/* esperar 100us */      
  		}                                                              
  		write_lcd(SDA_LIN, CTRL_WR);                                   
  		delay(1);  				    			/* esperar 100us */      
 		for(i=LCD_16; i<len; i++)                                      
  		{                                                              
 			write_lcd(dato[i], DATO_WR);                               
 			delay(1);  				    		/* esperar 100us */      
  		}                                                              
	}
}
/* ******************************************************************************************************* */

void ppal(void)
{	unsigned char es[] = "sinESPACIOSandaBIENtbCON2LINEAS";
	write_lcd(CLEAR, CTRL_WR);
	delay(2);
	dato_lcd(es, 31);
	delay(1500);
	
	/* prueba de leds: verde 3, rojo 5, amarillo 10 */
	config_gpio_pin(&status_LV, "out", PIN3);
	config_gpio_pin(&status_LR, "out", PIN5);
	config_gpio_pin(&status_LA, "out", PIN10);
		
	set_gpio_pin(&status_LV, PIN3);
	sleep(3);
	clear_gpio_pin(&status_LV, PIN3);
	set_gpio_pin(&status_LR, PIN5);
	sleep(3);
	clear_gpio_pin(&status_LR, PIN5);
	set_gpio_pin(&status_LA, PIN10);
	sleep(3);
	clear_gpio_pin(&status_LA, PIN10);
	
	set_gpio_pin(&status_LV, PIN3);
	set_gpio_pin(&status_LR, PIN5);
	set_gpio_pin(&status_LA, PIN10);
	sleep(3);
	clear_gpio_pin(&status_LV, PIN3);
	clear_gpio_pin(&status_LR, PIN5);
	clear_gpio_pin(&status_LA, PIN10);
	sleep(3);
	set_gpio_pin(&status_LV, PIN3);
	set_gpio_pin(&status_LR, PIN5);
	set_gpio_pin(&status_LA, PIN10);
	sleep(3);
	clear_gpio_pin(&status_LV, PIN3);
	clear_gpio_pin(&status_LR, PIN5);
	clear_gpio_pin(&status_LA, PIN10);
	delay(1000);
	/* fin de la prueba de leds */
	
	write_lcd(CLEAR, CTRL_WR);
	
	write_lcd(DPLY_OFF, CTRL_WR);	    	
	clear_gpio_pin(&status_BL, PIN14);
}
