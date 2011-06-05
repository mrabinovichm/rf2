include ../utiles/Variables_Make


all: sam.o


sam.o: sam.c sam.h sam_util.o
	$(CC_arm) -c sam.c

sam_util.o: sam_util.c sam_util.h
	$(CC_arm) -c sam_util.c

install:

clean:
	rm -f *.o

distclean: clean
