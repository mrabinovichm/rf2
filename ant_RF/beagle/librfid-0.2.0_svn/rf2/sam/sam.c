//      rc632_utils.c
//      
//      Copyright 2011 proyecto RF²
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
/*
 * NAME:
 *      sam.c -- Copyright (C) 2011
 *
 * DESCRIPTION:
 *      This provides utilitis to communicate with SAM through rf2_sc reader
 * 
 * AUTHOR:
 *		Daniel Aicardi, Edgardo Vaz & Melina Rabinovich
 */

#include "sam.h"
#include "sammy.h"
#include <string.h>


LONG claves_mifare(BYTE * id_mifare, BYTE * claves_A, BYTE * claves_B){

    BYTE p2;
    BYTE le;
    BYTE respuesta[256];
    BYTE dato_plano[256];
    BYTE answer_sam_ini[256];
    
    BYTE uid_0[] = {0xfc, 0x21, 0x4b, 0x48, 0xde, 0x88, 0x04};
    BYTE uid_1[] = {0x7c, 0x95, 0x2e, 0x48, 0x8f, 0x88, 0x04};
    BYTE uid_2[] = {0x1c, 0x67, 0x29, 0x48, 0x1a, 0x88, 0x04};
    BYTE uid_3[] = {0x2c, 0xe6, 0x6b, 0x4a, 0xeb, 0x88, 0x04};
    BYTE uid_4[] = {0x56, 0x05, 0x35, 0xFA, 0x9C, 0x88, 0x04};
    
    int i = 0;

    for(i=0; i < 256; i++) {
        answer_sam_ini[i] = 0x00;
    }
    
    derive_claves(answer_sam_ini, claves_A, claves_B);

	if (id_mifare[0] == uid_0[0]) derive_claves(uid_fc214b48, claves_A, claves_B);
	else if (id_mifare[0] == uid_1[0]) derive_claves(uid_7c952e48, claves_A, claves_B);
	else if (id_mifare[0] == uid_2[0]) derive_claves(uid_1c672948, claves_A, claves_B);
	else if (id_mifare[0] == uid_3[0]) derive_claves(uid_2ce66b4a, claves_A, claves_B);
	else if (id_mifare[0] == uid_4[0]) derive_claves(uid_fa350556, claves_A, claves_B);
	else return -1;
        
    return 0; /*cod_resp;*/
}
