#include <avr/io.h>
#include <util/delay.h>
#include "7seg.h"

void init7Seg(){
    DDRC |= (1 << DDC0)| (1 << DDC1)| (1 << DDC2)| (1 << DDC3)| (1 << DDC4)| (1 << DDC5)| (1 << DDC6)| (1 << DDC7);
}

void turnOn7SegWithNum(int num){
    switch(num){
        case 0:
            PORTC = 0b00111111;
            break;

        case 1:
            PORTC = 0b00000110;
            break;

        case 2:
            PORTC = 0b01011011 ;
            break;

        case 3:
            PORTC = 0b01001111;
            break;
        
        case 4:
            PORTC = 0b01100110;
            break;
        
        case 5:
            PORTC = 0b01101101;
            break;
        
        case 6:
            PORTC = 0b01111100;
            break;
        
        case 7:
            PORTC = 0b00000111;
            break;
        
        case 8:
            PORTC = 0b01111111;
            break;
        
        case 9:
            PORTC = 0b01100111;
            break;
    }
    

}