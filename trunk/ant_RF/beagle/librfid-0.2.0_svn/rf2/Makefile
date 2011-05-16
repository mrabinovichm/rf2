all: rc632_utils.o

rc632_utils.o: rc632_utils.h rc632_utils.c
	arm-angstrom-linux-gnueabi-gcc -c rc632_utils.c -o rc632_utils.o

install:

clean:
	rm -f rc632_utils.o
