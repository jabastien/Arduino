#include <KeyPad.h>

void setup() {
  Serial.begin(115200);
  
  pinMode(A0, INPUT);
  
  pinMode(2, OUTPUT);
  digitalWrite (2, LOW);
  analogReference(EXTERNAL); 


//  for (int num = 0; num < 1023; num++){
//    keyPad.doKeys(num);
//  }
//  while(true){}
}

void loop() {
  keyPad.doKeys(analogRead(A0));
  byte b = keyPad.getKeyPressed();

  if (b > 0){
    Serial.println(b);
  }
}
