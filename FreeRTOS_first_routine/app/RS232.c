#include "RS232.h"

unsigned char USART1_receive[USART_REC_LEN];
uint16_t USART_RX_STA;

void USART1_Init(){
	GPIO_InitTypeDef GPIO_InitStructure_Tx, GPIO_InitStructure_Rx;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	//��ʼ��GPIOA���PIN�ź�USART1
	GPIO_InitStructure_Tx.GPIO_Pin = USART1_TX_PIN;	
	GPIO_InitStructure_Tx.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_Tx.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_InitStructure_Rx.GPIO_Pin = USART1_RX_PIN;	
	GPIO_InitStructure_Rx.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_Rx.GPIO_Mode = GPIO_Mode_IPU;

	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_Init(USART1_PORT, &GPIO_InitStructure_Tx);
	GPIO_Init(USART1_PORT, &GPIO_InitStructure_Rx);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_Init(USART1, &USART_InitStruct);   
	
	//ʹ��USART1�����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	//�����ж����ȼ��Լ�ʹ������ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	//ʹ��USART1
	USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void){
	uint8_t rec;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET){ 
		//���մ�������
		rec = USART_ReceiveData(USART1);
		if((USART_RX_STA & NEWLINE_STATE) == 0){ //δ���յ����У�����δ���
			if(USART_RX_STA & ENTER_STATE){  //���յ��˻س�
				if(rec != 0x0a) USART_RX_STA = 0; //���մ������¿�ʼ
				else USART_RX_STA |= NEWLINE_STATE;	 //�������
			}
			else{	 //δ���յ��س�
				if(rec == 0x0d) USART_RX_STA |= ENTER_STATE;
				else{
					USART1_receive[USART_RX_STA & 0X3FFF] = rec ;
					USART_RX_STA++;
					if(USART_RX_STA == USART_REC_LEN) USART_RX_STA = 0;	 //�������ݴ������¿�ʼ���� 
				}		 
			}
		} 
	}
	//��������жϱ�־λ
	USART_ClearFlag(USART1, USART_FLAG_RXNE);
}

int fputc(int ch, FILE *file){ 
	USART_GetFlagStatus(USART1, USART_FLAG_TC);  
	USART_SendData(USART1, (uint8_t)ch);
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TC));
	
	return ch;
}


