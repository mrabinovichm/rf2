#include "../gpio/beagle_gpio.h"
#include "../gpio/gpio.h"
#include "lcd16x2.h"

status_gpio status_D7;
status_gpio status_D6;
status_gpio status_D5;
status_gpio status_D4;
status_gpio status_RW;
status_gpio status_RS;
status_gpio status_BL;
status_gpio status_E;
status_gpio status_LV;
status_gpio status_LR;
status_gpio status_LA;


/* ******************************************************************************************************* */
/* ******************************** Inicialización de pines en beagleboard *********************************/
/* ******************************************************************************************************* */

void init_gpio_lcd(void)
{
	config_gpio_pin(&status_D7, OUT, PIN9);			/*D7*/
	config_gpio_pin(&status_D6, OUT, PIN16);		/*D6*/
	config_gpio_pin(&status_D5, OUT, PIN13);		/*D5*/
	config_gpio_pin(&status_D4, OUT, PIN18);		/*D4*/
	config_gpio_pin(&status_RW, OUT, PIN20);		/*RW*/
	config_gpio_pin(&status_RS, OUT, PIN22);		/*RS*/
	config_gpio_pin(&status_BL, OUT, PIN14);		/*BL*/
	config_gpio_pin(&status_E , OUT, PIN15);		/*E*/
		
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
	encender_bl();	

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
	encender_lcd();	
}
/* ******************************************************************************************************* */                                                                                                                    


/* ******************************************************************************************************* */     
/* ************ Envia los datos que se escribiran en el display y la longitud de los mismos ************** */
/* ******************************************************************************************************* */
 
void dato_lcd(unsigned char *dato, int len)
{
	short i;
	unsigned char blank = ' ';
	unsigned char zero = '0';
	
	write_lcd(CLEAR, CTRL_WR);							 		/* por si el display ya tuviera algo escrito */
	delay(2);
	
	if(len <= LCD_16)                                                  
  	{                                                                  
  		for(i=0; i<len; i++)                                           
  		{   
			if (dato[i] == blank)
			{
				write_lcd(0x10, DATO_WR);
			} else 
				if (dato[i] == zero)
				{
					write_lcd('O', DATO_WR);
				} else {
					write_lcd(dato[i], DATO_WR);                               
				}
				delay(1);  				    		/* esperar 100us */      	
  		}                                                              
  	}                                                                  
  	else                                                               
  	{                                                                  
  		for(i=0; i<LCD_16; i++)                                        
  		{   
			if (dato[i] == blank)
			{
				write_lcd(0x10, DATO_WR);
			} else 
				if (dato[i] == zero)
				{
					write_lcd('O', DATO_WR);
				} else {
					write_lcd(dato[i], DATO_WR);                               
				}
  			delay(1);  				    		/* esperar 100us */      
  		}                                                              
  		write_lcd(SDA_LIN, CTRL_WR);                                   
  		delay(1);  				    			/* esperar 100us */      
 		for(i=LCD_16; i<len; i++)                                      
  		{        
		if (dato[i] == blank)
			{
				write_lcd(0x10, DATO_WR);
			} else 
				if (dato[i] == zero)
				{
					write_lcd('O', DATO_WR);
				} else {
					write_lcd(dato[i], DATO_WR);                               
				}
 			delay(1);  				    		/* esperar 100us */      
  		}                                                              
	}
}
/* ******************************************************************************************************* */


/* ******************************************************************************************************* */     
/* **************************************** Borra el display ********************************************* */
/* ******************************************************************************************************* */
void apagar_lcd(void)
{
	write_lcd(CLEAR, CTRL_WR);
	write_lcd(DPLY_OFF, CTRL_WR);	    	
	apagar_bl();
}

/* ******************************************************************************************************* */     
/* ***************************************** Enciende el display ***************************************** */
/* ******************************************************************************************************* */
void encender_lcd(void)
{
	write_lcd(DPLY_ON, CTRL_WR);	    
	delay(1);  				    		
}

/* ******************************************************************************************************* */     
/* **************************************** Apaga el backlight ******************************************* */
/* ******************************************************************************************************* */
void apagar_bl(void)
{ 	
	clear_gpio_pin(&status_BL, PIN14);
}

/* ******************************************************************************************************* */     
/* ***************************************** Enciende el backlight *************************************** */
/* ******************************************************************************************************* */
void encender_bl(void)
{
	set_gpio_pin(&status_BL, PIN14);
}
