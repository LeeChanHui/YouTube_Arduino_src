#include "SevenSegmentTM1637.h"
#define PIN_CLK   2
#define PIN_DIO   3

SevenSegmentTM1637 display(PIN_CLK, PIN_DIO);

void setup() {
  display.begin();
  display.setBacklight(100);
  display.setPrintDelay(2000);
}

void loop() {
  display.clear();
  display.print("ABCDEFABCDEF");

}

