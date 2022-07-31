//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
#include <LiquidCrystal.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const int rs = 5, en = 18, d4 = 19, d5 = 21, d6 = 22, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(2,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(2,LOW);
  digitalWrite(15,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}



void loop() {
  char a;
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    a=SerialBT.read();
    Serial.println(a);   
  }
  if(a=='a'){
    digitalWrite(2,HIGH);
    lcd.setCursor(0,0);
    lcd.print("A on");
    lcd.print(" ");
    delay(5000);
  }
  else if(a=='b'){
    digitalWrite(15,HIGH);
    lcd.setCursor(0,0);
    lcd.print("B on");
    lcd.print(" ");
    delay(5000);
  }
  else if(a=='c'){
    digitalWrite(13,HIGH);
    lcd.setCursor(0,0);
    lcd.print("C on");
    lcd.print(" ");
    delay(5000);
  }
  else if(a=='d'){
    digitalWrite(12,HIGH);
    lcd.setCursor(0,0);
    lcd.print("D on");
    lcd.print(" ");
    delay(5000);
  }
  if(a == 'e'){
    digitalWrite(2,LOW);
    digitalWrite(15,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    lcd.setCursor(0,0);
    lcd.print("All off");
    lcd.print(" ");
    delay(5000);
  }
  
  //lcd.setCursor(0,0);
  lcd.clear();
  //delay(2000);
}
