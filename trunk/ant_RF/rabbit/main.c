/*************************************************************************
	Test antenna RF 13.56MHz   IC RC632

************************************************************************/
#class auto
#use "io_config.lib"
#use "rc632.lib"
#use "utils.lib"
#use "rfid_asic_rc632.lib"


void main()
{
   byte send[3], receive[60], buff[BUFF_SIZE];
   byte clave[6]={0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5};

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

   rc632_write_eeprom(buff, 0x30, 0x00, 16);
	rc632_read_eeprom(receive, 0x30, 0x00, 16);
	printHexa(receive, 16);

	rc632_storage_key_buffer(clave);

   while(1)
   {
      rc632_reg_read(RC632_REG_FIFO_LENGTH, receive);
      printHexa(receive, 1);
   }
}