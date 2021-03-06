#include "FastLED.h"
// How many leds are in the strip?
#define NUM_LEDS 60

// Data pin that led data will be written out over
#define DATA_PIN 7

typedef struct LEDColors{
  int RED;
  int GREEN;
  int BLUE;
}LedColors;


CRGB leds[NUM_LEDS];
LedColors State[NUM_LEDS];

// This function sets up the ledsand tells the controller about them
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

void LedTowers_WaveStart(int RED, int GREEN, int BLUE){
  State[0].RED = RED;
  State[0].GREEN = GREEN;
  State[0].BLUE = BLUE;
  LedTowers_WavePropegate();
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
