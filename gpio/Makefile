include ../Variables_Make

OBJS = gpio.o
SRCS = gpio.c
HDRS = gpio.h


all: gpio
	echo Listo!

# The variable $@ has the value of the target. In this case $@ = psort
gpio.o: ${HDRS} ${SRCS}
	${COMP} -c ${SRCS} -o $@ -g

gpio: ${OBJS} main.c
	${COMP} -g ${OBJS} main.c -o $@

clean:
	rm -f *.o gpio
