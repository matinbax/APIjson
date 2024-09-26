#include "APIjson.h"
#include <ArduinoJson.h> // نسخه 5

APIjson::APIjson() {
  // Constructor خالی
}

String APIjson::convertToJson(String input) {
  StaticJsonBuffer<200> jsonBuffer; // استفاده از StaticJsonBuffer در نسخه 5
  JsonObject& jsonObject = jsonBuffer.createObject();

  String key = "";
  String value = "";
  bool isKey = true;

  for (int i = 0; i < input.length(); i++) {
    char currentChar = input[i];

    if (currentChar == ',') {
      jsonObject[key] = value;
      key = "";
      value = "";
      isKey = true;
    } else if (currentChar == '=') {
      isKey = false;
    } else {
      if (isKey) {
        key += currentChar;
      } else {
        value += currentChar;
      }
    }
  }

  // افزودن آخرین جفت کلید-مقدار
  if (key.length() > 0 && value.length() > 0) {
    jsonObject[key] = value;
  }

  String jsonString;
  jsonObject.printTo(jsonString); // serializeJson در نسخه 5 به printTo تغییر کرده
  return jsonString;
}

String APIjson::httpGet(const char* serverUrl) {
  String payload;
  bool isHttps = strstr(serverUrl, "https://") != nullptr;
  HTTPClient http;
  WiFiClient client;
  WiFiClientSecure secureClient;

  if (isHttps) {
    secureClient.setInsecure();
    if (http.begin(secureClient, serverUrl)) {
      int httpCode = http.GET();
      if (httpCode > 0) {
        payload = http.getString();
      } else {
        payload = "Error on HTTP request";
      }
      http.end();
    } else {
      payload = "Unable to connect";
    }
  } else {
    if (http.begin(client, serverUrl)) {
      int httpCode = http.GET();
      if (httpCode > 0) {
        payload = http.getString();
      } else {
        payload = "Error on HTTP request";
      }
      http.end();
    } else {
      payload = "Unable to connect";
    }
  }
  return payload;
}
