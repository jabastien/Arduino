#ifndef def_h
#define def_h

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

/*
 include description files for other libraries used (if any)
#include <limits.h>
 https://github.com/esp8266/Arduino/blob/master/tools/sdk/libc/xtensa-lx106-elf/include/limits.h

  if (half){
    if (number > SHRT_MAX){
        number = SHRT_MAX;
    }
  }
 
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
PROGMEM const char  versionNum [] = {"v1.25"};

/**************************************************************************************/
/***************          date & time configurations               ********************/
/**************************************************************************************/
//const long day = 86400000; // 86400000 milliseconds in a day
//const long hour = 3600000; // 3600000 milliseconds in an hour
//const long minute = 60000; // 60000 milliseconds in a minute
//const long second =  1000; // 1000 milliseconds in a second

#define DAY  86400 // 86400000 milliseconds in a  day
#define HOUR  3600 //  3600000 milliseconds in an hour
#define MINUTE  60 //    60000 milliseconds in a  minute
#define SECOND   1 //     1000 milliseconds in a  second
 
#define DD(seconds) (   seconds / DAY)                   //number of days
#define HH(seconds) ((  seconds % DAY) / HOUR)           //the remainder from days division divided by hours, this gives the full hours
#define MM(seconds) ((( seconds % DAY) % HOUR) / MINUTE) //and so on...
#define SS(seconds) ((((seconds % DAY) % HOUR) % MINUTE) / SECOND)

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
PROGMEM const char lcd_param_lcdInit252_5V    [] = "5V Regulator";
PROGMEM const char lcd_param_lcdInit252_5Vmes [] = "Measure";
PROGMEM const char lcd_param_lcdInit252_5Vsys [] = "System";
PROGMEM const char lcd_param_lcdInit252_v5bit [] = "Volt/Bit";


//
// X254: 
// Start up
//                                                    123456789012 
PROGMEM const char lcd_param_lcdInit254_startUp [] = "Start up";



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

// ===========================================
// Display
// ===========================================
PROGMEM const char  digits8 []     = " ###";
PROGMEM const char  digits16[]     = " ##,###";
PROGMEM const char  digits32[]     = " #,###,###,###";

PROGMEM const char  volts_xx_xV[]  = " ##.#V";
PROGMEM const char  volts_x_xxxV[] = " #.###V";

PROGMEM const char  volts_0_0xxxxxV[] = " 0.0#####V";

//PROGMEM const char  ohm_xx_xxxO[] = "##,###^"; // K OHMs      //0xF4; //OHM  //  line[6] =  0xF4; //OHM
PROGMEM const char  ohm_xx_xxxO[] = {'#','#','.','#','#','#',char(244),char(0)};
//PROGMEM const char  ohm_xx_xxxO[] = {' ','#','.','#','#','#',char(0xF4),char(0x00)};

//PROGMEM const char  ohm_x_xxxxO[] = "#.####^"; // milla OHMs  //0xF4; //OHM
PROGMEM const char  ohm_x_xxxxO[] = {' ','#','.','#','#','#','#',char(0xF4),char(0x00)};

// ===========================================
// Custom Display
// ===========================================
PROGMEM const char  timer[]        = "##:##:##";
PROGMEM const char  timerDay[]     = "####:##:##:##";


/**************************************************************************************/
/***************             motor and servo numbers               ********************/
/**************************************************************************************/

/**************************************************************************************/
/***************                      Misc                         ********************/
/**************************************************************************************/

#define membersof(x) (sizeof(x) / sizeof(x[0]))

/**************************************************************************************/
/***************               Error Checking Section              ********************/
/**************************************************************************************/

//#if GPS && !defined(NMEA) && !defined(UBLOX)
//  #error "when using GPS you must specify the protocol NMEA, UBLOX..."
//#endif

#endif /* dev_h */

