#ifndef LedTowers_Animations
#define LedTowers_Animations

#include "FastLED.h"

// How many leds are in the strip?
#define NUM_LEDS 78

// Data pin that led data will be written out over
#define DATA_PIN 7

extern CRGB leds[NUM_LEDS];

void Wave_Propegate(void);
void Wave_Start(int RED, int GREEN, int BLUE);


#endif