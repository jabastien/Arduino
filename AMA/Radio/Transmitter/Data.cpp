/*
  Data.h - Data library for Wiring - implementation
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
#include "Data.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Data::Data(){
  // initialize this instance's variables
  //value = givenValue;

  // do whatever is required to initialize the library
//  pinMode(13, OUTPUT);
//  Serial.begin(115200);
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void Data::doSomething(void)
{
//  Serial.begin(115200); //Set the speed to 9600 bauds if you want.
  // eventhough this function is public, it can access
  // and modify this library's private variables
  Serial.println("Data class");
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


