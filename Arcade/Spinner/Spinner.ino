
//C:\Users\davidq\Documents\Arduino
// I must confess: I thought the task would be easy using the "mouse" 
// library I found online, little did I realize that this class only works 
// with:
// Arduino/Genoino Micro
// Arduino Leonard
// Arduino Leonard ETH
// Arduino Esplora
// Arduino Lilypad Arduino USB
// Arduino Robot Control
// Arduino Robot Motor
// Adafruit circuit playground


// ToSpin 2.0 firmware, 2017 by Stefan Burger (aka "ToS")

#include <Adafruit_NeoPixel.h>
#include <Mouse.h>

#define pinA1 0   //Paddle A, Sensor 1
#define pinA2 1   //Paddle A, Sensor 2
#define pinB1 2   //Paddle B, Sensor 1
#define pinB2 3   //Paddle B, Sensor 2
#define pinAc 7   //Paddle A, Config X/Y
#define pinBc 8   //Paddle B, Config X/Y
#define pinNP 5   //NeoPixel
#define faktor 3  //multiplier counts to mouse-move
#define msanim 60 //update frequenzy for neopix animation

Adafruit_NeoPixel np = Adafruit_NeoPixel(2, pinNP, NEO_RGB + NEO_KHZ400);

long cntX=0; //counter for mouse X-axis
long cntY=0; //counter for mouse Y-axis
long cntA=0; //counter for paddle A neopix animation
long cntB=0; //counter for paddle B neopix animation
int oldAC1=0;
int oldAC2=0;
int oldBC1=0;
int oldBC2=0;

long lastcntX;
long lastcntY;
long lastcntA;
long lastcntB;
int currA1;
int currA2;
int currB1;
int currB2;
int isAY;
int isBY;

long mslastA;
long mslastB;
  
void setup() {
  pinMode(pinA1, INPUT_PULLUP);
  pinMode(pinA2, INPUT_PULLUP);
  pinMode(pinB1, INPUT_PULLUP);
  pinMode(pinB2, INPUT_PULLUP);
  pinMode(pinAc, INPUT_PULLUP);
  pinMode(pinBc, INPUT_PULLUP);
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, HIGH);
  isAY=digitalRead(pinAc);
  isBY=digitalRead(pinBc);
  cntX=0;
  cntY=0;
  lastcntX=cntX;
  lastcntY=cntY;
  lastcntA=cntA;
  lastcntB=cntB;
  attachInterrupt(digitalPinToInterrupt(pinA1),changeA1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinA2),changeA2,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB1),changeB1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB2),changeB2,CHANGE);
  np.begin();
  np.show();
  mslastA=millis();
  mslastB=millis();
  Mouse.begin();
}

void loop() {
  //send mouse update to usb
  if(cntX!=lastcntX || cntY!=lastcntY){
    Mouse.move((cntX-lastcntX)*faktor,(cntY-lastcntY)*faktor);
    lastcntX=cntX;
    lastcntY=cntY;
  }

  //neopix animation for paddle B - abs(cntB-lastcntB) -> absolut number of counts since last neopix animation update -> speed indicator
  if(cntB!=lastcntB && (millis()-mslastB)>=msanim) {
    np.setPixelColor(0,min(255,abs(cntB-lastcntB)*9),0,max(0,(255-(abs(cntB-lastcntB)*9))));
    np.show();
    lastcntB=cntB;
    mslastB=millis();
  }

  //neopix animation for paddle A
  if(cntA!=lastcntA && (millis()-mslastA)>=msanim) {
    np.setPixelColor(1,min(255,abs(cntA-lastcntA)*9),0,max(0,(255-(abs(cntA-lastcntA)*9))));
    np.show();
    lastcntA=cntA;
    mslastA=millis();
  }
}

void changeA1() {
  if(isAY) {
    doACountY();
  } else {
    doACountX();
  }
}
void changeA2() {
  if(isAY) {
    doACountY();
  } else {
    doACountX();
  }
}
void changeB1() {
  if(isBY) {
    doBCountY();
  } else {
    doBCountX();
  }
}
void changeB2() {
  if(isBY) {
    doBCountY();
  } else {
    doBCountX();
  }
}

void doACountX() {
  int actAC1=digitalRead(pinA1);
  int actAC2=digitalRead(pinA2);
  
  if(actAC1!=oldAC1 || actAC2!=oldAC2) {
     if((oldAC1!=oldAC2 && actAC2!=oldAC2)||(oldAC1==oldAC2 && actAC1!=oldAC1)) {
       cntX--;
       cntA--;
     } else {
       cntX++;
       cntA++;
     }

    oldAC1=actAC1;
    oldAC2=actAC2;
  }
}
void doACountY() {
  int actAC1=digitalRead(pinA1);
  int actAC2=digitalRead(pinA2);
  
  if(actAC1!=oldAC1 || actAC2!=oldAC2) {
     if((oldAC1!=oldAC2 && actAC2!=oldAC2)||(oldAC1==oldAC2 && actAC1!=oldAC1)) {
       cntY--;
       cntA--;
     } else {
       cntY++;
       cntA++;
     }

    oldAC1=actAC1;
    oldAC2=actAC2;
  }
}

void doBCountX() {
  int actBC1=digitalRead(pinB1);
  int actBC2=digitalRead(pinB2);
  
  if(actBC1!=oldBC1 || actBC2!=oldBC2) {
     if((oldBC1!=oldBC2 && actBC2!=oldBC2)||(oldBC1==oldBC2 && actBC1!=oldBC1)) {
       cntX--;
       cntB--;
     } else {
       cntX++;
       cntB++;
     }

    oldBC1=actBC1;
    oldBC2=actBC2;
  }
}
void doBCountY() {
  int actBC1=digitalRead(pinB1);
  int actBC2=digitalRead(pinB2);
  
  if(actBC1!=oldBC1 || actBC2!=oldBC2) {
     if((oldBC1!=oldBC2 && actBC2!=oldBC2)||(oldBC1==oldBC2 && actBC1!=oldBC1)) {
       cntY--;
       cntB--;
     } else {
       cntY++;
       cntB++;
     }

    oldBC1=actBC1;
    oldBC2=actBC2;
  }
}

