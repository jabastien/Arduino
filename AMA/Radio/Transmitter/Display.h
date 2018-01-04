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
#include "config.h"
#include "def.h"
#include "types.h"
#include "utils.h"

#include "CustomChar.h"
#include "Data.h"
#include "Display.h"
#include "DisplayMask.h"

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

template <typename T> T setSign  (T number); // Return value of 'T'
template <typename T> T getDigit (T number, byte); // Return value of 'T'

char buffer [20]; // LCD width

    char *outputBinary (byte);

template <typename T>    char *outputDigitsX ( T, PGM_P, byte, byte );

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

  // ===================================
  // library-accessible "protected" interface
  // ===================================
  protected:
      

};

#endif

