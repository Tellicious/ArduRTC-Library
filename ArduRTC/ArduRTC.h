#ifndef ArduRTC_h
#define ArduRTC_h

#include "Arduino.h"
#include "Wire.h"
// Powered with a CR1225 41mAh

class RTC
{
	public:
		RTC(byte address);
			int seconds();
			int minutes();
			int hour();
			//char* day_week();
			String day_week();
			int day_month();
			int month();
			int year();
			//char* AM_PM();
			String AM_PM();
			String time();
			void time2(char Ttemp[]);
			String date();
			void date2(char Dtemp[]);
			int* values();
			void setTime(int hour, int minutes, int seconds,int tw_24, int day_week, int day_month, int month, int year);
			void sqWave(byte on_off, byte steady_flash, int freq);
			void startTime();
			void stopTime();
	private:
	byte _address;
	int _hour, _minutes, _seconds, _tw_24, _day_week, _day_month, _month, _year, _freq, temp3;
	byte _on_off, _steady_flash, temp1, temp2, temp4, temp5, temp6;
};










#endif