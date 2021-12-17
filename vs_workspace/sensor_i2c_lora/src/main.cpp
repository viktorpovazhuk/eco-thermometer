/*

Connecting the BME280 Sensor:
Sensor              ->  Board
-----------------------------
Vin (Voltage In)    ->  3.3V
Gnd (Ground)        ->  Gnd
SDA (Serial Data)   ->  P1.2
SCK (Serial Clock)  ->  P1.3
SDO                 ->  GND

 */

#include <SPI.h>
#include <LoRa.h>

/*
LORA

    MSP-EXP430FR2433  |  Ra-01 |
  ================================
          P3.1        |   CS   |
          P2.6        |  MOSI  |
          P2.5        |  MISO  |
          P2.4        |  SCK   |
          P1.0        |  RESET |
          P1.6        |  DIO0  |
*/

#include <Arduino.h>
#include <Wire.h>

#define SERIAL_BAUD 9600

#include <BME280I2C.h>

void printBME280Data(
    Stream *client);
BME280I2C bme; // Default : forced mode, standby time = 1000 ms
// Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

//////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(SERIAL_BAUD);

  while (!Serial)
  {
  } // Wait

  Wire.begin();

  while (!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  switch (bme.chipModel())
  {
  case BME280::ChipModel_BME280:
    Serial.println("Found BME280 sensor! Success.");
    break;
  case BME280::ChipModel_BMP280:
    Serial.println("Found BMP280 sensor! No Humidity available.");
    break;
  default:
    Serial.println("Found UNKNOWN sensor! Error!");
  }

  Serial.println("LoRa Sender");

  LoRa.setPins(P3_1, P1_0, P1_6);

  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  LoRa.setSyncWord(0xF3);
}

//////////////////////////////////////////////////////////////////
void loop()
{
  printBME280Data(&Serial);
  delay(500);
}

//////////////////////////////////////////////////////////////////
void printBME280Data(
    Stream *client)
{
  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  int32_t data[8];

  bme.read(pres, temp, hum, tempUnit, presUnit, data);

  Serial.print("Raw data: ");
  for (int i = 0; i < 8; i++)
  {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  delay(1000);

  Serial.print("Sending packet ");

  // send packet
  LoRa.beginPacket();
  // LoRa.print("temp: ");
  // LoRa.print(temp);
  // LoRa.print("hum: ");
  // LoRa.print(hum);
  // LoRa.print("pressure: ");
  // LoRa.print(pres);
  LoRa.write((uint8_t*)data, 8*4);

  LoRa.endPacket();

  delay(1000);
}