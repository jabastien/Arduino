////  VW Pumpkin, color swirl!, with a flashing of white...
////
//// connect an RGB LED to the PWM pins as indicated
////
//// public domain, enjoy!
// 
//
//
#define REDPIN 3
#define GREENPIN 5
#define BLUEPIN 6
#define WHITEPIN 9
 
#define FADESPEED 2     // make this higher to slow down
#define FLASHESPEED 40     // make this higher to slow down

#define LOOPS 10

  int r, g, b, w;  
  
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(WHITEPIN, OUTPUT);

  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(WHITEPIN, 0);
}
 

void loop() {

  for (int loop = 0; loop < LOOPS; loop++){
    analogWrite(WHITEPIN, 255);
//    analogWrite(REDPIN, 128);
//    analogWrite(GREENPIN, 128);
//    analogWrite(BLUEPIN, 128);
    delay(FLASHESPEED);
    analogWrite(WHITEPIN, 0);
//    analogWrite(REDPIN, 0);
//    analogWrite(GREENPIN, 0);
//    analogWrite(BLUEPIN, 0);
    delay(FLASHESPEED);
  }
  
  for (int loop = 0; loop < LOOPS; loop++){

    // (1) Red IN
    for (r = 0; r < 256; r++) { 
      analogWrite(REDPIN, r);
      delay(FADESPEED);
    } 

    // (6)Blue Out
    for (b = 255; b >= 0; b--) { 
      analogWrite(BLUEPIN, b);
      delay(FADESPEED);
    } 

    // (2) Green IN
    for (g = 0; g < 256; g++) { 
      analogWrite(GREENPIN, g);
      delay(FADESPEED);
    } 

    // (3) Red Out
    for (r = 255; r >= 0; r--) { 
      analogWrite(REDPIN, r);
      delay(FADESPEED);
    } 

    // (3) Blue IN
    for (b = 0; b < 256; b++) { 
      analogWrite(BLUEPIN, b);
      delay(FADESPEED);
    } 

    // (3) Green Out
    for (g = 255; g >= 0; g--) { 
      analogWrite(GREENPIN, g);
      delay(FADESPEED);
    }      
  }

  // --------------------------------
  // Exit to black
  // (6)Blue Out // fade from blue
  for (b = 255; b >= 0; b--) { 
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
}
