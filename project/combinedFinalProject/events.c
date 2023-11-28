#include <msp430.h>
#include "leds_and_switches.h"
#include "modules.h"
#include "../11-buzzer-change-tone/buzzer.h"
#include "../2-red-blink-quick/led.h"

void events(char p2val){	
	
	//if a switch associated with the corresponding bit is pressed
	 if(!(p2val & SW1)){ 	  //BIT0
		start_module11();
		start_module2();
	 }
	 else if(!(p2val & SW2)){ //BIT1
	 	start_module1();
	 }	 
	 else if(!(p2val & SW3)){ //BIT2
	 	start_module2();
		buttonSound();
	 }
	 else if(!(p2val & SW4)){ //BIT3
	 	start_module4();
		buzzer_set_period(0);// turn off buzzer with SW4
	 }
	 else if(p2val & SW3){	      //SW3 released
		buzzer_set_period(0); //turn off buttonSound()
		P1OUT |= LED_RED;     //turn on red led
		P1OUT &= ~LED_GREEN;
	 }
}
