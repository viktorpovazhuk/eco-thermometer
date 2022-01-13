/*
 * i2c.c
 *
 *  Created on: Jan 11, 2022
 *      Author: vityha
 */


#include "i2c.h"

void initI2C()
{
    UCB0CTLW0 = UCSWRST;                      // Enable SW reset
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCSSEL__SMCLK | UCSYNC; // I2C master mode, SMCLK
    UCB0BRW = 10;                            // fSCL = SMCLK/10 = ~100kHz
    UCB0CTLW0 &= ~UCSWRST;                    // Clear SW reset, resume operation
    UCB0IE |= UCNACKIE;
}
