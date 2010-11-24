/*************************************************************************
	Test antenna RF 13.56MHz   IC RC632

************************************************************************/
#class auto
#use "io_config.lib"
#use "rc632.lib"
#use "utils.lib"

void isr_RF();

void main()
{
	byte read_e2prom[2];
   byte aux[4], all_zero[1], all_one[1];
   byte cmd[2];
   byte data_e2prom[16], addr_buff[17];
   unsigned int i, status_spi;
   word t;

   for(i=0; i<16; i++)
   {
   	addr_buff[i]=0x84;
      data_e2prom[i]=0x01;
   }
   addr_buff[16]=0x00;
   status_spi = -1;

   init_IO_config();
   //init_Interrupt();
   SPIinit();

   BitWrPortI(PEDR, &PEDRShadow, 0, 1);	// chip select low
   BitWrPortI(PCDR, &PCDRShadow, 1, 4);	// not reset

   aux[0] = 0x04;     //00000100 escribir en el buffer FIFO
   aux[1] = 0x00;    //LSB
   aux[2] = 0x0F;    //MSB
   aux[3] = 0x10;    //Nº de bytes
   SPIWrite(aux, 4);

   read_e2prom[0]=0x02;
   read_e2prom[1]=RC632_CMD_READ_E2;
   SPIWrite(read_e2prom, 2);

   t = _SET_SHORT_TIMEOUT(20);
	while(!_CHK_SHORT_TIMEOUT(t));     //espera 20ms

//   cmd[0]=0x84;
//   status_spi = SPIWrite(cmd, 1);
//   printf("Valor devuelto por SPIWrite: %d\n", status_spi);

//	status_spi = SPIRead(data_e2prom, 16);
//   BitWrPortI(PEDR, &PEDRShadow, 1, 1);       // chip select high
//   printf("Valor devuelto por SPIRead: %d\n", status_spi);

   SPIWrRd(addr_buff, data_e2prom, 16);

   //printf("Valor del arreglo auxiliar:\n");
	//printHexa(aux, 4);

   printf("Valor de la posicion 0 de la E2PROM:\n");
	printHexa(data_e2prom, 16);

/*** Test para verificar que el pin MOSI oscila entre 0 y 1 ***/
   all_zero[0]=0x00;
   all_one[0]=0xFF;
   while(1)
   {
   	SPIWrite(all_zero, 1);
      t = _SET_SHORT_TIMEOUT(1000);
	   while(!_CHK_SHORT_TIMEOUT(t));
      SPIWrite(all_one, 1);
      t = _SET_SHORT_TIMEOUT(1000);
	   while(!_CHK_SHORT_TIMEOUT(t));
   }
/***************************************************************/   
}


nodebug root interrupt void isr_RF(void)
{
	printf("Llego una interrupcion en el pin PE0\n");
}