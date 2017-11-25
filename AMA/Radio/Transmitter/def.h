#ifndef DEF_H_
#define DEF_H_

#include <avr/pgmspace.h>

#define PGMSTR(x) (__FlashStringHelper*)(x)

/**************************************************************************************/
/***************      Serail Debug test configurations             ********************/
/**************************************************************************************/
//#define DEBUG_CD4051
//#define DEBUG_CD4051_MASK
//#define DEBUG_CD4052
//#define DEBUG_CD4052_VOLTS
//#define DEBUG_KEY
//#define DEBUG_MyControls


/**************************************************************************************/
/***************          constants configurations                 ********************/
/**************************************************************************************/
const char PROGMEM  qBytesWorld[] = "Q-Bytes World";
const char PROGMEM  deviceInfo [] = {"2.4G Transmitter"};
const char PROGMEM  versionNum [] = {"v1.15"};

const char PROGMEM  volts      [] = {"Volts: "};


//const String err = "Err:

//PROGMEM const String sampleMenu_back = "Back";
//PROGMEM const String sampleMenu_exit = "Exit";
//
//PROGMEM const String sampleMenu_2_1_1 = "1 Sub item A";
//PROGMEM const String sampleMenu_2_1_2 = "2 Sub item B";

//const char PROGMEM  D6      [] = {"%6d"};

/**************************************************************************************/
/***************           defaults configurations                 ********************/
/**************************************************************************************/
#define MAINMENU 1
#define FUNCTION 255

#define MAX 255
#define MID 128
#define MIN 0


/**************************************************************************************/
/***************             Proc specific definitions             ********************/
/**************************************************************************************/
// Proc auto detection
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
  #define PROMINI
#endif
#if defined(__AVR_ATmega32U4__) || defined(TEENSY20)
  #define PROMICRO
#endif
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
  #define MEGA
#endif


/**************************************************************************************/
/***************             motor and servo numbers               ********************/
/**************************************************************************************/



/**************************************************************************************/
/***************               Error Checking Section              ********************/
/**************************************************************************************/

#if GPS && !defined(NMEA) && !defined(UBLOX)
  #error "when using GPS you must specify the protocol NMEA, UBLOX..."
#endif



#endif /* DEF_H_ */
