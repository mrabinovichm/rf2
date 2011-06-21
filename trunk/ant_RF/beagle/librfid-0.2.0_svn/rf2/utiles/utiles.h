#ifndef _INT_HEX_H_
#define _INT_HEX_H_

#include "tipo_datos.h"


int pot(int base, int exp);

void int_hexa(int entero, BYTE *hexadecimal);

int arrToInt(char * buf, int largo_buf);

void IntToBytePair(int entero, BYTE *hex);

int concat_str_int(unsigned char *final, unsigned char *dato, int largo_dato, int entero);

int leer_linea (int nro_lin, char *path);

int escribir_linea (int nro_lin, char a, char *path);

#endif /*_INTHEX_H_*/
