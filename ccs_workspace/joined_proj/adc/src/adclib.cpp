/*
 * adc.cpp
 *
 *  Created on: Jan 12, 2022
 *      Author: vityha
 */

#include "adclib.h"

static const int16_t THRESHOLD_HIGH = 682;
static const int16_t THRESHOLD_LOW = 613;
int16_t adcResult;

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

//ADC10 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(ADC_VECTOR)))
#endif
void ADC_ISR (void)
l{
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
            // for debug
            GPIO_setOutputHighOnPin(
                                GPIO_PORT_LED1,
                                GPIO_PIN_LED1
                            );
            _low_power_mode_3();
            GPIO_setOutputLowOnPin(
                                GPIO_PORT_LED1,
                                GPIO_PIN_LED1
                            );
            break; //ADC10LO
        case 10: break; //ADC10IN
        case 12:        //ADC10IFG0
          break;
        default: break;
    }
}


