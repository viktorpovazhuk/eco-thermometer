/*
 * SPI.h
 *
 *  Created on: Jan 5, 2022
 *      Author: vityha
 */

#ifndef SPILIB_SPI_H_
#define SPILIB_SPI_H_

#include "driverlib.h"

class SPIClass {
public:
    SPIClass(void);
    void begin();
    void end();
    void beginTransaction();
    void endTransaction();
    uint8_t transfer(uint8_t data);
};

extern SPIClass SPI;



#endif /* SPILIB_SPI_H_ */
