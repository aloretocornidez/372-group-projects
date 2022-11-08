// Author: Jason Freeman        
// Net ID: japareman         
// Date: 11/7/2022          
// Assignment:     Lab 4
//----------------------------------------------------------------------//

#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"

// initialize timer3 and pin 5(PE3) as an output
void initPWMTimer3(){
    DDRB |= (1 << DDE3);

    // set Fast PWM 10-bit mode, not-inverting
    // set prescalar to 1
    TCCR3A |= (1 << COM3A1)|(1 << WGM31)|(1 << WGM30);
    TCCR3B |= (1 << WGM32)|(1 << CS30);
    // set arbitrary duty cycle of 25%
    // Duty Cycle = (OCRnX)/(TOP)
    // 0.25 = (OCRnX)/(0xFF)
    // OCRnX = 255
    OCR3A = 255;
}

// initialize timer4 and pin 6(PH3) as an output 
// set prescalar to 1
void initPWMTimer4(){
    DDRB |= (1 << DDH3);
    TCCR4A |= (1 << COM4A1)|(1 << WGM41)|(1 << WGM40);
    TCCR4B |= (1 << WGM42)|(1 << CS40);
    // set arbitrary duty cycle of 25%
    OCR4A = 255;
}

void changeDutyCycle(unsigned char adch, unsigned char adcl){
    OCR3A = (adch & 0b1111100000) | (adcl & 0b0000011111);
    OCR4A = (adch & 0b1111100000) | (adcl & 0b0000011111);
}