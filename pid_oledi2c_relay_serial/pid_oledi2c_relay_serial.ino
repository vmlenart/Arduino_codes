#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <PID_v1.h>
#include "max6675.h"

int thermoDO = 8;
int thermoCS = 9;
int thermoCLK = 10;
int pid_state;
int point;
int x;
String str;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define RELAY_PIN 7
#define OLED_ADDR 0x3C

double Setpoint, Input, Output;

double Kp = 2, Ki = 1, Kd = 25;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, P_ON_M, DIRECT);

int WindowSize = 1500;
unsigned long windowStartTime;

void setup()
{
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  pinMode(RELAY_PIN, OUTPUT);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(15, 25);
  display.print("vmlenart");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();

  pid_state = 0;

  windowStartTime = millis();
  /**************************************************/
  point = 30;
  /**************************************************/
  myPID.SetOutputLimits(0, WindowSize);
  myPID.SetMode(AUTOMATIC);
}

void loop()
{

  /************************************************/
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40, 0);
  display.print(thermocouple.readCelsius());
  display.setCursor(40, 25);
  display.print("P: ");
  display.print(point);
  display.setCursor(30, 50);
  if (pid_state == 0) {
    display.print("PID OFF");
  }
  if (pid_state == 1) {
    display.print("PID ON");
  }
  display.display();
  /************************************************/

  Serial.println(thermocouple.readCelsius());

  if (pid_state == 0) {

  }
  if (pid_state == 1) {
    /*Serial.println(thermocouple.readCelsius());*/
    Setpoint = point;
    Input = thermocouple.readCelsius();
    myPID.Compute();

    /****turn the output pin on/off based on pid output****/
    if (millis() - windowStartTime > WindowSize) {
      windowStartTime += WindowSize;
    }
    if (Output < millis() - windowStartTime) {
      digitalWrite(RELAY_PIN, LOW);
    }
    else {
      digitalWrite(RELAY_PIN, HIGH);
    }
    /************************************************/

  }
  if (Serial.available() > 0) {
    str = Serial.readStringUntil(':');
    x = Serial.parseInt();
    if (str.equals("*IDN?")) {
      Serial.println("Arduino de teste");
    }
    if (str.equals("T?")) {
      Serial.println(thermocouple.readCelsius());
    }
    if (str.equals("P")) {
      point = x;
    }
    if (str.equals("P?")) {
      Serial.print(Setpoint);
      Serial.print(":");
      Serial.println(pid_state);
    }
    if (str.equals("Pon")) {
      pid_state = 1;
    }
    if (str.equals("Poff")) {
      pid_state = 0;
      digitalWrite(RELAY_PIN, LOW);
    }
    if (str.equals("Roff")) {
      digitalWrite(RELAY_PIN, LOW);
    }
    if (str.equals("Ron")) {
      digitalWrite(RELAY_PIN, HIGH);
    }
  }
  delay(200);
}
