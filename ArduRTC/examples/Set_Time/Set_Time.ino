#include "Wire.h"
#include "RTC.h"
int wr=0;
int hours=100;
int minute=100;
int second=100;
int tw_tf=100;
int daywe=100;
int daymo=100;
int mo=100;
int y=100;
RTC rtc1(0x68);

void setup(){
  Serial.begin(9600);
  Serial.flush();
  Serial.print("Hours (in 24-hr format, if>23 no change): ");
  while(Serial.available()==0);{hours=Serial.parseInt();Serial.println(hours);while (Serial.available() > 0){ char junk = Serial.read() ; }}
    
    Serial.print("Minutes (if>60 no change): ");
   while(Serial.available()==0);{minute=Serial.parseInt();Serial.println(minute);while (Serial.available() > 0){ char junk = Serial.read() ; }}
   
    Serial.print("Seconds (if>60 no change): ");
    while(Serial.available()==0);{second=Serial.parseInt();Serial.println(second);while (Serial.available() > 0){ char junk = Serial.read() ; }}
    
    Serial.print("12-24 format (if not 12 or 24 no change): ");
    while(Serial.available()==0);{tw_tf=Serial.parseInt();Serial.println(tw_tf);while (Serial.available() > 0){ char junk = Serial.read() ; }}
    
    Serial.print("Day of the week (1=Monday, 7=Sunday, if>7 no change): ");
    while(Serial.available()==0);{daywe=Serial.parseInt();Serial.println(daywe);while (Serial.available() > 0){ char junk = Serial.read() ; }}

    Serial.print("Day of the month (if>31 no change): ");
    while(Serial.available()==0);{daymo=Serial.parseInt();Serial.println(daymo);while (Serial.available() > 0){ char junk = Serial.read() ; }}
    
    Serial.print("Month (if>12 no change): ");
    while(Serial.available()==0);{mo=Serial.parseInt();Serial.println(mo);while (Serial.available() > 0){ char junk = Serial.read() ; }}
    
    Serial.print("Year (if>99 no change): ");
    while(Serial.available()==0);{y=Serial.parseInt();Serial.println(y);while (Serial.available() > 0){ char junk = Serial.read() ; }}

    rtc1.setTime(hours,minute,second,tw_tf,daywe,daymo,mo,y);
    rtc1.stopTime();
    Serial.println(" ");
    Serial.println("Write 1 and press ENTER to write the current time to the RTC");
}
void loop(){
  while(Serial.available()==0);{wr=Serial.parseInt();while (Serial.available() > 0){ char junk = Serial.read() ; }
}
  if (wr==1){
  rtc1.startTime();
  }
  delay(5000);
  Serial.println();
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
  wr=0;
  }
