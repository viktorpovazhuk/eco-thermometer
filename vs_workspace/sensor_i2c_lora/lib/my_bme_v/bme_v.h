// Not used actually

#ifndef BME_280_V
#define BME_280_V

#define DEBUG_ON

#include <Arduino.h>
#include <Wire.h>

// uint8_t m_dig[32];

enum TempUnit
{
    TempUnit_Celsius,
    TempUnit_Fahrenheit
};

// Functions

void readTemp(float &temp);

#endif // BME_280_V