#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN    9
#define SDA_PIN    10

MFRC522 mfrc522(SDA_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;

  byte blockAddr      = 4;
  byte trailerBlock   = 7;
  byte len;
  byte buffer[16];
  Serial.println("Type anything without space, ending with # (smaller than 16 Charaters)");
  while (!Serial.available());
  len = Serial.readBytesUntil('#', (char *) buffer, 16) ;
  for (byte i = len; i < 16; i++) buffer[i] = ' ';

  Serial.println(F("Authenticating..."));
  mfrc522.PCD_Authenticate
  (MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  Serial.println(F("Writing data into block "));
  mfrc522.MIFARE_Write(blockAddr, buffer, 16);
  Serial.println("Success! Hallelujah!");

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

