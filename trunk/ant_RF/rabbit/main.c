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
   byte send[3], receive[3], buff[BUFF_SIZE];
   buff[0] = 0x00;
   buff[1] = 0x0F;
   buff[2] = 0x10;


   init_IO_config();
   //init_Interrupt();
   SPIinit();
   idle_rc632();
	page_disable();
   reset_FIFO_buffer();

   rc632_fifo_write(buff, 3);
//   send[0]=RC632_CMD_READ_E2;
//   spi_send(send, 1);
   rc632_fifo_read(receive, 3);
   printHexa(receive, 3);

   while(1)
   {
      send[0] = RC632_REG_FIFO_LENGTH;
		spi_receive(send, receive, 1);
      printHexa(receive, 1);
   }
}