#include "LedTowers_Animations.h"
void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
  // Uncomment one of the following lines for your leds arrangement.
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(115200);
  for(int CurrentLED =0; CurrentLED < NUM_LEDS; CurrentLED++){
        State[CurrentLED].RED = 0;
        State[CurrentLED].GREEN =0;
        State[CurrentLED].BLUE = 0;           
    }
}

void loop() {
  static int Alternate = 0;
    
    if(Alternate == 0 || Alternate == 1 || Alternate == 2){
      LedTowers_WaveStart(255,0,0);  
    }else if(Alternate == 12 || Alternate == 13 || Alternate == 14){
      LedTowers_WaveStart(0,255,0);
    }else if(Alternate == 23 || Alternate == 24 || Alternate == 25){
      LedTowers_WaveStart(0,0,255); 
    }else if(Alternate >= 26){ 
     Alternate = 0;
    }else{
    LedTowers_WaveStart(0,0,0);
    }
    Alternate++;
    delay(50);
}
