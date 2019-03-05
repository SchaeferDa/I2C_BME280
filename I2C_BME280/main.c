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
#include "I2C_BME280_LIB.h"

#define DEBUG_LED_conf() (DDRD |= (1 << PIND4))
#define DEBUG_LED_on() PORTD |= (1 << PIND4)
#define DEBUG_LED_off() PORTD &= ~(1 << PIND4)

int main(void)
{
	// I2C-Address of BME280
	unsigned char slaveAddressBME280 = 0b11101110;
	
	// I2C-Address of LCD1602
	unsigned char slaveAddressLCD1602 = 0b01001110;
	
	initI2C(10,'u');
	
	initLCD(slaveAddressLCD1602);
	
	BME280_init(slaveAddressBME280);
	
	// config BME280 in general
	BME280_set_filter_coefficient_2();
	BME280_set_normal_mode();
	BME280_set_standby_time_62_5();
	
	// config BME280 temperature measurement
	BME280_set_temperature_oversampling_1();
	BME280_calibrate_temperature();
	
	// config BME280 pressure measurement
	BME280_set_pressure_oversampling_1();
	BME280_calibrate_pressure();
	
	//config BME280 humidity meaurement
	BME280_set_humidity_oversampling_1();
	BME280_calibrate_humidity();
	
	while(1)
	{
		char temp[16] = {0};
		dtostrf(BME280_get_temperature(), 5, 2, temp);
		
		char press[16] = {0};
		dtostrf(BME280_get_pressure()/100000, 5, 3, press);
		
		char hum[16] = {0};
		dtostrf(BME280_get_humidity(), 4, 2, hum);
		
		setCursor(0, 0);
		writeString(temp);
		writeChar(0xDF);
		writeString("C");
		
		setCursor(1, 0);
		writeString(press);
		writeString(" bar");
		
		/*
		setCursor(1, 0);
		writeString(hum);
		writeString(" %rh");
		*/
		
		setCursor(3,17);
		
		_delay_ms(100);
	}
}