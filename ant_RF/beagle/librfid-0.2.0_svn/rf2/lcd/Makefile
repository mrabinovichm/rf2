include ../utiles/Variables_Make


all: lcd16x2.o


lcd16x2.o: lcd16x2.c lcd16x2.h ../gpio/gpio.o ../gpio/gpio.h ../gpio/beagle_gpio.h
	$(CC_arm) -c lcd16x2.c

../gpio/gpio.o:
	$(MAKE) -C ../gpio gpio.o

install:

clean:
	rm -f *.o

distclean: clean
