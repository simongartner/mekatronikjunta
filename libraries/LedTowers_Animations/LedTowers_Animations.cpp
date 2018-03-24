#include <LedTowers_Animations.h>

struct LEDColors{
  int RED;
  int GREEN;
  int BLUE;
}State[NUM_LEDS];


/*
Här skriver vi kommentarer, när vi orkar.
*/
void Wave_Propegate(void){
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
void Wave_Start(int RED, int GREEN, int BLUE){
  State[0].RED = RED;
  State[0].GREEN = GREEN;
  State[0].BLUE = BLUE;
  Wave_Propegate();
}
