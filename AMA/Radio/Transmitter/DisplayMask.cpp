/*
  DisplayMask.h - Test library for Wiring - implementation
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
#include "DisplayMask.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

DisplayMask::DisplayMask(){
  // initialize this instance's variables

  // do whatever is required to initialize the library
  mask = NULL;
  maskSize = 0;
  matchChar = 0;
  digitCnt = 0;
  courserPos = -1;
  expoFactor = -1;
  displayPos = 0;
  pVoid = NULL;
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void DisplayMask::doMaskInit(const  char *_mask, const  char _matchChar, byte _displayPos, void * _pVoid){

  mask = _mask;
  sprintf_P(buffer, PSTR("%S") , mask);
  //utils.reverse(buffer);  
  maskSize = utils.arraySize(buffer);
  matchChar = _matchChar;
  digitCnt = utils.countCharacters(buffer, matchChar);
  courserPos = -1;
  expoFactor = -1;
  displayPos = _displayPos;

  pVoid = _pVoid;
  
  // INIT, first time setup for mask, set defaults....
  doMaskEdit(LEFT);
}

void * DisplayMask::getVoidPointer(void){
  return pVoid;
}

byte DisplayMask::getDisplayPos(){
  return displayPos;
}

byte DisplayMask::getCourserPos(){
  return ((displayPos + (maskSize - 1)) - courserPos);
}

int8_t DisplayMask::getIncDirection(){
  return incDirection;
}

const char * DisplayMask::getMask(void){
  sprintf_P(buffer, PSTR("%S") , mask);
  return buffer;
}

// pow has a bug (not whole numbers).  It's a float point thing
// https://ucexperiment.wordpress.com/2016/02/02/floating-point-precision-or-arduino-dont-know-math/
uint32_t DisplayMask::getExpoValue(){

  uint32_t expoValue = 1;
  for (uint8_t i = 0; i < expoFactor; i++){
     expoValue *= 10;
  }

  return expoValue;
}

int8_t DisplayMask::getExpoFactor(){
  return expoFactor;
}

void DisplayMask::doMaskEdit(byte _keyPress){
  
  sprintf_P(buffer, PSTR("%S") , mask);
  utils.reverse(buffer);  

  #ifdef DEBUG_DISPLAYMASK_DETAIL
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
  #endif
  int8_t tmpCurserPos = (uint8_t)courserPos;
  boolean done = false;
  int8_t moveLR = 0;

  #ifdef DEBUG_DISPLAYMASK_DETAIL
  if (false){
    Serial.print  ("tmpCurserPos ");
    Serial.print  (tmpCurserPos);
    Serial.println();
  }
  #endif  

  incDirection = 0;

  // NOKEY, leave.
  if (_keyPress == NOKEY){
    return;
  }

  // Direction for number increment.
  if (_keyPress == UP) {
    incDirection = 1;
  }
  if (_keyPress == DOWN) {
    incDirection = -1;  
  }

  // Move cursor LEFT/RIGHT?
  if (_keyPress == LEFT) {
    moveLR =  1; // Not (-1), backward because array is reversed.
  }
  if (_keyPress == RIGHT) {
    moveLR = -1; // Not (+1), backward because array is reversed.
  }
    
  if (moveLR != 0) { //_keyPress == LEFT || _keyPress == RIGHT
    // Limit move to width of mask
    while(!done){
      bool cond = ((tmpCurserPos+moveLR) < 0 || (tmpCurserPos+moveLR >= maskSize));
       #ifdef DEBUG_DISPLAYMASK_DETAIL
      if (false){
        bool cond1 = ((tmpCurserPos+moveLR) < 0);
        bool cond2 = ((tmpCurserPos+moveLR) >= maskSize);      
        Serial.print  (" Condition T:M:C ");
        Serial.print  (tmpCurserPos+moveLR);
        Serial.print  (":");
        Serial.print  (maskSize - 1);
        Serial.print  (":");
        Serial.print  (cond);
        Serial.println();
      }
       #endif      
      if (cond){
        #ifdef DEBUG_DISPLAYMASK_DETAIL
        if (false){
          Serial.println("range ==============");
          Serial.print  ("tmpCurserPos ");
          Serial.print  (tmpCurserPos);
          Serial.println();        
        }
        #endif        
        done = true;
      }
      if (!done){
        // Allow moves only to '#' cells
        #ifdef DEBUG_DISPLAYMASK_DETAIL        
        if (false){
          Serial.println("!done");
        }
        #endif        
        tmpCurserPos += moveLR;
        if (buffer[tmpCurserPos] == matchChar){
          courserPos = tmpCurserPos;
          expoFactor += moveLR;
          #ifdef DEBUG_DISPLAYMASK_DETAIL          
          if (false){
            Serial.println("Inc/Dec ==============");        
          }
          #endif          
          done = true;
        }
      } else {
        // End of mask, no match, no move
        #ifdef DEBUG_DISPLAYMASK_DETAIL
        if (false){
          Serial.println("Fail =============="); 
          Serial.print  ("tmpCurserPos ");
          Serial.print  (tmpCurserPos);
          Serial.println();  
        }
        #endif             
        done = true;
      }
    }
  }

  #ifdef DEBUG_DISPLAYMASK
  if (true){
    Serial.print  (" _keyPress ");
    Serial.print  (_keyPress);
    Serial.print  (" moveLR ");
    Serial.print  (moveLR);
    Serial.print  ("\t tmpCurserPos ");
    Serial.print  ((int8_t)tmpCurserPos);  
    Serial.print  ("  \t courserPos ");
    Serial.print  (courserPos);

    buffer[courserPos] = '?';
    
    Serial.print  (" Post 1: '");
    Serial.print  (buffer);    
    Serial.print  ("'");        

    Serial.print  (" Post 2: '");
    utils.reverse(buffer);      
    Serial.print  (buffer);    
    Serial.print  ("'");        

    Serial.print  (" displayPos() ");
    Serial.print  (getDisplayPos());
    Serial.print  (" courserPos() ");
    Serial.print  (getCourserPos());

    Serial.print  (" expoFactor ");
    Serial.print  (expoFactor);
    

//    Serial.print  (" pow "); 
//    Serial.print  (pow(10.000, 9.000));
//    Serial.print  (pow(10.0, (float)expoFactor));

//float expo = expoFactor;
//float fact = 10.00;
//    Serial.print  (" pow ");
//    Serial.print  ((uint32_t)pow(fact, expo));

//    Serial.print  (" x^y ");
//    Serial.print  ((uint32_t)exp(expo * log(fact)));

//    float pow (float A, float B)//{
//     return exp (B * log(A));
//    }


  
    // This is my work around
    Serial.print  (" getExpoValue ");
    Serial.print  (getExpoValue());
//    uint32_t expoValue = 1;
//    for (uint8_t i = 0; i < expoFactor; i++){
//       expoValue *= 10;
//    } 
//    Serial.print  (" uint32_t ");
//    Serial.print  (expoValue);
    Serial.println();        
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

  if (false){
    Serial.println();
    Serial.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");     
  }
  #endif

}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

