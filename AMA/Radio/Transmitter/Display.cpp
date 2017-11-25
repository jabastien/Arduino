/*
  Display.h - Test library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include core Wiring API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
//  #include "WConstants.h"
#endif

// include this library's description file
#include "Display.h"

// include description files for other libraries used (if any)
#include <limits.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
//        2147483647
char digit1000000000 (uint16_t v) {return '0' + v / 1000000000 - (v/10000000000) * 10;}
char digit100000000  (uint16_t v) {return '0' + v / 100000000  - (v/1000000000)  * 10;}
char digit10000000   (uint16_t v) {return '0' + v / 10000000   - (v/100000000)   * 10;}
char digit1000000    (uint16_t v) {return '0' + v / 1000000    - (v/10000000)    * 10;}
char digit100000     (uint16_t v) {return '0' + v / 100000     - (v/1000000)     * 10;}
char digit10000      (uint16_t v) {return '0' + v / 10000      - (v/100000)      * 10;}
char digit1000       (uint16_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
char digit100        (uint16_t v) {return '0' + v / 100        - (v/1000)        * 10;}
char digit10         (uint16_t v) {return '0' + v / 10         - (v/100)         * 10;}
char digit1          (uint16_t v) {return '0' + v / 1          - (v/10)          * 10;} 

Display::Display(){
  // initialize this instance's variables


  // do whatever is required to initialize the library

}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries
//char *itoa(int n)
//  {
//  static char retbuf[25];
//  sprintf(retbuf, "%d", n);
//  return retbuf;
//  }

char * Display::formatUnsignedInt(unsigned int number, boolean half){
//static char line[8] = "+65,535"; // Max number
//static char line[8] = "-32,767"; // Half number
//static char line[8] = "012,456"; // Digit possition (+1 for terminator /0.
  static char line[8] = " --,---";
  
  if (half){
    if (number > SHRT_MAX){
        number = SHRT_MAX;
    }
  }
  
  line[1] =  digit10000 (number);
  line[2] =  digit1000  (number);
  line[4] =  digit100   (number);
  line[5] =  digit10    (number);
  line[6] =  digit1     (number);

//  Serial.print(digit10000 (number));
//  Serial.print(digit1000  (number));
//  Serial.print(digit100   (number));
//  Serial.print(digit10    (number));
//  Serial.print(digit1     (number));
//  Serial.println();

  return line;
}

char * Display::formatInt(int number){

//static char line[8] = "+65,535"; // Max number
//static char line[8] = "-32,767"; // Half number
//static char line[8] = "012,456"; // Digit possition (+1 for terminator /0.
  static char line[8] = "+--,---";
  
  if (number < 0 ) { // Can't be negative.
    number = -number;
    line[0] = '-';
  } else {
    number = number;
    line[0] = ' ';
  }
  
  line[1] =  digit10000 (number);
  line[2] =  digit1000  (number);
  line[4] =  digit100   (number);
  line[5] =  digit10    (number);
  line[6] =  digit1     (number);

//  Serial.print(digit10000 (number));
//  Serial.print(digit1000  (number));
//  Serial.print(digit100   (number));
//  Serial.print(digit10    (number));
//  Serial.print(digit1     (number));
//  Serial.println();

  return line;
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


