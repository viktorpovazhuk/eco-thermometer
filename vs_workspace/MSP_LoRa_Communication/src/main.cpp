#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

/*
    MSP-EXP430FR2433  |  Ra-01 |
  ================================
          P3.1        |   CS   |
          P2.6        |  MOSI  |
          P2.5        |  MISO  |
          P2.4        |  SCK   |
          P1.0        |  RESET |
          P1.6        |  DIO0  |
*/

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  LoRa.setPins(P3_1, P1_0, P1_6);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0xF3);
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(500);
}
