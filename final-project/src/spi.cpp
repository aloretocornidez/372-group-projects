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

    clear();
}

void testDisplay(float *input)
{

    // Data array to set the power of the signal.
    byte level[8] = {0b10000000, 0b11000000, 0b11100000, 0b11110000, 0b11111000, 0b11111100, 0b11111110, 0b11111111};

    // An array to load the column that will be printed to.
    int column[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    // The thresholds that decides how much of each column will be lit up.
    float divisions[8] = {100, 200, 300, 400, 500, 600, 700, 800};

    for (int i = 0; i < 8; i++)
    {
        if (input[i] < divisions[0])
        {
            write_execute(column[i], level[0]);
        }
        else if (input[i] < divisions[1])
        {
            write_execute(column[i], level[1]);
        }
        else if (input[i] < divisions[2])
        {
            write_execute(column[i], level[2]);
        }
        else if (input[i] < divisions[3])
        {
            write_execute(column[i], level[3]);
        }
        else if (input[i] < divisions[4])
        {
            write_execute(column[i], level[4]);
        }
        else if (input[i] < divisions[5])
        {
            write_execute(column[i], level[5]);
        }
        else if (input[i] < divisions[6])
        {
            write_execute(column[i], level[6]);
        }
        else if (input[i] < divisions[7])
        {
            write_execute(column[i], level[7]);
        }
        else
        {
            write_execute(column[i], level[0]);
        }
    }
}

// Clears the array to prepare data.
void clear()
{
    write_execute(0x01, 0b00000000); // all LEDS in Row 1 are off
    write_execute(0x02, 0b00000000); // row 2 LEDS
    write_execute(0x03, 0b00000000); // row 3 LEDS
    write_execute(0x04, 0b00000000); // row 4 LEDS
    write_execute(0x05, 0b00000000); // row 5 LEDS
    write_execute(0x06, 0b00000000); // row 6 LEDS
    write_execute(0x07, 0b00000000); // row 7 LEDS
    write_execute(0x08, 0b00000000); // row 8 LEDS
}
