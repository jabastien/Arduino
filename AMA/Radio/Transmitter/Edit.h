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

#include "def.h"
#include "Utils.h"

//#include "Menu.h"

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
      void doMaskInit(const  char *, const  char, byte);
      
      void doMaskEdit(byte);
      byte getDisplayPos(void);
      byte getCourserPos(void);

      const char * getMask(void);

  // ===========================================
  // library-accessible "private" interface
  // ===========================================
  private:
      Utils utils = Utils();

      char buffer[20];

      const char * mask;
      byte maskSize;       // length of the mask
      char matchChar;      // what we are looking for.
      byte digitCnt;       // number of '#' in edit mask
      byte courserPos;     // pos in edit mask
      byte expoFactor;     // (digit under edit) digit exponential factor (1=1, 2=10, 3=100, n=^10
      int8_t incDirection; // Increase/Decrease number by expoFactor (1 up, -1 down)  [<T>incAmt = (1^10) * incDirection;]
      byte displayPos;

  // ===========================================
  // library-accessible "protected" interface
  // ===========================================
  protected:
  
};

#endif

