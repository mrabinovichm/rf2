/*************************************************************************
	Test antenna RF 13.56MHz   IC RC632

************************************************************************/
#class auto
#use "io_config.lib"
#use "rc632.lib"
#use "utils.lib"
#use "rfid_asic_rc632.lib"
#use "rfid_layer2_iso14443A.lib"

#define ON  1
#define OFF 0

void main()
{
	byte status, bcc, checksum, ac_sel_code_CL;
   byte atq[2], atq_len[1], CtUidBcc[5], CtUidBcc_len[1], sak[3], sak_len[1];
   short complete, level;
   auto word t;

/************************************************************************/
/*Inicializacion*/

   init_IO_config();    //inicializa los puertos
   SPIinit();           //inicializa los parametros del SPI
   idle_rc632();        //espera que el rc632 este ocioso
	page_disable();      //convierte el direccionamiento en lineal
   reset_FIFO_buffer(); //resetea el buffer fifo

/************************************************************************/

   rc632_powerRF(ON);   //enciende RF
/*Luego de encender la RF se debe esperar más de 5ms antes de comenzar*/
/*la transmisión, AN10834 pag.4, 2.1_Polling for cards*/
   t = _SET_SHORT_TIMEOUT(10);        /*espera de 10ms*/
	while(!_CHK_SHORT_TIMEOUT(t));

   status = iso14443a_request(ISO14443A_SF_CMD_REQA, atq, atq_len);
   printf("STATUS: %02X\n", status);
   printf("Respuesta de la tarjeta: ");
	printHexa(atq, atq_len[0]);
   if(status == 0x00 && atq[0] == 0x04)
   {
   	level = ISO14443A_LEVEL_CL1;
   	complete = 0;
   	while(!complete)
   	{
      	switch(level)
         {
         	case ISO14443A_LEVEL_CL1: ac_sel_code_CL = ISO14443A_AC_SEL_CODE_CL1; break;
            case ISO14443A_LEVEL_CL2: ac_sel_code_CL = ISO14443A_AC_SEL_CODE_CL2; break;
            case ISO14443A_LEVEL_CL3: ac_sel_code_CL = ISO14443A_AC_SEL_CODE_CL3; break;
            default: printf("Error Cascade Level\n");
         }
   		status = iso14443a_anticollition(ac_sel_code_CL, CtUidBcc, CtUidBcc_len, &checksum);
 printf("STATUS: %02X\n", status);
 printf("Respuesta de la tarjeta: ");
 printHexa(CtUidBcc, CtUidBcc_len[0]);
 printf("Checksum OK: %02X\n", checksum);
   		bcc = CtUidBcc[4];
   		if(bcc == checksum)
         {
				status = iso14443a_select(ac_sel_code_CL, CtUidBcc, sak, sak_len);
printf("STATUS: %02X\n", status);
printf("Respuesta de la tarjeta: ");
printHexa(sak, sak_len[0]);
   			if(CtUidBcc[0] != CT)
            	complete = 1;
     			else
         		level++;
         }
         else
         	printf("Error Checksum\n");
      }
   }

   t = _SET_SHORT_TIMEOUT(2000);        /*espera de 2s*/
	while(!_CHK_SHORT_TIMEOUT(t));
   rc632_powerRF(OFF);
/************************************************************************/
}