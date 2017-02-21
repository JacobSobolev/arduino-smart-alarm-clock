#include <Arduino.h>
#include "Wire.h"
#include <LiquidCrystal.h>

 // initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define DS3231_I2C_ADDRESS 0x68
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  // Serial.print(dayOfMonth, DEC);
  // Serial.print("/");
  // Serial.print(month, DEC);
  // Serial.print("/");
  // Serial.print(year, DEC);

}

char* getTime(){
  char* msg = new char[17];
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  // Serial.print(hour, DEC);
  // // convert the byte variable to a decimal number when displayed
  // Serial.print(":");
  // if (minute<10)
  // {
  //   Serial.print("0");
  // }
  // Serial.print(minute, DEC);
  // Serial.print(":");
  // if (second<10)
  // {
  //   Serial.print("0");
  // }
  // Serial.print(second, DEC);
  // Serial.print(" ");


  sprintf(msg,"%2d:%02d:%02d %d/%d/%d",hour,minute,second,dayOfMonth,month,year);

  return msg;
}

void printTimeOnLcd()
{
  char* msg = new char[17];
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);

  lcd.clear();
  lcd.setCursor(4,0);
  sprintf(msg,"%2d:%02d:%02d",hour,minute,second);
  lcd.print(msg);
  lcd.setCursor(4,1);
  sprintf(msg,"%2d/%02d/%02d",dayOfWeek,dayOfMonth,year);
  lcd.print(msg);

}

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // setDS3231time(0,48,1,2,22,2,17);
}
void loop()
{
  // displayTime(); // display the real-time clock data on the Serial Monitor,
  printTimeOnLcd();
  delay(1000); // every second
}
