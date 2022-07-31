#include <Servo.h>
#include <LiquidCrystal.h>
static const int servoPin = 25;

Servo servo1;
const int rs = 5, en = 18, d4 = 19, d5 = 21, d6 = 22, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
    lcd.begin(16,2);
    Serial.begin(115200);
    servo1.attach(servoPin);
    pinMode(36,INPUT);
}

void loop() {

    int gas=analogRead(36);
    lcd.setCursor(0,0);
    lcd.print(gas);
    if(gas >3500){
      lcd.setCursor(0,1);
      lcd.print("gas detected");
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        //delay(20);
    }
   delay(1000);
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }
    }
    delay(1000);
    lcd.clear();
}
