all:
	avr-gcc -O2 -mmcu=attiny85 main.c && avr-objcopy -O ihex -j.text -j.data a.out out.hex && avrdude -c usbasp -p t85 -U flash:w:out.hex:i

