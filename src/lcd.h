// Author: Alan Manuel Loreto Cornídez
// Net ID: aloretocornidez
// Date: October 3rd, 2022
// Assignment: Lab 3
//----------------------------------------------------------------------//

#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

void initLCD();
void raiseEnablePin();
void fourBitCommandWithDelay(unsigned char data, unsigned int delay);
void eightBitCommandWithDelay(unsigned char command, unsigned int delay);
void writeCharacter(unsigned char character);
void writeString(const char *string);
void moveCursor(unsigned char x, unsigned char y);
void initLCDPins();
void initLCDProcedure();

#endif


