#include "USART.h"
#include "stm32f4xx.h" 


extern ARM_DRIVER_USART Driver_USART3;
static ARM_DRIVER_USART * USARTdrv = &Driver_USART3;

int init_USART (void){
	int status = 0;
	
		/*Initialize the USART driver */
   status =  USARTdrv->Initialize(NULL);
		if (status != 0) return status;
	  /*Power up the USART peripheral */
   status =  USARTdrv->PowerControl(ARM_POWER_FULL);
		if (status != 0) return status;
    /*Configure the USART to 9600 Bits/sec */
  status =   USARTdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
                      ARM_USART_DATA_BITS_8 |
                      ARM_USART_PARITY_NONE |
                      ARM_USART_STOP_BITS_1 |
                      ARM_USART_FLOW_CONTROL_NONE, 9600);
		if (status != 0) return status;

     
    /* Enable Receiver and Transmitter lines */
	status =   USARTdrv->Control (ARM_USART_CONTROL_TX, 1);
	if (status != 0) return status;
	
	return status;
}

int tx_USART (uint8_t ch ){
	int status = 0;
	ARM_USART_STATUS st;
	
	uint8_t buf[1];
 
  buf[0] = ch;
	
	status = USARTdrv->Send(buf, 1);
//	st = USARTdrv->GetStatus();
//	while(!(USARTdrv->SR & (1<<6))) 	st = USARTdrv->GetStatus();
	while (!(USART3->SR & (1<<6)));
	return status;
}