/*************************************************************************
	Test antenna RF 13.56MHz   IC RC632

************************************************************************/
#class auto
#use "io_config.lib"
#use "utils.lib"
#use "rc632.lib"
#use "rfid_asic_rc632.lib"
#use "rfid_layer2_iso14443A.lib"
#use "rfid_iso14443A_mifare.lib"

#define ON  1
#define OFF 0

#define BLOCK_LEN 16

void main()
{
	byte err_flags, UID_MF_len, rec_buf_len;
   byte atq[2], UID_MF[10], sak[3], key_mifare[6], sndbuf[2], rec_buf[16];
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

	err_flags = iso14443a_activ_sequence(ISO14443A_SF_CMD_REQA, atq, UID_MF, &UID_MF_len, sak);
   printf("Error de Activacion: %02X\n", err_flags);
   printf("ATQ de la tarjeta: ");
	printHexa(atq, ATQ_SIZE);
	printf("UID de la tarjeta: ");
	printHexa(UID_MF, UID_MF_len);
   printf("SAK de la tarjeta: ");
	printHexa(sak, SAK_SIZE);

   /*clave del sector 0, tarjeta UID FA350556*/
   key_mifare[0] = 0x82;
   key_mifare[1] = 0x1C;
   key_mifare[2] = 0xB4;
   key_mifare[3] = 0x24;
   key_mifare[4] = 0x1F;
   key_mifare[5] = 0x4A;

   err_flags = iso14443a_authentication(0x60, 0x00, key_mifare, UID_MF);    /*autenticar sector 0*/
   printf("Error de AUTHEN: %02X\n", err_flags);

   err_flags = iso14443a_read(0x30, 0x01, rec_buf, &rec_buf_len);
   printf("Error de Read: %02X\n", err_flags);
   if(err_flags == OK)
   {
   	printf("Datos de la tarjeta:\n");
   	printHexa(rec_buf, BLOCK_LEN);
   }
   else
   {
   	printf("Ha ocurrido un error en la lectura!!!\n");
      printf("Cantidad de datos recibidos: %d\n", rec_buf_len);
   	printHexa(rec_buf, rec_buf_len);
   }

   t = _SET_SHORT_TIMEOUT(1000);        /*espera de 1s*/
	while(!_CHK_SHORT_TIMEOUT(t));
   rc632_powerRF(OFF);

/************************************************************************/
}