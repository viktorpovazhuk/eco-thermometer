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
//  Calendar and Tamper Detect using MSP430 MCUs
//
//  --------------------------------------------------------------------------
//  Description
//  --------------------------------------------------------------------------
//  This example implements two functions. One is calendar, which is realized by
//  RTC module and Real-Time-Clock Library. RTC module triggers an interrupt
//  every second, calling library functions to update the calendar. The ohter
//  one is tamper detect. When a tamper event is detected in P2.3, An interrupt
//  is triggered, and the time stamp is stored to FRAM, while P1.0 is set up to
//  light up the LED. At other times, the MCU works in low-power mode(LPM) 3.5.
//
//  Port P2.7 is used to be triggered to enter the calendar editable mode.
//  In the calendar editable mode, the microcontroller remains active, waiting
//  to receive data from the host. Until the finish editing command is received,
//  it will return to the non-editable calendar mode and enter low power mode.
//  LED of P1.1 shows the status of calendar edit mode.
//
//  By using the compute through power loss (CTPL) library the original example
//  code is greatly simplified. The peripherals are initialized once at the
//  start of the application and the library will save the peripheral and
//  application state in FRAM before entering LPM. Upon wakeup from LPM the
//  peripheral and application state is restored and the code continues
//  execution from the next line of code.
//
//  ACLK = 32.768kHz, MCLK = SMCLK = DCO = ~1MHz
//
//           MSP430FR2433
//         ---------------
//    /|\ |           P1.0|---> tamper warning Status (LED1)
//     |  |           P1.1|---> Status of calendar edit mode (LED2)
//     ---|RST            |
//        |            XIN|-
//        |               | 32kHz
//        |           XOUT|-
//        |               |
//        |   P1.4/UCA0TXD|---> PC
//        |   P1.5/UCA0RXD|<--- PC
//        |               |
//        |           P2.3|<--- tamper detect (S1)
//        |           P2.7|<--- Trigger source for entering editable calendar mode  (S2)
//        |               |
//
//
//  Yuhao Zhao
//  Texas Instruments Inc.
//  June 2021
//  Built with Code Composer Studio v10.3 and IAR Embedded Workbench v7.12.2
//******************************************************************************

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctpl.h>
#include "RTC_Calendar.h"

#if defined(__ENABLE_GUI__)
#include <GUI.h>
#include <HAL.h>
#include <Include/GUIComm.h>
#include <Include/callbacks.h>
#endif

// Declare global variables
volatile bool warn_flg = 0;          // display LED status
volatile bool warn_led = 0;          // tamper detect warning flag
volatile uint8_t commandFlag;
#pragma PERSISTENT(stamp_second)
#pragma PERSISTENT(stamp_minute)
#pragma PERSISTENT(stamp_hour)
#pragma PERSISTENT(stamp_day)
#pragma PERSISTENT(stamp_month)
#pragma PERSISTENT(stamp_year)
#pragma PERSISTENT(stamp_PM)
char stamp_second;      // 0x00 - 0x59
char stamp_minute;      // 0x00 - 0x59
char stamp_hour;        // 0x00 - 0x12
char stamp_day;         // 0x01 - 0x31
char stamp_month;       // 0x00 - 0x11 .. Jan = 0
int  stamp_year;        // 0x0000-0x2399 .. leapyears not computed for 0x2400
char stamp_PM;          // AM = 0, PM = 1

// Function prototypes
void GPIO_Init();
void UART_Init();

#if defined(__ENABLE_GUI__)

 //! \brief RX Command structure.
 //!         The corresponding callback will be called when the command is
 //!         received from GUI.
 //! Note: shorter command names take less time to process
 const tGUI_RxCmd GUI_RXCommands[] =
 {
      {"RT0", GUICallback_Second},
      {"RT1",  GUICallback_Minute},
      {"RT2", GUICallback_Hour},
      {"RT3", GUICallback_Day},
      {"RT4", GUICallback_Month},
      {"RT5", GUICallback_Year},
      {"RT6", GUICallback_PM},
      {"RTD", GUICallback_Timeset_Done},
 };
#endif

// main.c
int main(void)
{
    // Stop internal watchdog timer
    WDTCTL = WDTPW | WDTHOLD;                                     // Stop watchdog timer

    // Initialize variables
    commandFlag = 0;                        // Clear command flag for communication state machine

    // Initialize Calendar
    setDate(2021,6,25);                     // encoded as decimal numbers with Jan = 1 and 1st day = 1, 31st day = 31
    setTime(0x5,0x30,0,1);                  // encoded as BCD chars

    // Initialize ports
    GPIO_Init();                                             // Set all pins as outputs

    // Configure GPIOs
    P1OUT &= ~BIT0;                         // Set P1.0 (Tamper Detect Status) as low (active high)
    P1OUT &= ~BIT1;                         // Set P1.1 (Calendar Edit Enable)  as low
    P1DIR |= BIT0 | BIT1;                   // Set P1.0, P1.1 as outputs
    P2DIR &= ~(BIT3 | BIT7);                // Set P2.3 (tamper detect), P2.7 (set time) as inputs
    P2OUT |= BIT3 | BIT7;                   // Configure P2.3, P2.7 as pulled-up
    P2REN |= BIT3| BIT7;                    // Enable P2.3, P2.7 pull-up resistors
    P2IES |= BIT3 | BIT7;                   // Select P2.3, P2.7 as high-to-low interrupt edge

    // Disable the GPIO power-on default high-impedance
    // mode to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Configure UART pins
    P1SEL0 |= BIT4 | BIT5;                  // Configure P1.4 and P1.5 for UART

#ifdef __ENABLE_XT1__
    // Configure XT1
    P2SEL0 |= BIT0 | BIT1;                  // Set XT1 pins as second function
    do
    {
        CSCTL7 &= ~(XT1OFFG | DCOFFG);      // Clear XT1 and DCO fault flags
        SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1 & OFIFG);               // Test oscillator fault flag
#endif

#if defined(__ENABLE_GUI__)
    // Initialize GUI layer
    GUI_Init();

    // Initialize GUI receive
    GUI_InitRxCmd( &GUI_RXCommands[0],(sizeof(GUI_RXCommands)/sizeof(GUI_RXCommands[0])) );

    // Send the default data
    GUIComm_sendUInt16(  "ST0", 3, 30);
    GUIComm_sendUInt16(  "ST1", 3, 30);
    GUIComm_sendUInt16(  "ST2", 3, 12);
#endif

    // Configure RTC
#ifdef __ENABLE_XT1__
    RTCMOD = 32768-1;
    RTCCTL = RTCSS__XT1CLK | RTCSR;
    RTCCTL |= RTCIE;
#else
    RTCMOD = 10-1;
    RTCCTL = RTCSS__VLOCLK | RTCSR |RTCPS__1024;
    RTCCTL |= RTCIE;
#endif

    // Enable GPIO Interrupts
    P2IFG = 0;                              // Clear all P2 interrupt flags
    P2IE |= BIT3| BIT7;                     // Enable P2.3, P2.7 interrupts

    __enable_interrupt();
    //__bis_SR_register(LPM0_bits | GIE);   // Go to LPM0 with interrupts

    // Communication state machine
    while (1)
    {
        ctpl_enterLpm35(CTPL_DISABLE_RESTORE_ON_RESET);     // Enter into LPM3.5 with restore on reset disabled
        __no_operation();                                   // For debugger only
        while(commandFlag==1)
        {
            __no_operation();                               // For debugger only
        }

    }

}


#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
    uint16_t mid_second,mid_minute,mid_hour,mid_day,mid_month,mid_year;
    switch(__even_in_range(RTCIV, RTCIV_RTCIF)) {
        case RTCIV_NONE : break;
        case RTCIV_RTCIF:
            incrementSeconds();             //update calendar

            // Convert BCD to decimal
            mid_second=(TI_second) / 16*10+(TI_second) % 16;
            mid_minute=(TI_minute) / 16*10+(TI_minute) % 16;
            mid_hour=(TI_hour) / 16*10+(TI_hour) % 16;
            mid_day=(TI_day) / 16*10+(TI_day) % 16;
            mid_month=(TI_month) / 16*10+(TI_month) % 16+1;
            mid_year=(TI_year)/4096*1000+(TI_year)/256%16*100+(TI_year)/16%16*10+(TI_year) % 16;

            UART_Init();

            // Send calendar message to GUI
            GUIComm_sendUInt16(  "TT0", 3, (mid_second));                    // Send ADC value to GUI
            GUIComm_sendUInt16(  "TT1", 3, (mid_minute));
            GUIComm_sendUInt16(  "TT2", 3, (mid_hour));
            GUIComm_sendUInt16(  "TT3", 3, (mid_day));
            GUIComm_sendUInt16(  "TT4", 3, (mid_month));
            GUIComm_sendUInt16(  "TT5", 3, (mid_year));
            GUIComm_sendUInt16(  "TT6", 3, TI_PM);
            GUIComm_sendBool(   "WN", 2, warn_led);                          // Send warning sataus
            GUIComm_sendBool(   "STD", 3, commandFlag);
            GUIComm_sendBool(   "NSTD", 4, (commandFlag==0));

            // Send time stamp to GUI
            if(warn_flg)
            {
                GUIComm_sendUInt16(  "ST0", 3, (mid_second));
                GUIComm_sendUInt16(  "ST1", 3, (mid_minute));
                GUIComm_sendUInt16(  "ST2", 3, (mid_hour));
                GUIComm_sendUInt16(  "ST3", 3, (mid_day));
                GUIComm_sendUInt16(  "ST4", 3, (mid_month));
                GUIComm_sendUInt16(  "ST5", 3, (mid_year));
                GUIComm_sendUInt16(  "ST6", 3, TI_PM);
                warn_flg=0;
            }
            break;
        default: break;
    }
}

// Port 2 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void)
#else
#error Compiler not supported!
#endif
{
    if(P2IFG & BIT3)
    {
    P2IFG &= ~BIT3;                         // Clear P1.3 IFG
    SYSCFG0 = FRWPPW | DFWP;                // Program FRAM write enable
    stamp_second=TI_second;                 // 0x00 - 0x59
    stamp_minute=TI_minute;                 // 0x00 - 0x59
    stamp_hour=TI_hour;                     // 0x00 - 0x12
    stamp_day=TI_day;                       // 0x01 - 0x31
    stamp_month=TI_month;                   // 0x00 - 0x11 .. Jan = 0
    stamp_year=TI_year;                     // 0x0000-0x2399 .. leapyears not computed for 0x2400
    stamp_PM=TI_PM;                         // AM = 0, PM = 1
    SYSCFG0 = FRWPPW | PFWP | DFWP;         // Program FRAM write protected (not writable)

    warn_flg=1;
    warn_led=1;
    if(warn_led)P1OUT |= BIT0;
    }
    if(P2IFG & BIT7)
    {
        P2IFG &= ~BIT7;             // Clear P2.7 interrupt flag
        UART_Init();
        commandFlag=1;
        if(commandFlag)P1OUT |= BIT1;
    }

}

// Function for initializing GPIOs
void GPIO_Init()
{
    P1DIR = 0xFF; P2DIR = 0xFF; P3DIR = 0xFF;
    P1REN = 0xFF; P2REN = 0xFF; P3REN = 0xFF;
    P1OUT = 0x00; P2OUT = 0x00; P3OUT = 0x00;
}

void UART_Init()
{
    // Configure UART 9600 baud
    UCA0CTLW0 |= UCSWRST;                                         // eUSCI_A logic held in reset state.
    UCA0CTLW0 |= UCSSEL__SMCLK;                                   // One stop bit, no parity, LSB first, 8-bit data as the default setting
    UCA0BR0 = 6;                                                  // 1000000/16/9600
    UCA0BR1 = 0x00;
    UCA0MCTLW = 0x2000 | UCOS16 | UCBRF_8;
    UCA0CTLW0 &= ~UCSWRST;                                        // eUSCI_A reset released for operation
    UCA0IE = UCRXIE;                                            // Enable USCI_A0 RX interrupt
}
