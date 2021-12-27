/*
 * uart_lib.h
 *
 *  Created on: Dec 26, 2021
 *      Author: vityha
 */

#ifndef UARTLIB_UARTLIB_H_
#define UARTLIB_UARTLIB_H_

void initUart(void);
void initClocks(void);
void initGpio(void);
void sendUartMsg(char* str);
uint8_t stringLength(char* str);



#endif /* UARTLIB_UARTLIB_H_ */
