/*
This code is intended for receiving packets via LoRa on TTGO LoRa v2.0
*/

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "board_def.h"

OLED_CLASS_OBJ display(OLED_ADDRESS, OLED_SDA, OLED_SCL);

#include "BME280I2C.h"

void printBME280Data(
    Stream *client,
    uint32_t *data);
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

int count = 0;

void loop()
{
  uint32_t data[8];
  int i = 0;

  if (LoRa.parsePacket())
  {
    String recv = "";
    recv += LoRa.readString();
    // LoRa.readBytes((uint8_t*)data, 8*4);
    count++;
    display.clear();
    display.drawString(display.getWidth() / 2, display.getHeight() / 2, recv);
    String info = "RSSI = " + String(LoRa.packetRssi());
    display.drawString(display.getWidth() / 2, display.getHeight() / 2 - 16, info);
    display.display();
  }

  Serial.print("Raw data: ");
  for (int i = 0; i < 8; i++)
  {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  printBME280Data(&Serial, data);
  delay(500);
}

//////////////////////////////////////////////////////////////////
void printBME280Data(
    Stream *client,
    uint32_t *data)
{
  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.read(data, pres, temp, hum, tempUnit, presUnit);

  client->print("Temp: ");
  client->print(temp);
  client->print("°" + String(tempUnit == BME280::TempUnit_Celsius ? 'C' : 'F'));
  client->print("\t\tHumidity: ");
  client->print(hum);
  client->print("% RH");
  client->print("\t\tPressure: ");
  client->print(pres);
  client->println("Pa");

  delay(1000);
}