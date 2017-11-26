/*
  Data.cpp - Data for the Transmitter
*/

// include core Arduino API
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


#include <EEPROM.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Data::Data(){
  // initialize this instance's variables

  // do whatever is required to initialize the library


  //Print length of data to run CRC on.
  Serial.print(F("EEPROM length: "));
  Serial.println(EEPROM.length());  
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries
//
// ===========================================
// ===========================================
// ===========================================
// EEPROM
// ===========================================
// ===========================================
// ===========================================

void Data::factoryReset() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

//
//void readEEPROM() {
//  int eeAddress = 0;
//
//  EEPROM.get(eeAddress, myVoltsMap);
//  eeAddress += sizeof(myVoltsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//
//  //
//  EEPROM.get(eeAddress, myControlsMapThrottle);
//  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//  //  eeAddress += sizeof(myControlsMapThrottle); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//
//  EEPROM.get(eeAddress, myControlsMapYaw);
//  eeAddress += sizeof(myControlsMapThrottle); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//
//  EEPROM.get(eeAddress, myControlsMapRoll);
//  eeAddress += sizeof(myControlsMapThrottle); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//
//  EEPROM.get(eeAddress, myControlsMapPitch);
//  eeAddress += sizeof(myControlsMapThrottle); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//}
//
//
//void writeEEPROM() {
//  int eeAddress = 0;
//
//  //
//  EEPROM.put(eeAddress, myVoltsMap);
//  eeAddress += sizeof(myVoltsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//
//  //
//  //eeAddress += sizeof(myControlsMapSet);
//  EEPROM.put(eeAddress, myControlsMapThrottle);
//  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//
//  EEPROM.put(eeAddress, myControlsMapYaw);
//  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//
//  EEPROM.put(eeAddress, myControlsMapRoll);
//  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//
//  EEPROM.put(eeAddress, myControlsMapPitch);
//  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
//}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


