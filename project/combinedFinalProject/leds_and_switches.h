#ifndef leds_and_switches_included
#define leds_and_switches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3

#define SWITCHES (SW1 | SW2 | SW3 | SW4)

void led_init();
void switch_init();
static char switch_update_interrupt_sense();
void switch_interrupt_handler();

#endif
