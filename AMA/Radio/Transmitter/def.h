#ifndef def_h
#define def_h

#include <avr/pgmspace.h>

// fun with PROGMEM
#define PGMSTR(x) (__FlashStringHelper*)(x)
#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))

  ///__FlashStringHelper*
//# define PSTR(s) ((const PROGMEM char *)(s))
  
/*
  review these again:

    http://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html
    http://arduino-esp8266.readthedocs.io/en/latest/PROGMEM.html
    
    
const PROGMEM char   sampleMenu_back = "Back";
PROGMEM const String sampleMenu_exit = "Exit";

const String err = "Err:

c:\users\davidq\appdata\local\arduino15\packages\arduino\tools\avr-gcc\4.9.2-atmel3.5.4-arduino2\avr\include\avr\pgmspace.h:408:0: note: this is the location of the previous definition
 # define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))

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
/***************      Serail Debug test configurations             ********************/
/**************************************************************************************/
//#define DEBUG_CD4051
//#define DEBUG_CD4051_MASK
//#define DEBUG_CD4052
//#define DEBUG_CD4052_VOLTS
//#define DEBUG_CALCVOLTS
//#define DEBUG_CALCVOLTS_PP
//#define DEBUG_DATASTORE
//#define DEBUG_DISPLAY
//#define DEBUG_DISPLAYMASK
//#define DEBUG_DISPLAYMASK_DETAIL
//#define DEBUG_FPS
//#define DEBUG_KEY
//#define DEBUG_MyControls
//#define DEBUG_JoyAux



/**************************************************************************************/
/***************          constants configurations                 ********************/
/**************************************************************************************/


/**************************************************************************************/
/***************             motor and servo numbers               ********************/
/**************************************************************************************/
#define THROTTLE 0
#define YAW      1
#define ROLL     2
#define PITCH    3

  // 4052 (x1) Read Analog
  //
//  // Aux Controls
//#define AUX0 0  // 0 = x0 = Aux0,
//#define AUX1 2  // 2 = x1 = Aux1,
//#define AUX2 4  // 4 = x2 = Aux2,
//#define AUX3 6  // 6 = x3 = Aux3

// Voltage
#define POST 1  // 1 = y0 = Post,
#define KEY  3  // 3 = y1 = Key
#define V5   5  // 5 = y2 = 5V
#define PRE  7  // 7 = y3 = Pre  
  
/**************************************************************************************/
/***************          date & time configurations               ********************/
/**************************************************************************************/
#define DAY  86400 // 86400000 milliseconds in a  day / 1000
#define HOUR  3600 //  3600000 milliseconds in an hour / 1000
#define MINUTE  60 //    60000 milliseconds in a  minute / 1000
#define SECOND   1 //     1000 milliseconds in a  second / 1000

#define DD(seconds) (   seconds / DAY)                   //number of days
#define HH(seconds) ((  seconds % DAY) / HOUR)           //the remainder from days division divided by hours, this gives the full hours
#define MM(seconds) ((( seconds % DAY) % HOUR) / MINUTE) //and so on...
#define SS(seconds) ((((seconds % DAY) % HOUR) % MINUTE) / SECOND)
 
/**************************************************************************************/
/***************           defaults configurations                 ********************/
/**************************************************************************************/
#define MAINMENU   1   // Main Menu

#define X_MITTER   2   // Transmitter Main Menu
#define MODEL      50  // Model Main Menu
#define SYSTEM     100 // System Menu

#define INITMENU  150 // This is the Init/Startup screen.
#define SPLASH    151
#define FIRSTINIT 152
#define CTLCHECK  192 // Required 

#define FUNCTION  255 // Function indicator


#define BYTE_MAX 255
#define BYTE_MID 128
#define BYTE_MIN 0

#define INT_MIN 0
#define INT_MID 1023/2
#define INT_MAX 1023

/**************************************************************************************/
/***************             Proc specific definitions             ********************/
/**************************************************************************************/
// Common
const PROGMEM char lcd_param_common_set [] = "(Set)";

const PROGMEM char lcd_param_common_Digits []  = "Digits";
const PROGMEM char lcd_param_common_Pos    [] = "12345678";
const PROGMEM char lcd_param_common_Values [] = "Values";


//const dataType variableName[] PROGMEM = {}; // use this form
//const PROGMEM dataType variableName[] = {}; // or this form
//const dataType PROGMEM variableName[] = {}; // not this one


//                                              01234567890123456789 
const PROGMEM char lcd_param_common_Joystick [] = "Joystick";
const PROGMEM char lcd_param_common_Set    []   = "Set?";
//                                              1023 1023 1023 1023 
const PROGMEM char lcd_param_common_MMM  []  = "Read Min. Ctr. Max.";


//
// X000: 
//                                 123456789012 
const PROGMEM char ERR000 []     = "ERR000";

// X102
// lcdSys102
// Vin pre 1.1 & 1.2 ohms                         12345678901234
const PROGMEM char lcd_param_lcdSys102_Vpre [] = "Vin pre ohms";
const PROGMEM char lcd_param_lcdSys102_R11 [] = "R1.1";
const PROGMEM char lcd_param_lcdSys102_R12 [] = "R1.2";

// X104
// lcdSys104
// Vin pst 2.1 & 2.2 ohms                         12345678901234
const PROGMEM char lcd_param_lcdSys104_Vpst [] = "Vin post ohms";
const PROGMEM char lcd_param_lcdSys104_R21 [] = "R2.1";
const PROGMEM char lcd_param_lcdSys104_R22 [] = "R2.2";



// X106
// lcdSys106
//5.0V 3.1 & 3.2 ohms                              12345678901234
const PROGMEM char lcd_param_lcdSys106_V5div [] = "5V divide ohm";
const PROGMEM char lcd_param_lcdSys106_R31 [] = "R3.1";
const PROGMEM char lcd_param_lcdSys106_R32 [] = "R3.2";


// X112
// lcdSys112
// Shunt ohms 
const PROGMEM char lcd_param_lcdSys112_Shunt [] = "Shunt ohm";
const PROGMEM char lcd_param_lcdSys112_Rshnt [] = "Shunt";


// X114
// lcdSys114
// V5.0 Reference
const PROGMEM char lcd_param_lcdSys114_5Vref [] = "5V Reference";
const PROGMEM char lcd_param_lcdSys114_5Vmes [] = "Measure";
const PROGMEM char lcd_param_lcdSys114_5Vsys [] = "System";
const PROGMEM char lcd_param_lcdSys114_v5bit [] = "Volt/Bit";


// X122
// lcdSys122
// Switch buttons
const PROGMEM char lcd_param_lcdSys122_Switch [] = "Switch";
//const PROGMEM char lcd_param_lcdSys122_Desc []   = "0 = Nor : 1 = Rev";



// X124
// lcdSys124    
// Trim buttons
const PROGMEM char lcd_param_lcdSys124_Trim [] = "Trim";



// X126
// lcdSys126    
// Menu buttons
const PROGMEM char lcd_param_lcdSys126_Menu [] = "Menu";



// X135
// lcdSys135
// Joystick range limits                            12345678901234567890
const PROGMEM char lcd_param_lcdSys135_Throttle [] = "Throttle";
const PROGMEM char lcd_param_lcdSys135_YAW      [] = "Yaw";
const PROGMEM char lcd_param_lcdSys135_ROLL     [] = "Roll";
const PROGMEM char lcd_param_lcdSys135_PITCH    [] = "Pitch";

const PROGMEM char lcd_param_common_UD [] = "Move up/down";
const PROGMEM char lcd_param_common_LR [] = "Move left/right";


// X148
// lcdSys148
// System Reset



// ===========================================
// Init / Startup
// ===========================================
    
// X150: 
// lcdInit150
// Starting [click (select) out to 254]
const PROGMEM char lcd_param_lcdInit150_startUp [] = "Start up";

// X151: 
// lcdInit151
// Splash   [no click 'select button' out to 151]
const char  lcd_param_lcdInit151_qBytesWorld[] PROGMEM = "Q-Bytes World";
const char  lcd_param_lcdInit151_deviceInfo [] PROGMEM = {"2.4G Transmitter"};
const char  lcd_param_lcdInit151_versionNum [] PROGMEM = {"v1.1.35"};

// X192: 
// lcdInit192
// Control check
const PROGMEM char  lcd_param_lcdInit192_controlCheck[]       = {"Control check"};
//                                                                12345678901234567890
//                                                                u/d xxx xxx xxxxxxxx
const PROGMEM char  lcd_param_lcdInit192_controlCheck_LRXXX[] = {     "L   R  Switches"};
const PROGMEM char  lcd_param_lcdInit192_controlCheck_UD[]    = {"U/D"};
const PROGMEM char  lcd_param_lcdInit192_controlCheck_LR[]    = {"L/R"};

//const PROGMEM char lcd_param_lcdInit192_volts [] = {"Volts"};





//
// X216: 
//                                   123456789012 
const PROGMEM char ERR216_0 []   = "ERR216-0"; // Attempt to change number, "displayMask[menuCol].getMask()" or "displayMask[menuCol].getVoidPointer()" is NULL.

//
// X255: 
//                                   123456789012 
const PROGMEM char  ERR255 []     = "ERR255";

// ===========================================
// Display
// ===========================================
const PROGMEM char  digits8 []     = " ###";
const PROGMEM char  digits16[]     = " ##,###";
const PROGMEM char  digits32[]     = " #,###,###,###";

const PROGMEM char  joyStickxxxx[] = "####";

const PROGMEM char  volts_xx_xV[]  = " ##.#V";
const PROGMEM char  volts_x_xxxV[] = " #.###V";

const PROGMEM char  volts_0_0xxxxxV[] = " 0.0#####V";

//const PROGMEM char  ohm_xx_xxxO[] = "##,###^"; // K OHMs      //0xF4; //OHM  //  line[6] =  0xF4; //OHM
//const PROGMEM char  ohm_xx_xxxO[] = {'#','#','.','#','#','#',char(244),char(0)};
const PROGMEM char  ohm_xx_xxxO[] = {'#','#','.','#','#','#',char(0xF4),char(0x00)};

//const PROGMEM char  ohm_x_xxxxO[] = "#.####^"; // milla OHMs  //0xF4; //OHM
const PROGMEM char  ohm_x_xxxxO[] = {' ','#','.','#','#','#','#',char(0xF4),char(0x00)};

// ===========================================
// Custom Display
// ===========================================
const PROGMEM char  timer[]        = "##:##:##";
const PROGMEM char  timerDay[]     = "####:##:##:##";


//const PROGMEM char  testLB[]   = "012#4567";
//const PROGMEM char  testOdd[]  = "1234567";
//const PROGMEM char  testEven[] = "12345678";


/**************************************************************************************/
/***************                      Misc                         ********************/
/**************************************************************************************/


#define membersof(x) (sizeof(x) / sizeof(x[0]))

#define NOKEY  0
#define SELECT 1
#define LEFT   2
#define DOWN   3
#define RIGHT  4
#define UP     5

const PROGMEM char  dashes[]   = "====================";
const PROGMEM char  freeram[]  = "Free Ram: ";
const PROGMEM char  eepromSz[] = "EEPROM length: ";
/**************************************************************************************/
/***************               Error Checking Section              ********************/
/**************************************************************************************/


/*
Directive  Meaning
# include include a source file
# define  define a macro
# undef undefine a macro
# if  conditional compilation
# ifdef conditional compilation
# ifndef  conditional compilation
# elif  conditional compilation
# else  conditional compilation
# endif conditional compilation
# line  control error reporting
# error force an error message
# pragma  used for implementation-dependent control
# null directive; no effect

http://publications.gbdirect.co.uk/c_book/chapter7/directives.html
*/

//#if GPS && !defined(NMEA) && !defined(UBLOX)
//  #error "when using GPS you must specify the protocol NMEA, UBLOX..."
//#endif

#endif /* dev_h */


