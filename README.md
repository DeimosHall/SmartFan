# SmartFan

This is a simple project to control a fan using a Raspberry Pi and a temperature sensor.

## Hardware

- Raspberry Pi Pico
- USB cable
- 1x DS18B20 temperature sensor
- 1x 4.7k resistor
- 1x 12 V fan (You can use the fan you want, but you need to change the circuit to match the fan voltage)
- 1x 12 V power supply (Or the voltage of the fan you are using)
- 1x TIP41C transistor (Or any other transistor that can handle the current of your fan)

## Software

You can use one of the following options:

- [Arduino IDE](https://www.arduino.cc/en/software)
- [arduino-cli](https://arduino.github.io/arduino-cli/latest/installation/)

## Circuit

![Circuit](circuit.png)

## Libraries

| Used library   |   Version |
|----------------|-----------|
| [OneWireNg](https://github.com/pstolarz/OneWireNg)      |   0.13.1  |
| [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library.git) | 3.9.0  |

> Note: [OneWire](https://github.com/PaulStoffregen/OneWire) does not work with the Raspberry Pi Pico, so I used [OneWireNg](https://github.com/milesburton/Arduino-Temperature-Control-Library.git) instead.
