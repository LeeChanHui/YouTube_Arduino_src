#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define RST_PIN   9
#define SDA_PIN   10

MFRC522 mfrc522(SDA_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin();

  lcd.backlight();


  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;
  lcd.clear();
  byte blockAddr      = 4;
  byte trailerBlock   = 7;
  byte accessByte[]    = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f
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
  lcd.setCursor(0,1);
  for (byte i = 8; i < 16; i++) {
    lcd.print(buffer[i] < 0x10 ? "0" : "");
    lcd.print(buffer[i], HEX);
    delay(50);
  }
  delay(1000);
  lcd.clear();
  char cnt = 0;
  for(char i = 0; i <16; i++){
    if(accessByte[i] == buffer[i]){}
    else{
      cnt++;
    }
  }

  if(cnt ==0){
    lcd.print("Authorized.Good!");
  }
  else{
    lcd.print("Permission");
    lcd.setCursor(0,1);
    lcd.print("denied...");
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

