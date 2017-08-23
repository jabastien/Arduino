/*

The *.cpp contains the implementations of the methods

*/
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif 
 
 // FormatPrint
#include <FormatPrint.h>
//#include <Formats.h> ==> this must be in the main program


char c[10];        // long enough to hold complete integer string


	  
/*
 * Constructor (Empty) 
 */
FormatPrint::FormatPrint() { // constructor
  }
  
/*
 * Print and int variable
 */
int FormatPrint::printInt(int n, String format){
  char charBuf[20];
  format.toCharArray(charBuf,20);
  int m = sprintf(c, charBuf, n);    // build integer string using C integer formatters  (m is length, and not used in this code)
  Serial.print(c);   
  return m;
}

/*
 * Print a float variable 
 */
void FormatPrint::printFloat(float d, int whole, int decimal ){

  dtostrf(d,whole,decimal,c);                          // -n.nnn Use this for a consistent float format
  Serial.print(c);  
}