/*
 * LCD.h
 *
 *  Created on: Oct 7, 2023
 *      Author: nguye
 */

#ifndef INC_LCD_LCD_H_
#define INC_LCD_LCD_H_

void PCF8574_Init(I2C_TypeDef* I2Cx);
void LCD_Init(I2C_TypeDef* I2Cx);
void LCD_PrintString(const char *str, uint8_t row, uint8_t col);

#endif /* INC_LCD_LCD_H_ */
