#ifndef _RFIDTOOL_H
#define _RFIDTOOL_H

#define _GNU_SOURCE
#include <getopt.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/*####################################################################*/

#define SECTOR_MONEDERO 	6			/*sector donde se encuentra el monedero*/
#define MONEDERO 			3			/*lugar del arreglo "bloque" donde se encuentra el monedero*/
#define BLOQUE_MONEDERO 	0			/*bloque donde se encuentra el monedero*/
#define BLOQUE_RESPALDO 	1			/*bloque donde se encuentra el respaldo del saldo*/
#define BLOQUES_POR_SECTOR 	4			
#define LARGO_BLOQUE 		16			
#define LARGO_CLAVE 		6
#define LARGO_UID_SAM 		7			/*largo de uid usado*/
#define TIEMPO_BUZZER		350000		/*tiempo de encendido del buzzer en us*/
#define PAUSA_BUZZER		100000		/*tiempo entre dos encendidas del buzzer en us*/
#define TIEMPO_LED			1			/*tiempo de encendido del led en s*/
#define TIPO_A 				0			/*clave tipo A*/
#define TIPO_B 				1			/*clave tipo B*/

#include "../rf2/utiles/tipo_datos.h"

/*####################################################################*/


extern const char *
hexdump(const void *data, unsigned int len);

extern int
hexread(unsigned char *result, const unsigned char *in, unsigned int len);

extern struct rfid_reader_handle *rh;
extern struct rfid_layer2_handle *l2h;
extern struct rfid_protocol_handle *ph;

extern int reader_init(void);
extern int l2_init(int layer2);
extern int l3_init(int protocol);

#define LIBRFID_TOOL_VERSION	"0.1"

struct rfidtool_module {
	struct rfidtool_module *next;
	char *name;
	char *version;
	const struct option *extra_opts;

	unsigned int option_offset;
};

/*####################################################################*/

// nombre:		autenticar
// descripción:	autentica con la tarjeta mifare
// @clave:		puntero a la clave correspondiente al sector al que refiere page
// @page:		número de bloque si comenzamos a contar desde el principio de la memoria
// @tipo_clave:	indica el tipo de clave que le pasamos; 0: si el tipo de clave es A, 1: si el tipo de clave es B
// @return		0: todo funcionó correctamente, < 0: error
static int autenticar(BYTE *clave, int page, int tipo_clave);


// nombre: 		escribir_tarjeta
// descripción:	escribe un bloque de la tarjeta
// @sector:		sector donde se encuentra el bloque a escribir
// @bloque:		bloque a escribir
// @buf:		buffer con el contenido a escribir
// @len:		largo de buf
// @clave_B: 	clave B del sector necesaria para escribir un bloque del sector 
// @return		0: todo funcionó correctamente, -1: error de autenticación, -2: error en la escritura
int escribir_tarjeta(int sector, int bloque , BYTE *buf, int len, BYTE *clave_B);

// nombre: 		leer_tarjeta
// descripción:	lee un bloque de la tarjeta
// @sector:		sector donde se encuentra el bloque a leer
// @bloque:		bloque a leer
// @buf:		buffer donde se guarda lo leido
// @len:		largo de buf
// @clave_A: 	clave B del sector necesaria para escribir un bloque del sector 
// @return		0: todo funcionó correctamente, -1: error de autenticación, -2: error en la escritura
int leer_tarjeta(int sector, int bloque, BYTE *buf, int len, BYTE *clave_A);

// nombre: 		lectura_completa
// descripción:	lee todos los bloques de la tarjeta
// @claves_A: 	arreglo donde se guardan todas las claves A de la tarjeta en la forma de dato plano 
// @return		0: todo funcionó correctamente, -1: error de autenticación, -2: error en la escritura
int lectura_completa(BYTE *claves_A);

// nombre: 		resetear_saldo
// descripción:	deja el saldo en 0 (solo utilizado para pruebas)
// @claves_B: 	arreglo donde se guardan todas las claves B de la tarjeta en la forma de dato plano 
// @return		0: todo funcionó correctamente, < 0: error
int resetear_saldo(BYTE *claves_B);

// nombre: 		consulta_recarga
// descripción:	pregunta si la tarjeta tiene saldo a recargar o no (en estos momentos está implementada para pruebas)
// @uid: 		identificador de la tarjeta
// @return		saldo a recargar
int consulta_recarga(BYTE *uid);

// nombre: 		reseteo_recarga
// descripción:	(solo para pruebas). escribe ceros en el archivo de recarga
// @uid: 		identificador de la tarjeta
// @return		0
int reseteo_recarga(BYTE *uid);

// nombre: 		recarga
// descripción:	recarga la tarjeta, realizando primero un respaldo del monedero y se interactua con el usuario
// @claves_A: 	arreglo donde se guardan todas las claves A de la tarjeta en la forma de dato plano
// @claves_B: 	arreglo donde se guardan todas las claves B de la tarjeta en la forma de dato plano
// @a_recargar: saldo a recargar
// @return		0: todo bien, -1: error
int recarga(BYTE *claves_A, BYTE *claves_B, int a_recargar);

// nombre: 		consulta
// descripción:	lee la tarjeta, obtiene el saldo actual y se interactua con el usuario
// @claves_A: 	arreglo donde se guardan todas las claves A de la tarjeta en la forma de dato plano
// @return		0: todo bien, -1: error
int consulta(BYTE *claves_A);

// nombre: 		obtener_uid
// descripción:	obtiene el uid de la tarjeta siempre y cuando esta sea de las de prueba
// @uid: 		identificador de la tarjeta
// @len:		largo del uid
// @return		0: todo bien, < 0: error
int obtener_uid(BYTE *uid, int len);

// nombre: 		busqueda
// descripción:	hace una única busqueda de tarjeta en el campo y realiza un reinicio del campo según first
// @first: 		0: busca tarjeta, 1: reinicia el campo y busca tarjeta
// @return		3: todo bien, 2: error en protocolo, 0: error en capa 2
static int busqueda(int first);

// nombre: 		busqueda_tarjeta
// descripción:	realiza busqueda de tarjeta en el campo y finaliza solo cuando se encuentra una
static void busqueda_tarjeta(void);

// nombre: 		lb_error
// descripción:	manejo de leds y buzzer para los casos de error
void lb_error(void);

// nombre: 		lb_consulta
// descripción:	manejo de leds y buzzer para el caso de consulta
void lb_consulta(void);

// nombre: 		lb_recarga
// descripción:	manejo de leds y buzzer para el caso de recarga
void lb_recarga(void);

// nombre: 		inicio_rf2
// descripción:	inicialización de los distintos módulos del sistema
// @return		0
int inicio_rf2(void);

// nombre: 		principal
// descripción:	programa principal del proyecto RF², accedido mediante el uso del comando "librfid-tool -n"
// @first: 		0: busca tarjeta, 1: reinicia el campo y busca tarjeta
// @return		3: todo bien, 2: error en protocolo, 0: error en capa 
int principal(void);

/*####################################################################*/

#endif /* _RFIDTOOL_H */
