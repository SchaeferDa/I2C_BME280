/*
 * BME280.c
 *
 * Created: 04.03.2019 16:30:04
 * Author: Daniel Schäfer
 * Contact: code@schaeferservices.de
 */ 
#include "I2C_LIB.h"
#include "BME280.h"

int32_t BME280_compensate_T_int32(int32_t adc_T);
boolean writeToRegister(unsigned char registerAddress, unsigned char data);
void getCalibrationValues();

unsigned char slaveAddressR = 0x00;
unsigned char slaveAddressW = 0x00;
uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;
int32_t t_fine;

void initBME280(unsigned char address)
{
	slaveAddressR = address | 0b00000001;
	slaveAddressW = address & 0b11111110;
}

void configBME280ForTemperatureMeasurement()
{
	// T_oversampling = x1; P_oversampling = x1; activate sleep mode
	writeToRegister(0xF4, 0b00100100);
	
	// filter = 2
	writeToRegister(0xF5, 0b00000100);
	
	// T_oversampling = x1; P_oversampling = x1; activate forced mode
	writeToRegister(0xF4, 0b00100101);
	
	// get calibration values
	getCalibrationValues();
}

boolean writeToRegister(unsigned char registerAddress, unsigned char data)
{
	boolean state = FALSE;
	
	sendStartCondition();
	
	if(sendByte(slaveAddressW) && sendByte(registerAddress) && sendByte(data))
		state = TRUE;
	
	sendStopCondition();
	
	return state;
}

int32_t getTemperature()
{
	// initiate measurement
	writeToRegister(0xF4, 0b00100001);
	
	int32_t temp = 0;
	
	temp |= ((int32_t)readRegister(slaveAddressW, 0xFA) << 12);
	temp |= ((int32_t)readRegister(slaveAddressW, 0xFB) <<  4);
	temp |= ((int32_t)readRegister(slaveAddressW, 0xFC) >>  4);
	
	return BME280_compensate_T_int32(temp);
}

void getCalibrationValues()
{	
	dig_T1 = 0;
	dig_T2 = 0;
	dig_T3 = 0;
	
	dig_T1 |= readRegister(slaveAddressR, 0x88);
	dig_T1 |= (readRegister(slaveAddressR, 0x89) << 8);
	
	dig_T2 |= readRegister(slaveAddressR, 0x8A);
	dig_T2 |= (readRegister(slaveAddressR, 0x8B) << 8);
	
	dig_T3 |= readRegister(slaveAddressR, 0x8C);
	dig_T3 |= (readRegister(slaveAddressR, 0x8D) << 8);
}

// from Bosch Sensortec [datasheet]
int32_t BME280_compensate_T_int32(int32_t adc_T)
{
	int32_t var1, var2, T;
	var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	
	return T;
}