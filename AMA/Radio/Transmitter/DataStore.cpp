/*
  DataStore.cpp - Data for the Transmitter

  EEPROM Data read/write from Data.cpp
*/


// https://github.com/esp8266/Arduino/issues/1539



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

// include description files for other libraries used (if any)
#include "HardwareSerial.h"


#include <EEPROM.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

//extern MyResistorMap myResistorMap;

//DataStore::DataStore(){
//}

DataStore::DataStore(Data * data){
  // initialize this instance's variables
  //Serial.begin(115200); //Set the speed to 9600 bauds if you want.
  
  // do whatever is required to initialize the library


  /*
    void setJoystick(byte, int);
    int getJoystick(byte);
   */
  _data = data;

  
//  _data->setJoystick(1,11);
//
//  Serial.println("DataStore");
//  Serial.println(_data->getJoystick(0));
//  Serial.println(_data->getJoystick(1));
//  Serial.println(_data->getJoystick(2));
//  Serial.println(_data->getJoystick(3));
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
int DataStore::eepromSize(){
  return EEPROM.length();  
}

void DataStore::factoryReset() {
  for (unsigned int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}



//
//void readEEPROM() {
//  int eeAddress = 0;
//
//  EEPROM.get(eeAddress, myResistorMap);
//  eeAddress += sizeof(myResistorMap); //Move address to the next byte after MyControlsRangeMap 'myControlsRangeMap'.
//
//  //
//  EEPROM.get(eeAddress, myControlsRangeMap);
//  eeAddress += sizeof(myControlsRangeMap); //Move address to the next byte after myControlsRangeMap 'myControlsRangeMap'.
//  //  eeAddress += sizeof(myControlsRangeMap); //Move address to the next byte after myControlsRangeMap 'myControlsRangeMap'.

//}
//
//
//void writeEEPROM() {
//  int eeAddress = 0;
//
//  //
//  EEPROM.put(eeAddress, myControlsRangeMap);
//  eeAddress += sizeof(myControlsRangeMap); //Move address to the next byte after myControlsRangeMap 'myControlsRangeMap'.
//
//  //
//  //eeAddress += sizeof(myControlsRangeMap);
//  EEPROM.put(eeAddress, myControlsRangeMap);
//  eeAddress += sizeof(myControlsRangeMap); //Move address to the next byte after myControlsRangeMap 'myControlsRangeMap'.
//}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


