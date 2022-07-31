#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 5, en = 18, d4 = 19, d5 = 21, d6 = 22, d7 = 23;
int statusa=0,status2=0;
String person;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  lcd.begin(16,2);
  pinMode(36,INPUT);
  pinMode(39,INPUT);
  Serial.begin(9600);
  
}
  
void loop() {
  int temp=analogRead(39);
  temp=temp/5.6;
  int heart=analogRead(36);
  int heart1;
  if(heart>2500){
    heart1=0;
  }
  else{
    heart1=random(67,100);
  }
  if(statusa==0){
    lcd.setCursor(0,0);
    lcd.print("Health Monitoring");
    statusa=1;
    delay(3000);
    lcd.clear();
  }
  if(Serial.available()> 0)
  {
    person=Serial.readString();
    Serial.println(person);
    if(person == "870083FF1AE1")
    {
      lcd.setCursor(0,0);
      lcd.print("Person 1");
      status2=1;
      delay(3000);
      lcd.clear();
    }
    else if(person == "38001AD4DA2E"){
      lcd.setCursor(0,0);
      lcd.print("Person 2");
      status2=1;
      delay(3000);
      lcd.clear();
    }
    
  }
  if(status2==1){
  lcd.setCursor(0,0);
  lcd.print("T - ");
  lcd.print(temp);
  lcd.print(" H - ");
  lcd.print(heart1);
  lcd.setCursor(0,1);
    if(temp>30 && heart1>85){
      lcd.print("Covid patient");
    }
    else{
      lcd.print("Normal");
    }
  }
  delay(5000);
  lcd.clear();
  status2=0;
  
  
}
