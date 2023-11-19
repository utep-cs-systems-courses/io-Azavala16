
#include <msp430.h>
#include "../2-red-blink-quick/led.h"
#include "../../demos/timerLib/libTimer.h"
#include "modules.h"
#include "../11-buzzer-change-tone/buzzer.h"
//implementation of all other directories are stored in this file for a final project result

//module1
int secondCount = 0;
int greenSec = 3; //time led will stay on (greenSeconds x secondCount)
int redSec = 3;

void start_module1(){	
	secondCount++;	
	if (secondCount >= 250){//change LEDs every 3 seconds since second count is 250 (1sec)
		secondCount =0;
		if (greenSec > 0){ //state 1
			P1OUT |= LED_GREEN;//turn on green for 3 sec
			P1OUT &= ~LED_RED; //red off
			greenSec--;	
		}
		else if (greenSec <=0 && redSec > 0){ //state 2
			P1OUT |= LED_RED;    //red on for 3 sec
			P1OUT &= ~LED_GREEN; //green off
			redSec--;
		}
		else{ //reset both states
			greenSec =3; 
			redSec =3;
		}	

	}
}

//module2
int greenSecCount = 0; 
int greenOnSec = 5, greenOffSec = 5; //time led will stay on (greenSeconds x secondCount)
int redSeconds = 2, redSecCount =0;

void green_behavior();
void red_behavior();

void start_module2(){
	
	greenSecCount +=15;	//faster blinks (normal behavior at +1)
	if (greenSecCount >= 250){ //toggle green every 5 sec (250 == 1sec)
		greenSecCount =0;
		green_behavior();
	}
	//reset green on/off seconds
	if(greenOnSec <=0 && greenOffSec <= 0) greenOnSec = greenOffSec = 5;


	redSecCount +=5;	//faster blinks (normal behavior at +1)
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
		P1OUT |= LED_RED; //red on 2s
		redSeconds--;	  
	} 	
	else{
		P1OUT &= ~LED_RED; //red off 1s
		redSeconds = 2;	   //reset red
	}

}

//module 4
int blinkLimit =5; //green turns on for 5 sec, off 2sec, on for 10 sec. 5 sec not repeated
int blinkCount =0;
int secCount =0;

void start_module4(){
	blinkCount++;
	if (blinkCount >= blinkLimit ){
		blinkCount =0;
		P1OUT &= ~LED_GREEN; //turn off green
		P1OUT |= LED_RED;    //turn on red

	} else{
		P1OUT &= ~LED_RED;	//turns off leds so they can change states
		P1OUT |= LED_GREEN;
	}

	secCount++;
	if (secCount >= 120) {//every second change blink state
		secCount =0;
		blinkLimit++;
		if (blinkLimit >= 10) { //green and red changes state 10 times
			blinkLimit =0;
		}
	}
}

//module11
int cycles, cyclesMin = 1500, cyclesMax = 4000;
int tone1Interval = 0, tone1Min = 100, tone1Max = 200;
void tone1()
{	
	//quick change high and low pitch
	if (tone1Interval <= tone1Min) cycles = cyclesMin; 
	else if (tone1Interval  <= tone1Max) cycles = cyclesMax;	
}

int tone2Interval = 0, tone2Min = 1500, tone2Max = 3500;
int tone3Interval = 0, tone3Min = 5000, tone3Max = 7000;
void tone2_and3()
{
	//tone2 intervals
	if(tone2Interval >= tone2Min && tone2Interval <= tone2Max){
		if(cycles <= cyclesMin) cycles = cyclesMax; //reset note to low pitch
		else cycles -=6;  			    //gradual change low to high pitch
	} 
	//tone3 intervals (decrease to execute tone3 right after tone2)
	else if (tone3Interval > tone3Min && tone3Interval <= tone3Max){ 
		if(cycles >= cyclesMax) cycles = cyclesMin; //reset note to high pitch
		else cycles +=12; 			    //gradual change high to low pitch
	}
	else tone1Interval =0;  //back to tone1 between tone2 and 3
	
}

void start_module11(){
	tone1();
	if(tone1Interval > tone1Max) tone2_and3();
	
	tone1Interval++; //increase for tone2 to happen
	
	//if tone2 and 3 finished executing	
	if (tone2Interval >= tone2Max && tone3Interval >= tone3Max){ 
		tone3Interval = tone2Interval =0; //reset tone2 and 3
	}

	tone2Interval++; tone3Interval++;
	buzzer_set_period(cycles);
	
}

int cy = 1500, cyMax = 2000;

void buttonSound(){
	if(cy <= cyMax)	cy +=20;
	if(cy > cyMax) cy = 1500;
	buzzer_set_period(cy);
}


