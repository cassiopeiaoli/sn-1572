all:
	avra main.asm

upload:
	avra main.asm && avrdude -c USBasp -p t85 -U flash:w:main.hex:i 
