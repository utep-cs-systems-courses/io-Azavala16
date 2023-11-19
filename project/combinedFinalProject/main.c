
#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"
#include "leds_and_switches.h"
#include "../11-buzzer-change-tone/buzzer.h"
#include "../2-red-blink-quick/module2.h"

void main(void) 
{  
 
  led_init();
  switch_init();
  
  configureClocks();
  buzzer_init();
  enableWDTInterrupts();
  or_sr(0x18); // CPU off, GIE on
} 

//keep modules in a specific state if button is released
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
	if(P2IE & SWITCHES){
		P2IFG &= ~SWITCHES;
		switch_interrupt_handler();
	}
}

//keep button pressed for normal behavior
void __interrupt_vec(WDT_VECTOR) WDT(){
	switch_interrupt_handler();
}
