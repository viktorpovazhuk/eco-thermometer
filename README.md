# Battery-free thermometer

**Battery-free thermometer** - battery-free low power device, that powers from solar energy, stored in the form of electric field of supercapacitor, and transmits sensor data (temperature, relative humidity and pressure) via radioband.

![Schematic of the device](https://drive.google.com/uc?id=1ibItwVbWWrtztcvywundsaXlyGfxLJ5s "Diagram of communication between battery-free thermometer and testing receiver")
*Diagram 1.* Communication between battery-free thermometer and testing receiver

## Operation of battery-free thermometer
1. MCU MSP430FR2433 reads raw data from registers of temperature sensor BME280 via I2C protocol.
2. MCU MSP430FR2433 transmits read raw data via RF band 433MHz using RF tranceiver Ra-01.
3. During time intervals between reading raw data, MCU is in low-power mode.
4. Tranciever Ra-01, temperature sensor BME280 та MCU MSP430FR2433 are power from stable power supply provided by CJMCU-2557, which stores the energy extracted from solar cell in the supercapacitor.


## Wiki

See <a href="https://github.com/viktorpovazhuk/eco-thermometer/wiki">Github wiki page of the project</a> for more detailed description, specifications and instruction for assembling the project.
