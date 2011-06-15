#ifndef _MENSAJES_H_
#define _MENSAJES_H_

/* ****************************** Mensajes para el display *********************************************** */
unsigned char prueba[] 	= "Esto funciona sin problemas, P3R";
unsigned char inicio[] 	= "Prototipo de carga/consulta RF²";
unsigned char tarjeta[] = "Aproxime su tarjeta.";
unsigned char quieto[] 	= "Por favor, no retire su tarjeta.";
unsigned char err[]		= "Error, vuelva a intentarlo.";
unsigned char esperar[] = "Espere un momento por favor.";
unsigned char saldoV[] 	= "Su saldo en viajes es de"; //acá hay que hacer una concatenación de Strings para poner cuántos viajes
unsigned char saldoP[] 	= "Su saldo en pesos es de"; //acá hay que hacer una concatenación de Strings para poner cuántos pesos
unsigned char fin[] 	= "Transacción finalizada.";

#endif /*_MENSAJES_H_*/
