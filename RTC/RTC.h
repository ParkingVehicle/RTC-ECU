/*
 * RTC.h
 *
 *  Created on: Jun 30, 2018
 *      Author: NadaHasan
 */

#ifndef RTC_RTC_H_
#define RTC_RTC_H_

#include "RTC_Drive.h"


void RTC_Init(void);
void RTC_Write_Clock(void);
void RTC_Cyclic20ms(void);

void RTC_SetRTCData(Clock_t *clockStatus);
void RTC_GetRTCData(Clock_t *clockStatus);

#endif /* RTC_RTC_H_ */
