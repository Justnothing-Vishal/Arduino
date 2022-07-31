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
  // put your main code here, to run repeatedly:
  int input=digitalRead(36);
  lcd.setCursor(0,0);
  lcd.print("L1 STATUS :");
  lcd.print(input);
  while(input == HIGH){
      input=digitalRead(36);
      digitalWrite(25,HIGH);
  }
  lcd.setCursor(0,1);
  lcd.print("While OUT");
  
}
