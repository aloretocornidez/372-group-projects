// Author: 
// Net ID: 
// Date: 11/28/2022
// Assignment: Lab 5
//----------------------------------------------------------------------//

#include "timer.h"
//You many use any timer you wish for the microsecond delay and the millisecond delay


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
	// set Timer1 to CTC mode by placing 1 into WGM12
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);

    //set prescaler to 8
    TCCR1B &= ~((1 << CS12) | (1 << CS10));
    TCCR1B |= (1 << CS11);
    // OCR1A Calculated = (1ms)(16MHz)/8 = 16000/8 = 2000
    OCR1A = 2000;
    OCR1AH = 0x07;
    OCR1AL = 0xD0;
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayMs(unsigned int delay){
    unsigned int delayCnt = 0;
    // set timer1 to 0 to avoid junk numbers
    TCNT1 = 0;
    // set the compare flag to start timer
    TIFR1 |= (1 << OCF1A);

    while (delayCnt < delay){
        // increment everytime the timer raises a flag(timer reached maxval/OCR1A)
        if(TIFR1 & (1 << OCF1A)){
            delayCnt++;
            // reset timer
            TIFR1 |= (1 << OCF1A);
        }
    }
}

