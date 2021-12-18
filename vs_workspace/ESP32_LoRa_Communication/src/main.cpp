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
    float& hum,
    float& pres);
    void printOnDisplay(String text);
BME280I2C bme; // Default : forced mode, standby time = 1000 ms
// Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

void setup()
{
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

    Serial.print("Raw data: ");
    for (int i = 0; i < 8; i++)
    {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    
    float temp(NAN), hum(NAN), pres(NAN);
  
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
    
    printOnDisplay("temp = " + String(temp));
  }
  
  

  delay(200);
}

//////////////////////////////////////////////////////////////////
void calculateBME280Data(
    Stream *client,
    uint32_t *data,
    uint8_t *m_dig,
    float &temp,
    float& hum,
    float& pres)
{
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);
  
  bme.setDig(m_dig);

  bme.read(data, pres, temp, hum, tempUnit, presUnit);

  
}

void printOnDisplay(String text) {
  display.clear();
  // String info = "RSSI = " + String(LoRa.packetRssi());
  display.drawString(display.getWidth() / 2, display.getHeight() / 2 - 16, text);
  display.display();
}