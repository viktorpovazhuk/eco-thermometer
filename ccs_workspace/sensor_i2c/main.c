#include <driverlib.h>

eI2C_masterInit(__MSP430_BASEADDRESS_EUSCI_B0__,
eI2C_CLOCKSOURCE_SMCLK,
//UCS_getSMCLK(__MSP430_BASEADDRESS_UCS__),
1000000,
eI2C_SET_DATA_RATE_400KBPS,
1,
eI2C_NO_AUTO_STOP
);
//Specify slave address
eI2C_setSlaveAddress(__MSP430_BASEADDRESS_EUSCI_B0__,
SLAVE_ADDRESS
);
//Set in transmit mode
eI2C_setMode(__MSP430_BASEADDRESS_EUSCI_B0__,
eI2C_TRANSMIT_MODE
);
//Enable I2C Module to start operations
eI2C_enable(__MSP430_BASEADDRESS_EUSCI_B0__);
while (1)
{
//Send single byte data.
eI2C_masterSendSingleByte(__MSP430_BASEADDRESS_EUSCI_B0__,
transmitData
);
//Delay until transmission completes
while (eI2C_isBusBusy(__MSP430_BASEADDRESS_EUSCI_B0__)) ;
//Delay between each transaction
__delay_cycles(50);
//Increment transmit data counter
transmitData++;
}
