// Author: Alan Manuel Loreto Cornídez
// Net ID: aloretocornidez
// Date: October 3rd, 2022
// Assignment: Lab 3
//----------------------------------------------------------------------//
#include "lcd.h"
#include "timer.h"
#include <util/delay.h>

/*
 * Initializes all pins related to the LCD to be outputs
 */
// PORTA0, PORTA1, PORTA2, and PORTA3 must be used for the data
// pins on the LCD with PORTA0 corresponding to the least significant bit
void initLCDPins()
{
	// Setting the pins to logical 1 enables them as output pins.
	// This line enables ports PA0, PA1, PA2, and PA3 to outputs.
	// On the microcontroller, these pins are 22, 23, 24, and 25.
	// Setting DDRA to a logical 1 sets the pins as output pins.
	DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);
	DDRB  |= (1 << DDB4) | (1 << DDB6);
}



void raiseEnablePin()
{
	PORTB |= (1 << PORTB6); // Raise the Enable pin, the enable pin is used on B4
	delayUs(1);
	PORTB &= ~(1 << PORTB6); //	Set the enable pin to 0

}

/* 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *      a. data is an unsigned char which has 8 bits. Therefore, you
 *         need assign the bottom 4 bits of "data" to the appropriate bits in
 *         PORTA
 *  2. This is a "command" signal, meaning RS should be Low
 *  3. Assert high on enable pin, delay, and asset low on enable pin
 *  4. delay the provided number in MICROseconds.
 */
void fourBitCommandWithDelay(unsigned char data, unsigned int delay)
{
	//PORTA = ((PORTA & 0xF0) | (data & 0x0F));
	PORTA = data;

	// Set RS pin to 0. The RS pin is used on B4.
	PORTB &= ~(1 << PORTB4);

	// Allowing command to execute.
	raiseEnablePin();

	delayUs(delay);
}

/* Similar to fourBitCommandWithDelay except that now all eight bits of command are
 * sent.
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *       a. unlike fourBitCommandWithDelay, you need to send the TOP four bits of
 *          "command" first. These should be assigned to appropriate bits in PORTA
 * 2. This is a command signal, meaning RS should be low
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of command to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay the provided number in MICROseconds.
 */
void eightBitCommandWithDelay(unsigned char command, unsigned int delay)
{
	PORTA = ((PORTA & 0xF0) | ((command >> 4) & 0x0F));

	// Set RS pin to 0. The RS pin is used on B6. Used for commands
	PORTB &= ~(1 << PORTB4);

	// Allowing command to execute.
	raiseEnablePin();

	// Bit masking with the bottom 4 bits.
	PORTA = (PORTA & 0xF0 | (command) & 0x0F);

	// Allowing command to execute.
	raiseEnablePin();

	// Need to delay for the command execution time specified in the data sheet.
	delayUs(delay);
}

/*
 * Similar to eightBitCommandWithDelay except that now RS should be high
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 * 2. This is a "data" signal, meaning RS should be high
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of character to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay is always 46 MICROseconds for a character write
 */
void writeCharacter(unsigned char character)
{
	// 1. Assert the upper 4 bits to the lcd screen.
	PORTA = (PORTA & 0xF0) | ((character >> 4) & 0x0F);

	// 2. Set Rs pin high since this is data input.
	PORTB |= (1 << PORTB4);

	// 3. Asserting high on the Enable pin, delaying, then lowering the enable pin.
	raiseEnablePin();

	// 4. Now setting the lower four bits
	PORTA = (PORTA & 0xF0) | (character & 0x0F);

	// 5. Asserting high on the Enable pin, delaying, then lowering the enable pin.
	raiseEnablePin();

	// 6. Delay time required for the command to execute.
	delayUs(46);
}

/*
 * Writes a provided string such as "Hello!" to the LCD screen. You should
 * remember that a c string always ends with the '\0' character and
 * that this should just call writeCharacter multiple times.
 */
void writeString(const char *str)
{
	while (*str != '\0')
	{
		writeCharacter(*str);
		str++;
	}
}

/*
 * This moves the LCD cursor to a specific place on the screen.
 * This can be done using the eightBitCommandWithDelay with correct arguments
 */
void moveCursor(unsigned char x, unsigned char y)
{
	eightBitCommandWithDelay((0x80) |  (x << 6) | y , 46); 
}

/*
 * This is the procedure outline on the LCD datasheet page 4 out of 9.
 * This should be the last function you write as it largely depends on all other
 * functions working.
 */
void initLCDProcedure()
{
	delayUs(5000);
	delayUs(5000);
	delayUs(5000);
	delayUs(5000);
	delayUs(5000);
	delayUs(5000);
	

	// //Step 2
	// eightBitCommandWithDelay(0b00000011, 4100);

	// //Step 3
	// eightBitCommandWithDelay(0b00000011, 100);

	// //Step 4
	// eightBitCommandWithDelay(0b00000011, 100);

	// //Step 5
	// eightBitCommandWithDelay(0b00000010, 100);
	// //Step 6
	// eightBitCommandWithDelay(0b00101000, 53);

	// //Step 7
	// eightBitCommandWithDelay(0b00001000, 53);

	// //Step 8
	// eightBitCommandWithDelay(0b00000001, 3000);

	// //Step 9
	// eightBitCommandWithDelay(0b00000110, 53);

	// //Step 10
	// eightBitCommandWithDelay(0b00001100, 53);

	
	// Delay 15 milliseconds
	delayUs(5000);
	delayUs(5000);
	delayUs(5000);

	// Write 0b0011 to DB[7:4] and delay 4100 microseconds
	eightBitCommandWithDelay(0b00000011, 4100);

	// Write 0b0011 to DB[7:4] and delay 100 microseconds
	eightBitCommandWithDelay(0b00000011, 100);

	// First collective eight bit command.
	eightBitCommandWithDelay(0b00110010, 100);

	// Function set in the command table with 53us delay
	eightBitCommandWithDelay(0b00101000, 53);

	// Display off in the command table with 53us delay
	eightBitCommandWithDelay(0b00001000, 53);

	// Clear display in the command table. Remember the delay is longer!!!
	eightBitCommandWithDelay(0b00000001, 3000);

	// Entry Mode Set in the command table.
	// eightBitCommandWithDelay(0b00000110, 53);
	eightBitCommandWithDelay(0b00000110, 53);

	// Display ON/OFF Control in the command table. (Yes, this is not specified),
	// in the data sheet, but you have to do it to get this to work. Yay datasheets!)
	eightBitCommandWithDelay(0b00001110, 53);
}

/* Initializes Tri-state for LCD pins and calls initialization procedure.
 * This function is made so that it's possible to test initLCDPins separately
 * from initLCDProcedure which will likely be necessary.
 */
void initLCD()
{
	initLCDPins();
	initLCDProcedure();
}