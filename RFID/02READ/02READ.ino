#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9
#define SDA_PIN   10

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

  byte blockAddr     = 9;
  byte trailerBlock   = 11;
  byte buffer[18];
  byte size = sizeof(buffer);

  Serial.println(F("Authenticating using key A..."));
  mfrc522.PCD_Authenticate
  (MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  Serial.println(F("Reading data from block "));
  mfrc522.MIFARE_Read(blockAddr, buffer, &size);

  dump_byte_array(buffer, 16); Serial.println();

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

