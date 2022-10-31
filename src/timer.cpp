// Author: Jason Freeman
// Net ID: japareman
// Date: 11/7/2022
// Assignment: Lab 4
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

    //set prescaler to 1024
    TCCR1B |= ((1 << CS12) | (1 << CS10));
    TCCR1B &= ~(1 << CS11);
    // OCR1A Calculated = (1us)(16MHz)/1024 = 16000000/1024 = 15625
    OCR1A = 15625;
    OCR1AH = 0x3D;
    OCR1AL = 0x09;
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayS(unsigned int delay){
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

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    // initiate timer to CTC mode
    TCCR0A &= ~(1 << WGM00);
    TCCR0A |= (1<< WGM01);
    TCCR0B &= ~((1 << WGM02) | (1 << CS02));
    TCCR0B |= ((1 << CS00) | (1 << CS01));

    // set prescaler to 64
    TCCR0B |=  (1 << CS00) | (1 << CS01);
    TCCR0B &= ~(1 << CS02);
    // OCR0A calculated = (1ms)(16MHz)/64 = 16000/64 = 250 - 1
    OCR0A = 249;
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
    unsigned int delayCnt = 0;
    // set timer0 to 0 to avoid junk numbers
    TCNT0 = 0; 
    // set the compare flag to start timer
    TIFR0 |= (1 << OCF0A);

    while (delayCnt < delay){
        // increment while flag is set (timer reached maxval/OCR0A)
        if(TIFR0 & (1 << OCF0A)){
            delayCnt++;
            // restart timer
            TIFR0 |= (1 << OCF0A); 
        }
    }
}