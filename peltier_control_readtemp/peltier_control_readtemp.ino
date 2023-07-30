#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define TEC 9

int x;
String str;

Adafruit_MLX90614 mlx = Adafruit_MLX90614(0x55);

void setup(){
   Serial.begin(9600);
   Serial.setTimeout(200);
   mlx.begin();

   pinMode(TEC, OUTPUT);
   analogWrite(TEC, 0);
            }

void loop() 
{
    if(Serial.available() > 0){
        str = Serial.readStringUntil(':');
        x = Serial.parseInt();
            if(str.equals("*IDN?")){
                Serial.println("VMLenart; Peltier V2; 27mai2018; Arduino_0");        
                                   }
            if(str.equals("AT")){
                Serial.println(mlx.readObjectTempC());        
                                 }
             if(str.equals("TEC")){
                analogWrite(TEC, x);        
                                 }  
                              }
}
