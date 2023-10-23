	.arch msp430g2553
	.p2align 1,0
	.text	


	.global oncePerSecond

oncePerSecond:
	//add #1, blinkLimit
	cmp blinkLimit, #8
	jz up			//ask what type of jump
	mov #0, blinkLimit
//	jz up
up:	add #1, blinkLImit
