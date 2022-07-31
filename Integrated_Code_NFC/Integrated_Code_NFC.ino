#include <SPI.h>      
#include <MFRC522.h>  
#include <Arduino.h>
#include<ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
//#include "addons/RTDBHelper.h"

// Selecting wifi to connect
#define WIFI_SSID "Varata Mamey Drrrrrr"
#define WIFI_PASSWORD "12345678"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDm5aC4dgldNG_itfADcuJepTIaUiQeBjI"

// Insert Firebase project ID
#define FIREBASE_PROJECT_ID "PROJECT_ID" 

// Insert RTDB URLefine the RTDB URL 
#define DATABASE_URL "https://nfc-for-non-supported-de-39d3b-default-rtdb.europe-west1.firebasedatabase.app/" 

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

// variable decleration 
String PrimaryID;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;

void setup() {
  Serial.begin(115200);

  // RC522 connection
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  
  // Wifi connection 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();    

  // Firebase connection
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);  
}

void loop() {
  // Card is not detected
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  // Card is detected  
  if (rfid.PICC_ReadCardSerial()) {
    // get input from card and stored in **PrimaryID** 
    for (byte i = 0; i < 4; i++) {
      PrimaryID += rfid.uid.uidByte[i]; 
    }                                    
    
    Serial.println(PrimaryID);

    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/test/int")) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
        Serial.println(intValue);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    
    if (Firebase.RTDB.getFloat(&fbdo, "/test/float")) {
      if (fbdo.dataType() == "float") {
        floatValue = fbdo.floatData();
        Serial.println(floatValue);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }


    
    // reset the tag ->
    PrimaryID = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1(); // <-
  }
}
