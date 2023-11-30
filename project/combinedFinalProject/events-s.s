	.arch  msp430g2553
	.p2align 1,0
	.text

	.global events
	.extern P1OUT

events:
		sub #1, r1 ;allocate a temp var (used to store expressions from if conditions)
		mov.b r12, 0(r1)	;move p2val into temp var
		and.b #1, 0(r1)		;and SW1 into temp var 
		cmp.b #0, 0(r1)	
		jnz skipif1		;jump skipif1, when if condition not zero
		call #start_module11
		call #start_module2
		jmp end			;unconditional jump
skipif1: 	mov.b r12, 0(r1)
		and.b #2, 0(r1)
		cmp.b #0, 0(r1)
		jnz skipif2
		call #start_module1
		jmp end	
skipif2: 	mov.b r12, 0(r1)
		and.b #4, 0(r1)
		cmp.b #0, 0(r1)
		jnz skipif3
		call #start_module2
		call #buttonSound
		jmp end
skipif3: 	mov.b r12, 0(r1)
		and.b #8, 0(r1)
		cmp.b #0, 0(r1)
		jnz skipif4
		call #start_module4
		mov #0, r12		;move argument 0 into function
		call #buzzer_set_period ;call function
		jmp end
skipif4: 	mov.b r12, 0(r1)
		and.b #4, 0(r1)
		cmp.b #0, 0(r1)
		jz skipif2
		mov #0, r12
		call #buzzer_set_period
		bis.b #1, P1OUT
		and.b #~64, P1OUT
end:		add #1, r1		;free temp var
		pop r0			;set pc to the return address

