#ifndef _RFIDTOOL_H
#define _RFIDTOOL_H

#define _GNU_SOURCE
#include <getopt.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/*####################################################################*/

#define SECTOR_MONEDERO 	6
#define MONEDERO 			3
#define BLOQUE_MONEDERO 	0
#define BLOQUE_RESPALDO 	1
#define BLOQUES_POR_SECTOR 	4
#define LARGO_BLOQUE 		16
#define LARGO_CLAVE 		6
#define LARGO_UID_SAM 		7
#define TIEMPO_BUZZER		350000		/*tiempo de encendido del buzzer en us*/
#define PAUSA_BUZZER		100000		/*tiempo entre dos encendidas del buzzer en us*/
#define TIEMPO_LED			1			/*tiempo de encendido del led en s*/

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

static int autenticar(BYTE *clave, int page, int tipo_clave);

int escribir_tarjeta(int sector, int bloque , BYTE *buf, int len, BYTE *clave_B);

int leer_tarjeta(int sector, int bloque, BYTE *buf, int len, BYTE *clave_A);

int lectura_completa(BYTE *claves_A);

int resetear_saldo(BYTE *claves_B);

int consulta_recarga(BYTE *uid);

int reseteo_recarga(BYTE *uid);

int recarga(BYTE *claves_A, BYTE *claves_B, int a_recargar);

int consulta(BYTE *claves_A);

int obtener_uid(BYTE *uid, int len);

static int busqueda(int first);

static void busqueda_tarjeta();

void lb_error(void);

void lb_consulta(void);

void lb_recarga(void);

int inicio_rf2(void);

int principal(void);

/*####################################################################*/

#endif /* _RFIDTOOL_H */
