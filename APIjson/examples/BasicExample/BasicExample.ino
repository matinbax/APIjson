#include <APIjson.h>
#include <Arduino.h>

const char* clientid = "ssid"; // wifi name
const char* paclientword = "pass"; // wifi pass
const char* serverUrl = "https://testurlfor get.mamad";

APIjson client;

void setup() {
  Serial.begin(115200);

  //connect to wifi
  WiFi.begin(clientid, paclientword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  //e.g. for get requst
  String responseGet = client.httpGet(serverUrl);
  Serial.println("GET Response: ");
  Serial.println(responseGet);
}
  //
void loop() {
  // :)
}
