/*
  DisplayMaskh - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef DisplayMask_h
#define DisplayMask_h

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
class DisplayMask
{
  // ===========================================
  // user-accessible "public" interface
  // ===========================================
  public:
      DisplayMask(void);
      void doMaskInit(PGM_P, const  char, byte, void *);
      
      void doMaskEdit(byte);
      byte getDisplayPos(void);
      byte getCourserPos(void);
      
      PGM_P getMaskPMG(void);
      const char * getMask(void);
      
      void * getVoidPointer(void);

      int8_t getIncDirection(void);
      int8_t getExpoFactor(void);
      uint32_t getExpoValue(void);

  // ===========================================
  // library-accessible "private" interface
  // ===========================================
  private:
      Utils utils = Utils();

      char buffer[20];
 
      PGM_P mask;    // (myMenuData.pgmData[1] = volts_x_xxxV;)
      byte maskSize;       // length of the mask
      char matchChar;      // what we are looking for.
      byte digitCnt;       // number of '#' in mask
      byte courserPos;     // pos in mask
      int8_t expoFactor;     // (digit in mask) digit exponential factor (1=1, 2=10, 3=100, n=^10
      int8_t incDirection; // Increase/Decrease number by expoFactor (1 up, -1 down)  [<T>incAmt = (1^10) * incDirection;]
      byte displayPos;      // (myMenuData.row[1] = 12;)
      void * pVoid;  //  Data element address for mask (myMenuData.pVoid[1] = &data->getMyResistorMap().shunt;)


  // ===========================================
  // library-accessible "protected" interface
  // ===========================================
  protected:
  
};

#endif

