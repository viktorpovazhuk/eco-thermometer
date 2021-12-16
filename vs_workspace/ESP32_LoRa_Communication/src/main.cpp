/*
This code is intended for receiving packets via LoRa on TTGO LoRa v2.0
*/

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "board_def.h"

OLED_CLASS_OBJ display(OLED_ADDRESS, OLED_SDA, OLED_SCL);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  if (OLED_RST > 0) {
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
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0xF3);
}

int count = 0;

void loop()
{
  if (LoRa.parsePacket()) {
    String recv = "";
    while (LoRa.available()) {
      recv += (char)LoRa.read();
    }
    count++;
    display.clear();
    display.drawString(display.getWidth() / 2, display.getHeight() / 2, recv);
    String info = "RSSI = " + String(LoRa.packetRssi());
    display.drawString(display.getWidth() / 2, display.getHeight() / 2 - 16, info);
    display.display();
  }
}