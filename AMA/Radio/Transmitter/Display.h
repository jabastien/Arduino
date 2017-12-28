/*
  Display.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Display_h
#define Display_h

// include types & constants of Wiring core API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <avr/pgmspace.h>

#include "def.h"
#include "utils.h"

// library interface description
#include "types.h"

/*
 * 
 * 
 *   //sprintf(buf, "%d.%d", ival/10, ival%10);
 * 
 * 
 */
class Display
{
  // ===================================
  // user-accessible "public" interface
  // ===================================
  public:


    Display(void);

template <typename T> T setSign (T number); // Return value of 'T'
char buffer [20]; // LCD width

    char *outputBinary (byte);

    char *outputDigitsU8 ( uint8_t, PGM_P );
//  char *outputDigitsU8 ( uint8_t, PGM_P , uint8_t);
    char *outputDigitsS8 (  int8_t, PGM_P );
//  char *outputDigitsS8 (  int8_t, PGM_P , uint8_t);
    
    char *outputDigitsU16(uint16_t, PGM_P );
    char *outputDigitsU16(uint16_t, PGM_P , uint8_t);
    char *outputDigitsS16( int16_t, PGM_P );    
    char *outputDigitsS16( int16_t, PGM_P , uint8_t);
        
//    char *outputDigitsU32(uint32_t, PGM_P );
//    char *outputDigitsU32(uint32_t, PGM_P , uint8_t);
//    char *outputDigitsS32( int32_t, PGM_P );
//    char *outputDigitsS32( int32_t, PGM_P , uint8_t);
//
////    char *outputOnTime(uint16_t);
////    char *outputServiceTime(uint32_t);    
//
////    char *concatBytesPGM(const char* , const char* );
////    char *concatBytesPGMSTR(const char* , const char* );

  // ===================================
  // library-accessible "private" interface
  // ===================================
  private:

    Utils utils;
    //void setBuffer(PGM_P );
    void setBuffer(PGM_P);

    // ---------------------------------------------------------
    // 8 bit unsigned intiger
    // ---------------------------------------------------------
    char u8Digit100        (uint8_t v) {return '0' + v / 100;} //   - (v/1000)        * 10;}
    char u8Digit10         (uint8_t v) {return '0' + v / 10         - (v/100)         * 10;}
    char u8Digit1          (uint8_t v) {return '0' + v / 1          - (v/10)          * 10;} 
   // typedef for class function
   typedef char (Display::*u8Digit) (uint8_t);
   // array of function pointers
    u8Digit u8Digit_Array [3] =
    {
      &Display::u8Digit100, 
      &Display::u8Digit10, 
      &Display::u8Digit1, 
    };

    // ---------------------------------------------------------
    // 8 bit signed intiger
    // ---------------------------------------------------------
    char s8Digit100        ( int8_t v) {return '0' + v / 100;} //   - (v/1000)        * 10;}
    char s8Digit10         ( int8_t v) {return '0' + v / 10         - (v/100)         * 10;}
    char s8Digit1          ( int8_t v) {return '0' + v / 1          - (v/10)          * 10;} 
   // typedef for class function
   typedef char (Display::*s8Digit) (int8_t);
   // array of function pointers
    s8Digit s8Digit_Array [3] =
    {
      &Display::s8Digit100, 
      &Display::s8Digit10, 
      &Display::s8Digit1, 
    };

    // ---------------------------------------------------------
    // 16 bit unsigned intiger
    // ---------------------------------------------------------
    // Unsigned  0 to 65535
    char u16Digit10000      (uint16_t v) {return '0' + v / 10000;} // - (v/100000)      * 10;}
    char u16Digit1000       (uint16_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
    char u16Digit100        (uint16_t v) {return '0' + v / 100        - (v/1000)        * 10;}
    char u16Digit10         (uint16_t v) {return '0' + v / 10         - (v/100)         * 10;}
    char u16Digit1          (uint16_t v) {return '0' + v / 1          - (v/10)          * 10;} 

   // typedef for class function
   typedef char (Display::*u16Digit) (uint16_t);
   // array of function pointers
    u16Digit u16Digit_Array [5] =
    {
      &Display::u16Digit10000, 
      &Display::u16Digit1000, 
      &Display::u16Digit100, 
      &Display::u16Digit10, 
      &Display::u16Digit1, 
    };
    
    // ---------------------------------------------------------
    // 16 bit signed intiger
    // ---------------------------------------------------------
    // Signed -32768 to +32767
    char s16Digit10000      ( int16_t v) {return '0' + v / 10000;} // - (v/100000)      * 10;}
    char s16Digit1000       ( int16_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
    char s16Digit100        ( int16_t v) {return '0' + v / 100        - (v/1000)        * 10;}
    char s16Digit10         ( int16_t v) {return '0' + v / 10         - (v/100)         * 10;}
    char s16Digit1          ( int16_t v) {return '0' + v / 1          - (v/10)          * 10;} 
   // typedef for class function
   typedef char (Display::*s16Digit) ( int16_t);
   // array of function pointers
    s16Digit s16Digit_Array [5] =
    {
      &Display::s16Digit10000, 
      &Display::s16Digit1000, 
      &Display::s16Digit100, 
      &Display::s16Digit10, 
      &Display::s16Digit1, 
    };

//    // ---------------------------------------------------------
//    // 32 bit unsigned intiger
//    // ---------------------------------------------------------
//    // Unsigned  0 to 4294967294
//    char u32Digit1000000000 (uint32_t v) {return '0' + v / 1000000000;}// - (v/10000000000) * 10;}
//    char u32Digit100000000  (uint32_t v) {return '0' + v / 100000000  - (v/1000000000)  * 10;}
//    char u32Digit10000000   (uint32_t v) {return '0' + v / 10000000   - (v/100000000)   * 10;}
//    char u32Digit1000000    (uint32_t v) {return '0' + v / 1000000    - (v/10000000)    * 10;}
//    char u32Digit100000     (uint32_t v) {return '0' + v / 100000     - (v/1000000)     * 10;}
//    char u32Digit10000      (uint32_t v) {return '0' + v / 10000      - (v/100000)      * 10;}
//    char u32Digit1000       (uint32_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
//    char u32Digit100        (uint32_t v) {return '0' + v / 100        - (v/1000)        * 10;}
//    char u32Digit10         (uint32_t v) {return '0' + v / 10         - (v/100)         * 10;}
//    char u32Digit1          (uint32_t v) {return '0' + v / 1          - (v/10)          * 10;} 
//   // typedef for class function
//   typedef char (Display::*u32Digit) (uint32_t);
//   // array of function pointers
//    u32Digit u32Digit_Array [10] =
//    {
//      &Display::u32Digit1000000000, 
//      &Display::u32Digit100000000, 
//      &Display::u32Digit10000000, 
//      &Display::u32Digit1000000, 
//      &Display::u32Digit100000, 
//      &Display::u32Digit10000, 
//      &Display::u32Digit1000, 
//      &Display::u32Digit100, 
//      &Display::u32Digit10, 
//      &Display::u32Digit1, 
//    };
//
//    // ---------------------------------------------------------
//    // 32 bit signed intiger
//    // ---------------------------------------------------------    
//    // Signed   -2147483648 to +2147483647
//    char s32Digit1000000000 ( int32_t v) {return '0' + v / 1000000000;}// - (v/10000000000) * 10;}
//    char s32Digit100000000  ( int32_t v) {return '0' + v / 100000000  - (v/1000000000)  * 10;}
//    char s32Digit10000000   ( int32_t v) {return '0' + v / 10000000   - (v/100000000)   * 10;}
//    char s32Digit1000000    ( int32_t v) {return '0' + v / 1000000    - (v/10000000)    * 10;}
//    char s32Digit100000     ( int32_t v) {return '0' + v / 100000     - (v/1000000)     * 10;}
//    char s32Digit10000      ( int32_t v) {return '0' + v / 10000      - (v/100000)      * 10;}
//    char s32Digit1000       ( int32_t v) {return '0' + v / 1000       - (v/10000)       * 10;}
//    char s32Digit100        ( int32_t v) {return '0' + v / 100        - (v/1000)        * 10;}
//    char s32Digit10         ( int32_t v) {return '0' + v / 10         - (v/100)         * 10;}
//    char s32Digit1          ( int32_t v) {return '0' + v / 1          - (v/10)          * 10;} 
//   // typedef for class function
//   typedef char (Display::*s32Digit) ( int32_t);
//   // array of function pointers
//    s32Digit s32Digit_Array [10] =
//    {
//      &Display::s32Digit1000000000, 
//      &Display::s32Digit100000000, 
//      &Display::s32Digit10000000, 
//      &Display::s32Digit1000000, 
//      &Display::s32Digit100000, 
//      &Display::s32Digit10000, 
//      &Display::s32Digit1000, 
//      &Display::s32Digit100, 
//      &Display::s32Digit10, 
//      &Display::s32Digit1, 
//    };

  // ===================================
  // library-accessible "protected" interface
  // ===================================
  protected:
      

};

#endif

