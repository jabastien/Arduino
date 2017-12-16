/*
  _Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef _Test_h
#define _Test_h

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
class _Test
{
  // ======================================    
  // user-accessible "public" interface
  // ======================================    
  public:
    _Test(int);
    void doSomething(void);

  // ======================================    
  // library-accessible "private" interface
  // ======================================    
  private:
    int value;
    void doSomethingSecret(void);


  // ======================================
  // library-accessible "protected" interface
  // ======================================    
  protected:
  
};

#endif

