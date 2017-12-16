/*
  DataStore.h - 

  EEPROM Data read/write
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
  #include "WConstants.h"
#endif

#include "Data.h"


// library interface description
class DataStore
{
  // ======================================
  // user-accessible "public" interface
  // ======================================
  public:
    DataStore();
    DataStore(Data *);
    void factoryReset(void);

     
  // ======================================
  // library-accessible "private" interface
  // ======================================
  private:
    Data * _data;   

    
  // ======================================
  // library-accessible "protected" interface
  // ======================================
  protected:
 
};

#endif

