/*
  Display.h - Test library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include core Wiring API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <avr/pgmspace.h>

// include this library's description file
#include "Def.h"
#include "Display.h"


// include description files for other libraries used (if any)
//#include <limits.h>
// https://github.com/esp8266/Arduino/blob/master/tools/sdk/libc/xtensa-lx106-elf/include/limits.h

#define DAY  86400 // 86400000 milliseconds in a  day
#define HOUR  3600 //  3600000 milliseconds in an hour
#define MINUTE  60 //    60000 milliseconds in a  minute
#define SECOND   1 //     1000 milliseconds in a  second
 
#define DD(seconds) (   seconds / DAY)                   //number of days
#define HH(seconds) ((  seconds % DAY) / HOUR)           //the remainder from days division divided by hours, this gives the full hours
#define MM(seconds) ((( seconds % DAY) % HOUR) / MINUTE) //and so on...
#define SS(seconds) ((((seconds % DAY) % HOUR) % MINUTE) / SECOND)

// ===========================================
// Macros
// ===========================================

// 8 bit intiger -------------------------------------------
// Unsigned+255
char u8Digit100        (uint8_t v) {return '0' + v / 100;} //   - (v/1000)        * 10;}
char u8Digit10         (uint8_t v) {return '0' + v / 10         - (v/100)         * 10;}
char u8Digit1          (uint8_t v) {return '0' + v / 1          - (v/10)          * 10;} 

// Signed  -128/+127
char s8Digit100        ( int8_t v) {return '0' + v / 100;}  //  - (v/1000)        * 10;}
char s8Digit10         ( int8_t v) {return '0' + v / 10         - (v/100)         * 10;}
char s8Digit1          ( int8_t v) {return '0' + v / 1          - (v/10)          * 10;} 

// 16 bit intiger -------------------------------------------
// Unsigned +65535
char u16Digit10000      (uint16_t v) {return '0' + v / 10000;} // - (v/100000)      * 10;}
char u16Digit1000       (uint16_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
char u16Digit100        (uint16_t v) {return '0' + v / 100        - (v/1000)        * 10;}
char u16Digit10         (uint16_t v) {return '0' + v / 10         - (v/100)         * 10;}
char u16Digit1          (uint16_t v) {return '0' + v / 1          - (v/10)          * 10;} 

// Signed -32768/+32767
char s16Digit10000      ( int16_t v) {return '0' + v / 10000;} // - (v/100000)      * 10;}
char s16Digit1000       ( int16_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
char s16Digit100        ( int16_t v) {return '0' + v / 100        - (v/1000)        * 10;}
char s16Digit10         ( int16_t v) {return '0' + v / 10         - (v/100)         * 10;}
char s16Digit1          ( int16_t v) {return '0' + v / 1          - (v/10)          * 10;} 

// 32 bit intiger -------------------------------------------
// Unsigned  4294967294
char u32Digit1000000000 (uint32_t v) {return '0' + v / 1000000000;}// - (v/10000000000) * 10;}
char u32Digit100000000  (uint32_t v) {return '0' + v / 100000000  - (v/1000000000)  * 10;}
char u32Digit10000000   (uint32_t v) {return '0' + v / 10000000   - (v/100000000)   * 10;}
char u32Digit1000000    (uint32_t v) {return '0' + v / 1000000    - (v/10000000)    * 10;}
char u32Digit100000     (uint32_t v) {return '0' + v / 100000     - (v/1000000)     * 10;}
char u32Digit10000      (uint32_t v) {return '0' + v / 10000      - (v/100000)      * 10;}
char u32Digit1000       (uint32_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
char u32Digit100        (uint32_t v) {return '0' + v / 100        - (v/1000)        * 10;}
char u32Digit10         (uint32_t v) {return '0' + v / 10         - (v/100)         * 10;}
char u32Digit1          (uint32_t v) {return '0' + v / 1          - (v/10)          * 10;} 

// Signed   -2147483648/+2147483647
char s32Digit1000000000 ( int32_t v) {return '0' + v / 1000000000;}// - (v/10000000000) * 10;}
char s32Digit100000000  ( int32_t v) {return '0' + v / 100000000  - (v/1000000000)  * 10;}
char s32Digit10000000   ( int32_t v) {return '0' + v / 10000000   - (v/100000000)   * 10;}
char s32Digit1000000    ( int32_t v) {return '0' + v / 1000000    - (v/10000000)    * 10;}
char s32Digit100000     ( int32_t v) {return '0' + v / 100000     - (v/1000000)     * 10;}
char s32Digit10000      ( int32_t v) {return '0' + v / 10000      - (v/100000)      * 10;}
char s32Digit1000       ( int32_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
char s32Digit100        ( int32_t v) {return '0' + v / 100        - (v/1000)        * 10;}
char s32Digit10         ( int32_t v) {return '0' + v / 10         - (v/100)         * 10;}
char s32Digit1          ( int32_t v) {return '0' + v / 1          - (v/10)          * 10;} 


// ===========================================
// Constructor
// Function that handles the creation and setup of instances
// ===========================================
Display::Display(){
  // initialize this instance's variables


  // do whatever is required to initialize the library

}

// ===========================================
// PROGMEM
// ===========================================
PROGMEM const char  digits8 []     = " ---";
PROGMEM const char  digits16[]     = " --,---";
PROGMEM const char  digits32[]     = " -,---,---,---";

PROGMEM const char  timer[]        = "--:--:--";
PROGMEM const char  timerDay[]     = "----:--:--:--";

PROGMEM const char  volts_xx_xV[]  = " --.-V";
PROGMEM const char  volts_x_xxxV[] = " -.---V";

PROGMEM const char  volts_0_00xxxxV[] = "0.0-----V";

PROGMEM const char  ohm_x_xxxx[] = "-.----^";

static char line [15];
static char buffer [20];
  
// ===========================================
// Misc Methods
// ===========================================

// -------------------------------------------
//void setSign(type T number){
//  if (number < 0 ) { // Can't be negative.
//    number = -number;
//    line[0] = '-';
//  } else {
//    number = number;
//    line[0] = ' ';
//  }  
//}

// -------------------------------------------
// https://forum.arduino.cc/index.php?topic=439117.0
// -------------------------------------------
template <typename T> T setSign (T number) 
  {
  if (number < 0){ // Can't be negative.
    number = -number;
    line[0] = '-';
  }
//  else{
//    line[0]='p';
//  }
  return number;
  }  // end of setSign
  
// -------------------------------------------
//// generic minimum
//template <typename T> T minimum (T a, T b) 
//  {
//  if (a < b)
//    return a;
//  return b;
//  }  // end of minimum

// generic setSign

// -------------------------------------------
//#define MACRO(num, str) {\
//            printf("%d", num);\
//            printf(" is");\
//            printf(" %s number", str);\
//            printf("\n");\
//           }

// -------------------------------------------
//  if (half){
//    if (number > SHRT_MAX){
//        number = SHRT_MAX;
//    }
//  }

// -------------------------------------------
//char *itoa(int n)
//  {
//  static char retbuf[25];
//  sprintf(retbuf, "%d", n);
//  return retbuf;
//  }


// ===========================================
// Digits
// ===========================================

char * Display::outputDigitsU8(uint8_t number){
// Number can be between 255
//static char line[5] = "0123"; // Digit possition (+1 for terminator /0.
//static char line[5] = " ---";

  strcpy_P(line, digits8);
  
  line[1] =  u8Digit100   (number);
  line[2] =  u8Digit10    (number);
  line[3] =  u8Digit1     (number);

  return line;
}

char * Display::outputDigitsS8(int8_t number){
// Number can be between -128 and 127
//static char line[5] = "0123"; // Digit possition (+1 for terminator /0.
//static char line[5] = " ---";

  strcpy_P(line, digits8);

  number = setSign(number);
  
  line[1] =  s8Digit100   (number);
  line[2] =  s8Digit10    (number);
  line[3] =  s8Digit1     (number);

  return line;
}

char * Display::outputDigitsU16(uint16_t number){
// Number can be between 0 and 65,535
//static char line[8] = "+65,535"; // Max number
//static char line[8] = "012,456"; // Digit possition (+1 for terminator /0.
//static char line[8] = " --,---";

  strcpy_P(line, digits16);
  
  line[1] =  u16Digit10000 (number);
  line[2] =  u16Digit1000  (number);
  line[4] =  u16Digit100   (number);
  line[5] =  u16Digit10    (number);
  line[6] =  u16Digit1     (number);

  return line;
}

char * Display::outputDigitsS16(int16_t number){

// Number can be between -32,768 and 32,767
//static char line[8] = "+32,768"; // Max number
//static char line[8] = "-32,767"; // Half number
//static char line[8] = "012,456"; // Digit possition (+1 for /0 terminator).
//static char line[8] = " --,---";

  strcpy_P(line, digits16);

  number = setSign(number);
  
  line[1] =  s16Digit10000 (number);
  line[2] =  s16Digit1000  (number);
  line[4] =  s16Digit100   (number);
  line[5] =  s16Digit10    (number);
  line[6] =  s16Digit1     (number);

  return line;
}

char * Display::outputDigitsU32(uint32_t number){
// Number can be between 0 and 65,535
//static char line[15] = "+4,294,967,294"; // Max number
//static char line[15] = "01234567890123"; // Digit possition (+1 for terminator /0.
//static char line[15] = " -,---,---,---";

  strcpy_P(line, digits32);

  line[1]  =  u32Digit1000000000 (number);
  //,
  line[3]  =  u32Digit100000000  (number);
  line[4]  =  u32Digit10000000   (number);
  line[5]  =  u32Digit1000000    (number);
  //,
  line[7]  =  u32Digit100000     (number);
  line[8]  =  u32Digit10000      (number);
  line[9]  =  u32Digit1000       (number);
  //,
  line[11] =  u32Digit100        (number);
  line[12] =  u32Digit10         (number);
  line[13] =  u32Digit1          (number);

  return line;
}

char * Display::outputDigitsS32( int32_t number){
// Number can be between 0 and 65,535
//static char line[15] = "+4,294,967,294"; // Max number
//static char line[15] = "01234567890123"; // Digit possition (+1 for terminator /0.
//static char line[15] = " -,---,---,---";

  strcpy_P(line, digits32);

  number = setSign(number);
    
  line[1]  =  s32Digit1000000000 (number);
  //,
  line[3]  =  s32Digit100000000  (number);
  line[4]  =  s32Digit10000000   (number);
  line[5]  =  s32Digit1000000    (number);
  //,
  line[7]  =  s32Digit100000     (number);
  line[8]  =  s32Digit10000      (number);
  line[9]  =  s32Digit1000       (number);
  //,
  line[11] =  s32Digit100        (number);
  line[12] =  s32Digit10         (number);
  line[13] =  s32Digit1          (number);

  return line;
}

// ===========================================
// Time Functions
// ===========================================
char * Display::outputOnTime(uint16_t seconds) {
  uint8_t h, m, s;
  h = HH(seconds);
  m = MM(seconds);
  s = SS(seconds);

  //                  Max: 18:12:15 (uint16_t) 65535
  //                       01234567
  //static char line[9] = "--:--:--";

  strcpy_P(line, timer);
  
  line[0] = u16Digit10 (h);
  line[1] = u16Digit1  (h);
  line[3] = u8Digit10  (m);
  line[4] = u8Digit1   (m);
  line[6] = u8Digit10  (s);
  line[7] = u8Digit1   (s);

  if (line[1] == '0' && line[1] == '0'){ // Should not get here, maybe someday?
    line[0]=' ';
    line[1]=' ';
    line[2]=' ';
  }
  
  return line;
}

char * Display::outputServiceTime(uint32_t seconds) {
  uint16_t dd;
  uint8_t hh, mm, ss;

  dd = DD(seconds);
  hh = HH(seconds);
  mm = MM(seconds);
  ss = SS(seconds);

  //            actual max:49710:06:28:14
  //            display max 9701:06:28:14
  //                        0123456789012
  //static char line[14] = "dddd:hh:mm:ss";

  strcpy_P(line, timerDay);
  
  line[ 0] = u16Digit1000 (dd);
  line[ 1] = u16Digit100  (dd);
  line[ 2] = u16Digit10   (dd);
  line[ 3] = u16Digit1    (dd);
  // :
  line[ 5] = u8Digit10    (hh);
  line[ 6] = u8Digit1     (hh);
  // :
  line[ 8] = u8Digit10    (mm);
  line[ 9] = u8Digit1     (mm);
  // :
  line[11] = u8Digit10    (ss);
  line[12] = u8Digit1     (ss);
  
  return line;
}

// ===========================================
// Volt Functions
// ===========================================
char * Display::output_xx_xV(uint16_t volts) {

// volts can be between -32,768 and 32,767 (12300 = 12.3v)
//static char line[5] = "012345"; // Digit possition (+1 for terminator /0.
//static char line[5] = " --.-V"

  strcpy_P(line, volts_xx_xV);

  volts = setSign(volts);
    
  line[1] =  u16Digit10000 (volts);
  line[2] =  u16Digit1000  (volts);
  line[4] =  u16Digit100   (volts);

  if (line[1] == '0'){ // Should not get here, maybe someday?
    line[1]=' ';
  }
  return line;
}

char * Display::output_x_xxxV(uint16_t volts) {

// volts can be between -32,768 and 32,767 (5246 = 5.246v)
//static char line[5] = "0123456"; // Digit possition (+1 for terminator /0.
//static char line[5] = " -.---V;

  strcpy_P(line, volts_x_xxxV);

  volts = setSign(volts);
    
  line[1] =  u16Digit1000  (volts);
  // .
  line[3] =  u16Digit100   (volts);
  line[4] =  u16Digit10    (volts);
  line[5] =  u16Digit1     (volts);
  
  return line;
}


char * Display::output_voltPerBit(uint16_t volts) {

// volts can be between  65,535 (05246 = 0.0005246v)
//static char line[5] = "01234567890"; // Digit possition (+1 for terminator /0.
//static char line[5] = "0.00-----V;

  strcpy_P(line, volts_0_00xxxxV);

  line[0] = '0';     
  // .
  line[2] = '0';     
  line[3] = u16Digit10000 (volts); 
  line[4] = u16Digit1000  (volts);
  line[5] = u16Digit100   (volts);
  line[6] = u16Digit10    (volts);
  line[7] = u16Digit1     (volts);
//  line[9] = 0xF4; OHM
  
  return line;
}



// Usage: concatBytesPGM(lcd_param_common_set,lcd_param_lcdInit252_5V);
char * Display::concatBytesPGM(const char* pgm1, const char* pgm2) {
  memset(buffer, 0x00, sizeof(buffer)); // for automatically-allocated a clean arrays
  int c = 0;

  for (int k = 0; k < strlen_P(pgm1); k++){
    buffer[c++]=pgm_read_byte_near(pgm1 + k);
  }
  
  buffer[c++]=' ';
  
  for (int k = 0; k < strlen_P(pgm2); k++){
    buffer[c++]=pgm_read_byte_near(pgm2 + k);
  }
  
  buffer[c]=0;
  
  buffer[sizeof(buffer)] = 0;          // end with a null terminator.

  if (false){
    Serial.println(buffer);
  }
    
  return buffer;
}

// Usage: concatBytesPGMSTR(qBytesWorld, versionNum);  
char * Display::concatBytesPGMSTR(const char* pgmstr1, const char* pgmstr2){
//  memset(buffer, 0x00, sizeof(buffer)); // for automatically-allocated arrays (clear the array);
    memcpy(buffer, PGMSTR(pgmstr1), strlen_P(pgmstr1)+1);
    buffer[strlen_P(pgmstr1)] = ' ';
    memcpy(buffer+strlen_P(pgmstr1)+1, PGMSTR(pgmstr2), strlen_P(pgmstr2)+1);

    if (false){
      Serial.println(buffer);
    }
  return buffer;    
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library



/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */


//===============================================================================
//int lcdInt(int n, String format){
//char charBuf[10];
//  format.toCharArray(charBuf,10); 
//  int m = sprintf (buffer, charBuf, n);
//  lcd.print(buffer);
//  return m;
//}
//int lcdInt(int n, String format){
//  int m = sprintf (buffer, "%6d", n);
//  lcd.print(buffer);
//  return m;
//}
//int lcdInt(int n, const char format){
//  //    lcd.print(PGMSTR(qBytesWorld));
//  int m = sprintf (buffer, format, n);
//  lcd.print(buffer);
//  return m;
//}
//////// ===========================================
//////// LCD Print DDDDDD
//////// ===========================================
//int lcdUnLong6D(unsigned long n){
//  Serial.println(n);
//  //int m = sprintf (buffer, "%06d", n);
//  int m = sprintf (buffer, "%06lu", n);
//  lcd.print(buffer);
//  return m;
//}
//
////char digit10000   (uint16_t v) {return '0' + v / 10000                   ;}
////char digit1000    (uint16_t v) {return '0' + v / 1000  - (v/10000) * 10;}
////char digit100     (uint16_t v) {return '0' + v / 100   - (v/1000)  * 10;}
////char digit10      (uint16_t v) {return '0' + v / 10    - (v/100)   * 10;}
////char digit1       (uint16_t v) {return '0' + v / 1     - (v/10)    * 10;}
//
////void lcdprint_uint32(uint32_t v) {
//void lcdprint_ulong(unsigned long v) {
//  static char line[14] = "-,---,---,---";
//  //                      0 2 4 6 8   12
//  line[0]  = '0' + v  / 1000000000;
//  line[2]  = '0' + v  / 100000000 - (v/1000000000) * 10;
//  line[3]  = '0' + v  / 10000000  - (v/100000000)  * 10;
//  line[4]  = '0' + v  / 1000000   - (v/10000000)   * 10;
//  line[6]  = '0' + v  / 100000    - (v/1000000)    * 10;
//  line[7]  = '0' + v  / 10000     - (v/100000)     * 10;
//  line[8]  = '0' + v  / 1000      - (v/10000)      * 10;
//  line[10] = '0' + v  / 100       - (v/1000)       * 10;
//  line[11] = '0' + v  / 10        - (v/100)        * 10;
//  line[12] = '0' + v  / 1         - (v/10)         * 10;
//
//  lcd.print(line);  
//}
////void lcdprint_uint32(uint32_t v) {
//void lcdprint_uint(unsigned int v) {
//  static char line[14] = "--,---";
//  //                      01 345
//
//  line[0] = '0' + v / 10000;
//  line[1] = '0' + v / 1000      - (v/10000)      * 10;
//  line[3] = '0' + v / 100       - (v/1000)       * 10;
//  line[4] = '0' + v / 10        - (v/100)        * 10;
//  line[5] = '0' + v             - (v/10)         * 10;
//
//  lcd.print(line);  
//}
//
//////// ===========================================
//////// LCD Print NNN.DDD
//////// ===========================================
////int printInt(int n, String format){
////
//
////  char buffer[10];         //the ASCII of the integer will be stored in this char array
////  itoa((int)changeMe,buffer,10); //(integer, yourBuffer, base)
//  
//////char dateFormat[] = "%02d:%02d:%02d:%02d";
//////    sprintf(buffer, dateFormat[3], days, hours, minutes, seconds); ///< This has 4 2-digit integers with leading zeros, separated by ":" . The list of parameters, hour, min, sec, provides the numbers the sprintf prints out with.
//////    lcd.print(buffer);    
////    //Serial.println(buffer); ///< You will get something like"01:13:02:09" 
////    
////char format[] = "ddddd";
////      
//////  char c[10];        // long enough to hold complete integer string
//////  char charBuf[20];
////  format.toCharArray(buffer,10);
////  int m = sprintf(c, buffer, n);    // build integer string using C integer formatters  (m is length, and not used in this code)
////  Serial.print(c);
////  return m;
////}
//
////// ===========================================
////// LCD Print NNN.DDD
////// ===========================================
//void lcdDouble63(double dbl) {
//  char *r = dtostrf(dbl, 6, 3, buffer);
////  lcd.print(buffer);
//  lcd.print(r);
//  lcd.print("V");
////  lcd.print(dtostrf(v5_System, 6, 3, buffer));
////  lcd.print("V");
//}
