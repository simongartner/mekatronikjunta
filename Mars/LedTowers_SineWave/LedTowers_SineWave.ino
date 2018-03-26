#include "FastLED.h"

LedColors LED;
int PrevMillis = 0;
int Interval = 5;

void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);
  
  LED.RED = 255;
  LED.GREEN = 255;
  LED.BLUE = 255;
  
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(115200);
  for(int CurrentLED =0; CurrentLED < NUM_LEDS; CurrentLED++){
        State[CurrentLED].RED = 0;
        State[CurrentLED].GREEN =0;
        State[CurrentLED].BLUE = 0;           
    }
}

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

void loop() {
  // put your main code here, to run repeatedly:
  static int Alternate = 0;
  int CurrMillis= millis();
  
  if (CurrMillis - PrevMillis >= Interval){
    PrevMillis = CurrMillis;
    LedTowers_SineWave(LED, 0.01);
  } 
}
