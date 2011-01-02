/*************************************************************************
	Test antenna RF 13.56MHz   IC RC632

************************************************************************/
#class auto
#use "io_config.lib"
#use "rc632.lib"
#use "utils.lib"
#use "rfid_asic_rc632.lib"

#define ON  1
#define OFF 0

void main()
{
   byte send[3], receive[60], buff[BUFF_SIZE], ret[1];
   static const byte clave_mifare[6]={0x4A, 0x1F, 0x24, 0xB4, 0x1C, 0x82};
   static const byte clave_mifare_inv[6]={0x82, 0x1C, 0xB4, 0x24, 0x1F, 0x4A};
   static const byte uid_mifare[4]={0xFA, 0x35, 0x05, 0x56};
   static const byte uid_mifare_inv[4]={0x56, 0x05, 0x35, 0xFA};

   init_IO_config();
   //init_Interrupt();
   SPIinit();
   idle_rc632();
	page_disable();
   reset_FIFO_buffer();

	buff[0]=0x11; buff[1]=0x12; buff[2]=0x13; buff[3]=0x14;
	buff[4]=0x15; buff[5]=0x16; buff[6]=0x17; buff[7]=0x18;
	buff[8]=0x19; buff[9]=0x1A; buff[10]=0x1B; buff[11]=0x1C;
	buff[12]=0x1D; buff[13]=0x1E; buff[14]=0x1F; buff[15]=0x20;

// datos en las direcciones 30 a 3F: 1112131415161718191A1B1C1D1E1F20

//   rc632_write_eeprom(buff, 0x30, 0x00, 16);
//	rc632_read_eeprom(receive, 0x30, 0x00, 16);
//	printHexa(receive, 16);

//	rc632_storage_key_buffer(clave);

   rc632_powerRF(ON);

//   idle_rc632();
   ret[0] = rc632_mifare_auth(0x60, 0x00, clave_mifare_inv, uid_mifare_inv);
//   ret[0] = rc632_mifare_auth(0x60, 0x00, clave_mifare, uid_mifare);
//	ret[0] = rc632_mifare_auth(0x60, 0x00, clave_mifare_inv, uid_mifare);
//   ret[0] = rc632_mifare_auth(0x60, 0x00, clave_mifare, uid_mifare_inv);
   printHexa(ret, 1);

   rc632_reg_read(RC632_REG_FIFO_LENGTH, ret);
   rc632_fifo_read(receive, ret[0]);
   printHexa(receive, ret[0]);

   rc632_powerRF(OFF);




   while(1)
   {
      rc632_reg_read(RC632_REG_FIFO_LENGTH, receive);
      printHexa(receive, 1);
   }
}