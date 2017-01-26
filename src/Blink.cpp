/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  // initialize LED digital pin as an output.
  // pinMode(LED_BUILTIN, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");


}

void loop()
{
  // // turn the LED on (HIGH is the voltage level)
  // digitalWrite(LED_BUILTIN, HIGH);
  // // wait for a second
  // delay(1000);
  // // turn the LED off by making the voltage LOW
  // digitalWrite(LED_BUILTIN, LOW);
  //  // wait for a second
  // delay(1000);

  // set the cursor to column 0, line 1
   // (note: line 1 is the second row, since counting begins with 0):
   lcd.setCursor(0, 1);
   // print the number of seconds since reset:
   lcd.print(millis()/1000); 

}
