#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String PrimaryID;

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  // get input from card and stored in **tag** -> 
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      PrimaryID += rfid.uid.uidByte[i]; 
    }                                    // <-
    
    Serial.println(PrimaryID+"hi");


    
    // reset the tag ->
    PrimaryID = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1(); // <-
  }
}
