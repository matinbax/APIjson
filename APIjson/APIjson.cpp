#include "APIjson.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

APIjson::APIjson() {
}

String APIjson::convertToJson(String input) {
  DynamicJsonDocument doc(1024);
  String key = "";
  String value = "";
  bool isKey = true;

  
  for (int i = 0; i < input.length(); i++) {
    char currentChar = input[i];

    if (currentChar == ',') {
      if (isNumeric(value)) {
        doc[key] = value.toFloat(); 
      } else {
        doc[key] = value;
      }
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

  if (key.length() > 0 && value.length() > 0) {
    if (isNumeric(value)) {
      doc[key] = value.toFloat(); 
    } else {
      doc[key] = value; 
    }
  }

  String jsonString;
  serializeJson(doc, jsonString);
  return jsonString;
}
bool APIjson::isNumeric(String str) {
  for (unsigned int i = 0; i < str.length(); i++) {
    if (!isDigit(str[i]) && str[i] != '.' && str[i] != '-') {
      return false;
    }
  }
  return true;
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

String APIjson::httpPost(const char* serverUrl, const char* input) {
  String payload;
  bool isHttps = strstr(serverUrl, "https://") != nullptr;
  HTTPClient http;
  WiFiClient client;
  WiFiClientSecure secureClient;

  String jsonData = convertToJson(input);

  if (isHttps) {
    secureClient.setInsecure();
    if (http.begin(secureClient, serverUrl)) {
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST(jsonData);
      if (httpCode > 0) {
        payload = http.getString();
      } else {
        payload = "POST request failed";
      }
      http.end();
    } else {
      payload = "Unable to connect";
    }
  } else {
    if (http.begin(client, serverUrl)) {
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST(jsonData);
      if (httpCode > 0) {
        payload = http.getString();
      } else {
        payload = "POST request failed";
      }
      http.end();
    } else {
      payload = "Unable to connect";
    }
  }
  return payload;
}

String APIjson::httpPut(const char* serverUrl, const char* input) {
  String payload;
  bool isHttps = strstr(serverUrl, "https://") != nullptr;
  HTTPClient http;
  WiFiClient client;
  WiFiClientSecure secureClient;

  String jsonData = convertToJson(input);
  if (isHttps) {
    secureClient.setInsecure();
    if (http.begin(secureClient, serverUrl)) {
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.PUT(jsonData);
      if (httpCode > 0) {
        payload = http.getString();
      } else {
        payload = "PUT request failed";
      }
      http.end();
    } else {
      payload = "Unable to connect";
    }
  } else {
    if (http.begin(client, serverUrl)) {
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.PUT(jsonData);
      if (httpCode > 0) {
        payload = http.getString();
      } else {
        payload = "PUT request failed";
      }
      http.end();
    } else {
      payload = "Unable to connect";
    }
  }
  return payload;
}

String APIjson::httpDelete(const char* serverUrl) {
  String payload;
  bool isHttps = strstr(serverUrl, "https://") != nullptr;
  HTTPClient http;
  WiFiClient client;
  WiFiClientSecure secureClient;

  if (isHttps) {
    secureClient.setInsecure();
    if (http.begin(secureClient, serverUrl)) {
      int httpCode = http.sendRequest("DELETE");
      if (httpCode > 0) {
        payload = http.getString();
      } else {
        payload = "DELETE request failed";
      }
      http.end();
    } else {
      payload = "Unable to connect";
    }
  } else {
    if (http.begin(client, serverUrl)) {
      int httpCode = http.sendRequest("DELETE");
      if (httpCode > 0) {
        payload = http.getString();
      } else {
        payload = "DELETE request failed";
      }
      http.end();
    } else {
      payload = "Unable to connect";
    }
  }
  return payload;
}
