#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <PID_v1.h>
#include "max6675.h"

int thermoDO = 8;
int thermoCS = 9;
int thermoCLK = 10;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define OLED_ADDR   0x3C

double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint, 2, 0, 0, P_ON_M, DIRECT);

void setup()
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15,25);
  display.print("vmlenart");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
    

  Setpoint = 40;

  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Serial.println(thermocouple.readCelsius());
  Input = thermocouple.readCelsius();
  myPID.Compute();
  analogWrite(3,255-Output);
  //Serial.println(Output);
  
     display.clearDisplay();
     display.setTextSize(2.5);
     display.setTextColor(WHITE);
     display.setCursor(40,25);
     display.print(Input);
     display.display();
  /************************************************
   * turn the output pin on/off based on pid output
   ************************************************/

 delay(200);
}
