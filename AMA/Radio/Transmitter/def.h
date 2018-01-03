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
//#define DEBUG_Volts



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
//#define AUX0 0  // x0 = Aux0,
//#define AUX1 1  // x1 = Aux1,
//#define AUX2 2  // x2 = Aux2,
//#define AUX3 3  // x3 = Aux3

// Voltage
#define POST 0  // y0 = Post,
#define KEY  1  // y1 = Key
#define V5   2  // y2 = 5V
#define PRE  3  // y3 = Pre   
  
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

#define MAINMENU   0   // Main Menu

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
/*
  const dataType variableName[] PROGMEM = {}; // use this form
  const PROGMEM dataType variableName[] = {}; // or this form
  const dataType PROGMEM variableName[] = {}; // not this one
*/
/**************************************************************************************/

// Common
const PROGMEM char lcd_param_common_set [] = "(Set)";

const PROGMEM char ERR [] = "Err:";
#define ERR200 200  // Err: setMenu : Don't use for FUNCTIONS"
#define ERR216 216  // Attempt to change number, "displayMask[menuCol].getMask()" or "displayMask[menuCol].getVoidPointer()" is NULL.
#define ERR239 239/* need to complete this....(then delete?)*/
#define ERR251 251  // setMenu menuOptions max size
#define ERR252 252  // setMenu Error : Don't use for FUNCTIONS
#define ERR253 253  // menuDisplay not found Error
#define ERR254 254  // funcDisplay not found Error
#define ERR255 255  // Attempt to use 255 in menu, not valid

#define ERR_DISPLAY 199 // 

//                                              01234567890123456789 
const PROGMEM char lcd_param_common_Joystick [] = "Joystick";
const PROGMEM char lcd_param_common_Set    []   = "Set?";
//                                              1023 1023 1023 1023 
const PROGMEM char lcd_param_common_MCM  []  = "Read Min. Ctr. Max.";


//
// X000: 
//                                 123456789012 

const PROGMEM char lcd_param_lcdSys000_MainMenu []     = "Main Menu";


//
// X001
// lcdMain001
//                                 123456789012 
const PROGMEM char lcd_param_lcdSys001_Xmitter [] = "Transmitter";
const PROGMEM char lcd_param_lcdSys001_Models  [] = "Model";
const PROGMEM char lcd_param_lcdSys001_System  [] = "System";


// X100
// lcdSys100
//                                                     12345678901234
const PROGMEM char lcd_param_lcdSys100_OhmsVolts [] = "OHMs & Volts";
const PROGMEM char lcd_param_lcdSys100_CntlRange [] = "Controls";
const PROGMEM char lcd_param_lcdSys100_FactReset [] = "Factory Reset";


// X101
// lcdSys101
// Vin pre 1.1 & 1.2 OHMs                          12345678901234
const PROGMEM char lcd_param_lcdSys101_Ohms  [] = "OHMs";
const PROGMEM char lcd_param_lcdSys101_Volts [] = "Volts";

// x102
// lcdSys102
//const PROGMEM char lcd_param_lcdSys102_Pre   [] = "Pre";
//const PROGMEM char lcd_param_lcdSys102_Post  [] = "Post";
//const PROGMEM char lcd_param_lcdSys102_V5Ref [] = "5.1v Ref";

    
// X104
// lcdSys104
// Vin pre 1.1 & 1.2 OHMs                         12345678901234
const PROGMEM char lcd_param_lcdSys104_Vpre [] = "Vin pre OHMs";
const PROGMEM char lcd_param_lcdSys104_R11 [] = "R1.1";
const PROGMEM char lcd_param_lcdSys104_R12 [] = "R1.2";

// X105
// lcdSys105
// Vin pst 2.1 & 2.2 OHMs                         12345678901234
const PROGMEM char lcd_param_lcdSys105_Vpst [] = "Vin post OHMs";
const PROGMEM char lcd_param_lcdSys105_R21 [] = "R2.1";
const PROGMEM char lcd_param_lcdSys105_R22 [] = "R2.2";

// X106
// lcdSys106
//5.0V 3.1 & 3.2 OHMs                              1234567890123456789
const PROGMEM char lcd_param_lcdSys106_V5div [] = "5.0V Reg. OHMs";
const PROGMEM char lcd_param_lcdSys106_R31 [] = "R3.1";
const PROGMEM char lcd_param_lcdSys106_R32 [] = "R3.2";

// X112
// lcdSys112
// Shunt OHMs 
const PROGMEM char lcd_param_lcdSys112_Shunt [] = "Shunt OHM";
const PROGMEM char lcd_param_lcdSys112_Rshnt [] = "Shunt";

// X114
// lcdSys114
// V5.0 Reference                                  1234567890123456789
const PROGMEM char lcd_param_lcdSys114_5Vref [] = "5.1V Reference";
const PROGMEM char lcd_param_lcdSys114_5Vmes [] = "Measure";
const PROGMEM char lcd_param_lcdSys114_5Vsys [] = "System";
const PROGMEM char lcd_param_lcdSys114_v5bit [] = "Volt/Bit";

// X116
// lcdSys116
// Pre, Post & V5 Regulator                        1234567890123456789
const PROGMEM char lcd_param_lcdSys116_Volts [] = "Voltages";
const PROGMEM char lcd_param_lcdSys116_Pre [] = "Pre";
const PROGMEM char lcd_param_lcdSys116_Pst [] = "Post";
const PROGMEM char lcd_param_lcdSys116_V5R [] = "5V Reg";

// X140
// lcdSys140
// AUX                            1234567890123456789
const PROGMEM char lcd_param_lcdSys140_AUX [] = "Aux";
const PROGMEM char lcd_param_lcdSys140_AUXc []= "Aux: ";


// X122
// lcdSys122
// Switch buttons
const PROGMEM char lcd_param_lcdSys122_Switch [] = "Switch";
const PROGMEM char lcd_param_lcdSys122_Pos    [] = "12345678";


// X124
// lcdSys124    
// Trim buttons
const PROGMEM char lcd_param_lcdSys124_Trim [] = "Trim";

// X126
// lcdSys126    
// Menu buttons
const PROGMEM char lcd_param_lcdSys126_Menu [] = "Button";


// X130
// lcdSys130
// Joystick range limits                                 12345678901234567890
const PROGMEM char lcd_param_lcdSys134_Cntl        [] = "Controls";
const PROGMEM char lcd_param_lcdSys134_LeftCtlRng  [] = "Left Cntl Rng";
const PROGMEM char lcd_param_lcdSys134_RightCtlRng [] = "Right Cntl Rng";
const PROGMEM char lcd_param_lcdSys134_SwitchesButtons    [] = "SWs & Btns";


// X134
// lcdSys134
// Joystick range limits                             12345678901234567890
const PROGMEM char lcd_param_lcdSys134_Throttle [] = "Throttle";
const PROGMEM char lcd_param_lcdSys134_YAW      [] = "Yaw";
const PROGMEM char lcd_param_lcdSys134_ROLL     [] = "Roll";
const PROGMEM char lcd_param_lcdSys134_PITCH    [] = "Pitch";

const PROGMEM char lcd_param_common_UD [] = "Move up/down";
const PROGMEM char lcd_param_common_LR [] = "Move left/right";


// X149
// lcdSys149
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
const char  lcd_param_lcdInit151_versionNum [] PROGMEM = {"v1.1.39"};

// X192: 
// lcdInit192
// Control check
const PROGMEM char  lcd_param_lcdInit192_controlHome[]      = {"Home All"};


// x199


//
// X216: 
//                                   123456789012 

//
// X255: 
//                                   123456789012 



// ===========================================
// Display
// ===========================================
const PROGMEM char  digits8 []     = " ###";
const PROGMEM char  digits16[]     = " ##,###";
const PROGMEM char  digits32[]     = " #,###,###,###";

const PROGMEM char  joyStickxxxx[] = "####";

const PROGMEM char  volts_xx_xxV[]  = " ##.##V";
const PROGMEM char  volts_x_xxxV[] = " #.###V";

const PROGMEM char  volts_0_0xxxxxV[] = " 0.0#####V";

//const PROGMEM char  ohm_xx_xxxO[] = "##,###^"; // K OHMs      //0xF4; //OHM  //  line[6] =  0xF4; //OHM
//const PROGMEM char  ohm_xx_xxxO[] = {'#','#','.','#','#','#',char(244),char(0)};
const PROGMEM char  ohm_xx_xxxO[] = {'#','#','.','#','#','#','K',char(0xF4),char(0x00)};

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


