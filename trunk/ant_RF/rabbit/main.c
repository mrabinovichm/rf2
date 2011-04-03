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
	byte status, bcc, checksum, ac_sel_code_CL, UID_MF_len;
   byte atq[2], atq_len[1], UID_MF[10], sak[3], sak_len[1];
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

	status = iso14443a_activ_secuence(ISO14443A_SF_CMD_REQA, atq, UID_MF, &UID_MF_len, sak);
   printf("STATUS: %02X\n", status);
   printf("ATQ de la tarjeta: ");
	printHexa(atq, ATQ_SIZE);
	printf("UID de la tarjeta: ");
	printHexa(UID_MF, UID_MF_len);
   printf("SAK de la tarjeta: ");
	printHexa(sak, SAK_SIZE);

   t = _SET_SHORT_TIMEOUT(2000);        /*espera de 2s*/
	while(!_CHK_SHORT_TIMEOUT(t));
   rc632_powerRF(OFF);
/************************************************************************/
}