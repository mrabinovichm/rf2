#include "sam.h"
#include "../utiles/tipo_datos.h"

void *handle = 0;
char *error;
BYTE p1;
BYTE data_rh[8];
BYTE cl_der7[16];
BYTE kscenc[16];
BYTE cmd_Send[256];
BYTE answer_sam[256];
BYTE answer_sam_ini[256];
BYTE claves_A[16*6];		//16 claves A de 6 bytes cada una.
BYTE claves_B[16*6];		//16 claves B de 6 bytes cada una.
LONG cod_resp;
DWORD cmd_SendLength,  answer_samLength;
DWORD dwActiveProtocol;
DWORD dwReaders;


LONG claves_mifare(BYTE * id_mifare, BYTE tipo_clave, BYTE * respuesta_sam){

    BYTE p2;
    BYTE le;
    BYTE respuesta[256];
    BYTE dato_plano[256];
    int i = 0;

    for(i=0; i < 256;i++) {
        answer_sam_ini[i] = 0x00;               
    }

    derive_claves(answer_sam_ini, claves_A, claves_B);

    //if (p1 == TESTING ) {
        //p2 = 0x00;
        //le = 0xE9;
        //answer_samLength = 235;
    //} else if (p1 == RECARGA) {
        //p2 = 0x01;
        //le = 0xF0;
        //answer_samLength = 242;
    //} else if (p1 == ATE_USU) {
        //p2 = 0x01;
        //le = 0xF0;
        //answer_samLength = 242;
    //}

    //generar_comando_apdu(GET_M1K_KEYS, tipo_clave, p2, 0x07, id_mifare, le, cmd_Send); 
    //cmd_SendLength = 13;
    //cod_resp = SCardTransmitPt(hCard, SCARD_PCI_T1, cmd_Send, cmd_SendLength, &pioRecvPci, answer_sam, &answer_samLength);

    //memcpy(respuesta,answer_sam,(answer_samLength-2));
    //memcpy(respuesta_sam,answer_sam+(answer_samLength-2),2);

    //if (p2 == RETORNO_SEGURO) {
        //decrypt_stm(respuesta, kscenc, dato_plano, (answer_samLength-2));  
    //} else {
        //memcpy(dato_plano,answer_sam,(answer_samLength-2));
    //}

    derive_claves(dato_plano, claves_A, claves_B);
 
    //printHexaArray(claves_A, 16*6);
    
    return cod_resp;

}

void clave_sector(BYTE sector, BYTE tipo_clave, BYTE * resp_clave){
    if (tipo_clave == TIPO_A ){
        memcpy(resp_clave, claves_A + sector*6,6);
    } else if (tipo_clave == TIPO_B) {
        memcpy(resp_clave, claves_B + sector*6,6);
    }	
}
