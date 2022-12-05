// Author: Alan, Jason, Jeremy
// Net ID:
// Date: 11/29/2022
// Assignment:     Final Project
#include <Arduino.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "../lib/kiss_fft.h"
#include "timer.h"
#include "spi.h"
#include "fft.h"
#include "adc.h"
#include "parameters.h"
#include "fix_fft.h"


static uint8_t channel = 0;

int main()
{

    // Initialize an array that shall hold the input signal
    float inputSignal[FFT_SIZE];
    float transformedSignal[FFT_SIZE]; // This is the size that the FFT renders.
    int m = log10(FFT_SIZE) / log10(2);

    // This array holds the power in each of the 8 frequency bins.
    float powerArray[8];

   

    /* Initialize Analog to Digital Conversion with an anolog input. */
    initADC(channel);      // Initialize ADC.

    /* Initialize 8x8 Matrix */
    init_SPI();

    /* Initialize FFT parameters to prepare for the fast fourier transform. */
    initFFTparams(); // Initialialize FFT parameters (like butterfly values).

    Serial.begin(9600); // using serial port to print values from I2C bus

    while (true)
    {

        /* Sample the data and write the data into a matrix (the matrix length should be a power of 2. */
        populateInputBuffer(inputSignal);

        /* Conduct a fourier transform on the data and ouptut a matrix. */
        // FFT(inputSignal, transformedSignal);
        fix_fftr((int_8t)inputSignal, m, 0);


        
        /* Take the fourier transform matrix and calculate the power within specified frequency bins. */
        


        /* Take the power matrix and  print out the bins on the 8x8 matrix*/
    }

    return 0;
}

