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
char charBuf[10];

// compile and run here:
// http://ide.geeksforgeeks.org/index.php
// http://ide.geeksforgeeks.org/p9haxd 

//https://stackoverflow.com/questions/27651012/arduino-sprintf-float-not-formatting

// itoa - convert int to string
// http://www.cplusplus.com/reference/cstdlib/itoa/?kw=itoa
// https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c


/*  http://www.cplusplus.com/reference/cstdio/sprintf/
//// Q 11/11/2017
//// s/b this easy, add leading zeros
//// String myString = String(n);

// sprintf example //
#include <stdio.h>

int main ()
{
  char buffer [50];
  int n, a=5, b=3;
  n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);
  printf ("[%s] is a string %d chars long\n",buffer,n);
  return 0;
}
------------------------------------------------------
Output:
[5 plus 3 is 8] is a string 13 chars long

*/
	  
/*
 * Constructor (Empty) 
 */
FormatPrint::FormatPrint() { // constructor
  }
  
/*
 * Print and int variable
 */
int FormatPrint::printInt(int n, String format){
//  char charBuf[10];
  format.toCharArray(charBuf,10);
  int m = sprintf(c, charBuf, n); // build integer string using C integer formatters  (m is length, and not used in this code)
  Serial.print(c);   
  return m;
}
  
/*
 * Get and int variable
 */
char *  FormatPrint::getInt(int n, String format){
//  char charBuf[10];
  format.toCharArray(charBuf,10);
  int m = sprintf(c, charBuf, n); // build integer string using C integer formatters  (m is length, and not used in this code)
  //Serial.print(c);     
  return c;
}

/*
 * Print a float variable 
 */
void FormatPrint::printFloat(float d, int whole, int decimal ){

  dtostrf(d,whole,decimal,c); // -n.nnn Use this for a consistent float format
  Serial.print(c);  
}

/*
 * Get a float variable 
 */
char * FormatPrint::getFloat(float d, int whole, int decimal ){

  dtostrf(d,whole,decimal,c); // -n.nnn Use this for a consistent float format
  return c;  
}
