#include "LedTowers_Animations.h"

CRGB leds[NUM_LEDS];
LedColors State[NUM_LEDS];
const int START =0;
const int STOP =1; 
const int FULL = 2;
const int SINGLE = 3;
//------------------------------------------------------------------------------------------//
/*
Här skriver vi kommentarer, när vi orkar.
*/
void LedTowers_WavePropegate(int MODE){
static LEDColors temp;  
static int CurrentLED_SINGLE = 1;

  for(int CurrentLED = 1; CurrentLED < NUM_LEDS; CurrentLED++) {
      if(MODE == SINGLE){
        CurrentLED = CurrentLED_SINGLE;
      }

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
      
      if(MODE == SINGLE){
        if(CurrentLED_SINGLE >= NUM_LEDS-1){
          CurrentLED_SINGLE = 0;    
        }else{
          CurrentLED_SINGLE++;  
        }
        break;
      }
      
   }
   cli();
   FastLED.show();
   sei();
}
//------------------------------------------------------------------------------------------//
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

//------------------------------------------------------------------------------------------//
/*
Här skriver vi kommentarer, när vi orkar.
*/
void LedTowers_FullColor(int red, int green, int blue){
  for(int CurrentLED = 0; CurrentLED < NUM_LEDS-1; CurrentLED++) {    
      // Turn our current led on.
      leds[CurrentLED] = CRGB (LedTowers_LimitInput(green), LedTowers_LimitInput(red), LedTowers_LimitInput(blue));
      // Save Previouse LED to Current LED.
   }
   FastLED.show();
}
//------------------------------------------------------------------------------------------//
/*
Här skriver vi kommentarer, när vi orkar.
*/
void LedTowers_ShiftFullColor(int red, int green, int blue){
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
//------------------------------------------------------------------------------------------//
/*
Här skriver vi kommentarer, när vi orkar.
*/
void LedTowers_WaveStart(int red, int green, int blue, int MODE){
  State[0].RED = LedTowers_LimitInput(red);
  State[0].GREEN = LedTowers_LimitInput(green);
  State[0].BLUE = LedTowers_LimitInput(blue);
  LedTowers_WavePropegate(MODE);
  
}
//------------------------------------------------------------------------------------------//
void LedTowers_Pulsating(LedColors LED, double frequency){
    static float Amplitud = 0.0;
    static int Increase = true;
    
    LedTowers_WaveStart(round(LED.RED*Amplitud),round(LED.GREEN*Amplitud), round(LED.BLUE*Amplitud), FULL);
    
    if(Amplitud <= 0.0){
    Increase = true;  
    }else if (Amplitud >= 1.0){
    Increase = false;    
    }
    
    if(Increase == true){
      Amplitud +=frequency;
    }else{
      Amplitud -=frequency;
    }
}
//------------------------------------------------------------------------------------------//
void LedTowers_SineWave(LedColors LED, double frequency){
    static float Amplitud = 0.0;
    static int Increase = true;

    LedTowers_WaveStart(round(LED.RED*Amplitud),round(LED.GREEN*Amplitud), round(LED.BLUE*Amplitud),FULL);
    if(Amplitud <= 0.0){
    Increase = true;  
    }else if (Amplitud >= 1.0){
    Increase = false;    
    }
    
    if(Increase == true){
      Amplitud +=frequency;
    }else{
      Amplitud -=frequency;
    }
}
