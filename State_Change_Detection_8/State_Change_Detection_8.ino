#define buttonCut 6
#define buttonAdd 4
#define buttonSelect 5
#define buttonInitiate 3
#define led 2
#define rele 7

const int LM35 = A0;

#define RST 12
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8

int Inicio = 10;
int start = 0;
int Timebt = 60;
int Nblink = 10;
int lastButtonState = 0;
int Select = 0;
int count = 0; 
int randon = 0;
int xory = 0;
float temperatura;

unsigned long seconds = 1000L; // !!! SEE THE CAPITAL "L" USED!!!
unsigned long minutes = seconds * 60;
unsigned long hours = minutes * 60;

static const byte ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c ?
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ?
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f ?
};

void LcdXY(int x, int y){
  LcdWriteCmd(0x80 | x); // Collumn
  LcdWriteCmd(0x40 | y); // Row
}

void LcdWriteString(char *character){
  while(*character) LcdWriteCharacter(*character++);
}

void LcdWriteCharacter(char character){
 for(int i=0; i<5; i++)LcdWriteData(ASCII[character - 0x20][i]);
    LcdWriteData(0x00);
}

void LcdWriteData(byte dat){
  digitalWrite(DC, HIGH);
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, dat);
  digitalWrite(CE, HIGH);
}

void LcdWriteCmd(byte cmd){
  digitalWrite(DC, LOW); 
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd);
  digitalWrite(CE, HIGH);
}

char string[8];

void setup() {
  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
  pinMode(buttonCut, INPUT);
  pinMode(buttonAdd, INPUT);
  pinMode(rele, OUTPUT);
  pinMode(led, OUTPUT);

  LcdWriteCmd(0x21); // LCD extended commands
  LcdWriteCmd(0xB8); // set LCD Vop (contrast)
  LcdWriteCmd(0x04); // set temp coefficent
  LcdWriteCmd(0x14); // LCD bias mode 1:40
  LcdWriteCmd(0x20); // LCD basic commands
  LcdWriteCmd(0x0C); // LCD normal video

  for(int i=0; i<504; i++) LcdWriteData(0x00);
  
  LcdXY(0,0);
  LcdWriteString(">");
  LcdXY(7,0);
  LcdWriteString("start:");
  LcdXY(7,1);
  LcdWriteString("timebt:");
  LcdXY(7,2);
  LcdWriteString("nblink:");
  LcdXY(7,3);
  LcdWriteString("rand:");
  LcdXY(15,4);
  LcdWriteString("Stand by");
  LcdXY(0,5);
  LcdWriteString("temp:"); 
  LcdXY(70,5);
  LcdWriteString("C");

  LcdXY (31,0);
  LcdWriteString(dtostrf(Inicio,5,0,string));
  LcdXY (65,0);
  LcdWriteString("min");
  LcdXY (45,1);
  LcdWriteString(dtostrf(Timebt,5,0,string));
  LcdXY (77,1);
  LcdWriteString("s");
  LcdXY (45,2);
  LcdWriteString(dtostrf(Nblink,5,0,string));
  LcdXY (77,2);
  LcdWriteString("x");
  LcdXY (50,3);
  LcdWriteString("ON");
  LcdXY(7,0);
  LcdWriteString("start:");         
  
}

void menu(){
    LcdXY(15,4);
    LcdWriteString("Stand by");
    count=0;
    int Seleciona = digitalRead(buttonSelect);
       if(Seleciona!=0){
          Select++;
          digitalWrite(led, HIGH); 
          delay(200);
          digitalWrite(led, LOW);     
       }
       else if (Select>=4){
          Select = 0;
          delay(200);
       }
    if (Select == 0) {
         LcdXY(0,0);
         LcdWriteString(">");
         LcdXY(0,1);
         LcdWriteString(" ");
         LcdXY(0,2);
         LcdWriteString(" ");
         LcdXY(0,3);
         LcdWriteString(" ");
        if (digitalRead(buttonCut) != 0){
            Inicio--;
            LcdXY (31,0);
            LcdWriteString(dtostrf(Inicio,5,0,string));
              LcdXY(7,0);
  LcdWriteString("start:"); 
        }
        delay(100);
        if (digitalRead(buttonAdd) != 0){
            Inicio++;
            LcdXY (31,0);
            LcdWriteString(dtostrf(Inicio,5,0,string));
            LcdXY(7,0);
            LcdWriteString("start:"); 
        }
        delay(100);
    }
    else if (Select == 1){
         LcdXY(0,0);
         LcdWriteString(" ");
         LcdXY(0,1);
         LcdWriteString(">");
         LcdXY(0,2);
         LcdWriteString(" ");
         LcdXY(0,3);
         LcdWriteString(" ");
        if (digitalRead(buttonCut) != 0){
            Timebt--;
            LcdXY (45,1);
            LcdWriteString(dtostrf(Timebt,5,0,string));
            LcdXY (77,1);
            LcdWriteString("s");
        }
        delay(100);
        if (digitalRead(buttonAdd) != 0){
            Timebt++;
            LcdXY (45,1);
            LcdWriteString(dtostrf(Timebt,5,0,string));
            LcdXY (77,1);
            LcdWriteString("s");
        }
        delay(100);
    }
    else if(Select == 2){
         LcdXY(0,0);
         LcdWriteString(" ");
         LcdXY(0,1);
         LcdWriteString(" ");
         LcdXY(0,2);
         LcdWriteString(">");
         LcdXY(0,3);
         LcdWriteString(" ");
        if (digitalRead(buttonCut) != 0){
            Nblink--;
            LcdXY (45,2);
            LcdWriteString(dtostrf(Nblink,5,0,string));
            LcdXY (77,2);
            LcdWriteString("x");
        }
        delay(100);
        if (digitalRead(buttonAdd) != 0){
            Nblink++;
            LcdXY (45,2);
            LcdWriteString(dtostrf(Nblink,5,0,string));
            LcdXY (77,2);
            LcdWriteString("x");
        }
        delay(100);     
      }
    else if(Select == 3){
         LcdXY(0,0);
         LcdWriteString(" ");
         LcdXY(0,1);
         LcdWriteString(" ");
         LcdXY(0,2);
         LcdWriteString(" ");
         LcdXY(0,3);
         LcdWriteString(">");
        if (digitalRead(buttonCut) != 0){
            randon=0;
            LcdXY (50,3);
            LcdWriteString("ON ");
        }
        delay(100);
        if (digitalRead(buttonAdd) != 0){
            randon = 1;
            LcdXY (50,3);
            LcdWriteString("OFF");
        }
        delay(100);     
      }
       }

void sensortemp(){
    temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
    LcdXY (35,5);
    LcdWriteString(dtostrf(temperatura-5,5,1,string));
}

void randoon(){
          unsigned long minicial = (Inicio+random(10,20)) * seconds * 60;
          LcdXY (31,0);
          LcdWriteString(dtostrf((minicial/seconds/60),5,0,string));
          LcdXY(7,0);
          LcdWriteString("start:"); 
          delay(minicial);
          int rNblink = Nblink + random(5,15);
          LcdXY (45,2);
          LcdWriteString(dtostrf(rNblink,5,0,string));
          LcdXY (77,2);
          LcdWriteString("x");
          do{
          int randomitebt = Timebt+random(20,30);
          LcdXY (45,1);
          LcdWriteString(dtostrf(randomitebt,5,0,string));
          LcdXY (77,1);
          LcdWriteString("s");
          digitalWrite(rele, HIGH); 
          delay(randomitebt * seconds);
          digitalWrite(rele, LOW);
          delay(randomitebt * seconds);
          count++;
          sensortemp();
          } while (Nblink > count);
}

void randonoff(){
          unsigned long minicial = Inicio * seconds * 60;
          delay(minicial);
          do{
          digitalWrite(rele, HIGH); 
          delay(Timebt * seconds);
          digitalWrite(rele, LOW);
          delay(Timebt * seconds);
          count++;
          sensortemp();
          } while (Nblink > count);
}


void loop() {

    sensortemp();

    start = digitalRead(buttonInitiate);
       if(start != 0){
          xory=0;
          LcdXY(15,4);
          LcdWriteString("Initiate");
        if(randon==0){ //ON  
         do{ 
         randoon();
         }while(xory=1);
        }else if(randon==1){ //OFF
         do{
         randonoff();
         }while(xory=1);
        }
       } else{
      menu();
    }}   
