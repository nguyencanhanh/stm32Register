#include"I2C_Configure.h"
#include "stm32f1xx.h"

void I2C_Configure(I2C_TypeDef* I2Cx, uint8_t i2c, uint8_t speedI2C, uint8_t ack){
	 RCC->APB1ENR |= 1<<(20+i2c);
	 GPIOB->CRL &=0x00FFFFFF;
	 GPIOB->CRL |= (15<<24)|(15<<28); // SCL
	 if (ack==1) I2Cx->CR1 |=(1<<10);
	 I2Cx->CR2 = (speedI2C&0x3F);
	 I2Cx->CCR = speedI2C*5;
	 I2Cx->CR1 |= I2C_CR1_PE;
}
void I2C_Start(I2C_TypeDef* I2Cx) {
	I2Cx->CR1 |= I2C_CR1_START;
    while (!(I2Cx->SR1 & I2C_SR1_SB));
}

void I2C_Stop(I2C_TypeDef* I2Cx) {
	I2Cx->CR1 |= I2C_CR1_STOP;
}
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t str) {
	while (!(I2Cx->SR1 & I2C_SR1_TXE));
	I2Cx->DR = str;
	while (!(I2Cx->SR1 & I2C_SR1_BTF));
}
void I2C_SendToLCD(I2C_TypeDef* I2Cx, uint8_t data, uint8_t control) {
    I2C_SendData(I2Cx, (data & 0xF0) | control);
    I2C_SendData(I2Cx, ((data << 4) & 0xF0) | control);
}


