/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/tool/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
//******************************************************************************
//  ctpl_ex1_gpio_lpm45 - LPM4.5 With GPIO Wakeup.
// 
//  This example is an adaptation of the C code example msp430fr243x_lpm4_5_01
//  and demonstrates how to enter LPM4.5 and wakeup from a GPIO interrupt. The
//  example will turn on P1.0 and enter into LPM4.5. When P2.3 (S1 on
//  MSP-EXP430FR2433) transitions from high to low the example will turn off
//  P1.0 to indicate the device is no longer in LPM4.5 and blink P1.1 forever.
// 
//  By using the compute through power loss (CTPL) library the original example
//  code is greatly simplified. The peripherals are initialized once at the
//  start of the application and the library will save the peripheral and
//  application state in FRAM before entering LPM. Upon wakeup from LPM the
//  peripheral and application state is restored and the code continues
//  execution from the next line of code.
// 
//  ACLK = VLOCLK, MCLK = SMCLK = DCO = ~1MHz
//
//           MSP-EXP430FR2433
//           ---------------
//       /|\|               |
//        | |           P1.1|---> LED2
//        --|RST        P1.0|---> LED1
//          |               |
//          |           P2.3|<--- S1 push-button
//          |               |
//
//  Brent Peterson
//  Texas Instruments Inc.
//  October 2017
//******************************************************************************
//#include <msp430.h>
#include <ctpl.h>
#include <driverlib.h>
#include <stdio.h>

//void initGpio(void);
void initAdc(void);

int main(void)
{
    /* Halt the watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;
//
//    /* Initialize GPIO */
//    initGpio();
//
//    /*
//     * Turn on P1.0 (LED1) while in LPM4.5 with restore on reset disabled. The
//     * device will wakeup when the P1.1 interrupt is triggered.
//     */
//    P1OUT |= BIT0;
//    ctpl_enterShutdown(20000);
//    P1OUT &= ~BIT0;
//
//    /* Now blink the LED in an endless loop. */
//    while (1) {
//        P1OUT ^= BIT1;
//        __delay_cycles(100000);
//    }

    printf("Program started\n");

    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_ACLK;
    param.clockPrescalar = 15;
    param.firstModReg = 0;
    param.secondModReg = 68;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param)) {
        printf("Program failed\n");
        return 0;
    }

    EUSCI_A_UART_enable(EUSCI_A0_BASE);
    // Enable USCI_A0 RX interrupt
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE,
    EUSCI_A_UART_RECEIVE_INTERRUPT);



//    initAdc();
//
//    while (1)
//    {
//        ADC_startConversion(ADC_BASE,
//        ADC_SINGLECHANNEL);
//        // Wait for the Interrupt Flag to assert
//        while (!(ADC_getInterruptStatus(ADC_BASE, ADC_COMPLETED_INTERRUPT_FLAG)))
//            ;
//        // Clear the Interrupt Flag and start another conversion
//        ADC_clearInterrupt(ADC_BASE, ADC_COMPLETED_INTERRUPT_FLAG);
//    }

    return 0;
}

//void initGpio(void)
//{
//    /* Configure GPIO to default state */
//    PAOUT = 0x0000;
//    PADIR = 0xFFFF;
//
//    /* Configure P2.3 for hi/lo transition interrupt. */
//    P2OUT |= BIT3;
//    P2REN |= BIT3;
//    P2DIR = 0xFF ^ BIT3;
//    P2IES |= BIT3;
//    P2IE |= BIT3;
//
//    /* Disable the GPIO power-on default high-impedance mode. */
//    PM5CTL0 &= ~LOCKLPM5;
//
//    /* Clear pending interrupts. */
//    P1IFG = 0;
//}

void initAdc(void)
{
    // example -> read each func

    ADC_init(ADC_BASE,
    ADC_SAMPLEHOLDSOURCE_SC,
             ADC_CLOCKSOURCE_ADCOSC,
             ADC_CLOCKDIVIDER_1);

    ADC_enable(ADC_BASE);

    ADC_setupSamplingTimer(ADC_BASE,
    ADC_CYCLEHOLD_16_CYCLES,
                           false);

    ADC_configureMemory(ADC_BASE,
    ADC_INPUT_A0,
                        ADC_VREFPOS_AVCC, // Vref+ = AVcc
                        ADC_VREFNEG_AVSS // Vref- = AVss
                        );
}
