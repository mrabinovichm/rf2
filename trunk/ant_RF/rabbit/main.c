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

   init_IO_config();
   //init_Interrupt();
   SPIinit();
   idle_rc632();
	page_disable();
   reset_FIFO_buffer();

	rc632_read_eeprom(receive, 60);
   printHexa(receive, 60);

   while(1)
   {
      rc632_reg_read(RC632_REG_FIFO_LENGTH, receive);
      printHexa(receive, 1);
   }
}