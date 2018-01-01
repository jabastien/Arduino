/*
  Utils.h - Utils library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Utils_h
#define Utils_h

// include types & constants of Wiring core API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

//#include "config.h"
#include "def.h"
//#include "types.h"

// library interface description
class Utils
{
  // ======================================    
  // user-accessible "public" interface
  // ======================================    
  public:
    Utils();
    byte  arraySizeBYTE(byte []);
    int  arraySizePMG(PGM_P );
    int  countCharacters(PGM_P , char);        
    int  freeRam(void);
    void reverse(char []);
    
//    void ErrorPrint(String, uint8_t, ...);
//    float Print( const char* , ... );
//    void myprintf(const char *, ...);
//    void Q_printf( char *, ... );
    void ShowVar( char *szTypes, ... );
    
  // ======================================    
  // library-accessible "private" interface
  // ======================================    
  private:
    int freeListSize(void);

  // ======================================
  // library-accessible "protected" interface
  // ======================================    
  protected:
  
};

#endif

