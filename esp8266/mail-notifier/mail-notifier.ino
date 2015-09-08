/*
ESP8266 Mail Notifier
copyright (c) 2015 Tyler Spadgenske
*/
 
#include <ESP8266WiFi.h>

#define HOST "192.168.0.102"
#define PORT 21

const char* ssid = "spadgenske";
const char* password = "68mustang";

void setup() {
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
}

void loop() {
  // Attempt a connection with base unit
   WiFiClient client;
   if (!client.connect(HOST, PORT)) {
     Serial.println("connection failed");
     return;
  }
  else {
    Serial.print("Connected");
    client.write("\nHello");
  }
  while(1){
    bool stat = client.connected();
    if (stat){
      client.write("Do you hear me");
      delay(2000);
    }
    else
    {
      Serial.print("\nLost Connection with ");
      Serial.print(HOST);
    }
  }
}