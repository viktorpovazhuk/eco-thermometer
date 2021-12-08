#include <driverlib.h>

#define ONE_SECOND 800000

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

	PMM_unlockLPM5();

	while (1) {
	    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);

	    _delay_cycles(ONE_SECOND);

	    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        _delay_cycles(ONE_SECOND);
	}

	return 0;
}
