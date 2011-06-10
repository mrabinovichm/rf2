#ifndef _SAM_H
#define _SAM_H
#define TIPO_A 0X00
#define TIPO_B 0X01

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utiles/tipo_datos.h"
#include "sam_util.h"


/**
 \brief Descifra las claves A y B para una tarjeta mifare concreta.
 \param id_mifare array de 4 bytes conteniendo el id de la mifare.
 \param tipo_clave Es un valor 0 o 1. Este valor indica el conjunto de claves que se desea usar.
  Este valor debe ser extraido de cada tarjeta mifare. Es el primer byte del primer bloque del primer sector.
 \param respuesta_sam (salida) array de 2 bytes donde se devuelve la respuesta de la ejecución del comando APDU.
 Si el comando fue exitoso retorna (0x90, 0x00). Por mas valores de error consultar el Manual de Usuario GD-SAM-STM-KeyDerivation
 seccion 5.7 GET_M1K_ACCESS_DERIVED_KEYS pag 22.
 \return código de error que retorna la función SCardTransmit de la biblioteca pcsclite que se usa para acceder a los servicios de la smart card.
 \todo En esta función se devuelve hacia afuera dos variables con códigos de error (respuesta_sam y valor de retorno).
 Debería existir una sola forma de retornar códigos de error. Una lista de códigos de error de la función SCardTransmit puede encontrarse
 <a href="http://msdn.microsoft.com/en-us/library/aa374738(VS.85).aspx#smart_card_return_values">aquí</a>
*/
LONG claves_mifare(BYTE * id_mifare, BYTE * claves_A, BYTE * claves_B);


/**
 \brief Devuelve la clave del tipo indicado (A o B) para el sector indicado (0 a 15).
 Previamente ha de haberse invocado \link #claves_mifare \endlink para generar las claves para la Mifare.
 \param sector número entre 0 y 15 que indica el sector del cual se desea la clave.
 \param tipo_clave número 0 o 1 que identifican a los tipos A o B respectivamente.
 \param resp_clave (salida) Array de 6 bytes conteniendo la clave del sector indicado del tipo indicado.
*/
void clave_sector(BYTE sector, BYTE tipo_clave, BYTE * resp_clave);


#endif
