#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int stepsPerRevolution = 1024;
Stepper Step1(stepsPerRevolution, 11, 9, 10, 8);
Stepper Step2(stepsPerRevolution, 7, 5, 6, 4);

#define button1 12
#define button2 13

int btn1;
int btn2;

bool finish = false;
char data;

void setup() {
  Step1.setSpeed(25);
  Step2.setSpeed(25);
  Serial.begin(9600);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  resetSystem();
}

void loop() {
  if (Serial.available()) {
    if (finish == false) {
      data = Serial.read();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Recognizing");
      processSerialData();
    }
  }
  
  if (button1 == HIGH) {
    btn1 == 1;
  }

  if (button2 == HIGH) {
    btn2 == 1;
  }

  if (finish == true) {
    checkButtons();
  }
}

void processSerialData() {
  switch (data) {
    case '0':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unknown");
      delay(200);
      break;
      
    case '1':
      Step1.step(stepsPerRevolution / 2);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1_Open");
      delay(1000);
      finish = true;
      break;

    case '2':
      Step2.step(stepsPerRevolution / 2);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("2_Open");
      delay(1000);
      finish = true;
      break;
      
    default:
      break;
  }
}

void checkButtons() {
  if (btn1 == 1) {
    Step1.step(-stepsPerRevolution / 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1_Close");
    btn1 = 0;
    delay(1000);
    resetSystem();
  }
  else if (btn2 == 1) {
    Step2.step(-stepsPerRevolution / 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("2_Close");
    btn2 = 0;
    delay(1000);
    resetSystem();
  }
}

void resetSystem() {
  finish = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for S");

  // 'S' 신호를 받을 때까지 대기
  while (!Serial.available()) {
    // 대기 루프
  }

  if (Serial.read() == 'S') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Recognizing");
  }
}
