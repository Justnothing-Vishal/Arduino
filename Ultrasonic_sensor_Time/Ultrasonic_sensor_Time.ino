/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-hc-sr04-ultrasonic-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/
#include <LiquidCrystal.h>


const int trigPin = 26;
const int echoPin = 25;
const int rs = 5, en = 18, d4 = 19, d5 = 21, d6 = 22, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
int distanceCm;
int distanceInch;
int T=1;
void setup() {
  lcd.begin(16,2);
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(36,INPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  // Sets the echoPin as an Input
}

void loop() {
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  lcd.setCursor(0,0);
  lcd.print(T);
  lcd.print(" ");
  lcd.setCursor(0,1);
  if(T<=10 && distanceCm >50){
    digitalWrite(32,HIGH);
    digitalWrite(33,LOW);
    T++;
  }
  else if(T>10 && T<21 && distanceCm >50){
    digitalWrite(33,HIGH);
    digitalWrite(32,LOW);
    T++;
  }
  else if(distanceCm<50){
    lcd.print(distanceCm);
    lcd.print(" ");
    if(distanceCm< 30){
      digitalWrite(32, HIGH);
      digitalWrite(33,LOW);

      T=1;
    }
    else{
      digitalWrite(33,HIGH);
      digitalWrite(32, LOW);
      
      T=1;
    }
  }
  else{
    digitalWrite(32,LOW);
    digitalWrite(33,LOW);
    T=1;
  }
  delay(1000);
}
