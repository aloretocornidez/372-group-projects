#include <stdio.h>
#include "parameters.h"
#include <math.h>

void initFFTparams()
{
}


void FFT(float *input, float *output)
{

}

void bitReversal(float *input, float *outputA, float *outputB)
{
    int n = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            outputA[i / 2] = input[i];
        }
        else
        {
            outputB[i / 2] = input[i];
        }
    }
}