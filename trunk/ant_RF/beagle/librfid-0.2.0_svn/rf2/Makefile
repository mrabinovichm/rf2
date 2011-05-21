CC = arm-angstrom-linux-gnueabi-gcc

all: rc632_utils.o gpio.o

rc632_utils.o: rc632_utils.h rc632_utils.c gpio.o
	$(CC) -c rc632_utils.c

gpio.o: gpio.c gpio.h beagle_gpio.h
	$(CC) -c gpio.c

install:

clean:
	rm -f *.o
