#include <stdio.h>
#include <stdint.h>
#include "stm32f103.h"
#include "GPIO_Configure.h"
#include "TIM_Configure.h"
#include "UART_Configure.h"
#include "DMA_Configure.h"
#include "ADC_Configure.h"
#include "I2C_Configure.h"
#include "PWM.h"
#include "LiquidCrystal_I2C.h"
#include "FreeRTOSConfig.h"
#include "cmsis_os.h"
int __io_putchar(int ch) {
    UART_SendData((char*)&ch);
    return ch;
}
LiquidCrystal_I2C lcd;
osThreadId defaultTaskHandle, task2;
void StartDefaultTask(void const * argument);
void StartDefaultTask2(void const * argument);
//volatile char receivedData[10];
//volatile uint8_t dataIndex = 0;
//volatile uint8_t dataReceivedFlag = 0;
uint8_t GPIOC_Pin[] = {13};
uint8_t GPIOC_mode[] = {1};
uint8_t GPIOB_Pin[] = {12,13};
uint8_t GPIOB_mode[] = {1,1};
//uint8_t GPIOA_Pin[] = {3,4};
//uint8_t numberADC[2] = {3,4};
//uint8_t GPIOA_mode[] = {0,0};
//uint16_t buffer[2];
int main(void){
	SystemInitAnh();
	RCC_Configure();
	TIM2_Configure(71, 0xFFFF);
	I2C_GPIO_Config();
	GPIO_configureRCC("");
//	GPIO_configure((GPIO_TypeDef*)GPIOC, (uint8_t*)GPIOC_Pin ,(uint8_t*)GPIOC_mode);
	GPIO_configure((GPIO_TypeDef*)GPIOB, (uint8_t*)GPIOB_Pin ,(uint8_t*)GPIOB_mode);
//	GPIO_configure((GPIO_TypeDef*)GPIOA, (uint8_t*)GPIOA_Pin ,(uint8_t*)GPIOA_mode);
//	I2C1_Configure();
//	lcd_init(&lcd, LCD_ADDR_DEFAULT);
//	lcd_set_cursor(&lcd, 0,0);
//	lcd_printf(&lcd, "canhanh!");
//	TIMx_PWM_Init((TIM_TypeDef*)TIM1, 1, 9999, 71);
//	ADC1_Configure((uint8_t*)numberADC, 5, 2);
//	UART_Configure();
//	DMA_ConfigureADC((uint32_t*)buffer, 2);
//	TIM4_Configure(7199, 999);
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
	osThreadDef(task2, StartDefaultTask2, osPriorityBelowNormal, 0, 128);
	task2 = osThreadCreate(osThread(task2), NULL);
	osKernelStart();
	while(1){
		GPIOB->ODR^=(1<<13);
		GPIOB->ODR^=(1<<12);
//		GPIOC->ODR^=(1<<13);
//		for (int i = 0; i < 1000000; i++);
		delay_ms2(2000);
	}
}
void StartDefaultTask(void const * argument)
{
 uint8_t count = 0;
 JUM1:
 for(;;){
	 if(!(GPIOA->IDR & (1 << 0)) && count == 0){
		 count=1;
	 }
	 if(count && GPIOA->IDR & (1 << 0)){
		 goto JUM2;
	 }
	GPIOC->ODR^=(1<<13);
	osDelay(1000);
 }
 JUM2:
 for(;;){
	 if(!(GPIOA->IDR & (1 << 0)) && count == 1){
		 count=0;
	 }
	 if (!count && GPIOA->IDR & (1 << 0)){
		 goto JUM1;
	 }
	 GPIOC->ODR^=(1<<13);
	 osDelay(3000);
 }
}
void StartDefaultTask2(void const * argument)
{
 for(;;)
 {
	printf("canhanh2\n");
   	osDelay(1000);
 }
}
void TIM4_IRQHandler(void) {
	if (TIM4->SR & TIM_SR_UIF) {
		xPortSysTickHandler();
		TIM4->SR &= ~TIM_SR_UIF;
	}
}
