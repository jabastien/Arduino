/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/


#if defined(ARDUINO) && ARDUINO >= 100
      #include "Arduino.h"
#else
      #include "WProgram.h"
#endif



const int buttonPin = A0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
//pinMode(buttonPin, INPUT_PULLUP);
//  pinMode(A0);
  Serial.println("Pushbutton bounce test:");
  
////        max / btn cnt / half
//int sub = 1023/       5 /    2;  // = 102
//
//  for (int lp = 0;lp<=1023;lp+=10)
//  {
//  Serial.print  (lp);
//  Serial.print  (" ");
//  Serial.print( map(lp, 0 - sub,1023 - sub,0,5));
//  Serial.print  (" ");
//  Serial.print  (lp  * (4.25 / 1023.0));
//  Serial.println(" ");
//  }

 // pinMode(A0, INPUT_PULLUP);
}


byte previousState = HIGH;         // what state was the button last time
unsigned int count = 0;            // how many times has it changed to low
unsigned long countAt = 0;         // when count changed
unsigned int countPrinted = 0;     // last count printed


// the loop routine runs over and over again forever:
void loop() {

//  // read the input on analog pin 0:
//  int sensorValue = analogRead(buttonPin);
//  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
////  float voltage = sensorValue * (5.0 / 1023.0);
//  float voltage = sensorValue * (4.25 / 1023.0);
//  // print out the value you read:
//
//  Serial.print( map(sensorValue, 0-102,1023-102,0,5));
//  Serial.print  ("  ");
//  Serial.print  (voltage);
//  Serial.print  ("V  ");
//  Serial.print  (sensorValue);
//  Serial.println(" ");

  byte buttonState = digitalRead(buttonPin);
  if (buttonState != previousState) {
    if (buttonState == LOW) {
      count = count + 1;
      countAt = millis();
    }
    previousState = buttonState;
  } else {
    if (count != countPrinted) {
      unsigned long nowMillis = millis();
      if (nowMillis - countAt > 100) {
        Serial.print("count: ");
        Serial.println(count);
        countPrinted = count;
      }
    }
  }
}
