
#include <FastLED.h>
#inlcude <Serial.h>
#define NUM_LEDS 150
#define DATA_PIN 5
#define BRIGHTNESS 64
#define REFRESH_MILLIS 10

enum Mode {
  BORING_MODE = 1,
  SOLID_COLOR_SCROLL = 2,
  PARTY_LIGHTS = 3,
  CHASING_DOT = 4,
  WRONG = 5,
  CASH_CAB = 6
};

CRGB leds[NUM_LEDS];

enum Mode color_mode = BORING_MODE;
int frame_count = 1;

ColorTemperature colorTemps[20] = {UncorrectedTemperature,
  Candle,
  Tungsten40W,
  Tungsten100W, 
  Halogen,
  CarbonArc,
  HighNoonSun,
  DirectSunlight,
  OvercastSky,
  ClearBlueSky,

  WarmFluorescent,
  StandardFluorescent,
  CoolWhiteFluorescent,
  FullSpectrumFluorescent,
  GrowLightFluorescent,
  BlackLightFluorescent,
  MercuryVapor,
  SodiumVapor,
  MetalHalide,
  HighPressureSodium
  };

int colorTempIndex = 0;

  

/*
typedef enum {
  Candle=0xFF9329,
  Tungsten40W=0xFFC58F,
  Tungsten100W=0xFFD6AA, 
  Halogen=0xFFF1E0,
  CarbonArc=0xFFFAF4,
  HighNoonSun=0xFFFFFB,
  DirectSunlight=0xFFFFFF,
  OvercastSky=0xC9E2FF,
  ClearBlueSky=0x409CFF,

  WarmFluorescent=0xFFF4E5,
  StandardFluorescent=0xF4FFFA,
  CoolWhiteFluorescent=0xD4EBFF,
  FullSpectrumFluorescent=0xFFF4F2,
  GrowLightFluorescent=0xFFEFF7,
  BlackLightFluorescent=0xA700FF,
  MercuryVapor=0xD8F7FF,
  SodiumVapor=0xFFD1B2,
  MetalHalide=0xF2FCFF,
  HighPressureSodium=0xFFB74C
  
  UncorrectedTemperature=0xFFFFFF
  } ColorTemperature;
*/

void setup() {
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  int block_size = 10;
  bool alternate = false;
  CRGB color1 = CRGB::Red;
  CRGB color2 = CRGB::Yellow;  
  bool toggle = false;
  
  while(true){
    
  poll_button();
    
    EVERY_N_MILLISECONDS(REFRESH_MILLIS){
      //timer has told us it's time for a new frame, so update the colors

      switch (color_mode) {
        case BORING_MODE:
          // solid color white lights - management approved color
          // maybe add a pot to allow "color temperature" adjustment

          //once we are in this mode, additional button presses will cycle through color temperatures
          fill_solid(leds, NUM_LEDS, CRGB::White);

          if (frame_count > 1000){
            colorTempIndex = (colorTempIndex + 1) % 20;
            FastLED.setTemperature(colorTemps[colorTempIndex]);
            frame_count = 0;
            Serial.println(colorTemps[colorTempIndex]);
          }
          
          break;

        case SOLID_COLOR_SCROLL:
          // whole strip is a solid color, slow fade through color pallette
          break;
        case PARTY_LIGHTS:
          // crazy party lights from party color pallette
          break;
        case CHASING_DOT:
          // single pixel dot running around the strips
          break;
        case WRONG:
          // alternating blocks of 10 leds red and white
          // flash twice and switch places

          if (toggle){
            color1=CRGB::Black;
            color2=CRGB::Red;
          }
          else {
            color1=CRGB::Red;
            color2=CRGB::Black;
          }

          if (frame_count%25 < 2){          
            fill_solid(leds, NUM_LEDS, color1);
            for (int i = 0; i<(NUM_LEDS/block_size/2); i++) {
              fill_solid(&(leds[i*2*block_size]), block_size, color2);
            }
          }
          else if (frame_count%25 < 4){
            fill_solid(leds, NUM_LEDS, CRGB::Black);
          }
          else if (frame_count%25 < 6){          
            fill_solid(leds, NUM_LEDS, color1);
            for (int i = 0; i<(NUM_LEDS/block_size/2); i++) {
              fill_solid(&(leds[i*2*block_size]), block_size, color2);
            }
            }
          else if (frame_count%25 < 25){
            fill_solid(leds, NUM_LEDS, CRGB::Black);
          }  

          if (frame_count > 50){
            toggle = !toggle;
            frame_count = 0;
          }

          break;
        case CASH_CAB:
          // chasing strips of color that cycle through a color pallette
          break;
      }

      FastLED.show();
      frame_count++;
    }
  }
}

void poll_button() {
  // look at the button and increment the color mode if pressed
  // debounce and track last button state to make sure we only increment once per press
}

const TProgmemPalette16 WhitePalette PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
