#ifndef LedTowers_Animations
#define LedTowers_Animations

#include "FastLED.h"

// How many leds are in the strip?
#define NUM_LEDS 78

// Data pin that led data will be written out over
#define DATA_PIN 7

typedef struct LEDColors{
  int RED;
  int GREEN;
  int BLUE;
}LedColors;


extern CRGB leds[NUM_LEDS];
extern LedColors State[NUM_LEDS];

// This is an array of leds.  One item for each led in your strip.

void LedTowers_WavePropegate(void);
void LedTowers_WaveStart(int red, int green, int blue);
int LedTowers_LimitInput(int input);
void LedTowers_FullColor(int red, int green, int blue);
#endif