.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we will need a .global statement to make available ASM
; functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.
.global _write_0, _write_1, _delay_100us, _delay_1ms
 

    
    ; 13 low ; 7 high
    _write_0:  ; 2 cycles to call
    repeat #5 ; 1 cycle
    nop ; 1   ; 5 + 1 cycles
    
    inc LATA ; 1 
    
    repeat #4   ; 1 cycle
    nop          ;4+1 cycles
    
    clr LATA ; 1
    
    return ; 3 cycles for the return
    

    
    ; 10 low  ; 10 high
    _write_1:    ; 2 cycles to call
    repeat #2  ; 1 cycle
    nop    ; 2 + 1 cycles
    
    inc LATA ; 1
    
    repeat #7 ; 1 cycle
    nop   ; 7 + 1 cycles
    
    clr LATA ; 1 cycle
    
    return ; 3 cycles for the return
    
_delay_100us:
	; for 100 us need 1,600 clock cycle delays
	; 2 cycles for function call
	
	repeat #1593    ; 1 cycle to load and prep
	nop          ;1593+1 cycles to execute NOP 1594 times 
    
	return ; 3 cycles for the return
    
_delay_1ms:
	; for 1 ms need 16,000 clock cycle delays
	; 2 cycles for function call
	
	repeat #15993    ; 1 cycle to load and prep
	nop          ;15993+1 cycles to execute NOP 15994 times
	
	return ; 3 cycles for the return
	






