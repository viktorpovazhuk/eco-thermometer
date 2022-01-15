/*
 * uartlib.c
 *
 *  Created on: Dec 27, 2021
 *      Author: vityha
 */

#include <uartp.h>
#include "driverlib.h"
#include "Board.h"

void initUart(void) {
    //Configure UART
    //SMCLK = 1MHz, Baudrate = 115200
    //UCBRx = 8, UCBRFx = 0, UCBRSx = 0xD6, UCOS16 = 0
    EUSCI_A_UART_initParam param = {0};
    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar = 8;
    param.firstModReg = 0;
    param.secondModReg = 0xD6;
    param.parity = EUSCI_A_UART_NO_PARITY;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
    param.uartMode = EUSCI_A_UART_MODE;
    param.overSampling = EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;

    if (STATUS_FAIL == EUSCI_A_UART_init(EUSCI_A0_BASE, &param)) {
        return;
    }

    EUSCI_A_UART_enable(EUSCI_A0_BASE);

    EUSCI_A_UART_clearInterrupt(EUSCI_A0_BASE,
        EUSCI_A_UART_RECEIVE_INTERRUPT);

    // Enable USCI_A0 RX interrupt
    EUSCI_A_UART_enableInterrupt(EUSCI_A0_BASE,
        EUSCI_A_UART_RECEIVE_INTERRUPT);
}

void sendUartMsg(const char* str) {
    uint8_t i;
    uint8_t length = stringLength(str);
    char curChar;

    for (i = 0; i < length; ++i) {

        curChar = str[i];

        //need to print first symbol correctly
        _delay_cycles(10000);

        // Load data onto buffer
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, curChar);

    }
}

uint8_t stringLength(char* str) {
    uint8_t i = 0;

    while (str[i] != '\0') {
        i++;
    }

    return i;
}
