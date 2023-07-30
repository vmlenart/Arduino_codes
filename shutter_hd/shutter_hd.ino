#define RELAY1  8                        

#define RELAY2  7   



void setup(){    
  Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY2,HIGH);
  digitalWrite(RELAY1,HIGH);

  // pinMode(LED_BUILTIN, OUTPUT);
}


void abre(){
   digitalWrite(RELAY1,HIGH);          
   // digitalWrite(RELAY2,LOW);
   }

void fecha(){
   // digitalWrite(RELAY2,HIGH);          
   digitalWrite(RELAY1,LOW);
   }

void off(){
   // digitalWrite(RELAY2,HIGH);          
   digitalWrite(RELAY1,HIGH);
   }

void loop() { 
  if(Serial.available()>0) {
    char c;
    c = Serial.read();
if(c=='f'){abre();digitalWrite(LED_BUILTIN, HIGH);}
if(c=='a'){fecha();digitalWrite(LED_BUILTIN, LOW);}
if(c=='o'){off();}
                         }
}
