#include <DS1302.h>
#define kCePin    8   // Chip Enable
#define kIoPin    7   // Input/Output
#define kSclkPin  6   // Serial Clock

DS1302 rtc(kCePin, kIoPin, kSclkPin);

void setup() {
  Serial.begin(9600);
  Serial.println("Type anything and Send it to me. Clock will be start!");
  while(!Serial.available());
  rtc.writeProtect(false);
  rtc.halt(false);
  Time t(2018, 9, 22, 18, 10, 00, Time::kSaturday);
  rtc.time(t);
}

void loop() {
  Time t = rtc.time();
  Serial.print(t.yr);
  Serial.print("/");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.date);
  Serial.print("(");
  Serial.print(t.day);
  Serial.print(")");
  Serial.print("  ");
  Serial.print(t.hr);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(":");
  Serial.println(t.sec);
  
  delay(1000);
}
