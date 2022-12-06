/*
 *
 * Author: Alan Manuel Loreto Cornídez
 * Initial Creation Date: December 1, 2022
 * Last Modified Date: December 1, 2022
 * Description: Header file for an fft library made from scratch.
 *
 */

#ifndef FFT_H
#define FFT_H

#include "parameters.h"


void FFT(float *input, fix* fr, fix* fi);

void initFFTparams();

void populateSinewave();

void bitReversal(float* input, fix* fr, fix* fi);

void powerCalculation(fix* input, float* output);

void normalizePower(float* input);

#endif