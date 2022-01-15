/*
 * uart_lib.h
 *
 *  Created on: Dec 26, 2021
 *      Author: vityha
 */

#ifndef UARTLIB_UARTLIB_H_
#define UARTLIB_UARTLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "driverlib.h"

void initUart(void);
void sendUartMsg(const char* str);
uint8_t stringLength(char* str);

#ifdef __cplusplus
}
#endif

#endif /* UARTLIB_UARTLIB_H_ */
