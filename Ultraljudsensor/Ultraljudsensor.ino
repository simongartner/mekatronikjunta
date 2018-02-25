/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/

// defines pins numbers
const int trigPin_rigth = 3;
const int echoPin_rigth = 2;
const int trigPin_left = 5;
const int echoPin_left = 4;

const int LED_RED = 9;
const int LED_GREEN = 10;
const int LED_BLUE = 11;
const int RIGHT = 0;
const int LEFT = 1;


// defines variables
long duration;
int distance;
int state = 0;
float prevMillis = 0;
float interval = 10;


void setup() {
  pinMode(trigPin_rigth, OUTPUT); // Sets the trigPin as an Output
  pinMode(trigPin_left, OUTPUT); // Sets the trigPin as an Output
  
  pinMode(echoPin_rigth, INPUT); // Sets the echoPin as an Input
  pinMode(echoPin_left, INPUT); // Sets the echoPin as an Input
  
  pinMode(LED_RED, OUTPUT); 
  pinMode(LED_GREEN, OUTPUT); 
  pinMode(LED_BLUE, OUTPUT); 
}

void Ultrasonic_RGBLED(int SIDE){
  int trigPin, echoPin;
  
  if(SIDE == RIGHT){
      trigPin = trigPin_rigth;
      echoPin = echoPin_rigth;
  }else if(SIDE == LEFT){
      trigPin = trigPin_left;
      echoPin = echoPin_left;
  }
   
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  
  // Map distance between 0 - 50 cm between BLUE, GREEN and RED.
  int GREEN_PWM = map(distance, 0, 50, 0 , 255);
  int BLUE_PWM = map(distance, 0, 50, 0 , 255);
  int RED_PWM = map(distance, 0, 50, 255 , 0);
  
  // Write PWM signals to the RGB LED 
  if(SIDE == RIGHT){
    analogWrite(LED_RED, RED_PWM);
    analogWrite(LED_GREEN, GREEN_PWM);  
  }else if(SIDE == LEFT){
    analogWrite(LED_RED, RED_PWM);
    analogWrite(LED_BLUE, BLUE_PWM);
  }
  
}

void loop() {
  float currMillis = millis();
  
  if(currMillis - prevMillis >= interval){
    prevMillis = currMillis;
    Ultrasonic_RGBLED(state);
    state = !state;
    }
  
}
