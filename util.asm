.ifndef __UTIL_ASM__
.define __UTIL_ASM__

; uses r20 as step limit
; uses r16 as iterator
; uses r21 as another internal iterator number
; it increments r16 only when r21 reaches 255
delay:
	inc r21
	cpi r21, 2504
	brlo delay
	ldi r21, 0
	inc r16
	cp r16, r20
	brlo delay
	ret
	
.endif
