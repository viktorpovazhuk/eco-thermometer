#include <adcp.h>
#include <i2cp.h>
#include <uartp.h>
#include "timerp.h"
#include "clockp.h"
#include "gpiop.h"
#include "LoRa.h"
#include "driverlib.h"
#include "Board.h"
#include "stdio.h"
#include "BME280I2C.h"
#include "SPI.h"

void sendBME280Data();

BME280I2C bme;

void main(void)
{
    //Stop Watchdog Timer
    WDT_A_hold(WDT_A_BASE);

    initClocks();

    initGpio();

    // clocks should be initialized
    // previously
    initUart();
    initI2C();
    SPI.begin();

    initTimer();

    PMM_unlockLPM5();

    // should unlock pins previously
    initAdc();
    ADC_startConversion(ADC_BASE,
    ADC_REPEATED_SINGLECHANNEL);

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
