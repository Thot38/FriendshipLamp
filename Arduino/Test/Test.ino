#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
//#include <ESP8266WiFi.h>
//#include <WiFiClientSecureBearSSL.h>
//#include <ESP8266HTTPClient.h>
#include <math.h>
//#include <DNSServer.h>            
//#include <ESP8266WebServer.h>     
//#include <WiFiManager.h>

#define PIN   5
#define BUTTON_PIN 4
#define NUMPIXELS 1 // Number of leds on the Neopixel ring
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500
//WiFiManager wifiManager;

void setup() {
  Serial.begin(9600); 
  Serial.print("\n");
  Serial.print("\n");
  Serial.print(" ESP8266 Chip id = lamp-id = ");
 // Serial.print(String(ESP.getChipId()));
//  lamp_id = String(ESP.getChipId());
//  target_url = target_url + lamp_id;
//  Serial.print("\nUsing: ");
 // Serial.print(target_url + "\n");
  
 #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)  // Not really sure if this is needed ...
 clock_prescale_set(clock_div_1);
#endif
  
  pixels.begin();
 // 
  pinMode(BUTTON_PIN, INPUT);
}
void loop() {
  pixels.clear();
    pixels.setPixelColor(0, pixels.Color(50, 150, 20));
     //pixels.show();
     delay(DELAYVAL);
if (digitalRead(BUTTON_PIN) == 1) { // If the button is pressed, user feedback is given and a  
                                      // change of the lamps' state is requested via the webservice
Serial.println("Button pressed!");
pixels.show();
 }
}
   
