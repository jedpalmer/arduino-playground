
#include <FastLED.h>
#define NUM_LEDS 150
#define DATA_PIN 5

CRGB leds[NUM_LEDS];

bool color_mode = 0;

void setup() {
  pinMode(5,OUTPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {

 //move a single dot around the LED Strip
  for (int i = 0; i < (NUM_LEDS/2); i++) {
    leds[2*i] = CRGB::Yellow;
    leds[(2*i+1)%150] = CRGB::Yellow;
    leds[((2*i+75)%150)] = CRGB::Red;
    leds[((2*i+76)%150)] = CRGB::Red;
    FastLED.show();
//    FastLED.delay(3);
  }
}

void fillPixels(int start, int finish, CRGB color) {
  for (int j = start; j > finish; j++) {
    leds[j] = color;
    }
}

