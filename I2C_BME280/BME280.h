/*
 * BME280.h
 *
 * Created: 04.03.2019 17:29:54
 * Author: Daniel Schäfer
 * Contact: code@schaeferservices.de
 */ 
#ifndef BME280_H_
#define BME280_H_

void initBME280(char address);
void configBME280ForTemperatureMeasurement();
int32_t getTemperature();
int32_t getRawTemperature();

#endif /* BME280_H_ */