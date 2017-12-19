/*
  Edit.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Edit_h
#define Edit_h

// include types & constants of Wiring core API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "Utils.h"

  // ===========================================
  // library interface description
  // ===========================================
class Edit
{
  // ===========================================
  // user-accessible "public" interface
  // ===========================================
  public:
    Edit(void);
    void doMaskEdit(byte , char [], uint16_t );
    void doMaskEdit2(byte , const  char *, uint16_t );

  // ===========================================
  // library-accessible "private" interface
  // ===========================================
  private:
    char* reverse(char [], byte);

    Utils utils = Utils();
    
  // ===========================================
  // library-accessible "protected" interface
  // ===========================================
  protected:
  
};

#endif

