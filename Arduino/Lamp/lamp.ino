#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN   5
#define BUTTON_PIN 4
#define NUMPIXELS 1 // Number of leds on the Neopixel ring
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

void setup()
{
  Serial.begin(9600); 
  Serial.print("\n");
  Serial.print("\n");
  Serial.print(" ESP8266 Chip id = lamp-id = ");	
}

void loop()
{
	
}
