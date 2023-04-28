
// https://controllerstech.com/ds3231-rtc-module-with-stm32/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DS3231_H
#define __DS3231_H

// Change the library according to your uC
#include "stm32f4xx_hal.h"
#include "main.h"

#define RTC_I2C			hi2c1
extern I2C_HandleTypeDef RTC_I2C;

#define DS3231_ADDRESS 0xD0

struct ds_time {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t date;
	uint8_t month;
	uint8_t year;
};

uint8_t decToBcd(int val);
int bcdToDec(uint8_t val);

void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
struct ds_time Get_Time(void) ;

float Get_Temp (void);
void force_temp_conv (void);




#endif
