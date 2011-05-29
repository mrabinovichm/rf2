###########################################################
# Makefile for RF2_SC
# Author: Edgardo Vaz, Melina Rabinovich, Daniel Aicardi
# License: See file LICENSE
# URL: https://sites.google.com/site/recargafacilrf2/home
##########################################################
CC      = arm-angstrom-linux-gnueabi-gcc
LD		= arm-angstrom-linux-gnueabi-ld
SRC_ARM = /usr/local/angstrom/arm/bin
CC_ARM  = ${SRC_ARM}/${CC}
LD_ARM  = ${SRC_ARM}/${LD}
OBJ     = ifdhandler.o ctapi.o serial.o ../gpio/gpio.o
INCLUDE = ./

all: lib test
	@echo Listo!!!

clean:
	rm -f test *.o *.lo *.so ../gpio/*.o

lib:  $(OBJ)
	$(LD_ARM) -G $(OBJ) -o rf2_sc.so

ifdhandler.o: ifdhandler.c ifdhandler.h
	$(CC_ARM) $(CFLAGS) -fPIC -c ifdhandler.c

ctapi.o: ctapi.c ctapi.h ctbcs.h pcscdefines.h
	$(CC_ARM) $(CFLAGS) -fPIC -c ctapi.c

serial.o: serial.c serial.h pcscdefines.h
	$(CC_ARM) $(CFLAGS) -fPIC -c serial.c

../gpio/gpio.o:
	$(MAKE) -C ../gpio gpio.o

test: test.c $(OBJ)
	$(CC_ARM) $(CFLAGS) -o test test.c $(OBJ)
