/* --COPYRIGHT--,BSD
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430FR2433 Demo - I2C sensors for building automation
//
//  Description: this code example using FLL to stabilize the DCO at 16MHz.
//  It Use MSP430 to communicate with 3 I2C sensors, including HDC2080, TMP117
//  and OPT3001, through I2C.
//
//           MSP430FR2433
//         ---------------
//        |               |
//     /|\|               |
//      | |               |
//      --|RST            |
//        |           P1.3|<-- SCL
//        |           P1.2|<-- SDA
//        |               |
//
//   Eason Zhou
//   Texas Instruments Inc.
//   April 2021
//   Built with IAR Embedded Workbench v7.10 & Code Composer Studio v10.1
//******************************************************************************
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "i2c_driver.h"
//#include "sensor_communication.h"
#include "BME280I2C.h"
#include "driverlib.h"
#include "Board.h"
#include "uartlib.h"


/* Local Function Prototypes */
void initClockTo1MHz();
void initGPIO();
void initI2C();
void Software_Trim();                       // Software Trim to get the best DCOFTRIM value

void printBME280Data();

#define MCLK_FREQ_MHZ 1                     // MCLK = 1MHz

BME280I2C bme;

#define STR_LEN 100

char str[STR_LEN];

// main.c
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                                     // Stop watchdog timer

    initClockTo1MHz();
    initGPIO();
    initI2C();
    initUart();

    __bis_SR_register(GIE);  // Enable global interrupts

    //for clocks to stable
    _delay_cycles(10000);

    while (!bme.begin())
      {
        sprintf(str, "BME failed!\r\n");
        sendUartMsg(str);
        __delay_cycles(100000);
      }

    printBME280Data();

    sprintf(str, "Success!\r\n");
                    sendUartMsg(str);

    while (1) {

                __delay_cycles(10000);

    }

    return 0;
}

void printBME280Data()
{
  float temp(0), hum(0), pres(0);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  int32_t data[8];
  uint8_t out_dig[32];

  bme.read(pres, temp, hum, tempUnit, presUnit, data);
  bme.readDig(out_dig);

  sprintf(str, "Raw data: ");
    sendUartMsg(str);
    for (int i = 0; i < 8; ++i)
    {
        sprintf(str, "%d ", ((uint32_t*)data)[i]);
        sendUartMsg(str);
        __delay_cycles(1000);
    }
    sprintf(str, "\r\n");
      sendUartMsg(str);

      sprintf(str, "Dig: ");
          sendUartMsg(str);
          for (int i = 0; i < 32; ++i)
          {
              sprintf(str, "%d ", out_dig[i]);
              sendUartMsg(str);
              __delay_cycles(1000);
          }
          sprintf(str, "\r\n");
            sendUartMsg(str);

//  Serial.print("Raw data: ");
//  for (int i = 0; i < 8; i++)
//  {
//    Serial.print(data[i], HEX);
//    Serial.print(" ");
//  }
//  Serial.println();
//
//  Serial.print("Dig: ");
//  for (int i = 0; i < 32; i++)
//  {
//    Serial.print(out_dig[i], HEX);
//    Serial.print(" ");
//  }
//  Serial.println();
}

void initClockTo1MHz()
{
//    //Set ACLK = REFOCLK with clock divider of 1
//              CS_initClockSignal(CS_ACLK,CS_REFOCLK_SELECT,CS_CLOCK_DIVIDER_1);
//              //Set SMCLK = DCO with frequency divider of 1
//              CS_initClockSignal(CS_SMCLK,CS_DCOCLKDIV_SELECT,CS_CLOCK_DIVIDER_1);
//              //Set MCLK = DCO with frequency divider of 1
//              CS_initClockSignal(CS_MCLK,CS_DCOCLKDIV_SELECT,CS_CLOCK_DIVIDER_1);

    __bis_SR_register(SCG0);                // Disable FLL
      CSCTL3 = SELREF__REFOCLK;               // Set REFO as FLL reference source
      CSCTL1 = DCOFTRIMEN | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_0;// DCOFTRIM=3, DCO Range = 1MHz
      CSCTL2 = FLLD_0 + 30;                   // DCODIV = 1MHz
      __delay_cycles(3);
      __bic_SR_register(SCG0);                // Enable FLL
      Software_Trim();                        // Software Trim to get the best DCOFTRIM value
      CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK; // set default REFO(~32768Hz) as ACLK source, ACLK = 32768Hz
//                                                  default DCODIV as MCLK and SMCLK source


}

void initGPIO()
{
    // I2C pins
    P1SEL0 |= BIT2 | BIT3;
    P1SEL1 &= ~(BIT2 | BIT3);

    // Configure UART pins
    P1SEL0 |= BIT4 | BIT5;                    // set 2-UART pin as second function

    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_UCA0TXD,
        GPIO_PIN_UCA0TXD,
        GPIO_FUNCTION_UCA0TXD
    );
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_UCA0RXD,
        GPIO_PIN_UCA0RXD,
        GPIO_FUNCTION_UCA0RXD
    );

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
}

void initI2C()
{
    UCB0CTLW0 = UCSWRST;                      // Enable SW reset
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCSSEL__SMCLK | UCSYNC; // I2C master mode, SMCLK
    UCB0BRW = 10;                            // fSCL = SMCLK/10 = ~100kHz
//    UCB0I2CSA = SLAVE_ADDR;                   // Slave Address
    UCB0CTLW0 &= ~UCSWRST;                    // Clear SW reset, resume operation
    UCB0IE |= UCNACKIE;
}

void Software_Trim()
{
    unsigned int oldDcoTap = 0xffff;
    unsigned int newDcoTap = 0xffff;
    unsigned int newDcoDelta = 0xffff;
    unsigned int bestDcoDelta = 0xffff;
    unsigned int csCtl0Copy = 0;
    unsigned int csCtl1Copy = 0;
    unsigned int csCtl0Read = 0;
    unsigned int csCtl1Read = 0;
    unsigned int dcoFreqTrim = 3;
    unsigned char endLoop = 0;

    do
    {
        CSCTL0 = 0x100;                         // DCO Tap = 256
        do
        {
            CSCTL7 &= ~DCOFFG;                  // Clear DCO fault flag
        }while (CSCTL7 & DCOFFG);               // Test DCO fault flag

        __delay_cycles((unsigned int)3000 * MCLK_FREQ_MHZ);// Wait FLL lock status (FLLUNLOCK) to be stable
                                                           // Suggest to wait 24 cycles of divided FLL reference clock
        while((CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)) && ((CSCTL7 & DCOFFG) == 0));

        csCtl0Read = CSCTL0;                   // Read CSCTL0
        csCtl1Read = CSCTL1;                   // Read CSCTL1

        oldDcoTap = newDcoTap;                 // Record DCOTAP value of last time
        newDcoTap = csCtl0Read & 0x01ff;       // Get DCOTAP value of this time
        dcoFreqTrim = (csCtl1Read & 0x0070)>>4;// Get DCOFTRIM value

        if(newDcoTap < 256)                    // DCOTAP < 256
        {
            newDcoDelta = 256 - newDcoTap;     // Delta value between DCPTAP and 256
            if((oldDcoTap != 0xffff) && (oldDcoTap >= 256)) // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim--;
                CSCTL1 = (csCtl1Read & (~(DCOFTRIM0+DCOFTRIM1+DCOFTRIM2))) | (dcoFreqTrim<<4);
            }
        }
        else                                   // DCOTAP >= 256
        {
            newDcoDelta = newDcoTap - 256;     // Delta value between DCPTAP and 256
            if(oldDcoTap < 256)                // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim++;
                CSCTL1 = (csCtl1Read & (~(DCOFTRIM0+DCOFTRIM1+DCOFTRIM2))) | (dcoFreqTrim<<4);
            }
        }

        if(newDcoDelta < bestDcoDelta)         // Record DCOTAP closest to 256
        {
            csCtl0Copy = csCtl0Read;
            csCtl1Copy = csCtl1Read;
            bestDcoDelta = newDcoDelta;
        }

    }while(endLoop == 0);                      // Poll until endLoop == 1

    CSCTL0 = csCtl0Copy;                       // Reload locked DCOTAP
    CSCTL1 = csCtl1Copy;                       // Reload locked DCOFTRIM
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked
}
