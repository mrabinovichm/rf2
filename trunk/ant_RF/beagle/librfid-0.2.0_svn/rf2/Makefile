include utiles/Variables_Make


all: gpio/gpio.o rf/rc632_utils.o


gpio/gpio.o:
	$(MAKE) -C gpio

rf/rc632_utils.o:
	$(MAKE) -C rf

install:

clean:
	rm -f *.o
	$(MAKE) -C gpio clean
	$(MAKE) -C rf clean

distclean: clean
