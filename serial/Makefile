include ../Variables_Make

OBJS = serialcomm.o
SRCS = serialcomm.c
HDRS = serialcomm.h


all: serial
	@echo Listo!!!

# The variable $@ has the value of the target. In this case $@ = psort
serialcomm.o: ${HDRS} ${SRCS}
	${COMP} -c ${SRCS} -o $@

serial: ${OBJS} main.c
	${COMP} -o $@ main.c ${OBJS}

clean:
	rm -f *.o serial
