#include "Delay.h"

int led = 13;
int ledstate = HIGH;
NonBlockDelay d;

void setup() {                
  pinMode(led, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  if (d.Timeout()) {
    digitalWrite(led, ledstate);
    ledstate = ledstate == LOW ? HIGH : LOW; //toggle state
    d.Delay(1000);
  } 
  //Code here runs frequently
}


