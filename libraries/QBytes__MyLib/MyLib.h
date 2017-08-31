#ifndef MyLib_h
#define MyLib_h

#include "Arduino.h"
class MyLibClass {
   public:
      // define public functions here
      int addem(int, int);
      int subem(int, int);
      int multem(int, int);
   private:
      // define private functions here	

};
extern MyLibClass MyLib;
#endif