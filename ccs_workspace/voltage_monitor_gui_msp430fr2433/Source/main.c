/* --COPYRIGHT--,BSD-3-Clause
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
//  Voltage Monitor with a Timestamp
//
//  Description: A voltage monitor based on the ADC window comparator with
//               internal 1.5V reference. Timer1_A3 is used as an interval timer
//               used to trigger the ADC samples. The MSP430 uses the RTC
//               counter module to increment the timestamp and toggle LED1 every
//               1 second. Use the UART to set an initial time after startup and
//               the RTC will increment from there. The timestamp is in the
//               POSIX time format. The timestamp can be read out over UART by
//               a host microcontroller or processor, so the MSP430 is
//               functioning as an external RTC to keep time. If the input
//               voltage on the ADC input is higher or lower than the window
//               comparator thresholds, that timestamp will be stored in FRAM,
//               so it will be retained through a power loss. Both window
//               comparator thresholds can be read out and changed over UART.
//
//  --------------------------------------------------------------------------
//  UART Communication Protocol (only applicable for standalone mode)
//  --------------------------------------------------------------------------
//  [COMMAND] <data> <data> <data> <data>
//
//  COMMANDS:                                     RESPONSES:
//  RTC_READ_TIME =      00h                      00h XXh XXh XXh XXh
//  RTC_WRITE_TIME =     01h XXh XXh XXh XXh
//  RTC_READ_THR_HIGH =  02h                      02h XXh XXh XXh XXh
//  RTC_READ_THR_LOW =   03h                      03h XXh XXh XXh XXh
//  ADC_READ_THR_HIGH =  04h                      04h XXh XXh
//  ADC_READ_THR_LOW =   05h                      05h XXh XXh
//  ADC_WRITE_THR_HIGH = 06h XXh XXh
//  ADC_WRITE_THR_LOW =  07h XXh XXh
//
//  --------------------------------------------------------------------------
//  Clock configuration
//  --------------------------------------------------------------------------
//  ACLK = default REFO ~32768Hz, SMCLK = MCLK = 16MHz
//
//  At this speed, the FRAM requires wait states. FLL reference clock is REFO.
//  XT1 can be used for ACLK if crystal selection resistors on LaunchPad are
//  changed and __ENABLE_XT1__ is added to Predefined Symbols in the compiler
//  settings.
//
//  --------------------------------------------------------------------------
//
//           MSP430FR2433
//         ---------------
//     /|\|           P1.0|---> LED1
//      | |               |
//      --| RST    P1.1/A1|<--- Voltage monitoring
//        |               |
//        |   P1.4/UCA0TXD|---> PC
//        |   P1.5/UCA0RXD|<--- PC
//        |               |
//
//
//  James Evans
//  Texas Instruments Inc.
//  October 2020
//  Built with Code Composer Studio v10.1
//******************************************************************************

// #includes for header files
#include <msp430.h>
#include <stdint.h>
#ifdef __ENABLE_GUI__
#include <Include/GUI.h>
#include <Include/HAL.h>
#include <Include/GUIComm.h>
#include <Include/callbacks.h>
#endif

#ifndef __ENABLE_GUI__
// #defines for communication protocol commands
#define RTC_READ_TIME        0      // Reads current timestamp
#define RTC_WRITE_TIME       1      // Sets new timestamp
#define RTC_READ_THR_HIGH    2      // Reads latest high threshold timestamp
#define RTC_READ_THR_LOW     3      // Reads latest low threshold timestamp
#define ADC_READ_THR_HIGH    4      // Reads current high threshold value
#define ADC_READ_THR_LOW     5      // Reads current low threshold value
#define ADC_WRITE_THR_HIGH   6      // Sets new high threshold value
#define ADC_WRITE_THR_LOW    7      // Sets new low threshold value

// #defines for initial window comparator voltage thresholds
#define ADC_THR_HIGH_MAX     1023   // Maximum high threshold
#define ADC_THR_HIGH_INIT    818    // (818 / 1023) x VREF = ~1.2V, VREF = 1.5V
#define ADC_THR_LOW_INIT     682    // (682 / 1023) x VREF = ~1.0V, VREF = 1.5V
#endif

// Data to be stored in FRAM and retained through power loss
// timeStamp values are in POSIX time format (# of seconds since midnight 1 Jan. 1970)
// User needs to set the starting time with the RTC_WRITE_TIME command
// (01h XXh XXh XXh XXh)
// RTC_READ_TIME command is answered by echoing command and sending timeStamp, LSB first (timeStamp[0])
// (00h XXh XXh XXh XXh)
#pragma PERSISTENT (timeStampThrHighFRAM)
#pragma PERSISTENT (timeStampThrLowFRAM)
uint8_t timeStampThrHighFRAM[4] = {0};
uint8_t timeStampThrLowFRAM[4] = {0};

// Global variables
volatile uint8_t command, data, byteCount, sendTimeStampThrHigh, sendTimeStampThrLow;
volatile uint8_t timeStamp[4] = {0};
volatile uint8_t voltageThr[2] = {0};
volatile uint16_t voltageThrHigh, voltageThrLow, voltageThrNew;
#ifdef __ENABLE_GUI__
volatile uint32_t timeStampNew;
#endif

// Function prototypes
void GPIO_Init();
void ADC_Disable();
void ADC_Configure(uint16_t hiThr, uint16_t loThr);
void ADC_Enable();
void UART_sendByte(uint8_t txByte);

#ifdef __ENABLE_GUI__
//! \brief RX Command structure.
//!         The corresponding callback will be called when the command is
//!         received from GUI.
//! Note: Shorter command names take less time to process
const tGUI_RxCmd GUI_RXCommands[] =
{
    {"getRTC",   GUICallback_GetRTCData},
    {"setRTC",   GUICallback_SetRTCData},
    {"getRTCHi", GUICallback_GetRTCHiData},
    {"getRTCLo", GUICallback_GetRTCLoData},
    {"getADCHi", GUICallback_GetADCHiData},
    {"getADCLo", GUICallback_GetADCLoData},
    {"setADCHi", GUICallback_SetADCHiData},
    {"setADCLo", GUICallback_SetADCLoData},
};
#endif

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;              // Stop watchdog timer

    // Initialize variables
    byteCount = 0;                         // Clear byteCount
    voltageThrHigh = ADC_THR_HIGH_INIT;    // Set initial window comparator high threshold
    voltageThrLow = ADC_THR_LOW_INIT;      // Set initial window comparator low threshold

    // Configure pin functions
    P1SEL0 |= BIT4 | BIT5;                 // UCA0 TXD, RXD
    SYSCFG2 |= ADCPCTL1;                   // ADC A1

    // Initialize pins
    GPIO_Init();

#ifdef __ENABLE_XT1__
    // Configure XT1
    P2SEL0 |= BIT0 | BIT1;                 // Set XT1 pins as second function
    do
    {
        CSCTL7 &= ~(XT1OFFG | DCOFFG);     // Clear XT1 and DCO fault flags
        SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1 & OFIFG);              // Test oscillator fault flag
#endif

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure one FRAM waitstate as required by the device datasheet for MCLK
    // operation beyond 8MHz _before_ configuring the clock system
    FRCTL0 = FRCTLPW | NWAITS_1;

    // Configure MCLK for 16MHz operation
    __bis_SR_register(SCG0);                      // Disable FLL
    CSCTL3 |= SELREF__REFOCLK;                    // Set REFO as FLL reference source
    CSCTL0 = 0;                                   // clear DCO and MOD registers
    CSCTL1 &= ~(DCORSEL_7);                       // Clear DCO frequency select bits first
    CSCTL1 |= DCORSEL_5;                          // Set DCO = 16MHz
    CSCTL2 = FLLD_0 + 487;                        // DCOCLKDIV = 16MHz
    __delay_cycles(3);
    __bic_SR_register(SCG0);                      // Enable FLL
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1));    // Delay until FLL has locked
#ifdef __ENABLE_XT1__
    CSCTL4 = SELMS__DCOCLKDIV | SELA__XT1CLK;     // Set default DCOCLKDIV as MCLK and SMCLK source;
                                                  // Set XT1 (~32768Hz) as ACLK source
#else
    CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK;    // Set default DCOCLKDIV as MCLK and SMCLK source;
#endif                                            // Set default REFO (~32768Hz) as ACLK source

    // Configure UART
    // Refer to Typical Baud Rates Table in User's Guide, 9600 baud at BRCLK = 16000000Hz
    // UCOS16 = 1
    // UCBRx = 104
    // UCBRFx = 2
    // UCBRSx = 0xD6
    UCA0CTLW0 = UCSWRST | UCSSEL__SMCLK;          // Reset eUSCI; BRCLK = SMCLK
    UCA0BRW = 104;
    UCA0MCTLW = 0xD600 | UCBRF_2 | UCOS16;
    UCA0CTLW0 &= ~UCSWRST;                        // Initialize eUSCI
    UCA0IE = UCRXIE;                              // Enable USCI_A0 RX interrupt

    // Configure RTC
#ifdef __ENABLE_XT1__
    RTCMOD = 32768-1;                             // RTC count re-load compare value at XT1CLK for ~1s interrupt
    RTCCTL = RTCSS__XT1CLK | RTCSR |              // Clock source = XT1CLK; Real-time software reset
            RTCPS__1 | RTCIE;                     // Pre-divide by 1 (default); Enable RTC interrupts
#else
    RTCMOD = 16000-1;                             // RTC count re-load compare value at SMCLK/1000 for ~1s interrupt
    RTCCTL = RTCSS__SMCLK | RTCSR |               // Clock source = SMCLK; Real-time software reset
             RTCPS__1000 | RTCIE;                 // Pre-divide by 1000; Enable RTC interrupts
#endif

    // Configure internal reference (1.5V)
    PMMCTL0_H = PMMPW_H;                          // Unlock PMM registers
    PMMCTL2 |= INTREFEN;                          // Enable internal reference
    while(!(PMMCTL2 & REFGENRDY));                // Delay until internal reference has settled

    // Configure ADC window comparator
    ADC_Disable();                                // Disable ADC
    ADC_Configure(voltageThrHigh, voltageThrLow); // Configure ADC

    // Configure ADC timer trigger TA1.1
    TA1CCR0 = 16384-1;                            // PWM period = 16384/32768 = ~0.5s
    TA1CCR1 = 8192-1;                             // TA1.1 duty cycle = ~50%
    TA1CCTL1 = OUTMOD_3;                          // TA1CCR1 set/reset mode
    TA1CTL = TASSEL__ACLK | MC_1 | TACLR;         // Clock source = ACLK; Up mode; Clear counter
    ADC_Enable();                                 // Enable ADC

#ifdef __ENABLE_GUI__
    GUI_Init();                                   // Initialize GUI layer
    GUI_InitRxCmd( &GUI_RXCommands[0],(sizeof(GUI_RXCommands)/sizeof(GUI_RXCommands[0])) );  // Initialize GUI receive

    // Send initial values to GUI
    GUIComm_sendUInt32("setRTC", 6, 0);                 // Send initial timestamp to GUI
    GUIComm_sendUInt16("setADCHi", 8, voltageThrHigh);  // Send initial high threshold to GUI
    GUIComm_sendUInt16("setADCLo", 8, voltageThrLow);   // Send initial low threshold to GUI
    GUIComm_sendUInt32("rtc1", 4, *(uint32_t*)timeStampThrHighFRAM);  // Send timestamp stored in FRAM for high threshold to GUI
    GUIComm_sendUInt32("rtc2", 4, *(uint32_t*)timeStampThrLowFRAM);   // Send timestamp stored in FRAM for low threshold to GUI
#endif

    // Communication state machine
    while(1)
    {
        __bis_SR_register(LPM0_bits | GIE);       // Enter LPM0, enable interrupts
        __no_operation();                         // For debugger only

        // 1st byte received (command byte)
        if(byteCount == 1)
        {
#ifndef __ENABLE_GUI__
            command = data;                       // Store command byte
#endif

            // RTC_READ_TIME command
            if(command == RTC_READ_TIME)
            {
                // Send current timestamp
#ifdef __ENABLE_GUI__
                GUIComm_sendUInt32("setRTC", 6, *(uint32_t*)timeStamp);
#else
                UART_sendByte(RTC_READ_TIME);     // Echo command byte
                UART_sendByte(timeStamp[0]);      // LSB to MSB
                UART_sendByte(timeStamp[1]);
                UART_sendByte(timeStamp[2]);
                UART_sendByte(timeStamp[3]);
#endif
                byteCount = 0;                    // No further bytes to receive for this command
            }

            // RTC_READ_THR_HIGH command
            else if(command == RTC_READ_THR_HIGH)
            {
                // Send timestamp for window comparator high threshold
#ifdef __ENABLE_GUI__
                GUIComm_sendUInt32("rtc1", 4, *(uint32_t*)timeStampThrHighFRAM);
#else
                UART_sendByte(RTC_READ_THR_HIGH);               // Echo command byte
                UART_sendByte(timeStampThrHighFRAM[0]);         // LSB to MSB
                UART_sendByte(timeStampThrHighFRAM[1]);
                UART_sendByte(timeStampThrHighFRAM[2]);
                UART_sendByte(timeStampThrHighFRAM[3]);
#endif
                byteCount = 0;                                  // No further bytes to receive for this command
            }

            // RTC_READ_THR_LOW command
            else if(command == RTC_READ_THR_LOW)
            {
                // Send timestamp for window comparator low threshold
#ifdef __ENABLE_GUI__
                GUIComm_sendUInt32("rtc2", 4, *(uint32_t*)timeStampThrLowFRAM);
#else
                UART_sendByte(RTC_READ_THR_LOW);                // Echo command byte
                UART_sendByte(timeStampThrLowFRAM[0]);          // LSB to MSB
                UART_sendByte(timeStampThrLowFRAM[1]);
                UART_sendByte(timeStampThrLowFRAM[2]);
                UART_sendByte(timeStampThrLowFRAM[3]);
#endif
                byteCount = 0;                                  // No further bytes to receive for this command
            }

            // ADC_READ_THR_HIGH command
            else if(command == ADC_READ_THR_HIGH)
            {
                // Send existing window comparator high threshold
#ifdef __ENABLE_GUI__
                GUIComm_sendUInt16("setADCHi", 8, voltageThrHigh);
#else
                UART_sendByte(ADC_READ_THR_HIGH);               // Echo command byte
                UART_sendByte(voltageThrHigh & 0xFF);           // LSB to MSB
                UART_sendByte(voltageThrHigh >> 8);
#endif
                byteCount = 0;                                  // No further bytes to receive for this command
            }

            // ADC_READ_THR_LOW command
            else if(command == ADC_READ_THR_LOW)
            {
                // Send existing window comparator low threshold
#ifdef __ENABLE_GUI__
                GUIComm_sendUInt16("setADCLo", 8, voltageThrLow);
#else
                UART_sendByte(ADC_READ_THR_LOW);                // Echo command byte
                UART_sendByte(voltageThrLow & 0xFF);            // LSB to MSB
                UART_sendByte(voltageThrLow >> 8);
#endif
                byteCount = 0;                                  // No further bytes to receive for this command
            }

#ifndef __ENABLE_GUI__
            // Error handler for unsupported commands
            else if(command > ADC_WRITE_THR_LOW)
            {
                byteCount = 0;                                  // No further bytes to receive for this command
            }
#endif
        }

        // 2nd through 5th byte received (data bytes)
        else if((byteCount >= 2) && (byteCount <= 5))
        {
            // RTC_WRITE_TIME command
            if(command == RTC_WRITE_TIME)
            {
                // Update timestamp
#ifndef __ENABLE_GUI__
                timeStamp[byteCount - 2] = data;                // LSB to MSB
#endif
                if(byteCount == 5)
                {
#ifdef __ENABLE_GUI__
                    timeStamp[0] = timeStampNew & 0xFF;         // LSB to MSB
                    timeStamp[1] = timeStampNew >> 8;
                    timeStamp[2] = timeStampNew >> 16;
                    timeStamp[3] = timeStampNew >> 24;
#endif
                    byteCount = 0;                              // No further bytes to receive for this command
                }
            }

            // ADC_WRITE_THR_HIGH command
            else if(command == ADC_WRITE_THR_HIGH)
            {
                // Receive new window comparator high threshold
#ifndef __ENABLE_GUI__
                voltageThr[byteCount - 2] = data;               // LSB to MSB
#endif
                if(byteCount == 3)
                {
#ifndef __ENABLE_GUI__
                    voltageThrNew = (voltageThr[1] << 8) | (voltageThr[0]);     // Concatenate the two bytes
#endif
                    // Check if new high threshold exceeds max value
                    if(voltageThrNew > ADC_THR_HIGH_MAX)
                    {
                        voltageThrHigh = ADC_THR_HIGH_MAX;                      // If so, limit high threshold to max value
#ifdef __ENABLE_GUI__
                        GUIComm_sendUInt16("setADCHi", 8, voltageThrHigh);      // Update high threshold in GUI
#endif
                    }

                    // Make sure new high threshold is greater than low threshold
                    else if(voltageThrNew > voltageThrLow)
                    {
                        voltageThrHigh = voltageThrNew;                         // If so, update high threshold

                        // Re-configure ADC window comparator
                        ADC_Disable();                                          // Disable ADC
                        ADC_Configure(voltageThrHigh, voltageThrLow);           // Apply new threshold
                        ADC_Enable();                                           // Enable ADC
                    }
#ifdef __ENABLE_GUI__
                    // If the new high threshold is lower than or equal to the low threshold, keep existing value
                    else
                    {
                        GUIComm_sendUInt16("setADCHi", 8, voltageThrHigh);      // Correct high threshold in GUI
                    }
#endif
                    byteCount = 0;                                              // No further bytes to receive for this command
                }
            }

            // ADC_WRITE_THR_LOW command
            else if(command == ADC_WRITE_THR_LOW)
            {
                // Receive new window comparator low threshold
#ifndef __ENABLE_GUI__
                voltageThr[byteCount - 2] = data;                               // LSB to MSB
#endif
                if(byteCount == 3)
                {
#ifndef __ENABLE_GUI__
                    voltageThrNew = (voltageThr[1] << 8) | (voltageThr[0]);     // Concatenate the two bytes
#endif
                    // Make sure new low threshold is less than high threshold
                    if(voltageThrNew < voltageThrHigh)
                    {
                        voltageThrLow = voltageThrNew;                          // If so, update low threshold

                        // Re-configure ADC window comparator
                        ADC_Disable();                                          // Disable ADC
                        ADC_Configure(voltageThrHigh, voltageThrLow);           // Apply new threshold
                        ADC_Enable();                                           // Enable ADC
                    }
#ifdef __ENABLE_GUI__
                    // If the new low threshold is higher than or equal to the high threshold, keep existing value
                    else
                    {
                        GUIComm_sendUInt16("setADCLo", 8, voltageThrLow);       // Correct low threshold in GUI
                    }
#endif
                    byteCount = 0;                                              // No further bytes to receive for this command
                }
            }
        }

        else
        {
            // Automatically send timestamps when window comparator thresholds are exceeded
            if(sendTimeStampThrHigh == 1)
            {
                // Send latest timestamp for high threshold
#ifdef __ENABLE_GUI__
                GUIComm_sendUInt32("rtc1", 4, *(uint32_t*)timeStampThrHighFRAM);
#else
                UART_sendByte(RTC_READ_THR_HIGH);               // Send command byte
                UART_sendByte(timeStampThrHighFRAM[0]);         // LSB to MSB
                UART_sendByte(timeStampThrHighFRAM[1]);
                UART_sendByte(timeStampThrHighFRAM[2]);
                UART_sendByte(timeStampThrHighFRAM[3]);
#endif
                sendTimeStampThrHigh = 0;                       // Clear flag
            }
            else if(sendTimeStampThrLow == 1)
            {
                // Send latest timestamp for low threshold
#ifdef __ENABLE_GUI__
                GUIComm_sendUInt32("rtc2", 4, *(uint32_t*)timeStampThrLowFRAM);
#else
                UART_sendByte(RTC_READ_THR_LOW);                // Send command byte
                UART_sendByte(timeStampThrLowFRAM[0]);          // LSB to MSB
                UART_sendByte(timeStampThrLowFRAM[1]);
                UART_sendByte(timeStampThrLowFRAM[2]);
                UART_sendByte(timeStampThrLowFRAM[3]);
#endif
                sendTimeStampThrLow = 0;                        // Clear flag
            }
        }
    }
}

// Function for configuring GPIOs
void GPIO_Init()
{
    P1DIR = 0xFF; P2DIR = 0xFF; P3DIR = 0xFF;
    P1REN = 0xFF; P2REN = 0xFF; P3REN = 0xFF;
    P1OUT = 0x00; P2OUT = 0x00; P3OUT = 0x00;
}

// Function for disabling ADC
void ADC_Disable()
{
    ADCCTL0 &= ~ADCENC;                           // Disable ADC conversions
}

// Function for configuring ADC and setting window comparator thresholds
void ADC_Configure(uint16_t hiThr, uint16_t loThr)
{
    ADCCTL0 = ADCSHT_2 | ADCON;                   // 16 ADCCLK cycles; Enable ADC core
    ADCCTL1 = ADCSHP | ADCSHS_2 |                 // Pulse sample mode; TA1.1 trigger
    ADCCONSEQ_2 |                                 // Repeat-single-channel mode
    ADCSSEL_1 | ADCDIV_0;                         // ADCCLK = ACLK; Divide by 1
    ADCCTL2 = ADCRES_1;                           // 10-bit conversion result resolution
    ADCMCTL0 = ADCINCH_1 | ADCSREF_1;             // ADC A1 channel; V(R+) = 1.5V VREF, V(R-) = AVSS
    ADCHI = hiThr;                                // Set window comparator high threshold
    ADCLO = loThr;                                // Set window comparator low threshold
    ADCIE |= ADCHIIE | ADCLOIE | ADCINIE;         // Enable ADCHI, ADCLO, ADCIN interrupts
}

// Function for enabling ADC
void ADC_Enable()
{
    ADCCTL0 |= ADCENC;                            // Enable ADC conversions
}

// Function for sending UART byte via polling method
#ifndef __ENABLE_GUI__
void UART_sendByte(uint8_t txByte)
{
    while(!(UCA0IFG & UCTXIFG));                  // Check if ready to TX
    UCA0TXBUF = txByte;                           // Send the data byte
}
#endif

// UART interrupt service routine
#ifndef __ENABLE_GUI__
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:                   // Receive interrupt
            data = UCA0RXBUF;                     // Read received byte
            byteCount++;                          // Increment byte
            __bic_SR_register_on_exit(LPM0_bits); // Wake from LPM
            break;
        case USCI_UART_UCTXIFG: break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
        default: break;
    }
}
#endif

// RTC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(RTC_VECTOR))) RTC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(RTCIV,RTCIV_RTCIF))
    {
        case  RTCIV_NONE:   break;                // No interrupt
        case  RTCIV_RTCIF:                        // RTC Overflow
            P1OUT ^= BIT0;                        // Toggle LED1
            (*(uint32_t*)timeStamp)++;            // Increment timestamp
            break;
        default: break;
    }
}

// ADC interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC_VECTOR))) ADC_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG:
            break;
        case ADCIV_ADCTOVIFG:
            break;
        case ADCIV_ADCHIIFG:                                            // ADCHI; ADC result > ADCTHRHIGH
            ADCIFG &= ~ADCHIIFG;                                        // Clear interrupt flag
            SYSCFG0 = FRWPPW;                                           // Open FRAM for writes to timeStampThrHighFRAM
            *(uint32_t*)timeStampThrHighFRAM = *(uint32_t*)timeStamp;   // Store timestamp in FRAM
            SYSCFG0 = FRWPPW | PFWP;                                    // FRAM write protected (not writable)
            sendTimeStampThrHigh = 1;                                   // Set flag to send timestamp over UART
            __bic_SR_register_on_exit(LPM0_bits);                       // Wake from LPM to send timestamp
            break;
        case ADCIV_ADCLOIFG:                                            // ADCLO; ADC result < ADCTHRLOW
            ADCIFG &= ~ADCLOIFG;                                        // Clear interrupt flag
            SYSCFG0 = FRWPPW;                                           // Open FRAM for writes to timeStampThrLowFRAM
            *(uint32_t*)timeStampThrLowFRAM = *(uint32_t*)timeStamp;    // Store timestamp in FRAM
            SYSCFG0 = FRWPPW | PFWP;                                    // FRAM write protected (not writable)
            sendTimeStampThrLow = 1;                                    // Set flag to send timestamp over UART
            __bic_SR_register_on_exit(LPM0_bits);                       // Wake from LPM to send timestamp
            break;
        case ADCIV_ADCINIFG:                                            // ADCIN; ADCTHRLOW < ADC result < ADCTHRHIGH
            ADCIFG &= ~ADCINIFG;                                        // Clear interrupt flag
            break;
        case ADCIV_ADCIFG:
            break;
        default:
            break;
    }
}
