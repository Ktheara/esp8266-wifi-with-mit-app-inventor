#include <ESP8266WiFi.h>

//Wifi
const char *ssid = "ESP-AP";
const char *password = "1234567890";
const uint8_t wifi_channel = 1;  //Default channel 1, Wi-Fi channel, from 1 to 13
bool hide_ssid = false; //set to true will hide SSID
const uint8_t max_connection = 4; //Default 4, max simultaneous connected stations, from 0 to 8

// SoftAP
IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

// Web Server
WiFiServer server(80);

String client_response = "-"; 

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();

  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid, password, wifi_channel, hide_ssid, max_connection) ? "Ready" : "Failed!"); //Wifi with password.
  //Serial.println(WiFi.softAP(ssid) ? "Ready" : "Failed!"); //Wifi without password.

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

void loop() {
  // If there no server connection, return
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  //Wait for client available
  while(!client.available()){
    delay(1);
  }
 
  //Read from client.
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  client_response = request;
  
  // Response to client.
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  Comillas importantes.
  client.print(client_response); //msg to client
 
}
