// Author: Alan, Jason, Jeremy
// Net ID:
// Date: 11/29/2022
// Assignment:     Final Project

#include <Arduino.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "spi.h"
#include "fft.h"
#include "adc.h"

// 512 is chosen because it is a power of 2, thus fft implementation is done without zero-padding.
#define FFT_SIZE 512

static uint8_t channel = 0;

int main()
{

    // Initialize an array that shall hold the input signal
    float inputSignal[FFT_SIZE];
    float transformedSignal[2 * FFT_SIZE - 1]; // This is the size that the FFT renders.

    // This array holds the power in each of the 8 frequency bins.
    float powerArray[8] = {1.2, 3.1, 4.4, 4.5, 3.2, 4.5, 5.2, 2.1};


    FFT(inputSignal, transformedSignal);

    /* Initialize Analog to Digital Conversion with an anolog input. */

    /* Initialize 8x8 Matrix */
    init_SPI(); // Initialize LED Matrix.
    initADC(); // Initialize ADC.
    initFFTparams(); // Initialialize FFT parameters (like butterfly values).

    
    Serial.begin(9600); // using serial port to print values from I2C bus

    

    while (true)
    {
        
        Serial.println(sampleVoltage(channel));
        _delay_ms(100);


        /* Sample the data and write the data into a matrix (the matrix length should be a power of 2. */
        /* Conduct a fourier transform on the data and ouptut a matrix. */

        /* Take the fourier transform matrix and calculate the power within specified frequency bins. */

        /* Take the power matrix and  print out the bins on the 8x8 matrix*/
    }

    return 0;
}
