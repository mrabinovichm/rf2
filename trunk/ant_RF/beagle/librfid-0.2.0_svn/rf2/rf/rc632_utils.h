#ifndef __RC632_UTILS_H__
#define __RC632_UTILS_H__

// nombre:		init_rc632
// descripción:	configura la pata rst_RF para poder usar el lector-escritor
// @return		0: todo bien, -1: error
int init_rc632(void);

// nombre:		encender_rc632
// descripción:	cambia el estado de rst_RF para habilitar el uso del lector-escritor
// @return		0: todo bien, -1: error
int encender_rc632(void);

// nombre:		apagar_rc632
// descripción:	cambia el estado de rst_RF para deshabilitar el uso del lector-escritor
// @return		0: todo bien, -1: error
int apagar_rc632(void);

#endif/*__RC632_UTILS_H__*/
