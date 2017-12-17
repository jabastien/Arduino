/*
  Display.h - 

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
#include "Display.h"


// ===========================================
// Data
// ===========================================
char line [20]; // LCD width
 
// ===========================================
// Constructor
// Function that handles the creation and setup of instances
// ===========================================
Display::Display(){
  // initialize this instance's variables

  // do whatever is required to initialize the library
}

// -------------------------------------------
// https://forum.arduino.cc/index.php?topic=439117.0
// -------------------------------------------
//void setSign(type T number){              // No return value
template <typename T> T setSign (T number){ // Return value of 'T'
  if (number < 0){ // Can't be negative.
    number *= -1;
    line[0] = '-';
  }
  else{
    line[0] = ' ';
  }
  return number;
}  // end of setSign

// ===========================================
// Digits
// ===========================================

// -------------------------------------------
// Number can be between 0 and 255
char * Display::outputDigitsU8(uint8_t number, const char * pattern){

  Display digits;
  strcpy_P(line, pattern );

  number = setSign(number);

  int digit = 0;

  for (int pos = 0; line[pos] != '\0'; pos++)
    {
      if (line[pos] == '#'){
        
        // get member function pointer from array
        Display::u8Digit f = digits.Display::u8Digit_Array [digit];
        
        // call the function
        line[pos]=( (digits.*f) (number));
        
        digit++;   
      }
    }  // end of for loop
  return line;  
}

// -------------------------------------------
// Number can be between -128 and 127
char * Display::outputDigitsS8( int8_t number, const char * pattern){

  Display digits;
  strcpy_P(line, pattern );

  number = setSign(number);

  int digit = 0;

  for (int pos = 0; line[pos] != '\0'; pos++)
    {
      if (line[pos] == '#'){
        
        // get member function pointer from array
        Display::s8Digit f = digits.Display::s8Digit_Array [digit];
        
        // call the function
        line[pos]=( (digits.*f) (number));
        
        digit++;   
      }
    }  // end of for loop
  return line;  
}

// -------------------------------------------
// int store a 2 byte value. Instead of storing negative numbers however they only store positive values
// Yielding a useful range of 0 to 65,535 (2^16) - 1).
char * Display::outputDigitsU16(uint16_t number, const char * pattern){
  return Display::outputDigitsU16( number, pattern, 0);
}

char * Display::outputDigitsU16(uint16_t number, const char * pattern, uint8_t startDigit){

  Display digits;
  strcpy_P(line, pattern );

//  number = setSign(number);

  int digit = startDigit;

  for (int pos = 0; line[pos] != '\0'; pos++)
    {
      if (line[pos] == '#'){
        
        // get member function pointer from array
        Display::u16Digit f = digits.Display::u16Digit_Array [digit];
        
        // call the function
        line[pos]=( (digits.*f) (number));
        digit++;   
      }
    }  // end of for loop
    
  return line;  
}

// -------------------------------------------
// An int stores a 16-bit (2-byte) value. This yields a range of -32,768 to 32,767
char * Display::outputDigitsS16( int16_t number, const char * pattern){
  return Display::outputDigitsS16( number, pattern, 0);
}

char * Display::outputDigitsS16( int16_t number, const char * pattern, uint8_t startDigit){

  Display digits;
  strcpy_P(line, pattern );

  number = setSign(number);

  int digit = startDigit;

  for (int pos = 0; line[pos] != '\0'; pos++)
    {
      if (line[pos] == '#'){
        
        // get member function pointer from array
        Display::s16Digit f = digits.Display::s16Digit_Array [digit];
        
        // call the function
        line[pos]=( (digits.*f) (number));
        
        digit++;   
      }
    }  // end of for loop
  return line;  
}

// -------------------------------------------
// Unsigned long variables are extended size variables for number storage, and store 32 bits (4 bytes). 
// Unlike standard longs unsigned longs won’t store negative numbers, making their range from 0 to 4,294,967,295 (2^32 - 1)
char * Display::outputDigitsU32(uint32_t number, const char * pattern){
 return Display::outputDigitsU32( number, pattern, 0);  
}

char * Display::outputDigitsU32(uint32_t number, const char * pattern, uint8_t startDigit){

  Display digits;
  strcpy_P(line, pattern );

  number = setSign(number);

  int digit = startDigit;

  for (int pos = 0; line[pos] != '\0'; pos++)
    {
      if (line[pos] == '#'){
        
        // get member function pointer from array
        Display::u32Digit f = digits.Display::u32Digit_Array [digit];
        
        // call the function
        line[pos]=( (digits.*f) (number));
        digit++;   
      }
    }  // end of for loop
  return line;  
}

// -------------------------------------------
// Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647. 
char * Display::outputDigitsS32( int32_t number, const char * pattern){
 return Display::outputDigitsS32( number, pattern, 0);  
}

char * Display::outputDigitsS32( int32_t number, const char * pattern, uint8_t startDigit){

  Display digits;
  strcpy_P(line, pattern );

  number = setSign(number);

  int digit = startDigit;

  for (int pos = 0; line[pos] != '\0'; pos++)
    {
      if (line[pos] == '#'){
        
        // get member function pointer from array
        Display::s32Digit f = digits.Display::s32Digit_Array [digit];
        
        // call the function
        line[pos]=( (digits.*f) (number));
        digit++;   
      }
    }  // end of for loop
  return line;  
}


// -------------------------------------------

/*

//char * Display::outputDigitsU32(uint32_t number){
//// Number can be between 0 and 65,535
////static char line[15] = "+4,294,967,294"; // Max number
////static char line[15] = "01234567890123"; // Digit possition (+1 for terminator /0.
////static char line[15] = " -,---,---,---";
//
//  strcpy_P(line, digits32);
//
//  line[1]  =  u32Digit1000000000 (number);
//  //,
//  line[3]  =  u32Digit100000000  (number);
//  line[4]  =  u32Digit10000000   (number);
//  line[5]  =  u32Digit1000000    (number);
//  //,
//  line[7]  =  u32Digit100000     (number);
//  line[8]  =  u32Digit10000      (number);
//  line[9]  =  u32Digit1000       (number);
//  //,
//  line[11] =  u32Digit100        (number);
//  line[12] =  u32Digit10         (number);
//  line[13] =  u32Digit1          (number);
//
//  line[14] =  '\0';
//  
//  return line;
//}
//
//char * Display::outputDigitsS32( int32_t number){
//// Number can be between 0 and 65,535
////static char line[15] = "+4,294,967,294"; // Max number
////static char line[15] = "01234567890123"; // Digit possition (+1 for terminator /0.
////static char line[15] = " -,---,---,---";
//
//  strcpy_P(line, digits32);
//
//  number = setSign(number);
//    
//  line[1]  =  s32Digit1000000000 (number);
//  //,
//  line[3]  =  s32Digit100000000  (number);
//  line[4]  =  s32Digit10000000   (number);
//  line[5]  =  s32Digit1000000    (number);
//  //,
//  line[7]  =  s32Digit100000     (number);
//  line[8]  =  s32Digit10000      (number);
//  line[9]  =  s32Digit1000       (number);
//  //,
//  line[11] =  s32Digit100        (number);
//  line[12] =  s32Digit10         (number);
//  line[13] =  s32Digit1          (number);
//
//  line[14] =  '\0';
//
//  return line;
//}

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

  line[8] =  '\0';
  
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

  line[14] =  '\0';

  return line;
}


// ===========================================
// Concatenate PGM string/char
// ===========================================
// Usage: concatBytesPGM(lcd_param_common_set,lcd_param_lcdInit252_5V);
char * Display::concatBytesPGM(const char* pgm1, const char* pgm2) {
  memset(line, 0x00, sizeof(line)); // for automatically-allocated a clean arrays
  int c = 0;

  for (int k = 0; k < strlen_P(pgm1); k++){
    line[c++]=pgm_read_byte_near(pgm1 + k);
  }
  
  line[c++]=' ';
  
  for (int k = 0; k < strlen_P(pgm2); k++){
    line[c++]=pgm_read_byte_near(pgm2 + k);
  }
  
  line[c]=0;  
  line[sizeof(line)] = 0;          // end with a null terminator.

  if (false){
    Serial.println(line);
  }
    
  return line;
}

// Usage: concatBytesPGMSTR(qBytesWorld, versionNum);  
char * Display::concatBytesPGMSTR(const char* pgmstr1, const char* pgmstr2){
//  memset(line, 0x00, sizeof(line)); // for automatically-allocated arrays (clear the array);
    memcpy(line, PGMSTR(pgmstr1), strlen_P(pgmstr1)+1);
    line[strlen_P(pgmstr1)] = ' ';
    memcpy(line+strlen_P(pgmstr1)+1, PGMSTR(pgmstr2), strlen_P(pgmstr2)+1);

    if (false){
      Serial.println(line);
    }
  return line;    
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


// require ::: stdlib.h
//char buffer[20]; //  Hold The Convert Data (width of the LCD)
//itoa(changeMe,buffer,10); //(integer, yourBuffer, base)   
 
// -------------------------------------------
//char *itoa(int n)
//  {
//  static char retbuf[25];
//  sprintf(retbuf, "%d", n);
//  return retbuf;
//  }

//===============================================================================

  // #include<stdlib.h>
  //  dtostrf(FLOAT,WIDTH,PRECSISION,BUFFER);

//  char *r = dtostrf(changeMe, 8, 2, buffer);
//  if (true){
//    Serial.print  (buffer);
//    Serial.print  (" r:");
//    Serial.print  (r);
//    Serial.println(":");
//  }

//==============================================================================
//int lcdInt(int n, String format){
//char charBuf[10];
//  format.toCharArray(charBuf,10); 
//  int m = sprintf (line, charBuf, n);
//  lcd.print(line);
//  return m;
//}
//int lcdInt(int n, String format){
//  int m = sprintf (line, "%6d", n);
//  lcd.print(line);
//  return m;
//}
//int lcdInt(int n, const char format){
//  //    lcd.print(PGMSTR(qBytesWorld));
//  int m = sprintf (line, format, n);
//  lcd.print(line);
//  return m;
//}
//////// ===========================================
//////// LCD Print DDDDDD
//////// ===========================================
//int lcdUnLong6D(unsigned long n){
//  Serial.println(n);
//  //int m = sprintf (line, "%06d", n);
//  int m = sprintf (line, "%06lu", n);
//  lcd.print(line);
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
////  char line[10];         //the ASCII of the integer will be stored in this char array
////  itoa((int)changeMe,line,10); //(integer, yourline, base)
//  
//////char dateFormat[] = "%02d:%02d:%02d:%02d";
//////    sprintf(line, dateFormat[3], days, hours, minutes, seconds); ///< This has 4 2-digit integers with leading zeros, separated by ":" . The list of parameters, hour, min, sec, provides the numbers the sprintf prints out with.
//////    lcd.print(line);    
////    //Serial.println(line); ///< You will get something like"01:13:02:09" 
////    
////char format[] = "ddddd";
////      
//////  char c[10];        // long enough to hold complete integer string
//////  char charBuf[20];
////  format.toCharArray(line,10);
////  int m = sprintf(c, line, n);    // build integer string using C integer formatters  (m is length, and not used in this code)
////  Serial.print(c);
////  return m;
////}
//
////// ===========================================
////// LCD Print NNN.DDD
////// ===========================================
//void lcdDouble63(double dbl) {
//  char *r = dtostrf(dbl, 6, 3, line);
////  lcd.print(line);
//  lcd.print(r);
//  lcd.print("V");
////  lcd.print(dtostrf(v5_System, 6, 3, line));
////  lcd.print("V");
//}

 */

