#include "FastLED.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

int PreviousMillis = 0;
int Interval= 50;

// How many leds are in the strip?
#define NUM_LEDS 78

// Data pin that led data will be written out over
#define DATA_PIN 7

struct LEDColors{
  int RED;
  int GREEN;
  int BLUE;
}State[NUM_LEDS];

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

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
void Wave_Propegate(void){
  // Move a single led 
  //Serial.println("===============================");
  //Serial.println("Wave_Propegate");
  static LEDColors temp;  
  for(int CurrentLED = 1; CurrentLED < NUM_LEDS; CurrentLED++) {
      // Turn our current led on.
      //Serial.println("CurrentLED");
      //Serial.println(CurrentLED);
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
      
      //Serial.println("State[CurrentLED].RED");
      //Serial.println(State[CurrentLED].RED);

      //Serial.println("State[CurrentLED-1].RED");
      //Serial.println(State[CurrentLED-1].RED);
      
      leds[CurrentLED] = CRGB (State[CurrentLED-1].RED, State[CurrentLED-1].GREEN, State[CurrentLED-1].BLUE);
   }
   FastLED.show();
}

void Wave_Start(int RED, int GREEN, int BLUE){
  State[0].RED = RED;
  State[0].GREEN = GREEN;
  State[0].BLUE = BLUE;
}

//if (CurrentMillis - PreviousMillis >= Interval){
//  PreviousMillis = CurrentMillis;
//int CurrentMillis = millis();
    
void loop() {
    static int Alternate = 0;
    //Serial.println("===================");
    //Serial.println("Alternate");
    //Serial.println(Alternate);
    
    if(Alternate == 0 || Alternate == 1 || Alternate == 2){
      Wave_Start(255,0,0);  
    }else if(Alternate == 12 || Alternate == 13 || Alternate == 14){
      Wave_Start(0,255,0);
    }else if(Alternate == 23 || Alternate == 24 || Alternate == 25){
      Wave_Start(0,0,255); 
    }else if(Alternate >= 26){ 
     Alternate = 0;
    }else{
    Wave_Start(0,0,0);
    }
    
    Alternate++;
    
    Wave_Propegate();
    delay(50);
}
