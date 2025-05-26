.include "./tn85def.inc"

.org 0x0000
	rjmp reset

.include "signals.asm"
.include "util.asm"
.include "faces.asm"

reset:
	ldi r16, (1 << PB0)
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
	ldi r19, 0
loop_24_bits:
	inc r19
	cpi r19, 23 
	brlo send_low
	brsh send_high
send_low:
	rcall ws2812b_zero_signal 
	rjmp after_send
send_high:
	rcall ws2812b_one_signal
after_send:
	cpi r19, 24
	brne loop_24_bits 
	inc r18
	cpi r18, 64
	brlo ws2812b_loop
	ret
