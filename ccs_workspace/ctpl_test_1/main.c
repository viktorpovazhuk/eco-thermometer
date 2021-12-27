#include <msp430.h>

#include <ctpl.h>

void initGpio(void);

int main(void)
{
    /* Halt the watchdog timer */
    WDTCTL = WDTPW | WDTHOLD;

    /* Initialize GPIO */
    initGpio();

    /*
     * Turn on P1.0 (LED1) while in LPM4.5 with restore on reset disabled. The
     * device will wakeup when the P1.1 interrupt is triggered.
     */
    P1OUT |= BIT0;
    ctpl_enterShutdown(20000);
    P1OUT &= ~BIT0;

    /* Now blink the LED in an endless loop. */
    while (1) {
        P1OUT ^= BIT1;
        __delay_cycles(100000);
    }
}

void initGpio(void)
{
    /* Configure GPIO to default state */
    PAOUT = 0x0000; PADIR = 0xFFFF;

    /* Configure P2.3 for hi/lo transition interrupt. */
    P2OUT |= BIT3;
    P2REN |= BIT3;
    P2DIR = 0xFF ^ BIT3;
    P2IES |= BIT3;
    P2IE |= BIT3;

    /* Disable the GPIO power-on default high-impedance mode. */
    PM5CTL0 &= ~LOCKLPM5;

    /* Clear pending interrupts. */
    P1IFG = 0;
}
