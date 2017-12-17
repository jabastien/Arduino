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

// library interface description
class Data
{
    // ===========================================
    // user-accessible "public" interface
    // ===========================================
  public:
    Data(void);
    void aux(byte, int);

    void setAnalog(byte, int);
    int getAnalog(byte);
    MyResistorMap& getMyResistorMap(void);

    MyResistorMap  myResistorMap; 

    // ===========================================
    // library-accessible "private" interface
    // ===========================================
  private:

    int mapJoystickRange(int, int, int, int, bool);
    int analog[8];


    MyButtons myButtons;
    MyAux myAux;
    MyControls myControls;
    MyControlsMap myControlsMapThrottle;
    MyControlsMap myControlsMapYaw;
    MyControlsMap myControlsMapRoll;
    MyControlsMap myControlsMapPitch;

    // ===========================================
    // library-accessible "protected" interface
    // ===========================================
  protected:

};

#endif
