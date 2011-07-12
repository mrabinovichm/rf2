#ifndef __RF2_SC_H__
#define __RF2_SC_H__

#include "../gpio/gpio.h"
#include "../gpio/beagle_gpio.h"

/*
 * Estructuras para mantener el estado de los pines
 */ 
status_gpio status_XOE;
status_gpio status_RST_SC;

/* nombre:		init_rf2_sc
 * descripción:	Inicializa los pines para el contro del lector de smart cards. 
 * @return		0: Ok, -1: error
 */ 
int init_rf2_sc(void);

/* nombre:		enable_clock
 * descripción:	Cambia el estado del pin XOE para habilitar el oscilador.
 * @return		0: Ok, -1: error
 */ 
int enable_clock(void);

/* nombre:		desable_clock
 * descripción:	Cambia el estado del pin XOE para deshabilitar el oscilador.
 * @return		0: Ok, -1: error
 */ 
int desable_clock(void);

/* nombre:		reset_high
 * descripción:	Pone a "1" el pin Reset de la smart card.
 * @return		0: Ok, -1: error
 */ 
int reset_high(void);

/* nombre:		reset_low
 * descripción:	Pone a "0" el pin Reset de la smart card.
 * @return		0: Ok, -1: error
 */ 
int reset_low(void);

/* nombre:		status_card
 * descripción:	Lee el pin XOE para saber si esta habilitado el oscilador.
 * 				Se hace lo anterior por no tener un pin extra y el zocalo
 * 				de la smart card no tiene switch para indicar presencia.
 * @return		0: Ok, -1: error
 */ 
int status_card(void);

#endif/*__RF2_SC_H__*/
