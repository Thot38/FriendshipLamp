#include "config.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <string>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        5
#define NUMPIXELS 5
const int BUTTON_PIN = A0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

int sensorValue = 0;

void setup() {
  Serial.begin(9600);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  // pinMode(BUTTON_PIN, INPUT);
  // if(sensorPressed()){
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("CIRCUIT DIGEST WiFi Manager");
  // }

  pixels.begin();
}


void loop() {
  pixels.clear();
  
  heartbeat();
  
  Serial.write("\n");
  pixels.setBrightness(25);
    
    if(sensorPressed()){
      pixels.setPixelColor(0, pixels.Color(0,0,255));
      Serial.println("a");
    }
    else{
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));
      Serial.println("b");
    }
    pixels.show();
    delay(DELAYVAL);
}

bool beat = false;
void heartbeat(){
  Serial.println(WiFi.status());
  if(millis() % 5000){
    httpGet();
  }
  if(beat){
    auto color = pixels.Color(255, 0, 0);
    if(WiFi.status() == WL_CONNECTED){
       color = pixels.Color(0, 255, 0);
    }
    pixels.setPixelColor(NUMPIXELS - 1, color);
    pixels.show();
  }
  beat = !beat;
}

void httpGet(){
  
  WiFiClient client;  // or WiFiClientSecure for HTTPS
  HTTPClient httpClient;

  httpClient.begin(client,  "http://arduinojson.org/example.json");

  Serial.printf_P(PSTR("%lu: Starting GET request to %s\r\n"), millis(),  "http://arduinojson.org/example.json");
    String getResult = "";
    int respCode = httpClient.GET();
    if (respCode >= 400) {
        Serial.printf_P(PSTR("%lu: HTTP Error %d\r\n"), millis(), respCode);
    } else if (respCode > 0) {
        Serial.printf_P(PSTR("%lu: HTTP %d\r\n"), millis(), respCode);
        getResult = httpClient.getString();
        Serial.printf_P(PSTR("\t%s\r\n"), getResult.c_str());
    } else {
        Serial.printf_P(PSTR("%lu: error: %s\r\n"), millis(), HTTPClient::errorToString(respCode).c_str());
    }
    httpClient.end();
}

bool sensorPressed(){
  return analogRead(BUTTON_PIN) > 100;
}

