/*
  DataStore.cpp - Data for the Transmitter

  EEPROM Data read/write from Data.cpp
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
#include "DataStore.h"
#include "Data.h"

#include "config.h"
#include "def.h"
#include "types.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"


#include <EEPROM.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

//extern MyResistorMap myResistorMap;

DataStore::DataStore(){
}

DataStore::DataStore(Data * data){
  // initialize this instance's variables
  Serial.begin(115200); //Set the speed to 9600 bauds if you want.
    // do whatever is required to initialize the library
    
  Serial.println("In DataStore");
//  data.doSomething();
  Serial.println("Out DataStore");
  
  //Print length of data to run CRC on.
  Serial.print(F("EEPROM length: "));
  Serial.println(EEPROM.length());  

  /*
    void setAnalog(byte, int);
    int getAnalog(byte);
   */
  _data = data;
  _data->setAnalog(1,11);

  Serial.println("DataStore");
  Serial.println(*_data.getAnalog(0));
  Serial.println(_data->getAnalog(1));
  Serial.println(_data->getAnalog(2));
  Serial.println(_data->getAnalog(3));
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

void DataStore::factoryReset() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

//
//void readEEPROM() {
//  int eeAddress = 0;
//
//  EEPROM.get(eeAddress, myResistorMap);
//  eeAddress += sizeof(myResistorMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
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
//  EEPROM.put(eeAddress, myResistorMap);
//  eeAddress += sizeof(myResistorMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
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


