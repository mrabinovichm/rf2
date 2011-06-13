#include "sam.h"
#include "sammy.h"
#include <string.h>

BYTE answer_sam_ini[256];
BYTE claves_A[16*6];		//16 claves A de 6 bytes cada una.
BYTE claves_B[16*6];		//16 claves B de 6 bytes cada una.
LONG cod_resp;


LONG claves_mifare(BYTE * id_mifare, BYTE * claves_A, BYTE * claves_B){

    BYTE p2;
    BYTE le;
    BYTE respuesta[256];
    BYTE dato_plano[256];
    
    BYTE uid_0[] = {0xfc, 0x21, 0x4b, 0x48, 0xde, 0x88, 0x04};
    BYTE uid_1[] = {0x7c, 0x95, 0x2e, 0x48, 0x8f, 0x88, 0x04};
    BYTE uid_2[] = {0x1c, 0x67, 0x29, 0x48, 0x1a, 0x88, 0x04};
    BYTE uid_3[] = {0x2c, 0xe6, 0x6b, 0x4a, 0xeb, 0x88, 0x04};
    
    int i = 0;

    for(i=0; i < 256; i++) {
        answer_sam_ini[i] = 0x00;
    }
    
    derive_claves(answer_sam_ini, claves_A, claves_B);

	if (id_mifare[0] == uid_0[0]) derive_claves(uid_fc214b48, claves_A, claves_B);
	else if (id_mifare[0] == uid_1[0]) derive_claves(uid_7c952e48, claves_A, claves_B);
	else if (id_mifare[0] == uid_2[0]) derive_claves(uid_1c672948, claves_A, claves_B);
	else if (id_mifare[0] == uid_3[0]) derive_claves(uid_2ce66b4a, claves_A, claves_B);
	
        
    return cod_resp;
}

void clave_sector(BYTE sector, BYTE tipo_clave, BYTE *resp_clave){
    if (tipo_clave == TIPO_A ){
        memcpy(resp_clave, claves_A + sector*6,6);
    } else if (tipo_clave == TIPO_B) {
        memcpy(resp_clave, claves_B + sector*6,6);
    }	
}
