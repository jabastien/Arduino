// FormatPrint.h
#ifndef FormatPrint_H
#define FormatPrint_H

/*
 * In general your *.h contains the class defition, which is all your data and all your method declarations. 
 */

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <String.h>
#include <WString.h>
//#include <stdio.h>


class FormatPrint{

  /*
   * public members / functions / class variables
   */
    public: 
     FormatPrint(); // constructor
     int  printInt  (int n, String format);

     void printFloat(float d, int whole, int decimal);
     char * getFloat(float d, int whole, int decimal);
     

	
	
//     String fmt;  

  /*
   * private members / functions / class variables
   */
    private:
  

  /*
   * protected members / functions / class variables
   */
    protected:

};

#endif //FormatPrint_H

