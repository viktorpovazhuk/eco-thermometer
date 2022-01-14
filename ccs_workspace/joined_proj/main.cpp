#include <adcp.h>
#include <i2cp.h>
#include <uartp.h>
#include "LoRa.h"
#include "driverlib.h"
#include "Board.h"
#include "stdio.h"
#include "BME280I2C.h"
#include "SPI.h"

#define MCLK_FREQ_MHZ 1

#define STR_LEN 100

char str[STR_LEN];

void initClocks(void);
void initGpio(void);
void initTimer(void);
void Software_Trim();

void sendBME280Data();

BME280I2C bme;

void main(void)
{
    //Stop Watchdog Timer
    WDT_A_hold(WDT_A_BASE);

    initClocks();

    initGpio();

    // clocks should be initialized
    // appropriately
    initUart();
    initI2C();
    SPI.begin();

    initTimer();

    PMM_unlockLPM5();

    // Enable global interrupts
    __enable_interrupt();

    LoRa.setSPI(SPI);
    while (!LoRa.begin(433000000))
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1,
                                       GPIO_PIN0);

        __delay_cycles(100000);
    }
    LoRa.setSyncWord(0xF3);

    while (!bme.begin())
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1,
                                               GPIO_PIN0);

        __delay_cycles(100000);
    }

    initAdc();

    ADC_startConversion(ADC_BASE,
                        ADC_REPEATED_SINGLECHANNEL);

    while (1)
    {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1,
                               GPIO_PIN1);
        sendBME280Data();

        _low_power_mode_3();
    }

    return;
}

void sendBME280Data()
{
    int32_t data[8];
    uint8_t out_dig[32];

    bme.readData(data);
    bme.readDig(out_dig);

    // send packet
    LoRa.beginPacket();

    LoRa.write((uint8_t*) data, 8 * 4);
    LoRa.write((uint8_t*) out_dig, 32);

    LoRa.endPacket();

    return;
}

void initTimer(void) {
    Timer_A_initUpModeParam initUpModeParam = {0};
    initUpModeParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    initUpModeParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
    initUpModeParam.timerPeriod = 2500;
    initUpModeParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initUpModeParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    initUpModeParam.timerClear = TIMER_A_DO_CLEAR;
    initUpModeParam.startTimer = true;
    Timer_A_initUpMode(TIMER_A0_BASE, &initUpModeParam);
}

void initClocks(void) {
    //Set ACLK = REFOCLK with clock divider of 1
    CS_initClockSignal(CS_ACLK,CS_REFOCLK_SELECT,CS_CLOCK_DIVIDER_1);
    //Set SMCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_SMCLK,CS_DCOCLKDIV_SELECT,CS_CLOCK_DIVIDER_1);
    //Set MCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_MCLK,CS_DCOCLKDIV_SELECT,CS_CLOCK_DIVIDER_1);

    Software_Trim();
}

void initGpio(void) {
    //Configure UART pins
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

        GPIO_setAsPeripheralModuleFunctionInputPin(
                GPIO_PORT_P2,
                GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6,
                GPIO_PRIMARY_MODULE_FUNCTION
            );

        // I2C pins
        P1SEL0 |= BIT2 | BIT3;
        P1SEL1 &= ~(BIT2 | BIT3);

        // for debug
        GPIO_setAsOutputPin(
                GPIO_PORT_P1,
                GPIO_PIN1
            );
        GPIO_setAsOutputPin(
                        GPIO_PORT_P1,
                        GPIO_PIN0
                    );
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

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER0_A0_VECTOR)))
#endif
void TIMER0_A0_ISR (void)
{
    _low_power_mode_off_on_exit();
}
