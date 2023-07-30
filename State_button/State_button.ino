int x;
String str;

const int  buttonPin = A0;

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void serialcontrol(){
  Serial.println("oi");
  delay(200);
  if(Serial.available() > 0){
        str = Serial.readStringUntil(':');
        x = Serial.parseInt();
            if(str.equals("on")){
                digitalWrite(LED_BUILTIN,HIGH);
                delay(x);
                digitalWrite(LED_BUILTIN,LOW);        
                                }
            if(str.equals("quick")){
                digitalWrite(LED_BUILTIN,HIGH);
                delay(500);
                digitalWrite(LED_BUILTIN,LOW);        
                                } 
                              }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  Serial.print("first");
 switch(digitalRead(A0)){
  case 0:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  break;
  case 1:
      serialcontrol();
  break;
 }
 delay(100);

}
