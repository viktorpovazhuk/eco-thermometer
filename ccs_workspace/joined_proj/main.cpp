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
#include "hash_function.h"

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
//    initAdc();
//    ADC_startConversion(ADC_BASE,
//    ADC_REPEATED_SINGLECHANNEL);

    // Enable global interrupts
    __enable_interrupt();

    LoRa.setSPI(SPI);
    while (!LoRa.begin(433000000))
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1,
        GPIO_PIN0);

        __delay_cycles(100000);
    }

    _low_power_mode_3();

    LoRa.setSyncWord(0xF3);

    GPIO_setOutputLowOnPin(GPIO_PORT_P1,
    GPIO_PIN0);

    while (!bme.begin())
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P1,
        GPIO_PIN0);

        __delay_cycles(100000);
    }

    GPIO_setOutputLowOnPin(GPIO_PORT_P1,
    GPIO_PIN0);

    while (1)
    {
        _low_power_mode_3();

        GPIO_toggleOutputOnPin(GPIO_PORT_P1,
        GPIO_PIN1);

        sendBME280Data();
    }

    return;
}

void sendBME280Data()
{
    int32_t data[8];
    uint8_t m_dig[32];

    bme.readData(data);
    bme.readDig(m_dig);

    _low_power_mode_3();

    uint8_t controlValue = calculateControlValue((uint8_t*) data, 32, (uint8_t*) m_dig, 32);

    // send packet
    LoRa.beginPacket();

    LoRa.write((uint8_t*) data, 8 * 4);

    _low_power_mode_3();

    LoRa.write((uint8_t*) m_dig, 32);

    _low_power_mode_3();

    LoRa.write(controlValue);

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
