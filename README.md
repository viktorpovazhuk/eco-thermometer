# Battery-free thermometer

**Battery-free thermometer** is a battery-free low power device, powered from solar energy, stored in the form of energy of electric field of the supercapacitor, that transmits sensor data (temperature, relative humidity and pressure) via radioband.

![Schematic of the device](https://drive.google.com/uc?id=1ibItwVbWWrtztcvywundsaXlyGfxLJ5s "Diagram of communication between battery-free thermometer and test receiver")
*Diagram 1.* Communication between battery-free thermometer and testing receiver

## Operation of battery-free thermometer
1. MCU MSP430FR2433 reads raw data from registers of temperature sensor BME280 via I2C protocol.
2. MCU MSP430FR2433 transmits read raw data via RF band 433MHz using RF tranceiver Ra-01.
3. During time intervals between reading raw data, MCU is in low-power mode.
4. Tranciever Ra-01, temperature sensor BME280 та MCU MSP430FR2433 are power from stable power supply provided by CJMCU-2557, which stores the energy extracted from solar cell in the supercapacitor.

## Project structure
* MSP_part/ - Code Composer Studio project for MSP430FR2433
* ESP32_LoRa_Communication/ - Platformio project for receiver TTGO LoRa32 v2.0

## Contributors
* Victor Povazhuk
* Bohdan Mahometa

## Acknowledgements
We want to thank our mentor Andrii Rachek, Senior Hardware Engineer at Renesas, for guiding us along developing the project.

## Wiki
See <a href="https://github.com/viktorpovazhuk/eco-thermometer/wiki">Github wiki page of the project</a> for a more detailed description, specifications and instruction for assembling the project.
