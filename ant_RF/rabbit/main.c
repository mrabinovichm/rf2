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
   byte send[2], receive[2];

   init_IO_config();
   //init_Interrupt();
   SPIinit();
   idle_rc632();
	page_disable();
   reset_FIFO_buffer();


   while(1)
   {
      send[0] = RC632_REG_FIFO_LENGTH;
		spi_receive(send, receive, 2);
      printHexa(receive, 2);
   }
}