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
   byte send[1], receive[2], rec_len[1], status[1];
   auto word t;

/************************************************************************/
/*Inicializacion*/

   init_IO_config();    //inicializa los puertos
   SPIinit();           //inicializa los parametros del SPI
   idle_rc632();        //espera que el rc632 este ocioso
	page_disable();      //convierte el direccionamiento en lineal
   reset_FIFO_buffer(); //resetea el buffer fifo

/************************************************************************/
/*Configuracion para enviar comando REQ_A*/

/*Without crypto1*/
	rc632_clear_bit_mask(RC632_REG_CONTROL, RC632_CONTROL_CRYPTO1_ON);

/*Transfer only 7 bits of last byte in frame */
	rc632_reg_write(RC632_REG_BIT_FRAMING, 0x07);

/*No Tx CRC, Rx CRC*/
   rc632_reg_write(RC632_REG_CHANNEL_REDUNDANCY, 0x03);

   rc632_powerRF(ON);   //enciende RF
/*Luego de encender la RF se debe esperar más de 5ms antes de comenzar*/
/*la transmisión, AN10834 pag.4, 2.1_Polling for cards*/
   t = _SET_SHORT_TIMEOUT(10);        /*espera de 10ms*/
	while(!_CHK_SHORT_TIMEOUT(t));

   send[0]=ISO14443A_SF_CMD_REQA;
   status[0] = rc632_transceive(send, 1, receive, rec_len);
   printf("STATUS: ");
	printHexa(status, 1);
   printf("Respuesta de la tarjeta: ");
	printHexa(receive, 2);

   t = _SET_SHORT_TIMEOUT(5000);        /*espera de 5s*/
	while(!_CHK_SHORT_TIMEOUT(t));
   rc632_powerRF(OFF);
/************************************************************************/

}