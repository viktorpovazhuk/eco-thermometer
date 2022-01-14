#include "LoRa.h"
#include "driverlib.h"
#include "Board.h"
#include "uartlib.h"
#include "stdio.h"


#define STR_LEN 100

char str[STR_LEN];
uint8_t RXData = 0;
uint8_t check = 0;

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

    PMM_unlockLPM5();

    // Enable global interrupts
    __enable_interrupt();

    if (!LoRa.begin(433000000)) //
    {
        sprintf(str, "Starting LoRa failed!\r\n");
        sendUartMsg(str);
        while (1)
          ;
    }
    LoRa.setSyncWord(0xF3);

    sprintf(str, "Start LoRa!\r\n");
    sendUartMsg(str);

    int32_t data[8];

    for (int i = 0; i < 8; i++) {
        data[i] = 1;
    }



    while (1) {
        LoRa.beginPacket();

        LoRa.write((uint8_t *)data, 8 * 4);

        LoRa.endPacket();

        __delay_cycles(10000);
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
        GPIO_setAsPeripheralModuleFunctionInputPin(
                GPIO_PORT_P2,
                GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6,
                GPIO_PRIMARY_MODULE_FUNCTION
            );
}
