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


/*
  Serial.print ("pttr ");
  Serial.println(PGMSTR(pttr));
  Serial.print ("volts_x_xxxV ");
  Serial.println(PGMSTR(volts_x_xxxV));
  Serial.print ("pgmData ");
  Serial.println(PGMSTR(myMenuData.pgmData[1]));

  sprintf_P(buffer, PSTR("%S") , pttr);
  Serial.print  ("buffer 1");
  Serial.println(buffer); 

void printOutMessage(const __FlashStringHelper* message){
  char buffer[40];
  sprintf_P(buffer, PSTR("Ha Ha %S") , message);
  Serial.println(buffer); 
}

sprintf_P(buffer, PSTR("%S") , myMenuData.pgmData[1]);
Serial.print  ("buffer 2");
Serial.println(buffer); 
 */

void Edit::doMaskInit(const  char *mask, const  char _matchChar){
  sprintf_P(buffer, PSTR("%S") , mask);
  maskSize = utils.arraySize(buffer);
  matchChar = _matchChar;
  digitCnt = utils.countCharacters(buffer, matchChar);
  courserPos = 0;
  expoFactor = 0;

  doMaskEdit(RIGHT, buffer, matchChar, 0);
}

// INIT, first time setup for mask, set defaults....
void Edit::doMaskEdit(byte _keyPress, const  char *mask, const  char _matchChar, byte _courserPos){

/* Force navigation, Don't allow this to be passed in, store locally */
const  char *mask,      // already have it
const  char _matchChar, // already have it
byte _courserPos        // already have it
/* Force navigation, Don't allow this to be passed in, store locally */
  
  sprintf_P(buffer, PSTR("%S") , mask);
  maskSize = utils.arraySize(buffer);
  matchChar = _matchChar;
  digitCnt = utils.countCharacters(buffer, matchChar);
  courserPos = _courserPos;
  expoFactor = 0;
  
  if (false){
  Serial.print  ("IN     : '");
  Serial.print  (buffer);  
  Serial.println("'");

  Serial.print  ("size   : ");
  Serial.println(maskSize);

  Serial.print  ("cnt'");
  Serial.print  (matchChar);
  Serial.print  ("' : ");
  Serial.println(digitCnt);  
  }
    
  utils.reverse(buffer);

  byte tmpCurserPos   = courserPos;
  boolean done = false;
  byte dir = 0;

  if (_keyPress == RIGHT) {
    dir = 1;
  }
  if (_keyPress == LEFT) {
    dir = -1;
  }
    
  if (dir != 0) { //_keyPress == LEFT || _keyPress == RIGHT
    // Limit move to width of mask
    while(!done){
        Serial.print  (" Condition ");
        Serial.print  (tmpCurserPos > 0 && tmpCurserPos < maskSize);
        Serial.println();
      if (tmpCurserPos >= 0 && tmpCurserPos < maskSize){
        // Allow moves only to '#' cells
        Serial.println("If ");        
        tmpCurserPos += dir;
        if (buffer[tmpCurserPos] == matchChar){
          courserPos = tmpCurserPos;
          expoFactor += dir;
           Serial.println("Inc");        
          done = true;
        }
      } else {
        // End of mask, no match, no move
        Serial.println("Fail");        
        done = true;
      }
    }
  }

/*
  if (dir != 0) {
        Serial.print  ("dir ");
        Serial.print  (dir);
        Serial.println();
    // Limit move to width of mask
    while(!done){
        Serial.print  (" Condition ");
        Serial.print  (tmpCurserPos > 0 && tmpCurserPos < maskSize);
        Serial.println();
      if (tmpCurserPos >= 0 && tmpCurserPos < maskSize){
        // Allow moves only to '#' cells
        Serial.println("If ");        
        tmpCurserPos += dir;
        if (buffer[tmpCurserPos] == matchChar){
          courserPos = tmpCurserPos;
          expoFactor += dir;
        Serial.println("Inc");        
          done = true;
        }
      } else {
        // End of mask, no match, no move
        Serial.println("Fail");        
        done = true;
      }
    }
  }
*/

  if (true){
    Serial.print  (" _keyPress ");
    Serial.print  (_keyPress);
    Serial.print  (" dir ");
    Serial.print  (dir);
    Serial.print  (" tmpCurserPos ");
    Serial.print  (tmpCurserPos);
    Serial.print  (" _courserPos ");
    Serial.print  (_courserPos);

    //Serial.println();

    buffer[courserPos] = '?';
    
    Serial.print  ("  Post : '");
    Serial.print  (buffer);    
    Serial.println("'");        
  }
  
  if (false){   
    Serial.print  ("Reverse: '");
    for (byte b = 0; b < maskSize; b++){
      Serial.print (buffer[b]);
    } 
    Serial.println("'");
    Serial.print  ("Buffer : '");
    Serial.print  (buffer);    
    Serial.println("'");
  }
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


