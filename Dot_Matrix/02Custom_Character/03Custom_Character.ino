#include "LedControl.h"
LedControl lc = LedControl(13, 11, 12, 1);
//Parameter: LedControl(DATA_IN, CLOCK, LOAD(/CS), Number_of_Object)


void setup()
{
  lc.shutdown(0, false); //Wake Up
  lc.setIntensity(0, 8); //Brightness: 8 (0~15)
  lc.clearDisplay(0); //Clear
}
void loop()
{
  big_Heart();
  delay(500);
  small_Heart();
  delay(500);
}

void small_Heart()
{
  boolean charater[8][8] { //이차원 배열
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
  };
  
for (char row = 0; row < 8; row++) { //이중 for로 표시
    for (char col = 0; col < 8; col++) {
      if (charater[row][col] == 0) {
        lc.setLed(0, col, 7 - row, false); }
      else if (charater[row][col] == 1) {
        lc.setLed(0, col, 7 - row, true); }
    }
  }
}
void big_Heart()
{
  boolean charater[8][8] {
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 1, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0},
  };
  for (char row = 0; row < 8; row++) {
    for (char col = 0; col < 8; col++) {
      if (charater[row][col] == 0) {
        lc.setLed(0, col, 7 - row, false); }
      else if (charater[row][col] == 1) {
        lc.setLed(0, col, 7 - row, true); }
    }
  }
}

