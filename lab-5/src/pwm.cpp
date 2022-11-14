// Author:         
// Net ID:         
// Date: 11/28/2022          
// Assignment:     Lab 5
//----------------------------------------------------------------------//

#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"

// initialize timer3 and pin 5(PE3) as an output
void initPWMTimer3(){
    DDRE |= (1 << DDE3);

    //  Use  PWM mode 14 bit, top value is determined by ICR1 value, 
    //  which determines the PWM frequency.
    TCCR3A &= ~((1 << COM3A0)|(1 << WGM30));
    TCCR3A |= (1 << COM3A1)|(1 << WGM31);
    TCCR3B &= ~((1 << CS31)|(1 << CS32));
    TCCR3B |= (1 << WGM32)|(1 << WGM33)|(1 << CS30);
    // PWM frequency calculation for FAST PWM mode on page 148 of datasheet
    //frequency of PWM = (F_clk)/((Prescaler)* (1 +TOP))
    // frequency of PWM = 16Mhz
    // Prescaler = 1
    // TOP value = ICRN = 15 
    // PWM frequency from calculation = 1 MHz

    // set ICR1 to 15
    ICR3 = 15;

    // duty cycle is set by dividing output compare OCR3A value by 1 + TOP value
    // the top value is (1 + ICR3) = 16
    //  calculate OCR1A value => OCR3A = duty cycle(fractional number) * (1 + TOP) 
    // we want a duty cycle = 75%
    // OCR3A = 0.75 * 16
    // OCRnX = 12
    OCR3A = 12;
}
