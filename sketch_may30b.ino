#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);

const int stepsPerRevolution = 1024;
Stepper Step1(stepsPerRevolution, 11, 9, 10, 8);
Stepper Step2(stepsPerRevolution, 7, 5, 6, 4);

#define LED1 2
#define LED2 3
#define btn1 12
#define btn2 13

void setup() {
  Step1.setSpeed(60);
  Step2.setSpeed(60);
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
    if (Serial.available()) {      
      int data = Serial.readString();
      if (data != 1 && data != 2) {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        lcd.setCursor(0, 0);
        lcd.print("얼굴을 카메라에 보여주세요");
        Step1.step(0);
        Step2.step(0);
      }
      if (btn1 == LOW) {
        if (data == 1) {
          Step1.step(512);
          digitalWrite(LED1, HIGH);
          lcd.setCursor(0, 0);
          lcd.print("1번 사물함 잠금해제");
          delay(200);
          }
      } 
      else {
        Step1.step(-512);
        digitalWrite(LED1, LOW);
        lcd.setCursor(0, 0);
        lcd.print("사물함이 잠겼다");
        delay(200);
      }
      if (btn2 == LOW) {
        if (data == 2) {
          Step2.step(512);
          digitalWrite(LED2, HIGH);
          lcd.setCursor(0, 0);
          lcd.print("2번 사물함 잠금해제");
          delay(200);
      }
    } 
      else {
        Step2.step(-512);
        digitalWrite(LED2, LOW);
        lcd.setCursor(0, 0);
        lcd.print("사물함이 잠겼다");
        delay(200);
      }  
    }  
}
