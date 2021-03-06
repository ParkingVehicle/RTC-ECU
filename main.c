#include <avr/io.h>
#include "LED.h"
#include "common.h"
#include "can.h"
#include "STKPRNT.h"
#include <util/delay.h>
#include "Timer1.h"
#include "CAN_APP.h"
#include "LEDH.h"
#include "RTC.h"

int main(void)
{



// inti runnables
	uint8_t cyclic20ms = 0;
	uint8_t cyclic200ms = 0;
	uint8_t cyclic1Sec = 0;


	STKPRNT_init();
	Timer1_init();

	CAN_APP_Init();
	RTC_Init();
	_delay_ms(500);

	LEDH_Init();



	RTC_Write_Clock();

		//STKPRNT_PrintSerial("UART INIT\r\n");

	while(1){
			if(EVENT_IS_SET(ev_5ms))
			{
				EVENT_CLR(ev_5ms);
				// start 5 ms runnables
		//_delay_ms(5);
							{
								LEDH_Cyclic5ms();
								STKPRNT_5ms();
							}
							if(WAIT(20ms))
							{

								CYCLIC_RST(20ms);
							}

							CYCLIC_INC(20ms);
				//   Cyclic for the 200 ms
							if(WAIT(200ms))
							{
								CYCLIC_RST(200ms);
							}

							CYCLIC_INC(200ms);
				//   Cyclic for the 1 Sec
							if(WAIT(1Sec))
							{
								// fill in the local compass data compass_data_local
								RTC_Cyclic20ms();
								CAN_APP_Cyclic20ms();
								CYCLIC_RST(1Sec);
							}
							CYCLIC_INC(1Sec);
			}



		}
	return 0;
}


ISR(USART_RXC_vect)
{
	char ReceivedByte;
	ReceivedByte = UDR; // Fetch the received byte value into the variable "ByteReceived"

	UDR = ReceivedByte; // Echo back the received byte back to the computer
}


