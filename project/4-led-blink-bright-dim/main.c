#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"
#include "led.h"

int main(void){
	P1DIR |= LEDS;

	configureClocks();
	enableWDTInterrupts();

	or_sr(0x18);
}

int blinkLimit =5; //green turns on for 5 sec, off 2sec, on for 10 sec. 5 sec not repeated
int blinkCount =0;
int secondCount =0;

void
__interrupt_vec(WDT_VECTOR) WDT(){
	blinkCount++;
	if (blinkCount >= blinkLimit ){
		blinkCount =0;
		P1OUT &= ~LED_GREEN; //turn off green
		P1OUT |= LED_RED;    //turn on red

	} else{
		P1OUT &= ~LED_RED;	//turns off leds so they can change states
		P1OUT |= LED_GREEN;
	}

	secondCount++;
	if (secondCount >= 120) {//every second change blink state
		secondCount =0;
		blinkLimit++;
		if (blinkLimit >= 10) { //green and red changes state 10 times
			blinkLimit =0;
		}
	}
}
