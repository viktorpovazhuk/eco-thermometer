/*
 * hash_function.h
 *
 *  Created on: Jan 15, 2022
 *      Author: vityha
 */

#ifndef LORA_SRC_HASH_FUNCTION_H_
#define LORA_SRC_HASH_FUNCTION_H_

#include "driverlib.h"
#include "Board.h"

uint8_t calculateControlValue(uint8_t* data, uint16_t data_length, uint8_t* m_dig, uint16_t m_dig_length);


#endif /* LORA_SRC_HASH_FUNCTION_H_ */
