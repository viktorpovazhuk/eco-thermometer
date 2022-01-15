/*
 * hash_function.cpp
 *
 *  Created on: Jan 15, 2022
 *      Author: vityha
 */

#include "hash_function.h"

uint8_t calculateControlValue(uint8_t* data, uint16_t data_length, uint8_t* m_dig, uint16_t m_dig_length) {
    uint8_t sum = 0;
    for (uint16_t i = 0; i < data_length; i++) {
        sum += data[i] % 10;
    }
    for (uint16_t i = 0; i < m_dig_length; i++) {
        sum += m_dig[i] % 10;
    }
    return sum;
}


