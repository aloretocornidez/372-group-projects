// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPD0(){
    DDRD &= ~(0 << DDD0); //initailize pin
    PORTD |= (1 << PORTD0); //iniatilize pulllup

    EICRA |= (1 << ISC00); //set up interrumpt
    EIMSK |= (1 << INT0);
}