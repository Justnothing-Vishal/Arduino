#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Varata Mamey Drrrrrr"
#define WIFI_PASSWORD "12345678"

/* 2. Define the API Key */
#define API_KEY "AIzaSyDm5aC4dgldNG_itfADcuJepTIaUiQeBjI"

/* 3. Define the project ID */
#define FIREBASE_PROJECT_ID "nfc-for-non-supported-de-39d3b"

/* 4. Define the user Email and password that alreadey registerd or added in your project */
//need to upgrade here
#define USER_EMAIL "justnothing@skiff.com"
#define USER_PASSWORD "12345678"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

int status=0;
void setup() {
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the project host and api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

#if defined(ESP8266)
    // In ESP8266 required for BearSSL rx/tx buffer for large data handle, increase Rx size as needed.
    fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
#endif

    // Limit the size of response payload to be collected in FirebaseData
    fbdo.setResponseSize(2048);

    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);
}

void loop() {
    if(status==0){
      status=1;

      String path="Primary_ID/123456";

      FirebaseJson content;

      content.set("fields/College_ID/integerValue",45);
      content.set("fields/Name/stringValue","john_wick");
      
      // by changing the create -> patch you can update 
      if(Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), content.raw(), "temperature,humidity")){
        Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        return;
      }else{
        Serial.println(fbdo.errorReason());
      }

       
      if(Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), content.raw())){
         Serial.printf("ok\n%s\n\n",fbdo.payload().c_str()); 
      }else{
        Serial.print(fbdo.errorReason()); 
      }
    }
}
