#include <Servo.h>
int trig = 8;
int echo = 9;
Servo servo;
int distanceleft;
int distanceright;
int distancecenter;

void Stop() {
  digitalWrite(2, 0)  ;
  digitalWrite(3, 0);
  digitalWrite(5, 0);
}
void forward() {
  analogWrite(2,  0);
  analogWrite(3, 255);
  analogWrite(4, 0);
  analogWrite(5, 150);
}
void backward() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
}
void left() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  delay(1000);
}

void right() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  delay(1000);
}

int distanceCheck() {
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);
  float distance = duration / 58;
  return distance ;
}


void setup() {
  servo.attach(6);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {
  servo.write(120);//서보 가운데 보기
  float distance = distanceCheck();
  Serial.print(distance);
  Serial.println("cm");
  if (distance < 25) {
    Serial.println("stop");
    Stop();
    distancecenter = distance;
    servo.write(180);//왼쪽보기
    delay(450);                      
    distanceleft = distanceCheck();
    delay(400);
    servo.write(40);//오른쪽보기
    delay(450);
    distanceright = distanceCheck();
    delay(400);
    servo.write(120);//서보 가운데 보기
    if (distanceleft > distanceright ) {
      left();
    }
    else if (distanceleft < distanceright ) {
      right();
    }
  }
  else {
    forward();
  }
}
