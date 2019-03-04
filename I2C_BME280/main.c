/*
 * I2C_BME280.c
 *
 * Created: 04.03.2019 14:51:25
 * Author : Daniel Schäfer
 * Contact: code@schaeferservices.de
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include "I2C_LIB.h"
#include "I2C_LCD_LIB.h"
#include "BME280.h"


#define DEBUG_LED_conf() (DDRD |= (1 << PIND4))
#define DEBUG_LED_on() PORTD |= (1 << PIND4)
#define DEBUG_LED_off() PORTD &= ~(1 << PIND4)

int main(void)
{
	// I2C-Address of BME280
	char slaveAddressBME280 = 0b11101110;
	
	// I2C-Address of LCD1602
	char slaveAddressLCD1602 = 0b01001110;
	
	initI2C(10,'u');
	
	initLCD(slaveAddressLCD1602);
	
	initBME280(slaveAddressBME280);
	
	configBME280ForTemperatureMeasurement();
	
	while(1)
	{
		char temp[16] = {0};
		sprintf(temp, "%ld", getTemperature());
		
		char rawTemp[16] = {0};
		sprintf(rawTemp, "%ld", getRawTemperature());
		
		clearScreen();
		
		setCursor(0, 0);
		writeString(temp);
		
		setCursor(1, 0);
		writeString(rawTemp);
		
		_delay_ms(1000);
	}
}