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

DataStore::DataStore(Data * _data){
  // initialize this instance's variables
  
  // do whatever is required to initialize the library

  data = _data;

#ifdef DEBUG_DATASTORE
if(true){
  Serial.begin(115200); //Set the speed to 9600 bauds if you want.
  
  Serial.println(PGMSTR(dashes)); 
  Serial.println(PGMSTR(dashes)); 
  Serial.println(PGMSTR(dashes)); 

  Serial.print  ("Size of MyJoysticks: "); 
  Serial.println(sizeof(MyJoysticks));

  Serial.print  ("Size of MyAux: "); 
  Serial.println(sizeof(MyAux));

  Serial.print  ("Size of MySwitchesButtons: "); 
  Serial.println(sizeof(MySwitchesButtons));

  Serial.print  ("Size of MyControlsRangeMap: "); 
  Serial.println(sizeof(MyControlsRangeMap));

  Serial.print  ("Size of MyVoltageMap: "); 
  Serial.println(sizeof(MyVoltageMap));

  Serial.print  ("Size of MyResistorMap: "); 
  Serial.println(sizeof(MyResistorMap));

  Serial.println(PGMSTR(dashes)); 
  Serial.println(PGMSTR(dashes)); 
  Serial.println(PGMSTR(dashes)); 
}  
#endif  
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

int eeAddrVer    = 000;
int eeAddrJoyMap = 100;
int eeAddrAuxMap = 200;

int eeAddrResMap = 300;
int eeAddrVltMap = 400;

void DataStore::loadFromEEPROM(){
Serial.println("loadFromEEPROM");

EEPROM.get(eeAddrJoyMap + 000, data->getMyJoysticksRangeMap(0));
EEPROM.get(eeAddrJoyMap + 020, data->getMyJoysticksRangeMap(1));
EEPROM.get(eeAddrJoyMap + 040, data->getMyJoysticksRangeMap(2));
EEPROM.get(eeAddrJoyMap + 060, data->getMyJoysticksRangeMap(3));

EEPROM.get(eeAddrAuxMap + 000, data->getMyAuxsRangeMap(0));
EEPROM.get(eeAddrAuxMap + 020, data->getMyAuxsRangeMap(1));
EEPROM.get(eeAddrAuxMap + 040, data->getMyAuxsRangeMap(2));
EEPROM.get(eeAddrAuxMap + 060, data->getMyAuxsRangeMap(3));

EEPROM.get(eeAddrResMap, data->getMyResistorMap());
EEPROM.get(eeAddrVltMap, data->getMyVoltageMap());

Serial.println("loadFromEEPROM - done");
}


void DataStore::saveToEEPROM(){
Serial.println("saveToEEPROM");
  char buffer1[10];
  strcpy_P(buffer1,lcd_param_lcdInit151_versionNum);  
  EEPROM.put(eeAddrVer, buffer1);
  
  // Load all EEPROM data

EEPROM.put(eeAddrJoyMap + 000, data->getMyJoysticksRangeMap(0));
EEPROM.put(eeAddrJoyMap + 020, data->getMyJoysticksRangeMap(1));
EEPROM.put(eeAddrJoyMap + 040, data->getMyJoysticksRangeMap(2));
EEPROM.put(eeAddrJoyMap + 060, data->getMyJoysticksRangeMap(3));

EEPROM.put(eeAddrAuxMap + 000, data->getMyAuxsRangeMap(0));
EEPROM.put(eeAddrAuxMap + 020, data->getMyAuxsRangeMap(1));
EEPROM.put(eeAddrAuxMap + 040, data->getMyAuxsRangeMap(2));
EEPROM.put(eeAddrAuxMap + 060, data->getMyAuxsRangeMap(3));

EEPROM.put(eeAddrResMap, data->getMyResistorMap());
EEPROM.put(eeAddrVltMap, data->getMyVoltageMap());
Serial.println("saveToEEPROM - done");
}

boolean DataStore::isVersionMatch(){
  char buffer1[10];
  strcpy_P(buffer1,lcd_param_lcdInit151_versionNum);

  char buffer2[10];
  EEPROM.get(eeAddrVer, buffer2);
  return !(strcmp(buffer2, buffer1));  
}
    
// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


