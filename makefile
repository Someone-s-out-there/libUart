

all: lib demo


lib: libUart.c libUart.h
	avr-gcc libUart.c -c -mmcu=atmega328p
	avr-ar -r libUart.a libUart.o
	ranlib libUart.a

demo: main.c lib
	avr-gcc main.c -L . -lUart -mmcu=atmega328p -O1 -o out.elf

.PHONY: clean
clean:
	rm *.o libUart.a out.elf