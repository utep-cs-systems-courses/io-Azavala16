#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"
#include "led.h"

int main(void){
	P1DIR |= LEDS;
	
	configureClocks();
	enableWDTInterrupts();
	or_sr(0x18);
}

int greenSecCount = 0; 
int greenOnSec = 5, greenOffSec = 5; //time led will stay on (greenSeconds x secondCount)
int redSeconds = 2, redSecCount =0;

void green_behavior();
void red_behavior();

void
__interrupt_vec(WDT_VECTOR) WDT(){
	greenSecCount++;
	if (greenSecCount >= 250){ //toggle green every 5 sec (250 == 1sec)
		greenSecCount =0;
		green_behavior();
	}
	//reset green on/off seconds
	if(greenOnSec <=0 && greenOffSec <= 0) greenOnSec = greenOffSec = 5;


	redSecCount +=5;	//faster blinks
	if (redSecCount >= 60){ //toggle red every 1/4 sec
		redSecCount=0;
		red_behavior();
	}
}

void green_behavior(){
	if (greenOnSec > 0){ 
		P1OUT |= LED_GREEN;	//turn on 5s
		greenOnSec--;
	}
	else{
		P1OUT &= ~LED_GREEN; 	//turn off 5s
		greenOffSec--;
	}
}

void red_behavior(){
	if (redSeconds > 0 ){ 	
		P1OUT |= LED_RED;  //red on 2s
		redSeconds--;
	}
	else{ 
		P1OUT &= ~LED_RED; //red off 1s
		redSeconds = 2;	   //reset red
	}	
}
