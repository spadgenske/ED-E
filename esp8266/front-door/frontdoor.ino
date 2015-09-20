/*
ESP8266 Front Door Notifier
copyright (c) 2015 Tyler Spadgenske
*/
 
#include <ESP8266WiFi.h>

#define DEVICE_ID "d11"
#define HOST "192.168.0.107"
#define PORT 21

const char* ssid = "spadgenske";
const char* password = "68mustang";

void setup() {

}

void loop() {
  //Connect to network
  delay(2000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to "); 
  Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) {
    Serial.print(".");
    delay(500);
    //Return error if cannot connect
    if(i == 21){
      Serial.print("Could not connect to"); 
      Serial.println(ssid);
      while(1) delay(500);
    }
  }
  // Attempt a connection with base unit
   WiFiClient client;
   if (!client.connect(HOST, PORT)) {
     Serial.println("connection failed");
     return;
  }
  else {
    Serial.print("Connected to base");
    client.write(DEVICE_ID);
    Serial.print("Sent data");
  }
  Serial.print("Entering Sleep Mode");
  ESP.deepSleep(6000000, WAKE_RF_DEFAULT); // Sleep for 6 seconds, then wait for sensor change
}
