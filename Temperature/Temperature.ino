#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en = 18, d4 = 19, d5 = 21, d6 = 22, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  pinMode(36,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a=analogRead(36);
  a=a/5.6;
  lcd.setCursor(0,0);
  lcd.print(a);
  delay(2000);
}
