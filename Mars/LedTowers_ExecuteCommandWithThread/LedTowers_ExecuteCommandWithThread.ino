#include "LedTowers_Animations.h"
#include "Thread.h"

LedColors LED;
int PrevMillis = 0;
int Interval = 20;
boolean newData = false;
const byte numChars = 20;
char receivedChars[numChars];

Thread myThread = Thread();

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
  myThread.enabled = true; // Default enabled value is true
  myThread.setInterval(100); // Setts the wanted interval to be 50ms
  // This will set the callback of the Thread: "What should I run"?
  myThread.onRun(TranslateAndExecuteCommand); // callback_function is the name of the function

  // Reset LED Strip
  LedTowers_FullColor(0,0,0);
  Serial.println("Enter a color!");
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void TranslateAndExecuteCommand(void){
  if(newData){
      String receivedString = String(receivedChars);
      if(receivedString.equals("RED")){
          LED.RED = 255;
          LED.GREEN = LED.BLUE = 0;
      }else if (receivedString.equals("GREEN")){
          LED.GREEN = 255;
          LED.RED = LED.BLUE = 0;
      }else if (receivedString.equals("BLUE")){
          LED.BLUE = 255;
          LED.GREEN = LED.RED = 0;
      }else{
          Serial.println("Invalid choice! Try again!");
      } 
      LedTowers_ShiftFullColor(LED.RED,LED.GREEN,LED.BLUE); 
      newData=false;
    }
}

void loop() {
  recvWithEndMarker();
  if(myThread.shouldRun()){
  // Yes, the Thread should be runned, let's run it
      myThread.run();
    }
}
