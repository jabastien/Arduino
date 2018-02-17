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

    void setVolts(byte, int);
    int  getVolts(byte);

    double getCalcVolts(unsigned int, unsigned int, unsigned int, boolean);

    double getPreVolts(boolean);
    double getPstVolts(boolean);
    double getV5Volts(boolean);
    double getMilliAmps(void);

    void setUint16_tPointer(void *);
    void setUint16_tNumber(int16_t);
    void adjUint16_tNumber(int16_t);
    void adjUint16_tNumber(int8_t, int8_t);

    MyControlsRangeMap& getMyJoysticksRangeMap(byte);
    MyControlsRangeMap& getMyAuxsRangeMap(byte);

    MyResistorMap& getMyResistorMap(void);
    MyVoltageMap&  getMyVoltageMap(void);
    MySwitchesButtons&   getMySwitchesButtons(void);
    
  // ===========================================
  // library-accessible "private" interface
  // ===========================================
  private:

    double avgE = 0.0;

    int volts[4];
    
    MyControlsRangeMap myJoysticksRangeMap[4];
    MyControlsRangeMap myAuxsRangeMap[4];

 //   MyControlsRangeMap myJoysticksRangeMap_single;
    
    MyVoltageMap myVoltageMap;
    MyResistorMap  myResistorMap; 
    
    MySwitchesButtons mySwitchesButtons;
    
    MyAux myAux;

  // ===========================================
  // library-accessible "protected" interface
  // ===========================================
  protected:

};

#endif
