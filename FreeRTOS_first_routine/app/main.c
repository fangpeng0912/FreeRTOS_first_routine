#include "FreeRTOS.h"
#include "Task.h"
#include "led.h"
#include "misc.h"
#include "RS232.h"

//任务优先级
#define LED0_TASK_PRIO 1
//任务堆栈大小
#define LED0_STK_SIZE 128
//任务句柄
TaskHandle_t Led0Task_Handler;
//任务函数
void led0_task(void *pvParameters);

//任务优先级
#define LED1_TASK_PRIO 2
//任务堆栈大小
#define LED1_STK_SIZE 128
//任务句柄
TaskHandle_t Led1Task_Handler;
//任务函数
void led1_task(void *pvParameters);


int main(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	LED_Init();
	USART1_Init();

	xTaskCreate((TaskFunction_t)led0_task, (const char*)"led0_task", (uint16_t)LED0_STK_SIZE, (void*)NULL, (UBaseType_t)LED0_TASK_PRIO, (TaskHandle_t*)&Led0Task_Handler);	
	xTaskCreate((TaskFunction_t)led1_task, (const char*)"led1_task", (uint16_t)LED1_STK_SIZE, (void*)NULL, (UBaseType_t)LED1_TASK_PRIO, (TaskHandle_t*)&Led1Task_Handler);
	
	vTaskStartScheduler();
}

void led0_task(void *pvParameters){
	while(1){
		led0 = !led0;
		printf("led0_task is running\n");
		vTaskDelay(500);	
	}
}

void led1_task(void *pvParameters){
	while(1){
		led1 = !led1;
		printf("led1_task is running\n");
		vTaskDelay(1000);
	}
}

