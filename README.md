## Overview
This project is an implementation of Bosch Sensortec BME280 and LCD1602-Display with I²C for Atmel ATmega328P.  
  
This is an education project. You can use it on your own risk.

## Current Features
- Measurement of current temperature in °C
    - accurancy of a tenth
    - measurement every 100 milliseconds

- Measurement of current pressure in bar
    - accurancy of a third
    - measurement every 100 milliseconds

- LCD 16x02 shows current temperature and pressure

- all data transfer through I²C

## Used Libraries
- [I2C_LIB [v1.0]](https://github.com/schaeferservices/I2C_LIB)
- [I2C_LCD_LIB [v1.0]](https://github.com/schaeferservices/I2C_LCD_LIB)
- [I2C_BME280_LIB [v1.0]](https://github.com/schaeferservices/I2C_BME280_LIB)

## Used Literature
- [Datasheet Bosch Sensortec BME280](https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf)
- [Datasheet Atmel ATmega328P](https://cdn-shop.adafruit.com/datasheets/ATMEGA328P.pdf)
