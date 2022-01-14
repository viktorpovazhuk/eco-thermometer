#include "SPI.h"

uint8_t wait;

SPIClass::SPIClass(void) {
}

void SPIClass::begin() {
    //Initialize Master
    EUSCI_A_SPI_initMasterParam param = {0};
    param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = CS_getSMCLK();
    param.desiredSpiClock = 500000;
    param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
    param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
    param.spiMode = EUSCI_A_SPI_3PIN;
    EUSCI_A_SPI_initMaster(EUSCI_A1_BASE, &param);

    //Enable SPI module
    EUSCI_A_SPI_enable(EUSCI_A1_BASE);

    // wait for slave to initialize
    __delay_cycles(1000);

    //Clear receive interrupt flag
    EUSCI_A_SPI_clearInterrupt(EUSCI_A1_BASE,
          EUSCI_A_SPI_RECEIVE_INTERRUPT
          );

    // Enable USCI_A0 RX interrupt
    EUSCI_A_SPI_enableInterrupt(EUSCI_A1_BASE,
                         EUSCI_A_SPI_RECEIVE_INTERRUPT);


    return;
}

// dummy
void SPIClass::beginTransaction() {
    return;
}

// dummy
void SPIClass::endTransaction() {
    return;
}

uint8_t SPIClass::transfer(uint8_t data)
{
    /* Wait for previous tx to complete. */
    while (!EUSCI_A_SPI_getInterruptStatus(EUSCI_A1_BASE,
    EUSCI_A_SPI_TRANSMIT_INTERRUPT))
        ;

    //Clear receive interrupt flag
    EUSCI_A_SPI_clearInterrupt(EUSCI_A1_BASE,
    EUSCI_A_SPI_RECEIVE_INTERRUPT);

    __delay_cycles(1000);

    //Transmit Data to slave
    EUSCI_A_SPI_transmitData(EUSCI_A1_BASE, data);

    wait = 1;

    while (wait)
        ;

    uint8_t RXData = EUSCI_A_SPI_receiveData(EUSCI_A1_BASE);

    return RXData;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A1_VECTOR)))
#endif
void USCI_A1_ISR(void)
{
    switch(__even_in_range(UCA1IV, USCI_SPI_UCTXIFG))
    {
        case USCI_SPI_UCRXIFG:
            wait = 0;
            __delay_cycles(40);
            break;
        default:
            break;
    }
}

/*
 * Pre-Initialize a SPI instances
 */
SPIClass SPI;


