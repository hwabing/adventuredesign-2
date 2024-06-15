#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int stepsPerRevolution = 1024;
Stepper Step1(stepsPerRevolution, 11, 9, 10, 8);
Stepper Step2(stepsPerRevolution, 7, 5, 6, 4);

#define LED1 A1
#define LED2 A0
#define btn1 12
#define btn2 13


bool finish = false;
char data;


void setup() {
  Step1.setSpeed(25);
  Step2.setSpeed(25);
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);


  lcd.init();
  lcd.backlight();
  if (Serial.available()) {
    if (Serial.read() == 'S') {
      Serial.println("O");
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      lcd.setCursor(0, 0);
      lcd.print("Recognizing");
    }

  }


}

void loop() {
  if (Serial.available()) {

    if (finish == false) {
      data = Serial.read();
      lcd.init();
      lcd.setCursor(0, 0);
      lcd.print("Recognizing");
    }
    else {
      data = 'X';
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      Step1.step(0);
      Step2.step(0);
      lcd.init();
      lcd.setCursor(0, 0);
      lcd.print("Recognized");
      
      if (digitalRead(btn1) == LOW) {
        Serial.println("1번 잠김");
        Step1.step(-stepsPerRevolution / 2);
        digitalWrite(LED1, LOW);
        lcd.init();
        lcd.setCursor(0, 0);
        lcd.print("Close");
        
      }
      else if (digitalRead(btn2) == LOW) {
        Serial.println("2번 잠김");
        Step2.step(-stepsPerRevolution / 2);
        digitalWrite(LED2, LOW);
        lcd.init();
        lcd.setCursor(0, 0);
        lcd.print("Close");
        
      }
    }




    switch (data) {
      case '0':
        lcd.init();
        lcd.setCursor(0, 0);
        lcd.print("Unknown");
        delay(200);
        break;

      case '1':
        Serial.println("1번");
        Step1.step(stepsPerRevolution / 2);
        digitalWrite(LED1, HIGH);
        lcd.init();
        lcd.setCursor(0, 0);
        lcd.print("1_Open");
        delay(1000);
        finish = true;
        break;

      case '2':
        Serial.println("2번");
        Step2.step(512);
        digitalWrite(LED2, HIGH);
        lcd.init();
        lcd.setCursor(0, 0);
        lcd.print("2_Open");
        delay(1000);
        finish = true;
        break;
      default:
        break;
    }



  }


}


#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);

const int stepsPerRevolution = 1024;
Stepper Step1(stepsPerRevolution, 11, 9, 10, 8);
Stepper Step2(stepsPerRevolution, 7, 5, 6, 4);

#define LED1 2
#define LED2 3
#define button1 12
#define button2 13

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
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  lcd.setCursor(0, 0);
  lcd.print("얼굴을 카메라에 보여주세요");
  Step1.step(0);
  Step2.step(0);
}

void Sb() {
  Step1.step(512);
  digitalWrite(LED1, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("1번 사물함 잠금해제");
  delay(200);    
}

void Sc() { 
  Step2.step(512);
  digitalWrite(LED2, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("2번 사물함 잠금해제");
  delay(200);
}

void Ra() {
  Step1.step(-512);
  digitalWrite(LED1, LOW);
  lcd.setCursor(0, 0);
  lcd.print("1번 사물함이 잠겼습니다");
  int btn1 = 0;
  delay(200);
}

void Rb() {
  Step2.step(-512);
  digitalWrite(LED2, LOW);
  lcd.setCursor(0, 0);
  lcd.print("2번 사물함이 잠겼습니다");
  int btn2 = 0;
  delay(200); 
}



