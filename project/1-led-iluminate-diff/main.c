#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"
#include "led.h"

int main(void){
	P1DIR |= LEDS;
	
	configureClocks();
	enableWDTInterrupts();
	or_sr(0x18);
}

int secondCount = 0;
int greenSeconds = 3; //time led will stay on (greenSeconds x secondCount)
int redSeconds = 3;

void
__interrupt_vec(WDT_VECTOR) WDT(){
	secondCount++;	
	if (secondCount >= 250){//change LEDs every 3 seconds since second count is 250 (1sec)
		secondCount =0;
		if (greenSeconds > 0){ //state 1
			P1OUT |= LED_GREEN;//turn on green for 3 sec
			P1OUT &= ~LED_RED; //red off
			greenSeconds--;	
		}
		else if (greenSeconds <=0 && redSeconds > 0){ //state 2
			P1OUT |= LED_RED;    //red on for 3 sec
			P1OUT &= ~LED_GREEN; //green off
			redSeconds--;
		}
		else{ //reset both states
			greenSeconds =3; 
			redSeconds =3;
		}	

	}
}
