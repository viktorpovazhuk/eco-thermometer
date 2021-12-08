#include <driverlib.h>
#include "onewire.h"
#include "delay.h"
#include <stdio.h>

/**
 * main.c
 */
int main(void)
{
      onewire_t ow;
      int i;
      uint8_t scratchpad[9];

      WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer
//      BCSCTL1 = CALBC1_8MHZ;
//      DCOCTL = CALDCO_8MHZ;

      ow.port_out = &P1OUT;
      ow.port_in = &P1IN;
      ow.port_ren = &P1REN;
      ow.port_dir = &P1DIR;
      ow.pin = BIT7;

      PMM_unlockLPM5();

      onewire_reset(&ow);
      onewire_write_byte(&ow, 0xcc); // skip ROM command
      onewire_write_byte(&ow, 0x44); // convert T command

      onewire_line_high(&ow);
      DELAY_MS(800); // at least 750 ms for the default 12-bit resolution
      onewire_reset(&ow);

      onewire_write_byte(&ow, 0xcc); // skip ROM command
      onewire_write_byte(&ow, 0xbe); // read scratchpad command

      for (i = 0; i < 9; i++) {
          scratchpad[i] = onewire_read_byte(&ow);
          printf("%d", scratchpad[i]);
      }

//      _BIS_SR(LPM0_bits + GIE);
      return 0;

//	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
//
//
//
//	PMM_unlockLPM5();
//
//    while (1) {
//        GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
//
//        _delay_cycles(ONE_SECOND);
//
//        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
//
//        _delay_cycles(ONE_SECOND);
//    }
}
