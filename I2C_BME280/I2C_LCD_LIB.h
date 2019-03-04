/*
 * I2C_LCD_LIB.h
 *
 * Created: 04.03.2019 16:30:04
 * Author: Daniel Schäfer
 * Contact: code@schaeferservices.de
 */ 
#ifndef I2C_1602LCD_H_
#define I2C_1602LCD_H_

//Initializes the LCD with given slave address
void initLCD(char slaveAddress);

//Set cursor to row(0,1) and column (0-15)
void setCursor(char row, char col);

//Clear screen
void clearScreen();

//Write string on LCD
void writeString(char* character);

//Write single char on LCD
void writeChar(char character);



#endif /* I2C_1602LCD_H_ */