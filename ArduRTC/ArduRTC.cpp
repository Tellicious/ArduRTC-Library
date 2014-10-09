#include "Arduino.h"
#include "ArduRTC.h"
#include "Wire.h"

//char* date=(char*)malloc(4);
//char* AMPM=(char*)malloc(3);

RTC::RTC(byte address){
_address=address;
Wire.begin();
}

int bcdToDec(byte val)
{
  return (int)( (val/16*10) + (val%16) );
}

byte decToBcd(int val)
{
  return (byte)( (val/10*16) + (val%10) );
}

String d_week(int val)
{
String day="";
switch (val){
case 1:
day+="Mon";
break;
case 2:
day+="Tue";
break;
case 3:
day+="Wed";
break;
case 4:
day+="Thu";
break;
case 5:
day+="Fri";
break;
case 6:
day+="Sat";
break;
case 7:
day+="Sun";
break;
}
return day;
}

void d_week2(int val,char dd[])
{
snprintf(dd,5," ");
switch (val){
case 1:
snprintf(dd,5,"Mon");
break;
case 2:
snprintf(dd,5,"Tue");
break;
case 3:
snprintf(dd,5,"Wed");
break;
case 4:
snprintf(dd,5,"Thu");
break;
case 5:
snprintf(dd,5,"Fri");
break;
case 6:
snprintf(dd,5,"Sat");
break;
case 7:
snprintf(dd,5,"Sun");
break;
default:
snprintf(dd,5," ");
break; 
}
return;
}

String AMPM(byte val)
{
String twtf="";
if ((val&0x40)==0x40){
 twtf+="";
	if((val&0x20)==0x20){twtf+="PM";}
	else {twtf+="AM";}
}
else {twtf+="";}
return twtf;
}

void AMPM2(byte val, char ap[])
{
snprintf(ap,5," ");
if ((val&0x40)==0x40){
	if((val&0x20)==0x20){snprintf(ap,5,"PM");}
	else {snprintf(ap,5,"AM");}
}
else {snprintf(ap,5," ");}
return;
}
//_________________________________________________________________
int RTC::seconds(){
Wire.beginTransmission(_address);
Wire.write((byte)0x00);
Wire.endTransmission();
Wire.requestFrom(_address,(byte) 1);
return bcdToDec(Wire.read() & 0x7f);
} 
int RTC::minutes(){
Wire.beginTransmission(_address);
Wire.write((byte)0x01);
Wire.endTransmission();
Wire.requestFrom(_address,(byte) 1);
return bcdToDec(Wire.read());
}
int RTC::hour(){
Wire.beginTransmission(_address);
Wire.write((byte)0x02);
Wire.endTransmission();
Wire.requestFrom(_address,(byte) 1);
temp1=Wire.read();
if (((byte)temp1 & (byte)0x40)==(byte)0x40){
return bcdToDec((byte)0x1f & temp1);}
else{return bcdToDec((byte)0x3f & temp1);}
}
//char* RTC::AM_PM(){
String RTC::AM_PM(){
Wire.beginTransmission(_address);
Wire.write((byte)0x02);
Wire.endTransmission();
Wire.requestFrom(_address,(byte) 1);
return AMPM(Wire.read());
}
//char* RTC::day_week(){
String RTC::day_week(){
Wire.beginTransmission(_address);
Wire.write((byte)0x03);
Wire.endTransmission();
Wire.requestFrom(_address,(byte) 1);
temp3=bcdToDec(Wire.read());
return d_week(temp3);
}
int RTC::day_month(){
Wire.beginTransmission(_address);
Wire.write((byte)0x04);
Wire.endTransmission();
Wire.requestFrom(_address,(byte) 1);
return bcdToDec(Wire.read());
}
int RTC::month(){
Wire.beginTransmission(_address);
Wire.write((byte)0x05);
Wire.endTransmission();
Wire.requestFrom(_address,(byte) 1);
return bcdToDec(Wire.read());
}
int RTC::year(){
Wire.beginTransmission(_address);
Wire.write((byte)0x06);
Wire.endTransmission();
Wire.requestFrom(_address,(byte) 1);
return (2000+bcdToDec(Wire.read()));
}
String RTC::time(){
uint8_t buf[3];
char temp2[16];
String Time="";
Wire.beginTransmission(_address);
Wire.write((byte)0x00);
Wire.endTransmission();
if(Wire.requestFrom(_address,(byte) 3)==3){
Wire.readBytes((char*) buf,3);
//int sec=bcdToDec(Wire.read() & 0x7f);
//int min=bcdToDec(Wire.read());
//byte temp=Wire.read();
int hour;
if ((buf[2] & 0x40)==0x40){
hour=bcdToDec(0x1f & buf[2]);}
else{hour= bcdToDec(0x3f & buf[2]);}
snprintf(temp2,16,"%02d:%02d:%02d ",hour,bcdToDec(buf[1]),bcdToDec(buf[0]&0x7f));
/* if ((temp & 0x40)==0x40){
hour=bcdToDec(0x1f & temp);}
else{hour= bcdToDec(0x3f & temp);}
String ampm=AMPM(temp);
if (hour<10){
Time+=0;
}
Time+=hour;
Time+=":";
if (min<10){
if(bcdToDec(buf[1])<10){
Time+=0;
}
Time+=bcdToDec(buf[1]);
Time+=min;
Time+=":";
if (sec<10){
if(bcdToDec(buf[0]&0x7f)<10){
Time+=0;
}
Time+=bcdToDec(buf[0]&0x7f);
Time+=sec;
Time+=" ";
Time+=ampm; */
Time+=temp2;
Time+=AMPM(buf[2]);
}
return Time;
}
void RTC::time2(char Ttemp[]){
uint8_t buf[3];
//char temp2[16];
char tmp2[5];
String Time="";
Wire.beginTransmission(_address);
Wire.write((byte)0x00);
Wire.endTransmission();
if(Wire.requestFrom(_address,(byte) 3)==3){
Wire.readBytes((char*) buf,3);
int hour;
if ((buf[2] & 0x40)==0x40){
hour=bcdToDec(0x1f & buf[2]);}
else{hour= bcdToDec(0x3f & buf[2]);}
AMPM2(buf[2],tmp2);
snprintf(Ttemp,20,"%02d:%02d:%02d %s",hour,bcdToDec(buf[1]),bcdToDec(buf[0]&0x7f),tmp2);
//Time+=temp2;
//Time+=AMPM(buf[2]);
}
//Time.toCharArray(Ttemp,20);
return;
}


String RTC::date(){
uint8_t buf[4];
char temp2[16];
String Date="";
Wire.beginTransmission(_address);
Wire.write((byte)0x03);
Wire.endTransmission();
if(Wire.requestFrom(_address,(byte) 4)==4){
Wire.readBytes((char*) buf,4);
Date+=d_week(bcdToDec(buf[0]));
snprintf(temp2,16," %02d/%02d/%02d",bcdToDec(buf[1]),bcdToDec(buf[2]),2000+bcdToDec(buf[3]));
Date+=temp2;
/* String dw=d_week(bcdToDec(Wire.read()));
int d=bcdToDec(Wire.read());
int m=bcdToDec(Wire.read());
int y=2000+bcdToDec(Wire.read());
Date+=dw;
Date+=" ";
if (d<10){
Date+=0;
}
Date+=d;
Date+="/";
if (m<10){
Date+=0;
}
Date+=m;
Date+="/";
Date+=y; */
}
return Date;
}


void RTC::date2(char Dtemp[]){
char tmp[5];
uint8_t buf[4];
Wire.beginTransmission(_address);
Wire.write((byte)0x03);
Wire.endTransmission();
if(Wire.requestFrom(_address,(byte) 4)==4){
Wire.readBytes((char*) buf,4);
d_week2(bcdToDec(buf[0]),tmp);
snprintf(Dtemp,20, "%s %02d/%02d/%02d",tmp,bcdToDec(buf[1]),bcdToDec(buf[2]),2000+bcdToDec(buf[3]));
}
return;
}
int* RTC::values(){
int* pointer;
static int val[8];
uint8_t buf2[7];
pointer=val;
Wire.beginTransmission(_address);
Wire.write((byte)(0x00));
Wire.endTransmission();
if(Wire.requestFrom(_address,(byte) 7)==7){
Wire.readBytes((char*)buf2, 7);
if ((buf2[2] & 0x40)==0x40){
val[0]=bcdToDec(0x1f & buf2[2]);
if((buf2[2]&0x20)==0x20){val[3]=2;}
	else {val[3]=1;}
}
else{
val[0]= bcdToDec(0x3f & buf2[2]);
val[3]=0;
}
val[1]=bcdToDec(buf2[1]);
val[2]=bcdToDec(buf2[0]&0x7f);
val[4]=bcdToDec(buf2[3]);
val[5]=bcdToDec(buf2[4]);
val[6]=bcdToDec(buf2[5]);
val[7]=2000+bcdToDec(buf2[6]);
/* int ii=0;
int jj=0;
while (ii<7){
switch (ii){
case 0:
//if (ii==0){
val[jj]=bcdToDec(buf[ii]&0x7f);
ii++;
jj++;
//continue;
//}
break;
case 2:
//if (ii==2){
if ((buf[ii] & 0x40)==0x40){
val[jj]=bcdToDec(0x1f & buf[ii]);
jj++;
if((buf[ii]&0x20)==0x20){val[jj]=2;}
	else {val[jj]=1;}
}
else{
val[jj]= bcdToDec(0x3f & buf[2]);
jj++;
val[jj]=0;
}
//continue;
//}
break;
case 7:
//if (ii==7){
val[jj]=2000+bcdToDec(buf[ii]);
//continue;
//}
break;
default:
val[jj]=bcdToDec(buf[ii]);
break;
}
ii++;
jj++;
}
*/
}

return pointer;
}


void RTC::sqWave(byte on_off, byte steady_flash, int freq){ // on=1,off=0,steady=1,flash=0
_on_off=on_off;
_steady_flash=steady_flash;
_freq=freq;
byte wave;
if (_on_off<=1 && _steady_flash<=1 && _freq<=4){
wave=0x00;
if (_steady_flash==1 && _on_off==0){wave=0x80;}
else if (_steady_flash==0 && _on_off==0){wave=0x00;}
if ((_on_off==1) && (_freq<5) && (_freq>0)){
wave=0x10 | decToBcd(_freq-1);
/* switch (_freq){
case 1:
temp4=0x00;
break;
case 2:
temp4=0x01;
break;
case 3:
temp4=0x02;
break;
case 4:
temp4=0x03;
break;
default:
temp4=0x00;
break;
}
wave= 0x10|temp4;
*/
}
Wire.beginTransmission(_address);
Wire.write((byte)(0x07));
Wire.write(wave);
Wire.endTransmission();
}
}

void RTC::setTime(int hour, int minutes, int seconds,int tw_24, int day_week, int day_month, int month, int year){
if (seconds<=60){
Wire.beginTransmission(_address);
Wire.write((byte)(0x00));
Wire.write(decToBcd(seconds));
Wire.endTransmission();
}
if (minutes<=60){
Wire.beginTransmission(_address);
Wire.write((byte)(0x01));
Wire.write(decToBcd(minutes));
Wire.endTransmission();
}
if (tw_24==24 && hour <=23){
Wire.beginTransmission(_address);
Wire.write((byte)(0x02));
Wire.write((byte)0x80 | decToBcd(hour));
Wire.endTransmission();
}
if (tw_24==12 && hour <=23){
	if (hour<=11){
	Wire.beginTransmission(_address);
	Wire.write((byte)(0x02));
	Wire.write((byte)0x40 | decToBcd(hour));
	Wire.endTransmission();
	}
	if (hour==12){
	Wire.beginTransmission(_address);
	Wire.write((byte)(0x02));
	Wire.write((byte)0x60 | decToBcd(hour));
	Wire.endTransmission();
	}
	if (hour>12){
	Wire.beginTransmission(_address);
	Wire.write((byte)(0x02));
	Wire.write((byte)0x60 | decToBcd(hour-12));
	Wire.endTransmission();
	}
	
}
if (day_week>=1 && day_week<=7){
Wire.beginTransmission(_address);
Wire.write((byte)(0x03));
Wire.write(decToBcd(day_week));
Wire.endTransmission();
}
if (day_month>=1 && day_month <=31){
Wire.beginTransmission(_address);
Wire.write((byte)(0x04));
Wire.write(decToBcd(day_month));
Wire.endTransmission();
}
if (month>=1 && month<=12){
Wire.beginTransmission(_address);
Wire.write((byte)(0x05));
Wire.write(decToBcd(month));
Wire.endTransmission();
}
if (year<=99){
Wire.beginTransmission(_address);
Wire.write((byte)(0x06));
Wire.write(decToBcd(year));
Wire.endTransmission();
}


}
void RTC::startTime(){
Wire.beginTransmission(_address);
Wire.write((byte)0x00);
Wire.endTransmission();
Wire.requestFrom(_address,(byte)1);
temp5=Wire.read();
Wire.beginTransmission(_address);
Wire.write((byte)0x00);
Wire.write((byte)0x80^temp5);
Wire.endTransmission();
}

void RTC::stopTime(){
Wire.beginTransmission(_address);
Wire.write((byte)0x00);
Wire.endTransmission();
Wire.requestFrom(_address,(byte)1);
temp6=Wire.read();
Wire.beginTransmission(_address);
Wire.write((byte)0x00);
Wire.write((byte)0x80|temp6);
Wire.endTransmission();
}