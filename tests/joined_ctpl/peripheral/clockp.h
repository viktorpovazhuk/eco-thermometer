/*
 * clockp.h
 *
 *  Created on: Jan 14, 2022
 *      Author: vityha
 */

#ifndef PERIPHERAL_CLOCKP_H_
#define PERIPHERAL_CLOCKP_H_

#include "driverlib.h"
#include "Board.h"

#define MCLK_FREQ_MHZ 1

void initClocks(void);
void Software_Trim();

#endif /* PERIPHERAL_CLOCKP_H_ */
