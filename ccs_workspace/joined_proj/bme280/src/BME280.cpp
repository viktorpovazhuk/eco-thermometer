/*
BME280.cpp
This code records data from the BME280 sensor and provides an API.
This file is part of the Arduino BME280 library.
Copyright (C) 2016   Tyler Glenn

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.   If not, see <http://www.gnu.org/licenses/>.

Written: Dec 30 2015.
Last Updated: Oct 07 2017.

This header must be included in any derived code or copies of the code.

Based on the data sheet provided by Bosch for the Bme280 environmental sensor,
calibration code based on algorithms providedBosch, some unit conversations courtesy
of www.endmemo.com, altitude equation courtesy of NOAA, and dew point equation
courtesy of Brian McNoldy at http://andrew.rsmas.miami.edu.
 */

#include "BME280.h"
#include "uartp.h"

#define STR_LEN 100

char str[STR_LEN];

/****************************************************************/
BME280::BME280(
    const Settings &settings) : m_settings(settings),
                                m_initialized(false)
{
}

/****************************************************************/
bool BME280::Initialize()
{
   bool success(true);

   success &= ReadChipID();

   sprintf(str, "after ReadChipID: %d\r\n", success);
   sendUartMsg(str);

   if (success)
   {
      success &= ReadTrim();

      sprintf(str, "after ReadTrim: %d\r\n", success);
      sendUartMsg(str);

      if (m_settings.filter != Filter_Off)
      {
         InitializeFilter();
      }

      WriteSettings();
   }

   m_initialized = success;

   return m_initialized;
}

/****************************************************************/
bool BME280::InitializeFilter()
{
   // Force an unfiltered measurement to populate the filter buffer.
   // This fixes a bug that causes the first read to always be 28.82 °C 81732.34 hPa.
   Filter filter = m_settings.filter;
   m_settings.filter = Filter_Off;

   WriteSettings();

   readData(nullptr);

   m_settings.filter = filter;
}

/****************************************************************/
bool BME280::ReadChipID()
{
   uint8_t id[1];

   ReadRegister(ID_ADDR, &id[0], 1);

   switch (id[0])
   {
   case ChipModel_BME280:
      m_chip_model = ChipModel_BME280;
      break;
   case ChipModel_BMP280:
      m_chip_model = ChipModel_BMP280;
      break;
   default:
      m_chip_model = ChipModel_UNKNOWN;
      return false;
   }

   return true;
}

/****************************************************************/
bool BME280::WriteSettings()
{
   uint8_t ctrlHum, ctrlMeas, config;

   CalculateRegisters(ctrlHum, ctrlMeas, config);

   WriteRegister(CTRL_HUM_ADDR, ctrlHum);
   WriteRegister(CTRL_MEAS_ADDR, ctrlMeas);
   WriteRegister(CONFIG_ADDR, config);
}

/****************************************************************/
void BME280::setSettings(
    const Settings &settings)
{
   m_settings = settings;
   WriteSettings();
}

/****************************************************************/
const BME280::Settings &BME280::getSettings() const
{
   return m_settings;
}

/****************************************************************/
bool BME280::begin()
{
   bool success = Initialize();

   sprintf(str, "after initialize: %d\r\n", success);
   sendUartMsg(str);

   success &= m_initialized;

   sprintf(str, "after m_initialized: %d\r\n", success);
      sendUartMsg(str);

   return success;
}

/****************************************************************/
void BME280::CalculateRegisters(
    uint8_t &ctrlHum,
    uint8_t &ctrlMeas,
    uint8_t &config)
{
   // ctrl_hum register. (ctrl_hum[2:0] = Humidity oversampling rate.)
   ctrlHum = (uint8_t)m_settings.humOSR;
   // ctrl_meas register. (ctrl_meas[7:5] = temperature oversampling rate, ctrl_meas[4:2] = pressure oversampling rate, ctrl_meas[1:0] = mode.)
   ctrlMeas = ((uint8_t)m_settings.tempOSR << 5) | ((uint8_t)m_settings.presOSR << 2) | (uint8_t)m_settings.mode;
   // config register. (config[7:5] = standby time, config[4:2] = filter, ctrl_meas[0] = spi enable.)
   config = ((uint8_t)m_settings.standbyTime << 5) | ((uint8_t)m_settings.filter << 2) | (uint8_t)m_settings.spiEnable;
}

/****************************************************************/
bool BME280::ReadTrim()
{
   uint8_t ord(0);
   bool success = true;

   // Temp. Dig
   success &= ReadRegister(TEMP_DIG_ADDR, &m_dig[ord], TEMP_DIG_LENGTH);
   ord += TEMP_DIG_LENGTH;

//   // Serial.print("temp trim ");
//   // Serial.print(success);
//   // Serial.println();

   // Pressure Dig

   // can't be used because
   // due to some reasons number of bytes to read with Wire.requestFrom()
   // is limited to 16
   // -> can't read 18 bytes for pressure at once
   // success &= ReadRegister(PRESS_DIG_ADDR, &m_dig[ord], PRESS_DIG_LENGTH);
   // ord += PRESS_DIG_LENGTH

   // fixed version
   success &= ReadRegister(PRESS_DIG_ADDR_1, &m_dig[ord], PRESS_DIG_LENGTH_1);
   ord += PRESS_DIG_LENGTH_1;
   success &= ReadRegister(PRESS_DIG_ADDR_2, &m_dig[ord], PRESS_DIG_LENGTH_2);
   ord += PRESS_DIG_LENGTH_2;

//   // Serial.print("press trim ");
//   // Serial.print(success);
//   // Serial.println();

   // Humidity Dig 1
   success &= ReadRegister(HUM_DIG_ADDR1, &m_dig[ord], HUM_DIG_ADDR1_LENGTH);
   ord += HUM_DIG_ADDR1_LENGTH;

//   // Serial.print("hum1 trim ");
//   // Serial.print(success);
//   // Serial.println();

   // Humidity Dig 2
   success &= ReadRegister(HUM_DIG_ADDR2, &m_dig[ord], HUM_DIG_ADDR2_LENGTH);
   ord += HUM_DIG_ADDR2_LENGTH;

   // Serial.print("hum2 trim ");
   // Serial.print(success);
   // Serial.println();

   // Serial.print("all trim ");
   // Serial.print(success);
   // Serial.println();

#ifdef DEBUG_ON
   // Serial.print("Dig: ");
   for (int i = 0; i < 32; ++i)
   {
      // Serial.print(m_dig[i], HEX);
      // Serial.print(" ");
   }
   // Serial.println();
#endif

   return success && ord == DIG_LENGTH;
}

/****************************************************************/
bool BME280::ReadData(
    int32_t data[SENSOR_DATA_LENGTH])
{
   bool success;
   uint8_t buffer[SENSOR_DATA_LENGTH];

   // For forced mode we need to write the mode to BME280 register before reading
   if (m_settings.mode == Mode_Forced)
   {
      WriteSettings();
   }

   // Registers are in order. So we can start at the pressure register and read 8 bytes.
   success = ReadRegister(PRESS_ADDR, buffer, SENSOR_DATA_LENGTH);

   for (int i = 0; i < SENSOR_DATA_LENGTH; ++i)
   {
      data[i] = static_cast<int32_t>(buffer[i]);
   }

   return success;
}

/****************************************************************/
bool BME280::readData(int32_t *data)
{
   if (data == nullptr) {
       return false;
   }

   return ReadData(data);
}

/****************************************************************/
void BME280::readDig(uint8_t *out_dig)
{
   memcpy(out_dig, m_dig, 32);
}

/****************************************************************/
BME280::ChipModel BME280::chipModel()
{
   return m_chip_model;
}
