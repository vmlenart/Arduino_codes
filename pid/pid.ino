#include <PID_v1.h>
#include "max6675.h"

int thermoDO = 8;
int thermoCS = 9;
int thermoCLK = 10;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

#define RELAY_PIN 7

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=15, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, P_ON_M, DIRECT);

int WindowSize = 5000;
unsigned long windowStartTime;

void setup()
{
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  
  windowStartTime = millis();

  //initialize the variables we're linked to
  Setpoint = 34;

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Serial.println(thermocouple.readCelsius());
  Input = thermocouple.readCelsius();
  myPID.Compute();

  /************************************************
   * turn the output pin on/off based on pid output
   ************************************************/
  if (millis() - windowStartTime > WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if (Output < millis() - windowStartTime) digitalWrite(RELAY_PIN, LOW);
  else digitalWrite(RELAY_PIN, HIGH);
 delay(200);
}
