#include <SoftwareSerial.h>
SoftwareSerial softSerial(8, 9); // RX, TX

#define DEBUG true

void setup() {
  
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  
  uint32_t baud = 9600;
  Serial.begin(baud);
  softSerial.begin(baud);
  Serial.print("SETUP!! @");
  Serial.println(baud);

  sendData("AT+RST\r\n",2000,DEBUG);
  sendData("AT+CIOBAUD=9600\r\n",2000,DEBUG);
  sendData("AT+CWJAP=\"TN_24GHz_D9EE2F\",\"AV4N3J3H7T\"\r\n",10000,DEBUG);
  sendData("AT+CWMODE=1\r\n",2000,DEBUG);
  //sendData("AT+CWMODE=3\r\n",2000,DEBUG);
  sendData("AT+CIFSR\r\n",2000,DEBUG);
  sendData("AT+CIPSTART=\"TCP\",\"192.168.10.160\",8005\r\n",5000,DEBUG);

  //sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  //sendData("AT+CIPSERVER=1,5006\r\n",1000,DEBUG); // turn on server on port 5005

  /*Serial.print(45);
  int a = 5;
  Serial.print(a);*/
}

int connectionId;
void loop() {
    
    while(softSerial.available() > 0) 
    {
      /*if(softSerial.find("+IPD,")) {
        Serial.print("hej");
        delay(300);
        connectionId = softSerial.read();
        Serial.print(char(connectionId));
      }*/
      
      
      char a = softSerial.read();
      Serial.write(a);
      if(a =='r')
      {
        digitalWrite(5,HIGH);
      } else if(a =='o') {
        digitalWrite(5,LOW);
      }
      /*sendData("AT+CIPSEND=connectionId,d.length())*/
      

      /*if(a == '\0')
        continue;
      if(a != '\r' && a != '\n' && (a < 32))
        continue;*/
      /*Serial.print(a);
      if(a == '+') {
       Serial.println("ja"); 
      }*/
      }
    
    /*while(Serial.available() > 0)
    {
      char a = Serial.read();
      Serial.write(a);
      softSerial.write(a);
    }*/
}


 
 /*void espsend(String d) {
  String cipSend = " AT+CIPSEND=";
  cipSend += connectionId; 
  cipSend += ",";
  cipSend +=d.length();
  cipSend +="\r\n";
  sendData(cipSend,1000,DEBUG);
  sendData(d,1000,DEBUG); 
  }*/


//////////////gets the data from esp and displays in serial monitor///////////////////////         
String sendData(String command, const int timeout, boolean debug) {
  String response = "";
  softSerial.print(command);
  long int time = millis();
  while( (time+timeout) > millis()) {
    while(softSerial.available()) {
      char c = softSerial.read(); // read the next character.
      response+=c;
      }  
  }
  if(debug) {
    Serial.print(response); //displays the esp response messages in arduino Serial monitor
    }
    return response;
}
