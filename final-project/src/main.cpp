// Author: Alan, Jason, Jeremy
// Net ID:
// Date: 11/29/2022
// Assignment:     Final Project

#include <Arduino.h>

#include <avr/io.h>
#include <avr/interrupt.h>


#include "timer.h"
#include "spi.h"





// Variables to keep track of the state of the face and the buzzer.
bool buzzerOn = false;
bool faceState = true; // True: Happy, False: sad

int main()
{
    // This array holds the power in each of the 8 frequency bins.
    float powerArray[8] = {1.2, 3.1, 4.4, 4.5, 3.2, 4.5, 5.2, 2.1};



    Serial.begin(9600); // using serial port to print values from I2C bus

    
    /* Initialize Analog to Digital Conversion with an anolog input. */

    /* Initialize 8x8 Matrix */
    init_SPI(); // Initialize SPI protocol for the LED Matrix (that shows the smiley face)


    while(true)
    {
        /* Sample the data and write the data into a matrix (the matrix length should be a power of 2. */

        /* Conduct a fourier transform on the data and ouptut a matrix. */

        /* Take the fourier transform matrix and calculate the power within specified frequency bins. */

        /* Take the power matrix and  print out the bins on the 8x8 matrix*/
    }
    

    return 0;
}

ISR(PCINT0_vect)
{

}
