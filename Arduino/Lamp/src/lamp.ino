#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <string>
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
  // Serial.print("\n");
  // Serial.print("\n");
  // Serial.print(" ESP8266 Chip id = lamp-id = ");

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  // pinMode(BUTTON_PIN, INPUT);

  pixels.begin();
}


void loop() {
  pixels.clear();

  Serial.println(String(sensorValue));
  Serial.write("\n");
  sensorValue = analogRead(BUTTON_PIN);
  // int analogOut = 1;
  pixels.setBrightness(25);
  Serial.write("test");
  // for(int i=0; i<NUMPIXELS; i++) {

    if(sensorValue > 100){
      pixels.setPixelColor(1, pixels.Color(0, 0, 150));
      Serial.println("a");
    }else{
      pixels.setPixelColor(1, pixels.Color(150, 0, 0));
      Serial.println("b");
    }
    pixels.show();
    delay(DELAYVAL);
  // }
}