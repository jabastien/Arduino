/*
  Edit.h - Test library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include core Wiring API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

// include this library's description file
#include "Edit.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Edit::Edit(){
  // initialize this instance's variables

  // do whatever is required to initialize the library

}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void Edit::doMaskEdit(byte _keyPress, char  mask[], uint16_t number){
  // eventhough this function is public, it can access
  // and modify this library's private variables

  if (true){
    Serial.print  ("mask in : ");
    Serial.print  (mask);    
  }
  
  byte maskSize = utils.arraySize(mask);
  byte digitCnt;     // number of # in edit mask
  byte digitPos;     // digit under edit
  byte CourserPos;   // pos in edit mask
  byte digitFactor;  // digit factor is 2 = 10, 3 = 100, e = 1000

  mask = reverse(mask,maskSize);

  if (true){
    Serial.print  (" rtn: '");
    Serial.print  (mask);
    Serial.println("'");    
  }
  
}

void Edit::doMaskEdit2(byte _keyPress, const  char *mask, uint16_t number){
  char buffer[20];
  sprintf_P(buffer, PSTR("%S") , mask);
  Serial.print  ("doMaskEdit2");
  Serial.println(buffer);  
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

char* Edit::reverse(char  mask [], byte maskSize ){

  maskSize--;
  byte halfSize = maskSize / 2;
  if (true){
    Serial.print  (" pre: ");
    Serial.print  (mask);
    Serial.print  (" maskSize: ");
    Serial.print  (maskSize);  
    Serial.print  (" halfSize: ");
    Serial.println(halfSize);
  }
  
  Serial.print  ("TMP: '");
  for (byte b = 0; b < halfSize; b++){
    char tmp = mask[b];
    Serial.print  (tmp);
    mask[b] = mask[maskSize-b];
    mask[maskSize-b] = tmp;
  }
  Serial.println("'");
  
  if (true){
    Serial.print  (" rev: ");
    Serial.print (mask);
  }
  
  return mask;
}
