#ifndef APIjson_h
#define APIjson_h

#include <Arduino.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>   
  #include <ESP8266HTTPClient.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #error "This library only supports ESP8266 and ESP32 platforms."
#endif

class APIjson {
  public:
    APIjson(); 
    String httpGet(const char* serverUrl);
    String httpPost(const char* serverUrl, const char* input);
    String httpPut(const char* serverUrl, const char* input);
    String httpDelete(const char* serverUrl);

  private:
   bool isNumeric(String str); 
    String convertToJson(String input);
};

#endif
