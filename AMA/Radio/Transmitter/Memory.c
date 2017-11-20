///*A basic 4 channel transmitter using the nRF24L01 module.*/
///* Like, share and subscribe, ELECTRONOOBS */
///* http://www.youtube/c/electronoobs */
//
///* First we include the libraries. Download it from
//   my webpage if you donw have the NRF24 library */
//
////#if defined(ARDUINO) && ARDUINO >= 100
//#if ARDUINO >= 100
//  #include "Arduino.h"
//#else
//  #include "WProgram.h"
//  #include "pins_arduino.h"
//  #include "WConstants.h"
//#endif
//
//
//
//// ===========================================
//// EEPROM
//// ===========================================
//#include <EEPROM.h>
//
//
////  //Print length of data to run CRC on.
////  Serial.print("EEPROM length: ");
////  Serial.println(EEPROM.length());
//  
//// ===========================================
//// ===========================================
//// ===========================================
//// EEPROM
//// ===========================================
//// ===========================================
//// ===========================================
//void factoryReset() {
//  for (int i = 0 ; i < EEPROM.length() ; i++) {
//    EEPROM.write(i, 0);
//  }
//}
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

