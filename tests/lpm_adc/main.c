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

#include <driverlib.h>
#include <Board.h>
#include <ctpl.h>

void initGpio(void);
void initAdc(void);

uint8_t sleep = 0;
int16_t THRESHOLD_HIGH = 682;
int16_t THRESHOLD_LOW = 613;
int16_t adcResult;

int main(void)
{
    /* Halt the watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;

    /* Initialize GPIO */
    initGpio();

    initAdc();

    /*
     * Turn on P1.0 (LED1) while in LPM4.5 with restore on reset disabled. The
     * device will wakeup when the P1.1 (no, P2.3) interrupt is triggered.
     */

    __bis_SR_register(GIE);

    ADC_startConversion(ADC_BASE,
                        ADC_REPEATED_SINGLECHANNEL);

    /* Now blink the LED in an endless loop. */
    while (1) {
//        //Enable and Start the conversion
//        //in Single-Channel, Single Conversion Mode
//        ADC_startConversion(ADC_BASE,
//                ADC_SINGLECHANNEL);
//
//        //LPM0, ADC10_ISR will force exit
//        __bis_SR_register(CPUOFF + GIE);
//        //For debug only
//        __no_operation();

        P1OUT ^= BIT1;
        __delay_cycles(100000);
    }
}

void initGpio(void)
{
    /* Configure GPIO to default state */
    PAOUT = 0x0000; PADIR = 0xFFFF;

    PMM_unlockLPM5();

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN3 + GPIO_PIN7);
    GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN3 + GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN3 + GPIO_PIN7);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN3 + GPIO_PIN7);

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN0, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN0);
}

void initAdc(void)
{
    //Initialize the ADC Module
    /*
     * Base Address for the ADC Module
     * Use internal ADC bit as sample/hold signal to start conversion
     * USE MODOSC 5MHZ Digital Oscillator as clock source
     * Use default clock divider of 1
     */
    ADC_init(ADC_BASE,
        ADC_SAMPLEHOLDSOURCE_SC,
        ADC_CLOCKSOURCE_ADCOSC,
        ADC_CLOCKDIVIDER_1);

    ADC_setWindowComp(ADC_BASE,
                      THRESHOLD_HIGH,
                      THRESHOLD_LOW);

    ADC_enable(ADC_BASE);

    /*
     * Base Address for the ADC Module
     * Sample/hold for 16 clock cycles
     * Do not enable Multiple Sampling
     */
    ADC_setupSamplingTimer(ADC_BASE,
            ADC_CYCLEHOLD_16_CYCLES,
            ADC_MULTIPLESAMPLESENABLE);

    //Configure Memory Buffer
    /*
     * Base Address for the ADC Module
     * Use input A7
     * Use positive reference of AVcc
     * Use negative reference of AVss
     */
    ADC_configureMemory(ADC_BASE,
            ADC_INPUT_A7,
            ADC_VREFPOS_INT,
            ADC_VREFNEG_AVSS);

    ADC_clearInterrupt(ADC_BASE,
                       ADC_BELOWTHRESHOLD_INTERRUPT);
    ADC_enableInterrupt(ADC_BASE,
                        ADC_BELOWTHRESHOLD_INTERRUPT);

    //Internal Reference ON
    PMM_enableInternalReference();

    //Configure internal reference
    //If ref voltage no ready, WAIT
    while (PMM_REFGEN_NOTREADY == PMM_getVariableReferenceVoltageStatus());
}

//#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
//#pragma vector=PORT2_VECTOR
//__interrupt
//#elif defined(__GNUC__)
//__attribute__((interrupt(PORT2_VECTOR)))
//#endif
//void PORT2_ISR(void)
//{
//    switch (__even_in_range(P2IV, P2IV_P2IFG7))
//    {
//        case P2IV_P2IFG3:
//            sleep = 0;
//            break;
//        case P2IV_P2IFG7:
//
//            break;
//        default:
//            break;
//    }
//}

//ADC10 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(ADC_VECTOR)))
#endif
void ADC_ISR (void)
{
    switch (__even_in_range(ADCIV,12)){
        case  0: break; //No interrupt
        case  2: break; //conversion result overflow
        case  4: break; //conversion time overflow
        case  6:
            // for debug
            adcResult = ADC_getResults(ADC_BASE);
            ADC_clearInterrupt(ADC_BASE,
                               ADC_BELOWTHRESHOLD_INTERRUPT);
            ADC_enableInterrupt(ADC_BASE,
                                ADC_BELOWTHRESHOLD_INTERRUPT);
            ADC_disableInterrupt(ADC_BASE,
                                 ADC_ABOVETHRESHOLD_INTERRUPT);
            _low_power_mode_off_on_exit();
            break; //ADC10HI
        case  8:
            // for debug
            adcResult = ADC_getResults(ADC_BASE);
            ADC_clearInterrupt(ADC_BASE,
                               ADC_ABOVETHRESHOLD_INTERRUPT);
            ADC_enableInterrupt(ADC_BASE,
                                ADC_ABOVETHRESHOLD_INTERRUPT);
            ADC_disableInterrupt(ADC_BASE,
                                 ADC_BELOWTHRESHOLD_INTERRUPT);
            GPIO_setOutputHighOnPin(
                                GPIO_PORT_LED1,
                                GPIO_PIN_LED1
                            );
//            ctpl_enterLpm45(CTPL_DISABLE_RESTORE_ON_RESET);
            _low_power_mode_3();
            GPIO_setOutputLowOnPin(
                                                GPIO_PORT_LED1,
                                                GPIO_PIN_LED1
                                            );
            break; //ADC10LO
        case 10: break; //ADC10IN
        case 12:        //ADC10IFG0
            //(Automatically clears ADC10IFG0 by reading memory buffer)
            adcResult = ADC_getResults(ADC_BASE);
            if (adcResult < 0x1FF){






            }
            else {

            }

          //Clear CPUOFF bit from 0(SR)
            //Breakpoint here and watch ADC_Result
          __bic_SR_register_on_exit(CPUOFF);
          break;
        default: break;
    }
}







