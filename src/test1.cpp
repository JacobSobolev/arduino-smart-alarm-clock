// /*
//  * Blink
//  * Turns on an LED on for one second,
//  * then off for one second, repeatedly.
//  */
//  #include <Arduino.h>
// #include <LiquidCrystal.h>
//
//  // initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//
// const int buttonPin1 = 8;
// const int buttonPin2 = 9;
// const int buttonPin3 = 10 ;
// int buttonState1 = 0;
//
// int buttonState2 = 0;
// int buttonState3 = 0;
//
// const int pinNumber = 11;
//
// // const int ledPin = 9;
//
// // const int buttonPin = 10;
//
// int buttonState = 0;
// int playingSound = 0;
//
// int button_pressed = 0;
//
//
//
//
// void setup()
// {
//
//
//   Serial.begin(9600);
//
// // pinMode(ledPin, OUTPUT);
// //
// // pinMode(buttonPin, INPUT);
// //
// // pinMode(pinNumber,OUTPUT);
//
//   // set up the LCD's number of columns and rows:
//  lcd.begin(16, 2);
//  // Print a message to the LCD.
//  lcd.print("hello, world2!");
//
//  //setting up the buttons:
//  pinMode(buttonPin1,INPUT);
//  digitalWrite(buttonPin1, HIGH);
//  pinMode(buttonPin2,INPUT);
//  digitalWrite(buttonPin2, HIGH);
//  pinMode(buttonPin3,INPUT);
//  digitalWrite(buttonPin3, HIGH);
//
// }
//
// int handle_button(int mybuttonPin)
// {
//   int button_pressed = digitalRead(mybuttonPin); // pin low -> pressed
//   return button_pressed;
// }
//
// void loop()
// {
//   // set the cursor to column 0, line 1
//  // (note: line 1 is the second row, since counting begins with 0):
//  lcd.setCursor(0, 1);
//  // print the number of seconds since reset:
//  lcd.print(millis()/1000);
//
//  // handle button
//  button_pressed = handle_button(buttonPin2);
//
//  // do other things
//  if (button_pressed == LOW){
//    playingSound = 1;
//  }
//  Serial.print(button_pressed == LOW ? "^" : ".");
//
//  // add newline sometimes
//  static int counter = 0;
//  if ((++counter & 0x3f) == 0){
//    Serial.println();
//  }
//
//
//
//
//
//
//
//  // if (playingSound){
//  //
//  //    for(int i=200;i<=800;i++)   // frequency from 200Hz to 800Hz
//  //    {
//  //
//  //     tone(pinNumber,i);       //output frequency at port 4, i.e., generate a sound
//  //     delay(5);       //generate a sound for 5ms
//  //    }
//  //  //   delay(4000);           //the highest frequency lasts for 4ms
//  //  //  for(int i=800;i>=200;i--)
//  //  //    {
//  //  //     pinMode(pinNumber,OUTPUT);
//  //  //     tone(pinNumber,i);
//  //  //     delay(10);
//  //  //   }
//  //  noTone(pinNumber);
//  //    playingSound = 0;
//  // }
//  // //
//  //
//  // buttonState1 = digitalRead(buttonPin1);
//  // buttonState2 = digitalRead(buttonPin2);
//  // buttonState2 = digitalRead(buttonPin2);
//  //
//  // if (buttonState1 == HIGH) {
//  //
//  // // digitalWrite(ledPin, HIGH);
//  // // playingSound = 1;
//  //
//  // Serial.println("Button 1 on");
//  //
//  // }
//  // else {
//
//  // digitalWrite(ledPin, LOW);
//
//  // Serial.println("Button 1 off");
//
//  // }
//  //
//  // if (buttonState2 == HIGH) {
//  //
//  // // digitalWrite(ledPin, HIGH);
//  // // playingSound = 1;
//  //
//  // Serial.println("Button 2 on");
//  //
//  // }
//  // else {
//  //
//  // // digitalWrite(ledPin, LOW);
//  //
//  // // Serial.println("Button 2 off");
//  //
//  // }
//  //
//  // if (buttonState3 == HIGH) {
//  //
//  // // digitalWrite(ledPin, HIGH);
//  // // playingSound = 1;
//  //
//  // Serial.println("Button 3 on");
//  //
//  // }
//  // else {
//  //
//  // // digitalWrite(ledPin, LOW);
//  //
//  // // Serial.println("Button 3 off");
//  //
//  // }
//
//  // delay(100);
//
// }
