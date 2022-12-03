// Source code for 8x8 Matrix interfacing.
#include <Arduino.h>
#include "spi.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define DDR_SPI DDRB      // Data Direction Register on ATMEGA2560 for SPI is DDRB
#define DD_SS DDB0        // SS Chip Select data direction bit B0 of ATMEGA2560 is DDB0
#define DD_SCK DDB1       // Clock pin connection data direction bit B1 on ATMEGA2560 is DDB1
#define DD_MOSI DDB2      // MOSI pin datadirection on ATMEGA2560 is DDB0
#define SPI_PORT PORTB    // PortB for SPI on ATMEGA2560 is PORTB
#define SPI_SS_BIT PORTB0 // Port B register Bit B0 of Chip Select on ATMEGA2560 is PORTB0

#define wait_for_complete         \
    while (!(SPSR & (1 << SPIF))) \
        ;

void SPI_MASTER_Init()
{
    // set MOSI,SCK,and SS direction to outputs
    DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);

    // note this program does not use MISO line. IT only writes to device

    // set SS high initially (chip select off)
    SPI_PORT |= (1 << SPI_SS_BIT);

    // enable SPI, master mode, CPOL, CPHA, default clock and fosc/128
    // datasheet says sample on rising edge CPOL = 1 CPHA =1
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA) | (1 << SPR1) | (1 << SPR0);
}

void write_execute(unsigned char CMD, unsigned char data)
{
    SPI_PORT &= ~(1 << SPI_SS_BIT); // enable chip select bit to begin SPI frame
    SPDR = CMD;                     // load the CMD address into register
    wait_for_complete;              // wait for flag to raise
    SPDR = data;                    // load the data into register
    wait_for_complete;              // wait for flag to raise
    SPI_PORT |= (1 << SPI_SS_BIT);  // disable chip select to end SPI frame
}

void disp_spectrum(int inputlevels[7])
{
    byte outputlevels[7];
    for (int i = 0; i < 8; i++)
    {
        switch (inputlevels[i])
        {
        case 0:
            outputlevels[i] = 0;
            break;

        case 1:
            outputlevels[i] = 128;
            break;

        case 2:
            outputlevels[i] = 192;
            break;

        case 3:
            outputlevels[i] = 224;
            break;

        case 4:
            outputlevels[i] = 240;
            break;

        case 5:
            outputlevels[i] = 248;
            break;

        case 6:
            outputlevels[i] = 252;
            break;

        case 7:
            outputlevels[i] = 254;
            break;

        case 8:
            outputlevels[i] = 255;
            break;

        default:
            outputlevels[i] = 0;
            break;
        }
    }
    display(outputlevels);
}

void display(byte input[7])
{

    write_execute(0x01, input[0]); // all LEDS in Row 1 are off
    write_execute(0x02, input[1]); // row 2 LEDS
    write_execute(0x03, input[2]); // row 3 LEDS
    write_execute(0x04, input[3]); // row 4 LEDS
    write_execute(0x05, input[4]); // row 5 LEDS
    write_execute(0x06, input[5]); // row 6 LEDS
    write_execute(0x07, input[6]); // row 7 LEDS
    write_execute(0x08, input[7]); // row 8 LEDS
}

void init_SPI()
{
    SPI_MASTER_Init(); // initialize SPI module and set the data rate
    // initialize 8 x 8 LED array (info from MAX7219 datasheet)
    write_execute(0x0A, 0x08); // brightness control
    write_execute(0x0B, 0x07); // scanning all rows and columns
    write_execute(0x0C, 0x01); // set shutdown register to normal operation (0x01)
    write_execute(0x0F, 0x00); // display test register - set to normal operation (0x01)
}

/*
 * Input: array pointer to an array with 8 indexes.
 * Purpose: Sets display of matrix to larger light up more of each column
 * whenever there is more power in an index.
 * Lower frequency bins (20 Hz - 100 Hz) will be in index[0], higher
 * frequency bins (15kHz - 20kHz) will be in index[7].
 *
 */
void displayArray(float *array)
{

    for (int i = 0; i < 8; i++)
    {
        printf("Value: %.1f\n", array[i]);
    }
    
    printf("Incmenting Array\n");
    for (int i = 0; i < 8; i++)
    {
        array[i] = array[i] + 1;
        printf("Value: %.1f\n", array[i]);
    }
}


// Here is some code that will display the function in action.
// You can run it at https://www.onlinegdb.com/online_c_compiler 
/*
#include <stdio.h>
void displayArray(float *array)
{

    for (int i = 0; i < 8; i++)
    {
        printf("Value: %.1f\n", array[i]);
    }
    
    printf("Incmenting Array\n");
    for (int i = 0; i < 8; i++)
    {
        array[i] = array[i] + 1;
        printf("Value: %.1f\n", array[i]);
    }
}

int main()
{
    // This array holds the power in each of the 8 frequency bins.
    float powerArray[8] = {1.2, 3.1, 4.4, 4.5, 3.2, 4.5, 5.2, 2.1};
    
    
    
    displayArray(powerArray);
    
    printf("Back in main, looking at values\n");
    for (int i = 0; i < 8; i++)
    {
        printf("Value: %.1f\n", powerArray[i]);
    }
    
    return 0;
}
*/