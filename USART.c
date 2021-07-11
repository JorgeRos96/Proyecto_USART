#include "USART.h"

extern ARM_DRIVER_USART Driver_USART3;
static ARM_DRIVER_USART * USARTdrv = &Driver_USART3;

int init_USART (void){
	int status = 0;
	/*Initialize the USART driver */
    USARTdrv->Initialize(NULL);
		if (status != 0) return status;
    /*Power up the USART peripheral */
    USARTdrv->PowerControl(ARM_POWER_FULL);
		if (status != 0) return status;
    /*Configure the USART to 4800 Bits/sec */
    USARTdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
                      ARM_USART_DATA_BITS_8 |
                      ARM_USART_PARITY_NONE |
                      ARM_USART_STOP_BITS_1 |
                      ARM_USART_FLOW_CONTROL_NONE, 9600);
		if (status != 0) return status;

     
    /* Enable Receiver and Transmitter lines */
  USARTdrv->Control (ARM_USART_CONTROL_TX, 1);
	if (status != 0) return status;

	USARTdrv->Control (ARM_USART_CONTROL_RX, 1);
	if (status != 0) return status;
	
	return status;
}

int tx_USART (char ch []){
	int status = 0;
	status = USARTdrv->Send( ch, strlen((char*)ch));
	return status;
}