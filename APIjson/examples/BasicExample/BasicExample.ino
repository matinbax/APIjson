#include <APIjson.h>
#include <Arduino.h>

const char* clientid = "your_clientID"; // wifi name
const char* paclientword = "your_PAclientWORD"; // wifi pass
const char* serverUrl = "http://example.com/api/data";

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

  //e.g. for put requst
  const char* inputs = "lit=2,temp=25,hum=60";
  String responsePost = client.httpPost(serverUrl, inputs);
  Serial.println("POST Response: ");
  Serial.println(responsePost);

  //e.g. for post requst
  const char* putInputs = "name=John,age=30";
  String responsePut = client.httpPut(serverUrl, putInputs);
  Serial.println("PUT Response: ");
  Serial.println(responsePut);

  // e.g. for delete requst
  String responseDelete = client.httpDelete(serverUrl);
  Serial.println("DELETE Response: ");
  Serial.println(responseDelete);
}

void loop() {
  // :)
}
