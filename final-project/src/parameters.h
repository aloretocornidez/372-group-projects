#ifndef PARAMETERS_H
#define PARAMETERS_H


// 512 is chosen because it is a power of 2, thus fft implementation is done without zero-padding.
#define FFT_SIZE 64
#define NUM_SAMPLES 64     // the number of gathered samples (power of two)
#define NUM_SAMPLES_M_1 63 // the number of gathered samples minus 1
#define LOG2_NUM_SAMPLES 6 // log2 of the number of gathered samples
#define SHIFT_AMOUNT 10    // length of short (16 bits) minus log2 of number of samples



typedef signed int fix;
#endif