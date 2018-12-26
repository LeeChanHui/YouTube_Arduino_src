#include <Keypad.h>
#include<Servo.h>
Servo servo;
#define ROWS  4
#define COLS  4
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
int password = 1234;

Keypad keypad = Keypad(makeKeymap(keys), rowPins,
                       colPins, ROWS, COLS);

int in() {
  char input_char[4];
  for (char i = 0; i < 4; i++) {
    char key1;
    while (1) {
      key1 = keypad.getKey();
      if (key1 != 0) break;
    }
    input_char[i] = key1 - 48;
  }
  int input_num = (1000  input_char[0]) + (100  input_char[1]) + (10  input_char[2]) + (1  input_char[3]);

  return input_num;
}
void changePassword() {
  int input_num = in();
  if (input_num == password) {
    Serial.println("맞음 바꿈");
    password = in();
  } else {
    Serial.println("틀림");
  }
}
void setup() {
  Serial.begin(9600);
  servo.attach(10);
}

void loop() {
  char key2 = keypad.getKey();
  if (key2) {
    if (key2 == 'A') {
      Serial.println("checkPassword");
      int input_num = in();
      if (input_num == password) {
        Serial.println("맞음");
        servo.write(0);
        delay(1000);
      } else {
        Serial.println("틀림");
       
      }
      Serial.println(input_num);
    }
    else if (key2 == 'B') {
      Serial.println("changePassword");
      changePassword();
    }
     if (key2 == 'C') {
      servo.write(90);
      delay(1000);
    }
  }
}
