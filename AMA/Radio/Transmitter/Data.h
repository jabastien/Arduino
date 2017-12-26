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

    void setJoyStick(byte, int);
    byte getJoyStick(byte);
    byte getJoyStick(MyControlsRangeMap);

    void setJoyAux(byte, int);
    int  getJoyAux(byte);    

    void setUint16_tPointer(void *);
    void setUint16_tNumber(int16_t);
    void adjUint16_tNumber(int16_t);
    void adjUint16_tNumber(int8_t, int8_t);

    MyControlsRangeMap& getMyControlsRangeMap(byte);

    MyResistorMap& getMyResistorMap(void);
    MyVoltageMap&  getMyVoltageMap(void);
    MySwitchMap&   getMySwitchMap(void);
    
  // ===========================================
  // library-accessible "private" interface
  // ===========================================
  private:

    byte mapJoystickRange(int, int, int, int, bool);
    
    int aux[8];

    MyControlsRangeMap myControlsRangeMap[4];

    MyControlsRangeMap myControlsRangeMap_single;
    
    MyVoltageMap myVoltageMap;
    MyResistorMap  myResistorMap; 
    MySwitchMap mySwitchMap;
    
    MyAux myAux;

  // ===========================================
  // library-accessible "protected" interface
  // ===========================================
  protected:

};

#endif
