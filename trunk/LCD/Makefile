include ../Variables_Make

all: display
	echo Listo!

display: main.c ../gpio/gpio.o lcd16x2.o
	$(COMP) main.c ../gpio/gpio.o lcd16x2.o -o $@
	
../gpio/gpio.o: ../gpio/gpio.c ../gpio/gpio.h ../gpio/beagle_gpio.h
	$(MAKE) -C ../gpio gpio.o
	
lcd16x2.o: lcd16x2.c lcd16x2.h ../gpio/gpio.o
	$(COMP) -c lcd16x2.c
	
clean:
	rm -f *.o display
