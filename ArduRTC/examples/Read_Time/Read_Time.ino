#include "Wire.h"
#include "RTC.h"
RTC rtc1(0x68);
void setup(){
Serial.begin(9600);
}

void loop(){
Serial.print("Current time: ");
  Serial.print(rtc1.hour());
  Serial.print(":");
  Serial.print(rtc1.minutes());
  Serial.print(":");
  Serial.print(rtc1.seconds());
  Serial.print(" "); Serial.println(rtc1.AM_PM());
  Serial.print("Day of the Week: ");
  Serial.println(rtc1.day_week());
  Serial.print("Date: ");
  Serial.print(rtc1.day_month());
  Serial.print("/");
  Serial.print(rtc1.month());
  Serial.print("/");
  Serial.println(rtc1.year());
  delay(2000);
}
