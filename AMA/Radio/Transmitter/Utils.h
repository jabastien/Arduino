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

// library interface description
class Utils
{
  // ======================================    
  // user-accessible "public" interface
  // ======================================    
  public:
    Utils();
    int freeRam(void);

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

