/*************************************************************************
	Test antenna RF 13.56MHz   IC RC632

************************************************************************/
#class auto
#use "io_config.lib"
#use "rc632.lib"
#use "utils.lib"


void main()
{
   byte send[2], recive[2];
   word t;

   init_IO_config();
   //init_Interrupt();
   SPIinit();
   init_uP_interface();

   send[0] = 0x86;     //10000110 Leer el Registro PrimaryStatus
   send[1] = 0x00;     //flag de fin de escritura SPI

   while(1)
   {
   	BitWrPortI(PEDR, &PEDRShadow, 0, 1);	//select RC632
  	   SPIWrite(send, 2);
  	   SPIRead(recive, 1);
    	BitWrPortI(PEDR, &PEDRShadow, 1, 1);	//not select RC632
      printHexa(recive, 1);
   }
}