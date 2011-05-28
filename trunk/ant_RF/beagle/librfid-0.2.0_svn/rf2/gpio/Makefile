include ../utiles/Variables_Make


all: gpio.o


gpio.o: gpio.c gpio.h
	$(CC_arm) -c gpio.c

install:

clean:
	rm -f *.o

distclean: clean
