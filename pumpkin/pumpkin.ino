//// color swirl! connect an RGB LED to the PWM pins as indicated
//// in the #defines
//// public domain, enjoy!
// 
//#define REDPIN 3
//#define GREENPIN 5
//#define BLUEPIN 6
//#define WHITEPIN 9
// 
//#define FADESPEED 5     // make this higher to slow down
// 
//void setup() {
//  pinMode(REDPIN, OUTPUT);
//  pinMode(GREENPIN, OUTPUT);
//  pinMode(BLUEPIN, OUTPUT);
//  pinMode(WHITEPIN, OUTPUT);
//}
// 
// 
//void loop() {
//  int r, g, b, w;
//
//  // fade from Red
//  for (r = 0; r < 256; r++) { 
//    analogWrite(REDPIN, r);
//    delay(FADESPEED);
//  } 
//   analogWrite(REDPIN, 0);
//
//  // fade from Green
//  for (r = 0; r < 256; r++) { 
//    analogWrite(GREENPIN, r);
//    delay(FADESPEED);
//  } 
//   analogWrite(GREENPIN, 0);
//
//  // fade from Blue
//  for (r = 0; r < 256; r++) { 
//    analogWrite(BLUEPIN, r);
//    delay(FADESPEED);
//  } 
//   analogWrite(BLUEPIN, 0);
//
//  // fade from White
//  for (r = 0; r < 256; r++) { 
//    analogWrite(WHITEPIN, r);
//    delay(FADESPEED);
//  } 
//   analogWrite(WHITEPIN, 0);
//
//delay(100);   
//analogWrite(REDPIN, 0);
//delay(100);   
//analogWrite(REDPIN, 255);
//delay(100);   
//analogWrite(REDPIN, 0);
//delay(100);   
//analogWrite(REDPIN, 255);
//delay(100);   
//analogWrite(REDPIN, 0);
//
//
//  
////  // fade from blue to violet
////  for (r = 0; r < 256; r++) { 
////    analogWrite(REDPIN, r);
////    delay(FADESPEED);
////  } 
////  // fade from violet to red
////  for (b = 255; b > 0; b--) { 
////    analogWrite(BLUEPIN, b);
////    delay(FADESPEED);
////  } 
////  // fade from red to yellow
////  for (g = 0; g < 256; g++) { 
////    analogWrite(GREENPIN, g);
////    delay(FADESPEED);
////  } 
////  // fade from yellow to green
////  for (r = 255; r > 0; r--) { 
////    analogWrite(REDPIN, r);
////    delay(FADESPEED);
////  } 
////  // fade from green to teal
////  for (b = 0; b < 256; b++) { 
////    analogWrite(BLUEPIN, b);
////    delay(FADESPEED);
////  } 
////  // fade from teal to blue
////  for (g = 255; g > 0; g--) { 
////    analogWrite(GREENPIN, g);
////    delay(FADESPEED);
////  } 
//}


#define REDPIN 3
#define GREENPIN 5
#define BLUEPIN 6
#define WHITEPIN 9

void setup()
{
pinMode(REDPIN, OUTPUT);
pinMode(GREENPIN, OUTPUT);
pinMode(BLUEPIN, OUTPUT);
pinMode(WHITEPIN, OUTPUT);

clearLED();
}

void clearLED(){
  analogWrite(REDPIN, 0);
  analogWrite(GREENPIN, 0);
  analogWrite(BLUEPIN, 0);
  analogWrite(WHITEPIN, 0);
}
unsigned long time;

void loop() {
  time = millis();
  if (time < 20000) {  
    analogWrite(REDPIN, random(100)+155);
    analogWrite(GREENPIN, random(120)+(127/2));
    delay(random(100));
  } else {
    clearLED();
    for (int loop = 0; loop < 15; loop++){
      analogWrite(WHITEPIN, 255);
      delay(random(150));
      analogWrite(WHITEPIN, 0);
      delay(random(150));      
    }

    clearLED();
    
    for (int loop = 0; loop < 3; loop++){
      analogWrite(REDPIN, 255);
      delay(random(150));
      analogWrite(REDPIN, 0);
      delay(random(150));      
    }

    // blead red
    for (int loop = 100; loop > 0; loop--){
      analogWrite(REDPIN, loop);
      delay(random(60));           
    }

    clearLED();
    
    delay(random(500));           
  
    //Change Millis
    setMillis(0);
  }
}


extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;

//Sets the millis value
void setMillis(unsigned long new_millis)
{
  uint8_t oldSREG = SREG;
 
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}
