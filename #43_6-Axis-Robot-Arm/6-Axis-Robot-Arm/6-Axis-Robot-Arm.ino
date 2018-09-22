/*
   rotation(90);
   center(90,90,90,90);
   gripper(0);
*/

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  servo1.attach(2, 550, 2070);
  servo2.attach(3, 630, 2200);
  servo3.attach(4, 600, 2100);
  servo4.attach(5, 580, 2270);
  servo5.attach(6, 700, 2350);
  servo6.attach(7);
}

void loop() {
  unsigned char degree1 = map(constrain(analogRead(A0), 120, 900), 120, 900, 0, 180);
  unsigned char degree2 = map(constrain(analogRead(A1), 120, 900), 120, 900, 0, 180);
  unsigned char degree3 = map(constrain(analogRead(A2), 160, 900), 160, 900, 180, 0);
  unsigned char degree4 = map(constrain(analogRead(A3), 120, 800), 120, 800, 0, 180);
  unsigned char degree5 = map(constrain(analogRead(A4), 120, 900), 120, 900, 0, 180);
  unsigned char degree6 = map(constrain(analogRead(A5), 300, 900), 300, 900, 0, 120);
  rotation(degree1);
  center(degree2, degree3, degree4, degree5);
  gripper(degree6);

}

void rotation(unsigned char degree1) {
  servo1.write(degree1);
}

void center(unsigned char degree2, unsigned char degree3, unsigned char degree4, unsigned char degree5) {
  servo2.write(degree2);
  servo3.write(180 - degree3);
  servo4.write(180 - degree4);
  servo5.write(degree5);
}

void gripper(unsigned char degree6) {
  servo6.writeMicroseconds(960 + (5 * degree6));
}
