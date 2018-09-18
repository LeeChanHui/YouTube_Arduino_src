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
        key.keyByte[i] = 0xFF;}
}

void loop() {
    if ( ! mfrc522.PICC_IsNewCardPresent()) return;
    if ( ! mfrc522.PICC_ReadCardSerial()) return;
        
    byte blockAddr      = 4;
    byte dataBlock[]    = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x08, 0x09, 0x0a, 0x0b,
        0x0c, 0x0d, 0x0e, 0x0f
    };
    byte trailerBlock   = 7;


    Serial.println(F("Authenticating..."));
    mfrc522.PCD_Authenticate
    (MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

    Serial.println(F("Writing data into block "));
    mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
    Serial.println("Success! Hallelujah!");

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}

