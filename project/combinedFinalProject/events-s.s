	.arch  msp430g2553
	.p2align 1,0
	.text

	.global events
	.extern P1OUT

events:
		sub #1, r1
		mov.b r12, 0(r1)
		and.b #1, 0(r1)
		cmp.b #0, 0(r1)
		jnz skipif1
		call #start_module11
		call #start_module2
		jmp end
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
		mov #0, r12
		call #buzzer_set_period
		jmp end
skipif4: 	mov.b r12, 0(r1)
		and.b #4, 0(r1)
		cmp.b #0, 0(r1)
		jz skipif2
		mov #0, r12
		call #buzzer_set_period
		bis.b #1, P1OUT
		and.b #~64, P1OUT
end:		add #1, r1
		pop r0

