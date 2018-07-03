/*
 * RTC.c
 *
 *  Created on: Jun 30, 2018
 *      Author: NadaHasan
 */


#include <avr/io.h>

#include "I2C_Master_H_file.h"
#include "RTC_Drive.h"
#include "RTC.h"
#include "UART_Drive.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <util/delay.h>
#include "STKPRNT.h"

void Update_RTC_Status(void);

static Clock_t Clock;

static char* days[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
static char buffer[20];



void RTC_Init(void)
{
	I2C_Init();
}

void RTC_Write_Clock(void)
{
      RTC_Clock_Write(0x5, 0x50, 0x00, hour_12_PM);/* Write Hour Minute Second Format */
      RTC_Calendar_Write(0x07, 0x30, 0x6, 0x18);	/* Write day date month and year */
}

void RTC_Cyclic20ms(void)
{
	Update_RTC_Status();
}


void RTC_SetRTCData(Clock_t *clockStatus)
{
	Clock.date = clockStatus->date;
	Clock.day = clockStatus->day;
	Clock.month = clockStatus->month;
	Clock.year = clockStatus->year;
	Clock.second = clockStatus->second;
	Clock.minute = clockStatus->minute;
	Clock.hour = clockStatus->hour;

}
void RTC_GetRTCData(Clock_t *clockStatus)
{
	clockStatus->date = Clock.date;
	clockStatus->day = Clock.day;
	clockStatus->month = Clock.month;
	clockStatus->year = Clock.year;
	clockStatus->second = Clock.second;
	clockStatus->minute = Clock.minute;
	clockStatus->hour = Clock.hour;
}

////////////////////   Begin of Local functions ////////////////////
void Update_RTC_Status(void)
{
	RTC_Read_Clock(0);							/* Read the clock with second address i.e location is 0 */

	get_time(&Clock);
	get_date(&Clock);
#ifdef debug_data
	if (Clock.hour & TimeFormat12)
	{
		sprintf(buffer, "%02x:%02x:%02x  ", (Clock.hour & 0b00011111), Clock.minute, Clock.second);
		buffer[10]=0;

		if(IsItPM(Clock.hour)){
			STKPRNT_PrintSerial(buffer);
			STKPRNT_PrintSerial("PM");

		}

		else{

			STKPRNT_PrintSerial(buffer);
			STKPRNT_PrintSerial("AM");
		}
		STKPRNT_PrintSerial("\r\n");

	}

	else
	{
		sprintf(buffer, "%02x:%02x:%02x  ", (Clock.hour & 0b00011111), Clock.minute, Clock.second);

		STKPRNT_PrintSerial(buffer);

		STKPRNT_PrintSerial("\r\n");

	}
#endif

	RTC_Read_Calendar(3);						/* Read the calender with day address i.e location is 3 */
	get_time(&Clock);
	get_date(&Clock);
#ifdef debug_data
	sprintf(buffer, "%02x/%02x/%02x %3s ", Clock.date, Clock.month, Clock.year,days[Clock.day-1]);
	STKPRNT_PrintSerial(buffer);
	STKPRNT_PrintSerial("\r\n");
#endif

}
//////////////////    End of Local functions ////////////////////
