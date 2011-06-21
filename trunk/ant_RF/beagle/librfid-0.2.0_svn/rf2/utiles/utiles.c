#include <stdio.h>
#include "utiles.h"

int pot(int base, int exp)
{
	int i, pot;
	
	if (exp == 0) return 1;
	
	pot = base;
	
	for(i = 1; i < exp; i++)
		pot *= base;
	
	return pot;
}


void int_hexa(int entero, BYTE *hexadecimal)
{
	int numero, potencia;
	int aux[8];
	int i, j;
	BYTE hexa[2];
	
	hexa[0] = 0x00;
	hexa[1] = 0x00;
		
	for (j = 0; j < 2; j++) { 
		
		if (j == 1) entero = entero >> 4;
			
		potencia = 0;
		numero = entero;

		
		for (i = 0; i < 4; i++) {
			numero = numero >> i;
			aux[i] = numero & 0x01;
			potencia += aux[i] * pot(2,i);
			numero = entero;
		}
		
		switch (potencia) {
			
			case 0 : hexa[j] = 0x00; 
					 break;
			case 1 : hexa[j] = 0x01; 
					 break;
			case 2 : hexa[j] = 0x02; 
					 break;
			case 3 : hexa[j] = 0x03; 
					 break;
			case 4 : hexa[j] = 0x04; 
					 break;
			case 5 : hexa[j] = 0x05; 
					 break;
			case 6 : hexa[j] = 0x06; 
					 break;
			case 7 : hexa[j] = 0x07; 
					 break;
			case 8 : hexa[j] = 0x08; 
					 break;
			case 9 : hexa[j] = 0x09; 
					 break;
			case 10: hexa[j] = 0x0A; 
					 break;
			case 11: hexa[j] = 0x0B; 
					 break;
			case 12: hexa[j] = 0x0C; 
					 break;
			case 13: hexa[j] = 0x0D; 
					 break;
			case 14: hexa[j] = 0x0E; 
					 break;
			case 15: hexa[j] = 0x0F; 
					 break;
		}
	}
	
	hexadecimal[0] = hexa[0] | (hexa[1] << 4);
}

int arrToInt(char * buf, int largo_buf)
{
	int i, numero;
	numero = 0;
	
	for(i=0; i<largo_buf; i++) 
		numero += ((int)buf[i] - (int)'0') * pot(10, largo_buf -1 -i);
	
	printf("arrayToInt devuelve %d\n", numero);
	return numero;
}

void IntToBytePair(int entero, BYTE *hex)
{
	int_hexa(entero, hex);
	if (entero < 256) {
		hex[1] = 0x00;
		
	}
	else {
		entero = entero >> 8;
		int_hexa(entero, hex+1);
	}
}

int concat_str_int(unsigned char *final, unsigned char *dato, int largo_dato, int entero)
{
	char str[4];
	int largo, largo_entero;
	
	largo_entero = 1;
	
    if (entero > 999) largo_entero = 4;
    else if (entero > 99)  largo_entero = 3;
    else if (entero > 9)  largo_entero = 2;
    
    strcpy(final, dato);
    sprintf(str, "%d", entero);
    strcat(final, str);
    
    largo = largo_dato + largo_entero;
    
    return largo; 
}

int leer_linea (int nro_lin, char *path)
{
        FILE *fp;
 
		int i = 1, r, j = 0, largo;
		char buf[] = "";
		
        fp = fopen( path, "r" );
 
		while (i < nro_lin)
		{
			if (fgetc(fp) == '\n')
				i++;
		}
		
		buf[0] = fgetc(fp);
		
		while (buf[j] != '\n')
		{
			j++;
			buf[j] = fgetc(fp);
		}
		
		buf[j] = '\0'; /* para sacar el \n */
		largo = j;
		r = arrToInt(buf, largo);
		fclose(fp);
 
        return r;
}


int escribir_linea (int nro_lin, char a, char *path)
{
        FILE *fp;
		int i = 1;
		
        fp = fopen( path, "r+" );
 
		while (i < nro_lin)
		{
			if (fgetc(fp) == '\n')
				i++;
		}
		
		fputc(a, fp);
		fputc('\n', fp);
		
        fclose(fp);
 
        return 0;
}
