#include <PID_v1.h>
#include "max6675.h"

#define thermoDO 8
#define thermoCS 9
#define thermoCLK 10
#define RELAY_PIN 7

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

int pid_state;
int point;
int x;
String str;

double S0, S1, S2, S3;

double Setpoint, Input, Output;
double Kp=10, Ki=25, Kd=15;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, P_ON_M, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;

void setup()
{
  Serial.begin(19200);
  Serial.setTimeout(500);

  pid_state = 0;

  pinMode(RELAY_PIN, OUTPUT);
  
  windowStartTime = millis();

  point = 60;

  myPID.SetOutputLimits(0, WindowSize);
  myPID.SetMode(AUTOMATIC);
}

void temper(){
    do{
    S3 = thermocouple.readCelsius();
    }while (3 <= S3 && S3 <= 99);
  do{
    S2 = thermocouple.readCelsius();
    }while (3 <= S2 && S2 <= 99);
  do{
    S1 = thermocouple.readCelsius();
    }while (3 <= S1 && S1 <= 99);
  do{
    S0 = thermocouple.readCelsius();
    }while (3 <= S0 && S0 <= 99);
}

void loop(){
  
  temper();
    
  if (pid_state == 0){
    Serial.println("ponff");
  }
  if (pid_state == 1){
  Serial.println(thermocouple.readCelsius());
  Setpoint = point;
  Input = S3;
  myPID.Compute();
  if (millis() - windowStartTime > WindowSize){
    windowStartTime += WindowSize;
  }
  if (Output < millis() - windowStartTime){
    digitalWrite(RELAY_PIN, LOW);}
  else{ digitalWrite(RELAY_PIN, HIGH);}
  }
  if (Serial.available() > 0) {
    str = Serial.readStringUntil(':');
    x = Serial.parseInt();
    if (str.equals("*IDN?")) {
      Serial.println("Arduino de teste");
    }
    if (str.equals("P")) {
      point = x;
    }
    if (str.equals("Pon")) {
      pid_state = 1;
    }
    if (str.equals("Poff")) {
      pid_state = 0;
      digitalWrite(RELAY_PIN, LOW);
    }
  }
  
 delay(200);
}
