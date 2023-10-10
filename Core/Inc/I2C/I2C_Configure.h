#ifndef INC_I2C_I2C_CONFIGURE_H_
#define INC_I2C_I2C_CONFIGURE_H_

#define COMMAND  0
#define DATA     1

#include "stm32f1xx.h"

void I2C_Configure(I2C_TypeDef* I2Cx, uint8_t i2c, uint8_t speedI2C, uint8_t ack);
void I2C_Start(I2C_TypeDef* I2Cx);
void I2C_Stop(I2C_TypeDef* I2Cx);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t str);
void I2C_SendToLCD(I2C_TypeDef* I2Cx, uint8_t data, uint8_t control);

#endif /* INC_I2C_I2C_CONFIGURE_H_ */
