/*
  LiquidCrystal Library - Serial Input

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch displays text sent over the serial port
 (e.g. from the Serial Monitor) on an attached LCD.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalSerialDisplay

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en = 18, d4 = 19, d5 = 21, d6 = 22, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int count=1;

void setup() {
  // set up the LCD's number of columns and rows:
  
  lcd.begin(16, 2);
  pinMode(25,OUTPUT);
  // initialize the serial communications:
  Serial.begin(9600);
  pinMode(36,INPUT);
}

void loop() {  
  int input=digitalRead(36);
  
  
  lcd.setCursor(0,1);
  lcd.print(count);
  //count=count+input;
  lcd.setCursor(0,0);
  lcd.print("L1 STATUS: ");
  lcd.print(input);
  //delay(1000);
  
  // when characters arrive over the serial port...
  if((count == 1) && (input == HIGH)){
    
  digitalWrite(25,HIGH);
  delay(500);
  digitalWrite(25,LOW);
  delay(500);
  count=count+1;
    lcd.setCursor(0,1);
  lcd.print(count);
  
  }
  /*
  lcd.setCursor(0,1);
  lcd.print("LED ON ");
  delay(2000);*/
 
  
  if((count==2) && (input == LOW)){
    digitalWrite(25,LOW);
    count=count+1;
      lcd.setCursor(0,1);
  lcd.print(count);
  }
  
  if((count==3) && (input==HIGH)){
  digitalWrite(25,HIGH);
  delay(500);
  digitalWrite(25,LOW);
  delay(500);
  digitalWrite(25,HIGH);
  delay(500);
  digitalWrite(25,LOW);
  delay(500);
  count=count+1;
    lcd.setCursor(0,1);
  lcd.print(count);
  }
  if((count==4) && (input==LOW)){
    digitalWrite(25,LOW);
    count=count+1;
      lcd.setCursor(0,1);
  lcd.print(count);
  }
  if((count==5) && (input==HIGH)){
  digitalWrite(25,HIGH);
  delay(500);
  digitalWrite(25,LOW);
  delay(500);
  digitalWrite(25,HIGH);
  delay(500);
  digitalWrite(25,LOW);
  delay(500);
  digitalWrite(25,HIGH);
  delay(500);
  digitalWrite(25,LOW);
  delay(500);
  count=count+1;
    lcd.setCursor(0,1);
  lcd.print(count);
  } 
  if(count==6 && input==LOW){
    digitalWrite(25,LOW);
    count=1;
    lcd.setCursor(0,1);
  lcd.print(count);
  }
   
}
