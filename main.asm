; =========================
; * Target: ATtiny85
; * By: Cassiopeia Lyra Ara Nizinkiewicz (itchydog)
; * 
; * Project for a visor, sending data to a WS2812b matrix/strip using bitbanging.
; * This project requires ATTiny85 to have PLL clock enabled, otherwise the timings
; * for the signals will be *off*
; * Fuse bytes for PLL clock include: 0xD1, 0xF1, 0xC1 and 0xE1
; * All of those fuse bytes also disable the internal clock division
; * Signal generation is defined in signals.asm
; * Delay functions and such are defined in util.asm
; * Faces/Animations are defined in faces.asm
; *
; * abababab BURN THE WORLD, BRING THEM DOWN AND MAKE THEM WATCH ~ ara


.include "./tn85def.inc"

; We should also take other vectors into account ~ Lyra
.org 0x0000
	rjmp reset

.include "signals.asm"
.include "util.asm"
.include "faces.asm"

reset:
	ldi r16, (1 << PB0)  ; set PB0 as output
	out DDRB, r16
	rjmp loop

loop:
	cpi r20, 1
	; this is so that we don't send the ws2812b signal forever -w-
	breq loop
	rcall ws2812b_loop
	rcall ws2812b_latch
	ldi r20, 1
	rjmp loop

; =====================================
; =     TESTING SIGNALS TO LEDS       =
; =====================================
; MAKE the thing blue ^^
; subroutine for sending 64*24 bits of data to WS2812B LED strip/matrix
; registers used:
; r16 (being used by ws2812b latch signal loop)
; r17 used by the same loop
; r18 used for outer 64 loop
; r19 used for internal 24 loop
ws2812b_loop:
	ldi r19, 0	; reset the 24 bit loop counter to 0 to start iteration over (if we're not finished with the outer loop)
loop_24_bits:
	inc r19
	cpi r19, 23		; we want to send ones only for last two bits of Blue 
	brlo send_low   ; we send zeroes if we're under 23 iterations
	brsh send_high  ; and we send ones if we're over 23 iterations
send_low:
	rcall ws2812b_zero_signal 
	rjmp after_send
send_high:
	rcall ws2812b_one_signal
after_send:
	cpi r19, 24		
	brne loop_24_bits	; continue sending bits until we sent all 24 bits (GRB) 
	inc r18
	cpi r18, 64			; loop until we're finished sending data to 64 LEDs
	brlo ws2812b_loop
	ret
