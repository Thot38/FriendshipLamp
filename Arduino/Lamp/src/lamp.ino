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
#define PIN       5
#define NUMPIXELS 6
const int BUTTON_PIN = A0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

int lampColor = 0;

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

int loopCounter = 0;
void loop() {  
  // if not connected, show red (todo: show animation here)
  if(WiFi.status() != WL_CONNECTED){
    lampColor = pixels.Color(255, 0, 0);
  }
  else{
    // --- every n seconds, query the current lamp state
    if(loopCounter == 0){
      lampColor = GetLampState().toInt();
    }

    // if sensor is pressed, call set state
    if(sensorPressed()){
      lampColor = pixels.Color(0,0,255);
      showColor();
      lampColor = SetLampState().toInt();
    }
  }

  // reset loop counter, after 100 times
  if(++loopCounter > 100) loopCounter = 0;
  showColor();
  delay(DELAYVAL);
}

int previousColor = 0;
void showColor(){
  if(lampColor < 16777216 && lampColor >= 0){
    if(previousColor == lampColor){
      pixels.clear();
      pixels.setBrightness(255);
      for(int i = 0; i < NUMPIXELS; i++){
        pixels.setPixelColor(i,lampColor);
      }
    }
  }
  else{
    // rainbow code here for undefined colors
  }

  pixels.show();
  previousColor = lampColor;
}


String GetColor(){
  return httpGet("Color");
}

String GetLampState(){
  String path = LAMP_ID;
  path += "/";
  path += USER_NAME;
  return httpGet(path);
}

String SetLampState(){
  String path = LAMP_ID;
  path += "/";
  path += USER_NAME;
  return httpPatch(path);
}


String httpGet(String path){
  
  WiFiClientSecure client;  // or WiFiClientSecure for HTTPS
  HTTPClient httpClient;

  client.setInsecure();

  String url = URL;
  url +=  path;

  httpClient.begin(client,  url);

  Serial.printf_P(PSTR("%lu: Starting GET request to %s\r\n"), millis(),  URL);
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

    return getResult;
}

String httpPatch(String path){
  
  WiFiClientSecure client;  // or WiFiClientSecure for HTTPS
  HTTPClient httpClient;

  client.setInsecure();

  String url = URL;
  url +=  path;

  httpClient.begin(client,  url);

  Serial.printf_P(PSTR("%lu: Starting PATCH request to %s\r\n"), millis(),  URL);
    String patchResult = "";
    int respCode = httpClient.PATCH("");
    if (respCode >= 400) {
        Serial.printf_P(PSTR("%lu: HTTP Error %d\r\n"), millis(), respCode);
    } else if (respCode > 0) {
        Serial.printf_P(PSTR("%lu: HTTP %d\r\n"), millis(), respCode);
        patchResult = httpClient.getString();
        Serial.printf_P(PSTR("\t%s\r\n"), patchResult.c_str());
    } else {
        Serial.printf_P(PSTR("%lu: error: %s\r\n"), millis(), HTTPClient::errorToString(respCode).c_str());
    }
    httpClient.end();

    return patchResult;
}


bool sensorPressed(){
  return analogRead(BUTTON_PIN) > 100;
}

