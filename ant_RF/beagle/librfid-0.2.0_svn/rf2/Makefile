include utiles/Variables_Make


all: gpio/gpio.o rf/rc632_utils.o lcd/lcd16x2.o sam/sam.o utiles/utiles.o


gpio/gpio.o:
	$(MAKE) -C gpio

rf/rc632_utils.o:
	$(MAKE) -C rf

lcd/lcd16x2.o:
	$(MAKE) -C lcd

sam/sam.o:
	$(MAKE) -C sam
	
utiles/utiles.o:
	$(MAKE) -C utiles

install:

clean:
	rm -f *.o
	$(MAKE) -C gpio clean
	$(MAKE) -C rf clean
	$(MAKE) -C lcd clean
	$(MAKE) -C sam clean
	$(MAKE) -C utiles clean

distclean: clean
