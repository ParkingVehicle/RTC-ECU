/*
 * RTC.c
 *
 * Created: 4/23/2018 6:26:43 PM
 *  Author: NadaHasan
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "I2C_Master_H_file.h"



//#define My_RTC
#include "RTC_Drive.h"



 


//struct Time_t t1;
static Clock_t clock;

void RTC_Clock_Write(char _hour, char _minute, char _second, char AMPM)
{
	_hour |= AMPM;
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(0);								/* Write on 0 location for second value */
	I2C_Write(_second);							/* Write second value on 00 location */
	I2C_Write(_minute);							/* Write minute value on 01 location */
	I2C_Write(_hour);							/* Write hour value on 02 location */
	I2C_Stop();									/* Stop I2C communication */
}

void RTC_Calendar_Write(char _day, char _date, char _month, char _year)	/* function for calendar */
{
	I2C_Start(Device_Write_address);			/* Start I2C communication with RTC */
	I2C_Write(3);								/* Write on 3 location for day value */
	I2C_Write(_day);							/* Write day value on 03 location */
	I2C_Write(_date);							/* Write date value on 04 location */
	I2C_Write(_month);							/* Write month value on 05 location */
	I2C_Write(_year);							/* Write year value on 06 location */
	I2C_Stop();									/* Stop I2C communication */
}

uint8_t IsItPM(char hour_)
{
	if(hour_ & (AMPM1))
	return 1;
	else
	return 0;
}

void RTC_Read_Clock(char read_clock_address)
{
	I2C_Start(Device_Write_address);				/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);					/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);		/* Repeated start with device read address */

	clock.second = I2C_Read_Ack();						/* Read second */
	clock.minute = I2C_Read_Ack();						/* Read minute */
	clock.hour = I2C_Read_Nack();							/* Read hour with Nack */
	I2C_Stop();										/* Stop i2C communication */
}

void RTC_Read_Calendar(char read_calendar_address)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(Device_Read_address);

	clock.day = I2C_Read_Ack();							/* Read day */
	clock.date = I2C_Read_Ack();							/* Read date */
	clock.month = I2C_Read_Ack();							/* Read month */
	clock.year = I2C_Read_Nack();							/* Read the year with Nack */
	I2C_Stop();										/* Stop i2C communication */
}



void set_time(Clock_t *t){
	clock.second = t->second;
	clock.minute = t->minute;
	clock.hour = t->hour;
	
}

void get_time(Clock_t *t){
	t ->second = clock.second;
	t ->minute = clock.minute;
	t ->hour = clock.hour;
}

void set_date(Clock_t *d){
	clock.day = d->day;
	clock.date = d->date;
	clock.month = d->month;
	clock.year = d->year;
	
}
void get_date(Clock_t *d){
	d->day = clock.day;
	d->date = clock.date;
	d->month = clock.month;
	d->year = clock.year;
}
