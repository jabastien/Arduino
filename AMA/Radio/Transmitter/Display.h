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

// library interface description



class Display
{
  // user-accessible "public" interface
  public:
    Display(void);
    char *outputDigitsU8 ( uint8_t);
    char *outputDigitsS8 (  int8_t);
    char *outputDigitsU16(uint16_t);
    char *outputDigitsS16( int16_t);
    char *outputDigitsU32(uint32_t);
    char *outputDigitsS32( int32_t);

    char *outputOnTime(uint16_t);
    char *outputServiceTime(uint32_t);

    char *output_xx_xV(uint16_t);
    char *output_x_xxxV(uint16_t);

    char * concatBytesPGM(const char* , const char* );
    char * concatBytesPGMSTR(const char* , const char* );
    
  // library-accessible "private" interface
  private:
    //int value;
    //void doSomethingSecret(void);
};

#endif

