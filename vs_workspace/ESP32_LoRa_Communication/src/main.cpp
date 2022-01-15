/*
This code is intended for receiving packets via LoRa on TTGO LoRa v2.0
*/

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "board_def.h"

OLED_CLASS_OBJ display(OLED_ADDRESS, OLED_SDA, OLED_SCL);

#include "BME280I2C.h"

void calculateBME280Data(
    Stream *client,
    uint32_t *data,
    uint8_t *m_dig,
    float &temp,
    float &hum,
    float &pres);
void printOnDisplay(float temp, float humidity, float pressure);

BME280I2C bme; // Default : forced mode, standby time = 1000 ms
// Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

uint8_t calculateControlValue(uint8_t *data, uint16_t data_length, uint8_t *m_dig, uint16_t m_dig_length);

int counter;

void setup()
{
  counter = 0;
  
  Serial.begin(9600);
  while (!Serial)
    ;

  if (OLED_RST > 0)
  {
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, HIGH);
    delay(100);
    digitalWrite(OLED_RST, LOW);
    delay(100);
    digitalWrite(OLED_RST, HIGH);
  }

  display.init();
  display.flipScreenVertically();
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2, LORA_SENDER ? "LoRa Sender" : "LoRa Receiver");
  display.display();
  delay(2000);

  SPI.begin(CONFIG_CLK, CONFIG_MISO, CONFIG_MOSI, CONFIG_NSS);
  LoRa.setPins(CONFIG_NSS, CONFIG_RST, CONFIG_DIO0);
  Serial.println(String("BAND =") + BAND);
  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  LoRa.setSyncWord(0xF3);
}

void loop()
{
  uint32_t data[8];
  uint8_t m_dig[32];

  if (LoRa.parsePacket())
  {
    Serial.println("In parsePacket");

    LoRa.readBytes((uint8_t *)data, 8 * 4);
    LoRa.readBytes((uint8_t *)m_dig, 8 * 4);
    uint8_t receivedControlValue = LoRa.read();

    uint8_t controlValue = calculateControlValue((uint8_t *)data, 32, m_dig, 32);

    Serial.print("Raw data: ");
    for (int i = 0; i < 8; i++)
    {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    Serial.print("m_dig: ");
    for (int i = 0; i < 32; i++)
    {
      Serial.print(m_dig[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    Serial.print("Received control value: ");
    Serial.println(receivedControlValue);
    Serial.print("Calculated control value: ");
    Serial.println(controlValue);

    float temp(NAN), hum(NAN), pres(NAN);

    if (receivedControlValue == controlValue)
    {
      calculateBME280Data(&Serial, data, m_dig, temp, hum, pres);

      Serial.print("Temp: ");
      Serial.print(temp);
      Serial.print("°C");
      Serial.print("\t\tHumidity: ");
      Serial.print(hum);
      Serial.print("% RH");
      Serial.print("\t\tPressure: ");
      Serial.print(pres);
      Serial.println("Pa");

      printOnDisplay(temp, hum, pres);
      
      counter++;
    }
  }

  delay(200);
}

uint8_t calculateControlValue(uint8_t *data, uint16_t data_length, uint8_t *m_dig, uint16_t m_dig_length)
{
  uint8_t sum = 0;
  for (uint16_t i = 0; i < data_length; i++)
  {
    sum += data[i] % 10;
  }
  for (uint16_t i = 0; i < m_dig_length; i++)
  {
    sum += m_dig[i] % 10;
  }
  return sum;
}

//////////////////////////////////////////////////////////////////
void calculateBME280Data(
    Stream *client,
    uint32_t *data,
    uint8_t *m_dig,
    float &temp,
    float &hum,
    float &pres)
{
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.setDig(m_dig);

  bme.read(data, pres, temp, hum, tempUnit, presUnit);
}

void printOnDisplay(float temp, float humidity, float pressure)
{
  display.clear();
  String tempText = "temp = " + String(temp) + " C";
  String humidityText = "hum = " + String(humidity) + " Rh";
  String pressureText = "press = " + String(((int) pressure) / 1000) + " kPa";
  String countText = "count = " + String(counter);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2 - 24, tempText);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2 - 10, humidityText);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2 + 4, pressureText);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2 + 18, countText);
  display.display();
}