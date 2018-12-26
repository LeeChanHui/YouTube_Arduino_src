
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <DHT11.h>
 
//----------------------------------------------------------------------------------------------------------------------
int measurePin = 0; 
int ledPower = 2;   
int pin = 6;
float sensitivity = 0.1;
float pre_dustDensity = 0;
 
//----------------------------------------------------------------------------------------------------------------------
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
LiquidCrystal lcd(3, 4, 10, 11, 12, 13);
DHT11 dht11(pin);
 
//----------------------------------------------------------------------------------------------------------------------
static const uint8_t PROGMEM
veryGood_bmp[] =
{ B00000000,
  B01000010,
  B10100101,
  B00000000,
  B00000000,
  B01111110,
  B00111100,
  B00000000
},
good_bmp[] =
{ B00000000,
  B00000000,
  B00100100,
  B00100100,
  B00000000,
  B01111110,
  B00111100,
  B00000000
},
normal_bmp[] =
{ B00000000,
  B00000000,
  B00100100,
  B00100100,
  B00000000,
  B01111110,
  B00000000,
  B00000000
},
bad_bmp[] =
{ B00000000,
  B00000000,
  B00000000,
  B01100110,
  B00000000,
  B00111100,
  B01000010,
  B00000000
},
veryBad_bmp[] =
{ B00000000,
  B00000000,
  B01000010,
  B00100100,
  B00000000,
  B00111100,
  B01000010,
  B00000000
};
 
//----------------------------------------------------------------------------------------------------------------------
float get_dustDensity() {
  int samplingTime = 280;
  int deltaTime = 40;
  int sleepTime = 9680;
  float voMeasured = 0;
  float calcVoltage = 0;
  float dustDensity = 0;
 
  digitalWrite(ledPower, LOW); 
  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(measurePin); 
 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH); 
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = (0.17 * calcVoltage - 0.1) * 1000;
 
  return dustDensity;
}
 
void dustCheckLed(float data) {
  if (data > 201) {
    //매우 나쁨
    matrix.clear();
    matrix.drawBitmap(0, 0, veryBad_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
  }
  else if (data > 120) {
    //나쁨
    matrix.clear();
    matrix.drawBitmap(0, 0, bad_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
  }
  else if (data > 80) {
    //약간 나쁨
    matrix.clear();
    matrix.drawBitmap(0, 0, normal_bmp, 8, 8, LED_YELLOW);
    matrix.writeDisplay();
  }
  else if (data > 30) {
    matrix.clear();
    matrix.drawBitmap(0, 0, good_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
  }
  else {
    matrix.clear();
    matrix.drawBitmap(0, 0, veryGood_bmp, 8, 8, LED_GREEN);
    matrix.writeDisplay();
  }
}
//----------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);
  pre_dustDensity = get_dustDensity();
  lcd.begin(16, 2);
  matrix.begin(0x70);  // pass in the address
}
 
//----------------------------------------------------------------------------------------------------------------------
void loop() {
 
  float temp, humi;
  float now_dustDensity = get_dustDensity();
  float filtered_dustDensity = (now_dustDensity * sensitivity) + (pre_dustDensity * (1 - sensitivity));
  float  abs_filtered_dustDensity = abs(filtered_dustDensity);
 
  dht11.read(humi, temp);
  delay(DHT11_RETRY_DELAY);
  lcd.clear();
 
  dustCheckLed(abs_filtered_dustDensity);
 
  Serial.print(abs_filtered_dustDensity);
  Serial.println("mg");
  lcd.setCursor(0, 0);
  lcd.print("Dust:");
  lcd.print(abs_filtered_dustDensity);
  lcd.print("mg");
 
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temp);
 
  lcd.print(" H:");
  lcd.print(humi);
}
