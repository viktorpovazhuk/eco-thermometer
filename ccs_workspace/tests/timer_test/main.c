#include "driverlib.h"
#include "Board.h"
#include "uartlib.h"
#include "stdio.h"

#define STR_LEN 100

char str[STR_LEN];

void initClocks(void);
void initGpio(void);


void main(void)
{
    //Stop Watchdog Timer
    WDT_A_hold(WDT_A_BASE);

    initClocks();

    initGpio();

    // clocks should be initialized
    // appropriately
    initUart();

    Timer_A_initUpModeParam initUpModeParam = {0};
    initUpModeParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    initUpModeParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
    initUpModeParam.timerPeriod = 2500;
    initUpModeParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initUpModeParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE;
    initUpModeParam.timerClear = TIMER_A_DO_CLEAR;
    initUpModeParam.startTimer = true;
    Timer_A_initUpMode(TIMER_A0_BASE, &initUpModeParam);

    PMM_unlockLPM5();

    // Enable global interrupts
    __enable_interrupt();

    while (1)
    {
        sendUartMsg("5 s passed\r\n");

        _low_power_mode_3();
    }

    return;
}

void initClocks(void) {
    //Set ACLK = REFOCLK with clock divider of 1
    CS_initClockSignal(CS_ACLK,CS_REFOCLK_SELECT,CS_CLOCK_DIVIDER_1);
    //Set SMCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_SMCLK,CS_DCOCLKDIV_SELECT,CS_CLOCK_DIVIDER_1);
    //Set MCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_MCLK,CS_DCOCLKDIV_SELECT,CS_CLOCK_DIVIDER_1);
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
