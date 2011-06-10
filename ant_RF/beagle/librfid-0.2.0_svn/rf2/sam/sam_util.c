#include <string.h>
#include "sam_util.h"


/** Transforma dos bytes a un entero. */
#define bytePairToInt(a, b) a * 0xFF + b

/** Obtiene el indice del primer elemento de cada clave. */
#define get_claves_index(k,b) ((k)*6+(b))
/** Define en que arreglo (A o B) y el lugar del mismo donde se guardara la clave. */
#define get_claves_vector(tipo_clave, fila) ((tipo_clave) + get_claves_index((fila),0))


void derive_claves(BYTE * answer_sam, BYTE * A, BYTE * B)
{
	BYTE * data_i;
    int i;

    int key_count = (int)answer_sam[0];                               // cantidad de claves A y B.

    for (i=0; i<key_count; i++) {
		data_i = answer_sam + 1 + i * 7;                          // byte que indica tipo de clave y numero de sector
        if (data_i[0] & 0x10) {                                    // si bit3 es "1" --> clave B, sino clave A  
			memcpy( get_claves_vector(B, data_i[0] & 0x0F) , data_i + 1, 6);  //copia la clave B del sector en el arreglo de claves B.
        }
        else {
			memcpy( get_claves_vector(A, data_i[0] & 0x0F) , data_i + 1, 6);  //copia la clave A del sector en el arreglo de claves A.
		}
	}
}
