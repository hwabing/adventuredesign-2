#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);

const int stepsPerRevolution = 1024;
Stepper Step1(stepsPerRevolution, 11, 9, 10, 8);
Stepper Step2(stepsPerRevolution, 7, 5, 6, 4);

#define button1 12
#define button2 13

void setup() {
  Step1.setSpeed(60);
  Step2.setSpeed(60);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
    if (Serial.available()) {      
      int data = Serial.readString();
    if (data == 0 && btn1 == 0 && btn2 == 0) {
      Sa();
    }
    if (data == 1) {
      Sb();    
    }
    if (data == 2) {
      Sc();
    }
    if (btn1 == 1) {
      Ra();
    }
    if (btn2 == 1) {
      Rb();   
    }
    if (button1 == HIGH) {
      int btn1 = 1; 
    }
    if (button2 == HIGH) {
      int btn2 = 1;
    }
}

void Sa() {
  lcd.setCursor(0, 0);
  lcd.print("See Your face on screen");
  Step1.step(0);
  Step2.step(0);
}

void Sb() {
  Step1.step(512);
  lcd.setCursor(0, 0);
  lcd.print("no.1 rocker open");
  delay(200);    
}

void Sc() { 
  Step2.step(512);
  lcd.setCursor(0, 0);
  lcd.print("no.2 rocker open");
  delay(200);
}

void Ra() {
  Step1.step(-512);
  lcd.setCursor(0, 0);
  lcd.print("no.1 rocker rock");
  int btn1 = 0;
  delay(200);
}

void Rb() {
  Step2.step(-512);
  lcd.setCursor(0, 0);
  lcd.print("no.2 rocker rock");
  int btn2 = 0;
  delay(200); 
}
