#ifndef _INT_HEX_H_
#define _INT_HEX_H_

#include "tipo_datos.h"


// nombre:		pot
// descripción:	calcula la potencia de un número (base) elevado al exponente (exp)
// @base:		puntero a la clave correspondiente al sector al que refiere page
// @exp:		número de bloque si comenzamos a contar desde el principio de la memoria
// @return		resultado de la potencia
int pot(int base, int exp);

// nombre:		int_hexa
// descripción:	convierte un entero a hexadecimal
// @entero:		entero a convertir
// @hexadecimal:puntero a un arreglo donde se guarda el resultado de la conversión
void int_hexa(int entero, BYTE *hexadecimal);

// nombre:		arrToInt
// descripción:	convierte un arreglo de caracteres a entero
// @buf:		puntero a arreglo de caracteres
// @largo_buf:	largo de buf
// @return		entero convertido
int arrToInt(char * buf, int largo_buf);

// nombre:		intToBytePair
// descripción:	convierte un entero a dos bytes
// @entero:		entero a convertir		
// @hex:		puntero donde se guarda el resultado
void IntToBytePair(int entero, BYTE *hex);

// nombre:		concat_str_int
// descripción:	concatena un entero a un string dado y devuelva un nuevo string
// @final:		string donde se guarda el string resultante de la concatenación
// @dato:		string original
// @largo_dato:	largo string original
// @entero:		número a agregar al final de dato
// @return		retorna el largo del string resultante de la concatenación
int concat_str_int(unsigned char *final, unsigned char *dato, int largo_dato, int entero);

// nombre:		leer_linea
// descripción:	lee una linea de un fichero y convierte el resultado a entero
// @nro_lin:	número de linea a leer
// @path:		dirección completa donde se encuentra el fichero (incluido el nombre del archivo)
// @return		conversión de lo leido a entero
int leer_linea (int nro_lin, char *path);

int escribir_linea (int nro_lin, char *path);

#endif /*_INTHEX_H_*/
