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
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
bool taskCompleted = false;

unsigned long dataMillis = 0;


void setup()
{

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

    /* Assign the api key (required) */
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

    // For sending payload callback
    // config.cfs.upload_callback = fcsUploadCallback;
}

void loop()
{

    // Firebase.ready() should be called repeatedly to handle authentication tasks.

    if (Firebase.ready() && (millis() - dataMillis > 60000 || dataMillis == 0))
    {
        dataMillis = millis();

        /*if (!taskCompleted)
        {
            taskCompleted = true;

            // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create.ino
            FirebaseJson content;

            content.set("fields/Japan/mapValue/fields/time_zone/integerValue", "9");
            content.set("fields/Japan/mapValue/fields/population/integerValue", "125570000");

            content.set("fields/Belgium/mapValue/fields/time_zone/integerValue", "1");
            content.set("fields/Belgium/mapValue/fields/population/integerValue", "11492641");

            content.set("fields/Singapore/mapValue/fields/time_zone/integerValue", "8");
            content.set("fields/Singapore/mapValue/fields/population/integerValue", "5703600");

            // info is the collection id, countries is the document id in collection info.
            String documentPath = "info/countries";

            Serial.print("Create document... ");*/

           //if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw()))
           //     Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
          //  else
          //      Serial.println(fbdo.errorReason());
       // }
        String path="Primary_ID/123456";
        FirebaseObject object = Firebase.get(path);

        String College = object.getString("College_ID");

        Serial.println(String(College));
        
        // If the document path contains space e.g. "a b c/d e f"
        // It should encode the space as %20 then the path will be "a%20b%20c/d%20e%20f"

        Serial.print("Get a document... ");

        if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), mask.c_str()))
            Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        else
            Serial.println(fbdo.errorReason());
    }
}
