#include <stdio.h>
#include "parameters.h"
#include <math.h>
#include <stdfix.h>
#include "fft.h"

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//////////// Fixed point arithmetic definitions ////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

// Using fixed point multiplication to speed up calculations.
// typedef signed int fix; // This line is included in the parameters.h file since it is used globally.

// Datatype change definitions for fixed point arithmetic
#define int2fix(a) (fix)((a) << 15)

#define fix2int(a) (int)((a >> 15))

#define float2fix(a) (fix)(a * 32768.0)

#define fix2float(a) ((float)(a) / 32768.0)

// Multiplication definition for fixed point arithmetic
#define multfix(a, b) (fix)((((signed long long)a) * ((signed long long)b) >> 15))

// Division definition for fixed point arithmetic
#define divfix(a, b) (fix)((((signed long long)(a) << 15 / (b))))

// Square-root definition for fixed point arithmetic
#define sqrtfix(a) (float2fix(sqrt(fix2float(a))))

fix Sinewave[NUM_SAMPLES];

// void FFTfix(fix* fr, fix* fi)
void FFTfix(fix *fr, fix *fi)
{

    unsigned short m;  // one of the indices being swapped
    unsigned short mr; // the other index being swapped (r for reversed)
    fix tr, ti;        // for temporary storage while swapping, and during iteration

    int i, j; // indices being combined in Danielson-Lanczos part of the algorithm
    int L;    // length of the FFT's being combined
    int k;    // used for looking up trig values from sine table

    int istep; // length of the FFT which results from combining two FFT's

    fix wr, wi; // trigonometric values from lookup table
    fix qr, qi; // temporary variables used during DL part of the algorithm

    //////////////////////////////////////////////////////////////////////////
    ////////////////////////// BIT REVERSAL //////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    // Bit reversal code below based on that found here:
    // https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
    for (m = 1; m < NUM_SAMPLES_M_1; m++)
    {
        // swap odd and even bits
        mr = ((m >> 1) & 0x5555) | ((m & 0x5555) << 1);
        // swap consecutive pairs
        mr = ((mr >> 2) & 0x3333) | ((mr & 0x3333) << 2);
        // swap nibbles ...
        mr = ((mr >> 4) & 0x0F0F) | ((mr & 0x0F0F) << 4);
        // swap bytes
        mr = ((mr >> 8) & 0x00FF) | ((mr & 0x00FF) << 8);
        // shift down mr
        mr = mr >> SHIFT_AMOUNT;
        // don't swap that which has already been swapped
        if (mr <= m)
            continue;
        // swap the bit-reveresed indices
        tr = fr[m];
        fr[m] = fr[mr];
        fr[mr] = tr;
        ti = fi[m];
        fi[m] = fi[mr];
        fi[mr] = ti;
    }

    //////////////////////////////////////////////////////////////////////////
    ////////////////////////// Danielson-Lanczos //////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    // Adapted from code by:
    // Tom Roberts 11/8/89 and Malcolm Slaney 12/15/94 malcolm@interval.com
    // Length of the FFT's being combined (starts at 1)
    L = 1;
    // Log2 of number of samples, minus 1
    k = LOG2_NUM_SAMPLES - 1;
    // While the length of the FFT's being combined is less than the number of gathered samples
    while (L < NUM_SAMPLES)
    {
        // Determine the length of the FFT which will result from combining two FFT's
        istep = L << 1;
        // For each element in the FFT's that are being combined . . .
        for (m = 0; m < L; ++m)
        {
            // Lookup the trig values for that element
            j = m << k;                         // index of the sine table
            wr = Sinewave[j + NUM_SAMPLES / 4]; // cos(2pi m/N)
            wi = -Sinewave[j];                  // sin(2pi m/N)
            wr >>= 1;                           // divide by two
            wi >>= 1;                           // divide by two
            // i gets the index of one of the FFT elements being combined
            for (i = m; i < NUM_SAMPLES; i += istep)
            {
                // j gets the index of the FFT element being combined with i
                j = i + L;
                // compute the trig terms (bottom half of the above matrix)
                tr = multfix(wr, fr[j]) - multfix(wi, fi[j]);
                ti = multfix(wr, fi[j]) + multfix(wi, fr[j]);
                // divide ith index elements by two (top half of above matrix)
                qr = fr[i] >> 1;
                qi = fi[i] >> 1;
                // compute the new values at each index
                fr[j] = qr - tr;
                fi[j] = qi - ti;
                fr[i] = qr + tr;
                fi[i] = qi + ti;
            }
        }
        --k;
        L = istep;
    }
}

//
void initFFTparams()
{
    populateSinewave();
}

void FFT(float *input, fix *fr, fix *fi)
{
    bitReversal(input, fr, fi);
    FFTfix(fr, fi);
}

// This function does bit reversal on the arrays
void bitReversal(float *input, fix *fr, fix *fi)
{

    for (int i = 0; i < FFT_SIZE; i++)
    {
        if (i % 2 == 0)
        {
            fr[i / 2] = float2fix(input[i]);
        }
        else
        {
            fi[i / 2] = float2fix(input[i]);
        }
    }
}

// This function populates the array of sinewave values to create a lookup table for calculations.
void populateSinewave()
{
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        Sinewave[i] = float2fix(sin(6.283 * ((float)(i) / NUM_SAMPLES)));
    }
}

void powerCalculation(fix *input, float *output)
{

    int inputSize = sizeof(input) / sizeof(input[0]);

    int binSize = FFT_SIZE / 8;

    int bins = 8;

    // First loop does the calculation for each bin.
    for (int i = 0; i < bins; i++)
    {

        // Second Loop calculates the power in a frequency bin.
        int sum = 0;

        // The offset is used to select the bin that we are in for the elements.
        int offset = i * binSize;

        for (int j = 0; j < binSize; j++)
        {
            int k = input[j + offset];

            // Get the total Sum of the elements in the array for a total offset.
            if (k > 0)
            {
                sum = sum + k;
            }
            else
            {
                sum = sum - k;
            }
        }

        // Get the power in a single bin.
        int power = sum / bins;

        // Set the current bin as the total power calculation.
        output[i] = power;
    }
}

void normalizePower(float* input)
{
    for(int i = 0; i < 8; i++)
    {
        float k = input[i];

        if( k < 3)
        {
            input[i] = 0;
        }
        else if(k < 5)
        {
            input[i] = 1;
        }

    }
}