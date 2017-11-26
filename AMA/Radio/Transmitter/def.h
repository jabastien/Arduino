#ifndef DEF_H_
#define DEF_H_

#include <avr/pgmspace.h>

#define PGMSTR(x) (__FlashStringHelper*)(x)

/*
  review these again:

    http://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html
    http://arduino-esp8266.readthedocs.io/en/latest/PROGMEM.html
    
PROGMEM const char   sampleMenu_back = "Back";
PROGMEM const String sampleMenu_exit = "Exit";

const String err = "Err:
 */
 
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
PROGMEM const char  qBytesWorld[] = "Q-Bytes World";
PROGMEM const char  deviceInfo [] = {"2.4G Transmitter"};
PROGMEM const char  versionNum [] = {"v1.16"};

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
// Common
//                                           123456789012 
PROGMEM const char lcd_param_common_set [] = "(Set)";



//
// X240
// Check controls
//                                               123456789012 
PROGMEM const char lcd_param_lcdInit240_volts [] = {"Volts"};

//
// X252
//5.0V Regulator
//                                               123456789012 
PROGMEM const char lcd_param_lcdInit252_5V [] = "5V Regulator";


//// Proc auto detection
//#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
//  #define PROMINI
//#endif
//#if defined(__AVR_ATmega32U4__) || defined(TEENSY20)
//  #define PROMICRO
//#endif
//#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
//  #define MEGA
//#endif


/**************************************************************************************/
/***************             motor and servo numbers               ********************/
/**************************************************************************************/



/**************************************************************************************/
/***************               Error Checking Section              ********************/
/**************************************************************************************/

//#if GPS && !defined(NMEA) && !defined(UBLOX)
//  #error "when using GPS you must specify the protocol NMEA, UBLOX..."
//#endif

#endif /* DEF_H_ */
