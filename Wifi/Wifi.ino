#include <WiFi.h>

const char* ssid     = "iotbegin200";
const char* password = "iotbegin200";
void setup() 
{
  Serial.begin(9600);
  // put your setup code here, to run once:
  WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
Serial.println("wifi connected");
}

void loop() 
{
  // put your main code here, to run repeatedly:

}
