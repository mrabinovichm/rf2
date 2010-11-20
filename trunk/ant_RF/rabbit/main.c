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
   byte aux[4];
   byte cmd[2];
   byte data_e2prom[16];
   unsigned int i;
   word t;

   for(i=0; i<16; i++)
   {
   	data_e2prom[i]=0x01;
   }

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

   cmd[0]=0x84;
   SPIWrite(cmd, 1);

	SPIRead(data_e2prom, 16);

   printf("Valor del arreglo auxiliar:\n");
	printHexa(aux, 4);

   printf("Valor de la posicion 0 de la E2PROM:\n");
	printHexa(data_e2prom, 16);

   while(1);
}


nodebug root interrupt void isr_RF(void)
{
	printf("Llego una interrupcion en el pin PE0\n");
}