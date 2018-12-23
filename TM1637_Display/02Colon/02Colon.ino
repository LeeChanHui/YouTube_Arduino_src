#include "SevenSegmentTM1637.h"
#define PIN_CLK   2
#define PIN_DIO   3
SevenSegmentTM1637 display(PIN_CLK, PIN_DIO);

void setup() {
  display.begin();
  display.setBacklight(100);
  
  display.setColonOn(true);
  display.print(1234);
  delay(1000);
}


void loop() {
  display.clear();
  display.setCursor(0, 2);
  display.print(99);
  delay(2000);
  
  display.clear();
  display.print("ABCD");
  delay(2000);

}

