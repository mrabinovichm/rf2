CC = arm-angstrom-linux-gnueabi-gcc
CFLAGS = -Wall
SRC = /usr/local/angstrom/arm/bin/
COMP = ${SRC}/${CC} ${CFLAGS}

OBJS = gpio.o
SRCS = gpio.c
HDRS = gpio.h


all: gpio
	echo Listo!

# The variable $@ has the value of the target. In this case $@ = psort
gpio.o: ${HDRS} ${SRCS}
	${COMP} -c ${SRCS} -o $@

gpio: ${OBJS} main.c
	${COMP} -o $@ main.c ${OBJS}

clean:
	rm -f *.o gpio
