#include "LedTowers_Animations.h"

CRGB leds[NUM_LEDS];
LedColors State[NUM_LEDS];

/*
Här skriver vi kommentarer, när vi orkar.
*/
void LedTowers_WavePropegate(void){
static LEDColors temp;  
  for(int CurrentLED = 1; CurrentLED < NUM_LEDS; CurrentLED++) {
      temp.RED=State[CurrentLED].RED;
      temp.GREEN=State[CurrentLED].GREEN;
      temp.BLUE=State[CurrentLED].BLUE;
      
      // Save Previouse LED to Current LED.
      State[CurrentLED].RED = State[CurrentLED-1].RED;
      State[CurrentLED].GREEN = State[CurrentLED-1].GREEN;
      State[CurrentLED].BLUE = State[CurrentLED-1].BLUE;

      State[CurrentLED-1].RED = temp.RED;
      State[CurrentLED-1].GREEN = temp.GREEN;
      State[CurrentLED-1].BLUE = temp.BLUE;
          
      leds[CurrentLED] = CRGB (State[CurrentLED-1].RED, State[CurrentLED-1].GREEN, State[CurrentLED-1].BLUE);
   }
   FastLED.show();
}

/*
Här skriver vi kommentarer, när vi orkar.
*/
int LedTowers_LimitInput(int input){
  if(input >= 255){
    input = 255;
  }else if (input <= 0){
    input = 0;
  }
  return input;
}

/*
Här skriver vi kommentarer, när vi orkar.
*/
void LedTowers_FullColor(int red, int green, int blue){
  State[0].RED = LedTowers_LimitInput(red);
  State[0].GREEN = LedTowers_LimitInput(green);
  State[0].BLUE = LedTowers_LimitInput(blue);
  // Move a single led 
  for(int CurrentLED = 1; CurrentLED < NUM_LEDS; CurrentLED++) {    
      // Turn our current led on.
      leds[CurrentLED] = CRGB (State[CurrentLED].GREEN, State[CurrentLED].RED, State[CurrentLED].BLUE);
      // Save Previouse LED to Current LED.
      State[CurrentLED].RED = State[CurrentLED-1].RED;
      State[CurrentLED].GREEN = State[CurrentLED-1].GREEN;
      State[CurrentLED].BLUE = State[CurrentLED-1].BLUE;
      FastLED.show();
   }
}

/*
Här skriver vi kommentarer, när vi orkar.
*/
void LedTowers_WaveStart(int red, int green, int blue){
  State[0].RED = LedTowers_LimitInput(red);
  State[0].GREEN = LedTowers_LimitInput(green);
  State[0].BLUE = LedTowers_LimitInput(blue);
  LedTowers_WavePropegate();
}
