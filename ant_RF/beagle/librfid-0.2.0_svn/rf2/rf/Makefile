include ../utiles/Variables_Make


all: rc632_utils.o


rc632_utils.o: rc632_utils.c rc632_utils.h ../gpio/gpio.o ../gpio/gpio.h ../gpio/beagle_gpio.h
	$(CC_arm) -I$(rf2dir) -c rc632_utils.c

../gpio/gpio.o:
	$(MAKE) -C ../gpio gpio.o

install:

clean:
	rm -f *.o

distclean: clean
