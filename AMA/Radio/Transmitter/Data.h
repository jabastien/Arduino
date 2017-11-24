/*
  Data.h - 
*/

// ensure this library description is only included once
#ifndef DATA_H
#define DATA_H

// include types & constants of Wiring core API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
//  #include "WConstants.h"
#endif


// library interface description
class Data
{
  // user-accessible "public" interface
  public:
    Data(void);
    void factoryReset(void);

  // library-accessible "private" interface
  private:
    int value;
    
};

#endif

