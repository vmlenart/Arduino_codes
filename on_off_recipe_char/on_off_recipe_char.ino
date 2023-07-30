void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void on(){
   digitalWrite(LED_BUILTIN,HIGH);
   }

void off(){
  digitalWrite(LED_BUILTIN,LOW);
   }

void loop() {
  if(Serial.available()>0) {
    char c;
    c = Serial.read();
  if(c == 'o'){on();}
  if(c == 'f'){off();}
  }
}
