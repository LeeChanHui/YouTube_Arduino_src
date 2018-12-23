#include "LedControl.h"
LedControl lc = LedControl(12, 10, 11, 1);
//Parameter: LedControl(DATA_IN, CLOCK, LOAD(/CS), Number_of_Object)

void setup()
{
  lc.shutdown(0, false); //Wake Up
  lc.setIntensity(0, 8); //Brightness: 8 (0~15)
  lc.clearDisplay(0); //Clear
}
void loop()
{
  char col = 0; //Column: 0 ~ 7
  char row = 0; //Row: 0~7
  
  lc.setLed(0, col, row, true); //ON
  delay(500);
  lc.setLed(0, col, row, false); //OFF
  delay(500);
}

