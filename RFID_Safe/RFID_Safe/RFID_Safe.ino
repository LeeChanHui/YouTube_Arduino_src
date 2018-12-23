#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include <Servo.h>

Servo myservo;

#define RST_PIN   9
#define SDA_PIN   10

MFRC522 mfrc522(SDA_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
#define piezo_Pin  4
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin();
  myservo.attach(7);
  lcd.backlight();
  myservo.write(70);
  lcd.print("LOCKED!!!");
  pinMode (piezo_Pin, OUTPUT);
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;
  lcd.clear();
  byte blockAddr      = 9;
  byte trailerBlock   = 11;
  byte accessByte[]    = {
    0x69, 0x5F, 0x77, 0x69,
    0x6C, 0x6C, 0x5F, 0x61,
    0x6E, 0x73, 0x77, 0x65,
    0x72, 0x20, 0x20, 0x20
  };

  byte buffer[18];
  byte size = sizeof(buffer);

  Serial.println(F("Authenticating using key A..."));
  mfrc522.PCD_Authenticate
  (MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  Serial.println(F("Reading data from block "));
  mfrc522.MIFARE_Read(blockAddr, buffer, &size);

  for (byte i = 0; i < 8; i++) {
    lcd.print(buffer[i] < 0x10 ? "0" : "");
    lcd.print(buffer[i], HEX);
    delay(50);
  }
  lcd.setCursor(0, 1);
  for (byte i = 8; i < 16; i++) {
    lcd.print(buffer[i] < 0x10 ? "0" : "");
    lcd.print(buffer[i], HEX);
    delay(50);
  }
  delay(1000);
  lcd.clear();
  char cnt = 0;
  for (char i = 0; i < 16; i++) {
    if (accessByte[i] == buffer[i]) {}
    else {
      cnt++;
    }
  }

  if (cnt == 0) {
    lcd.print("Authorized.Good!");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("OPENED!");
    myservo.write(120);
    tone (piezo_Pin, 261);
    delay(150);
    tone (piezo_Pin, 329);
    delay(150);
    tone (piezo_Pin, 391);
    delay(150);
    noTone(piezo_Pin);
  }
  else {
    lcd.print("Permission");
    lcd.setCursor(0, 1);
    lcd.print("denied...  :(");
    myservo.write(70);
    tone (piezo_Pin, 349);
    delay(150);
    noTone(piezo_Pin);
    delay(150);
    tone (piezo_Pin, 349);
    delay(150);
    noTone(piezo_Pin);
  }
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    lcd.print(buffer[i] < 0x10 ? " 0" : " ");
    lcd.print(buffer[i], HEX);
    delay(100);
  }
}

