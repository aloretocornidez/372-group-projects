// Author: Alan Manuel Loreto Cornídez
// Net ID: aloretocornidez
// Date: October 3rd, 2022
// Assignment: Lab 3
//
// Description: This file implements turnOnLED and initLED to control
// the LEDs.
//----------------------------------------------------------------------//

#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

/*
 * Initialize PD0, PD1, PD2, and PD3 to outputs
 */
void initLED()
{
    // This line enables ports PA0, PA1, PA2, and PA3 to outputs.
    // On the microcontroller, these pins are 22, 23, 24, and 25.
    // Setting PORTF to a logical 1 sets the pins as output pins.
    DDRD |= ((1 << DD0) | (1 << DD1) | (1 << DD2) | (1 << DD3));
    
}

/* This must be one line of code.
 * In this function you will be giving a number "num" which will be represented
 * in binary by four LEDs. You must effectively assign the lowest four bits of
 * "num" to the appropriate bits of PORTD.
 */
void turnOnLEDWithChar(unsigned char num)
{
    // The first section of the statement sets all lower bits to zero
    // The second section then sets all of the bits in 'num' to one.
    PORTD = (PORTD & 0xF0) | (num & 0x0F);
}
