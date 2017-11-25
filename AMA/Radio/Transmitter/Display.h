/*
  Display.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Display_h
#define Display_h

// include types & constants of Wiring core API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
//  #include "WConstants.h"
#endif


// library interface description
class Display
{
  // user-accessible "public" interface
  public:
    Display(void);
    char *formatUnsignedInt(unsigned int, boolean);
    char *formatInt(int);

    
  // library-accessible "private" interface
  private:
    //int value;
    //void doSomethingSecret(void);
};

#endif




//
////void lcdprint_uint32(uint32_t v) {
//void lcdprint_ulong(unsigned long v) {
//  static char line[14] = "-,---,---,---";
//  //                      0 2 4 6 8   12
//  line[0]  = '0' + v  / 1000000000;
//  line[2]  = '0' + v  / 100000000 - (v/1000000000) * 10;
//  line[3]  = '0' + v  / 10000000  - (v/100000000)  * 10;
//  line[4]  = '0' + v  / 1000000   - (v/10000000)   * 10;
//  line[6]  = '0' + v  / 100000    - (v/1000000)    * 10;
//  line[7]  = '0' + v  / 10000     - (v/100000)     * 10;
//  line[8]  = '0' + v  / 1000      - (v/10000)      * 10;
//  line[10] = '0' + v  / 100       - (v/1000)       * 10;
//  line[11] = '0' + v  / 10        - (v/100)        * 10;
//  line[12] = '0' + v  / 1         - (v/10)         * 10;
//
//  lcd.print(line);  
//}
