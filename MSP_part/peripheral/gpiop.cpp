/*
 * gpiop.cpp
 *
 *  Created on: Jan 14, 2022
 *      Author: vityha
 */

#include "gpiop.h"

void initGpio(void)
{
    P1OUT = 0;

    //Configure UART pins
    GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_UCA0TXD,
                                               GPIO_PIN_UCA0TXD,
                                               GPIO_FUNCTION_UCA0TXD);
    GPIO_setAsPeripheralModuleFunctionInputPin(
    GPIO_PORT_UCA0RXD,
                                               GPIO_PIN_UCA0RXD,
                                               GPIO_FUNCTION_UCA0RXD);

    // SPI pins
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P2,
            GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6,
            GPIO_PRIMARY_MODULE_FUNCTION);

    // I2C pins
    P1SEL0 |= BIT2 | BIT3;
    P1SEL1 &= ~(BIT2 | BIT3);

    // ADC input pin
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_ADC7,
            GPIO_PIN_ADC7,
            GPIO_FUNCTION_ADC7);

    // LEDs for debug
    GPIO_setAsOutputPin(
    GPIO_PORT_P1,
                        GPIO_PIN1);
    GPIO_setAsOutputPin(
    GPIO_PORT_P1,
                        GPIO_PIN0);
}


