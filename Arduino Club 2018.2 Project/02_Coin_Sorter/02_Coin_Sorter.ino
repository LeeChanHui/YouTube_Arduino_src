#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int ten = 0;
int fifty = 0;
int hundred = 0;
int fivehundred = 0;

int beforeReadTen = 1;
int beforeReadFifty = 1;
int beforeReadHundred = 1;
int beforeReadFivehundred = 1;


void setup() {

  lcd.begin();
  lcd.backlight();

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(10, 100);
  digitalWrite(9, LOW);
  //10원
  if (digitalRead(2) == 0 && beforeReadTen == 1) {
    Serial.println("10원이 추가됨");
    ten += 1;
    beforeReadTen = 0;
  } else if (digitalRead(2) == 1) {
    beforeReadTen = 1;
  }
  //50원
  if (digitalRead(3) == 0 && beforeReadFifty == 1) {
    Serial.println("50원이 추가됨");
    fifty += 1;
    beforeReadFifty = 0;
  } else if (digitalRead(3) == 1) {
    beforeReadFifty = 1;
  }
  //100원
  if (digitalRead(4) == 0 && beforeReadHundred == 1) {
    Serial.println("100원이 추가됨");
    hundred += 1;
    beforeReadHundred = 0;
  } else if (digitalRead(4) == 1) {
    beforeReadHundred = 1;
  }
  //500원
  if (digitalRead(5) == 0 && beforeReadFivehundred == 1) {
    Serial.println("500원이 추가됨");
    fivehundred += 1;
    beforeReadFivehundred = 0;
  } else if (digitalRead(5) == 1) {
    beforeReadFivehundred = 1;
  }
  lcd.home();
  lcd.setCursor(0, 0);
  lcd.print(ten);
  lcd.setCursor(3, 0);
  lcd.print(fifty);
  lcd.setCursor(7, 0);
  lcd.print(hundred);
  lcd.setCursor(10, 0);
  lcd.print(fivehundred);

  lcd.setCursor(0, 1);
  lcd.print("total: ");
  int sum = ten * 10 + fifty * 50 + hundred * 100 + fivehundred * 500;
  lcd.print(sum);

}
