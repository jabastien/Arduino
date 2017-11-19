#include <CD4051.h>

//CD4051 cd4051 = CD4051();
CD4051 cd4051 = CD4051(4, 5, 6, 8);

/*
 * 
 * 
 */
void setup() {
  // put your setup code here, to run once:

  // Setup communication
  Serial.begin(115200);
  Serial.println("Hello!, testing CD4051");
}

int looping = 9;
int pinSwitchs = 0b00000000;

/*
 * 
 * 
 */
void loop() {

  cd4051.setChannel(looping);

  // Get the switch values
  byte pinmask = ~(1<<(looping%8)); 
  byte readmask = (cd4051.digitalReadC()<<(looping%8)); 
  pinSwitchs = (pinSwitchs & pinmask) | readmask;

//  // Print switches
  Serial.print(" ");
  if (false){
    Serial.print(" Pin ");  
    Serial.print(pinmask + 0x100, BIN);
    Serial.print(" Mask ");  
    Serial.print(readmask + 0x100, BIN);
    }
  Serial.print(" Switch ");  
  Serial.print(pinSwitchs + 0x100, BIN);
  
  
  // Increment looping
  if (++looping >=8){
    looping = 0;  
    }
      
  Serial.println();
}