
#include "ds3231.h"

//ds_time time;

// Convert normal decimal numbers to binary coded decimal
uint8_t decToBcd(int val) {
	return (uint8_t) ((val / 10 * 16) + (val % 10));
}
// Convert binary coded decimal to normal decimal numbers
int bcdToDec(uint8_t val) {
	return (int) ((val / 16 * 10) + (val % 16));
}

// function to set time

void Set_Time_2(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom,
		uint8_t month, uint8_t year) {
	uint8_t set_time[7];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(dow);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	HAL_I2C_Mem_Write(&RTC_I2C, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
}

void Set_Time(struct ds_time set_time) {
	uint8_t convt_time[7];
	convt_time[0] = decToBcd(set_time.seconds);
	convt_time[1] = decToBcd(set_time.minutes);
	convt_time[2] = decToBcd(set_time.hour);
	convt_time[3] = decToBcd(set_time.dayofweek);
	convt_time[4] = decToBcd(set_time.date);
	convt_time[5] = decToBcd(set_time.month);
	convt_time[6] = decToBcd(set_time.year);

	HAL_I2C_Mem_Write(&RTC_I2C, DS3231_ADDRESS, 0x00, 1, convt_time, 7, 1000);
}

struct ds_time Get_Time(void) {
	uint8_t get_time[7];
	HAL_I2C_Mem_Read(&RTC_I2C, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000);

	struct ds_time rtc_time;
	rtc_time.seconds = bcdToDec(get_time[0]);
	rtc_time.minutes = bcdToDec(get_time[1]);
	rtc_time.hour = bcdToDec(get_time[2]);
	rtc_time.dayofweek = bcdToDec(get_time[3]);
	rtc_time.date = bcdToDec(get_time[4]);
	rtc_time.month = bcdToDec(get_time[5]);
	rtc_time.year = bcdToDec(get_time[6]);
	return rtc_time;
}

float Get_Temp(void) {
uint8_t temp[2];

HAL_I2C_Mem_Read(&RTC_I2C, DS3231_ADDRESS, 0x11, 1, temp, 2, 1000);
return ((temp[0]) + (temp[1] >> 6) / 4.0);
}

void force_temp_conv(void) {
uint8_t status = 0;
uint8_t control = 0;
HAL_I2C_Mem_Read(&RTC_I2C, DS3231_ADDRESS, 0x0F, 1, &status, 1, 100); // read status register
if (!(status & 0x04)) {
	HAL_I2C_Mem_Read(&RTC_I2C, DS3231_ADDRESS, 0x0E, 1, &control, 1, 100); // read control register
	HAL_I2C_Mem_Write(&RTC_I2C, DS3231_ADDRESS, 0x0E, 1,
			(uint8_t*) (control | (0x20)), 1, 100);
}
}
