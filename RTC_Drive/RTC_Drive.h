/*
 * RTC.h
 *
 * Created: 4/23/2018 6:27:15 PM
 *  Author: NadaHasan
 */ 


#ifndef RTC_H_
#define RTC_H_

/*
#ifdef My_RTC
#define EXTERN
#else
#define EXTERN extern
#endif
*/

#define Device_Write_address	0xD0			/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address	0xD1			/* Make LSB bit high of slave address for read operation */
#define hour_12_AM	0x40
#define TimeFormat12	0x40
#define hour_12_PM	0x60
#define hour_24	0x00
#define AMPM1	0x20

#include "common.h"

//int get_time (void);



void RTC_Clock_Write(char _hour, char _minute, char _second, char AMPM);
void RTC_Calendar_Write(char _day, char _date, char _month, char _year);

uint8_t IsItPM(char hour_);
void RTC_Read_Clock(char read_clock_address);
void RTC_Read_Calendar(char read_calendar_address);

typedef struct Clock
{
	uint8 second;
	uint8 minute;
	uint8 hour;
	uint8 day;
	uint8 date;
	uint8 month;
	uint8 year;
}Clock_t;



void set_time(Clock_t *t);
void get_time(Clock_t *t);

void set_date(Clock_t *d);
void get_date(Clock_t *d);


#endif /* RTC_H_ */
