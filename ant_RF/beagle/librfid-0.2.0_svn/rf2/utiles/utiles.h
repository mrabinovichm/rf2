#ifndef _INT_HEX_H_
#define _INT_HEX_H_

#include "tipo_datos.h"


int pot(int base, int exp);

void int_hexa(int entero, BYTE *hexadecimal);

void IntToBytePair(int entero, BYTE *hex);

int concat_str_int(unsigned char *final, unsigned char *dato, int largo_dato, int entero);


#endif /*_INTHEX_H_*/
