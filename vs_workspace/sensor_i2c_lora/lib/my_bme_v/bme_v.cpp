#include "bme_v.h"

#define SENSOR_DATA_LENGTH 8

static const uint8_t BME_ADDR = 0x76;
static const uint8_t PRESS_ADDR = 0xF7;

bool ReadRegister(
    uint8_t addr,
    uint8_t data[],
    uint8_t length)
{
    uint8_t ord(0);

    Wire.beginTransmission(BME_ADDR);
    Wire.write(addr);
    Wire.endTransmission();

    Wire.requestFrom(static_cast<uint8_t>(BME_ADDR), length);

    while (Wire.available())
    {
        data[ord++] = Wire.read();
    }

    return ord == length;
}

bool ReadData(
    int32_t data[SENSOR_DATA_LENGTH])
{
    bool success;
    uint8_t buffer[SENSOR_DATA_LENGTH];

    // For forced mode we need to write the mode to BME280 register before reading
    // if (m_settings.mode == Mode_Forced)
    // {
    //     WriteSettings();
    // }

    // Registers are in order. So we can start at the pressure register and read 8 bytes.
    success = ReadRegister(PRESS_ADDR, buffer, SENSOR_DATA_LENGTH);

    for (int i = 0; i < SENSOR_DATA_LENGTH; ++i)
    {
        data[i] = static_cast<int32_t>(buffer[i]);
    }

#ifdef DEBUG_ON
    Serial.print("Data: ");
    for (int i = 0; i < 8; ++i)
    {
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
#endif

    return success;
}

float CalculateTemperature(
    int32_t raw,
    int32_t &t_fine,
    TempUnit unit)
{
    uint8_t m_dig[32];

    // Code based on calibration algorthim provided by Bosch.
    int32_t var1, var2, final;
    uint16_t dig_T1 = (m_dig[1] << 8) | m_dig[0];
    int16_t dig_T2 = (m_dig[3] << 8) | m_dig[2];
    int16_t dig_T3 = (m_dig[5] << 8) | m_dig[4];
    var1 = ((((raw >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((raw >> 4) - ((int32_t)dig_T1)) * ((raw >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;
    final = (t_fine * 5 + 128) >> 8;
    return unit == TempUnit_Celsius ? final / 100.0 : final / 100.0 * 9.0 / 5.0 + 32.0;
}

void readTemp(float &temp)
{
    int32_t data[8];
    int32_t t_fine;

    if (!ReadData(data))
    {
        // pressure = temp = humidity = NAN;
        temp = NAN;
        return;
    }

    uint32_t rawPressure = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
    uint32_t rawTemp = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
    uint32_t rawHumidity = (data[6] << 8) | data[7];
    temp = CalculateTemperature(rawTemp, t_fine, TempUnit_Celsius);

    Serial.println("deb");
    Serial.println(temp);

    // pressure = CalculatePressure(rawPressure, t_fine, presUnit);
    // humidity = CalculateHumidity(rawHumidity, t_fine);
}