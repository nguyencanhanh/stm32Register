#include <stdio.h>
#include <stdint.h>
#include "stm32f103.h"
#include "GPIO_Configure.h"
#include "TIM_Configure.h"
#include "UART_Configure.h"
#include "DMA_Configure.h"
#include "ADC_Configure.h"
#include "FreeRTOSConfig.h"
#include "cmsis_os.h"

int __io_putchar(int ch) {
    UART_SendData((char*)&ch);
    return ch;
}

osThreadId defaultTaskHandle, task2;
void StartDefaultTask(void const * argument);
void StartDefaultTask2(void const * argument);
volatile char receivedData[10];
volatile uint8_t dataIndex = 0;
volatile uint8_t dataReceivedFlag = 0;
uint8_t GPIOB_Pin[] = {14,13};
uint8_t GPIOB_mode[] = {1,1};
uint8_t GPIOA_Pin[] = {3,4};
uint8_t numberADC[2] = {3,4};
uint8_t GPIOA_mode[] = {0,0};
uint16_t buffer[2];
int main(void){
	RCC_Configure();
	TIM4_Configure(7199, 999);
	GPIO_configureRCC("AB");
	GPIO_configure((GPIO_TypeDef*)GPIOB, (uint8_t*)GPIOB_Pin ,(uint8_t*)GPIOB_mode);
	GPIO_configure((GPIO_TypeDef*)GPIOA, (uint8_t*)GPIOA_Pin ,(uint8_t*)GPIOA_mode);
	TIM2_Configure(71, 0xFFFF);
	UART_Configure();
	ADC1_Configure((uint8_t*)numberADC, 5, 2);
	DMA_ConfigureADC((uint32_t*)buffer, 2);
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
	osThreadDef(task2, StartDefaultTask2, osPriorityBelowNormal, 0, 128);
	task2 = osThreadCreate(osThread(task2), NULL);
	osKernelStart();
	while(1){
		GPIOB->ODR^=(1<<13);
//		Read_ADC1((uint16_t*)buffer, 2);
		delay_ms2(2000);
	}
}
void StartDefaultTask(void const * argument)
{
  for(;;)
  {

	GPIOB->ODR ^= (1<<13);
	printf("canhanh1\n");
	osDelay(1000);
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
void USART1_IRQHandler(void) {
	if (USART1->SR & USART_SR_RXNE) {
	    char receivedChar = USART1->DR;
	    receivedData[dataIndex++] = receivedChar;
	    if (receivedChar == '\n') {
	      dataReceivedFlag=1;
	      printf("chuoi nhan duoc la: %s\n",receivedData);
	      dataIndex = 0;
	    }
	  }
}
