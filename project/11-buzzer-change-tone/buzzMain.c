#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"
#include "buzzer.h"

int main() {
	configureClocks();
	buzzer_init();

	enableWDTInterrupts();
	or_sr(0x18);
}

void tone2_and3();

int cycles, cyclesMin = 1500, cyclesMax = 4000;
int tone1Interval = 0;
int tone2Interval = 0, tone2Min = 1500, tone2Max = 3500;
int tone3Interval = 0;
void
__interrupt_vec(WDT_VECTOR) WDT()
{

	if (tone1Interval <= 100) cycles = cyclesMin; //tone 1
	else if (tone1Interval  < 200) cycles = cyclesMax;
	else tone2_and3();
       	
	tone1Interval++; 
	
	if (tone2Interval >= tone2Max){ 
		if (tone3Interval >= 7000) {
			tone3Interval = 0; tone2Interval =0; //reset tone2 and 3
		} 		
	}
	
	tone2Interval++; tone3Interval++;
	buzzer_set_period(cycles);
}

void tone2_and3()
{
	//change for 2nd part sooner
	if(tone2Interval >= tone2Min && tone2Interval <= tone2Max){ 	//tone 2
		if(cycles < cyclesMin) cycles = cyclesMax;
		else cycles -=6;
	}
	else if (tone3Interval > 5000 && tone3Interval <= 7000){ // >3500 <= 6000 //tone 3
		if(cycles >= 4000) cycles = 1500;
		else cycles +=12;
	}
	else tone1Interval =0; //reset between cycles in tone 1
	
}
