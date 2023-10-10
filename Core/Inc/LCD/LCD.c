#include"I2C_Configure.h"

void LCD_Init(I2C_TypeDef* I2Cx) {
	I2C_Start(I2Cx);
	I2C_SendData(I2Cx, 0x27 << 1 | 0);
	I2C_SendData(I2Cx, 0x00);
    I2C_SendToLCD(I2Cx, 0x28, COMMAND);
    I2C_SendToLCD(I2Cx, 0x0C, COMMAND);
    I2C_SendToLCD(I2Cx, 0x01, COMMAND);
    I2C_SendToLCD(I2Cx, 0x06, COMMAND);
    I2C_Stop(I2Cx);
}

void LCD_PrintString(I2C_TypeDef* I2Cx, const char *str, uint8_t row, uint8_t col) {
	I2C_Start(I2Cx);
	uint8_t position = col + (row == 1 ? 0x40 : 0);
	I2C_SendToLCD(I2Cx, 0x80 | position, 0);
    while (*str != '\0') {
        I2C_SendToLCD(I2Cx, *str, 1);
        str++;
    }
    I2C_Stop(I2Cx);
}
