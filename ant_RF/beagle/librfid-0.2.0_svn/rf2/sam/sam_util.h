#ifndef SAM_UTIL_H
#define SAM_UTIL_H

#include "../utiles/tipo_datos.h"

/**
 \brief Separa las claves A y B que le llegan en un arreglo, en dos arreglos independientes.
 
 La función recibe un arreglo con la siguiente estructura:
 \verbatim
 N, i, xxxxxx, i, xxxxxx, i, xxxxxx, .....
 
 donde los bits de i son: 000tnnnn \endverbatim
 El primer byte del arreglo (\a N) indica la cantidad de claves que contiene el array. A continuación siguen \a N tupolas de 7 bytes.
 El primer byte de cada tupla indica de que sector es la clave y de que tipo (A o B). La forma de interpretarlo es por nibbles (4 bits).
 El nibble más significativos consta de 3 ceros y un bit \a t que indica el tipo de clave del que se trata (0=A, 1=B).
 El nibble menos significativo \a nnnn indica el sector al que corresponde. No es necesario que el array contenga todas las claves ni que
 estén en un orden particular siempre que se respete la sintaxis planteada.
 Por último, los 6 siguientes bytes de la tupla de 7 contienen la clave propiamente dicha identificada por el byte i.\n
 La función además recibe dos buffers de 96 (16 * 6) bytes donde se alojarán de forma contigua las claves que se extraigan del array original,
 de manera que el primer byte de la cláve i-ésima podrá accederse mediante \c A[i*6] (en el caso de las claves A). Así, las claves que
 no aparezcan en el array original dejarán el espacio vacío correspondiente en el buffer de salida.
 \param answer_sam array conteniendo la respuesta del SAM al comando DERIVE_CRIPTO_KEYS
 \param A buffer de 96 bytes donde se alojarán las claves de tipo A extraidas
 \param B buffer de 96 bytes donde se alojarán las claves de tipo B extraidas
*/
void derive_claves(BYTE *answer_sam, BYTE *A, BYTE *B);

#endif /*SAM_UTIL_H*/
