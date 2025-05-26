; by Cassiopeia Lyra Ara Nizinkiewicz
; this file defines routines for sending valid WS2812b signals (https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf)
; 
; ============================================
; 
; This project uses ATTiny85, in order for those signals to have correct widths
; we will need to use the PLL clock (which requires editing fuse bits in tn85)

.include "./tn85def.inc"

.ifndef __SIGNALS_ASM__
.define __SIGNALS_ASM__

; Arguments:
; r15 - loop limit
; r16 - loop start
nop_loop:
	nop
	inc r16
	cp r16, r15
 	brne nop_loop
	ret
	

; Sends ONE signal to ws2812b (~800 nanoseconds high and ~400 nanoseconds low)
;
;   ~850ns
;  <------>
;   ______ ~400ns
;  |      |<--->
;  |      |
;  |      |
; _        _____
ws2812b_one_signal:
	sbi PORTB, PB0 
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
 	cbi PORTB, PB0
	ret

; Sends ZERO signal to ws2812b (~400 nanoseconds high and ~800 nanoseconds low)
;
;  ~400ns
;  <---->
;   ____  ~800ns
;  |    |<----->
;  |    |
;  |    |
; _      _______
ws2812b_zero_signal:
	sbi PORTB, PB0
	nop
 	nop
	nop
	nop
	cbi PORTB, PB0
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	ret

; a simple loop to create a bit more than 60 nanoseconds of low signal 
ws2812b_latch:
	ldi r17, 100
	ldi r16, 0
	rcall nop_loop
	ret

.endif
