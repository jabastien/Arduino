#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <KeyPad.h>

KeyPad keyPad(LED_BUILTIN, 5, 10);
//KeyPad keyPad;  // Empty constructor does not require ().
//KeyPad keyPad(); // this is an error


void setup() {
  Serial.begin(9600);
  Serial.flush() ;
  Serial.println("KeyPad starting");
  
  analogReference(EXTERNAL); 

  pinMode(A0, INPUT);
  
  if (false){
    for (int num = 0; num < 1023; num++){
      keyPad.doKeys(num);
    }
    Serial.println("Holding here.");
    while(true){} // display only: hold here.
  }

  Serial.println("KeyPad running");
}

void loop() {
  keyPad.doKeys(analogRead(A0));
  byte b = keyPad.getKeyPressed();

  if (b > 0){
    Serial.println(b);
  }
}