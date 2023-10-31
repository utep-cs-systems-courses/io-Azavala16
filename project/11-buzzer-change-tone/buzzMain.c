#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"
#include "buzzer.h"

int main() {
	configureClocks();
	buzzer_init();

	enableWDTInterrupts();
	or_sr(0x18);
}

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

void
__interrupt_vec(WDT_VECTOR) WDT()
{
	tone1();
	if(tone1Interval > tone1Max) tone2_and3();
	
	tone1Interval++; //increase for tone2 to happen
	
	//if tone2 and 3 finished executing	
	if (tone2Interval >= tone2Max && tone3Interval >= tone3Max){ 
		tone3Interval = tone2Interval =0; //reset tone2 and 3
	}
	
	tone2Interval++; tone3Interval++; //increase for the other tones to happen
	buzzer_set_period(cycles);
}

