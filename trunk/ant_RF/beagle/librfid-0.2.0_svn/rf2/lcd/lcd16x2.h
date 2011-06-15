#ifndef LCD16x2_H
#define LCD16x2_H

#define LCD_16 16	   /*Long de una linea del Dply*/

/* ***************************** Lineas de control RS, R/W, E y Backlight ******************************** */
#define CTRL_WR 0x4200 /* x10xx01x BL=1(backlight on), RS=0, R/W=0, E=1 */
#define CTRL_RD 0x4600 /* x10xx11x BL=1(backlight on), RS=0, R/W=1, E=1 */
#define DATO_WR	0x6200 /* x11xx01x BL=1(backlight on), RS=1, R/W=0, E=1 */
#define DATO_RD	0x6600 /* x11xx11x BL=1(backlight on), RS=1, R/W=1, E=1 */

/* ********************************* Palabras de control del LCD16x2 ************************************* */
#define CLEAR	      0x01 /* 00000001 Borra Dply y vuelve cursor al inicio		   */
#define RET_HOME      0x02 /* 00000010 Contador de direcciones a cero			   */
#define ETY_MOD_SET	  0x06 /* 00000110 I/D=1 inc DDRAM, S=0 sin salto de Dply	   */
#define DPLY_ON		  0x0C /* 00001100 D=1 Dply on,  C=0 sin cursor, B=0 sin blink */
#define DPLY_OFF	  0x08 /* 00001000 D=0 Dply off, C=0 sin cursor, B=0 sin blink */
#define CSOR_SHFT  	  0x18 /* 00011000 */
#define FUN_SET		  0x28 /* 00111000 DL=0 4 bits, N=1 2_lineas, F=don't care	   */
#define SDA_LIN		  0xC0 /* 11000000 Posiciona el cursor en la 2da linea		   */

#define FSET		  0x30 /* 00110000 */
#define FSE		  	  0x20 /* 00100000 */

/* ****************************** Mensajes para el display *********************************************** */
static unsigned char prueba[] = "Esto funciona sin problemas, P3R";
static unsigned char inicio[] = "Prototipo de carga/consulta RF²";
static unsigned char tarjeta[] = "Aproxime su tarjeta.";
static unsigned char quieto[] = "Por favor, no retire su tarjeta.";
static unsigned char err[] = "Error, vuelva a intentarlo.";
static unsigned char esperar[] = "Espere un momento por favor.";
static unsigned char saldoV[] = "Su saldo en viajes es de"; //acá hay que hacer una concatenación de Strings para poner cuántos viajes
static unsigned char saldoP[] = "Su saldo en pesos es de"; //acá hay que hacer una concatenación de Strings para poner cuaátos pesos
static unsigned char fin[] = "Transacción finalizada.";

/* ******************************************************************************************************* */


/* Inicializa los GPIO en beagleboard */
void init_gpio(void);

/* Escribe un cartacter en la memoria del display */
void write_lcd(unsigned char simbolo, short ctrl_dat);

/* Produce un retardo proporcional a 100us */
void delay(int factor);

/* Inicializa el display LCD16x2 */
void init_lcd(void);

/* Envia los datos que se escribiran en el display */
void dato_lcd(unsigned char *dato, int len);

/* Borra el display y lo apaga */
void apagar_lcd(void);

/* Enciende el display */
void encender_lcd(void);

/* Apaga el backlight */
void apagar_bl(void);

/* Enciende el backlight */
void encender_bl(void);

#endif /*LCD16x2_H*/
