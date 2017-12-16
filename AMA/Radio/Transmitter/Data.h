/*
  Data.h - Data library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Data_h
#define Data_h

// include types & constants of Wiring core API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

// include this library's description file
#include "config.h"
#include "def.h"
#include "types.h"

#include "Data.h"

// library interface description
class Data
{
    // user-accessible "public" interface
  public:
    Data(void);
    void doSomething(void);
    void aux(byte, int);

    void setAnalog(byte, int);
    int getAnalog(byte);
    
    // library-accessible "private" interface
  private:

    int analog[8];

    MyResistorMap myResistorMap;
    MyButtons myButtons;
    MyAux myAux;
    MyControls myControls;
    MyControlsMap myControlsMapThrottle;
    MyControlsMap myControlsMapYaw;
    MyControlsMap myControlsMapRoll;
    MyControlsMap myControlsMapPitch;

  protected:

};

#endif
