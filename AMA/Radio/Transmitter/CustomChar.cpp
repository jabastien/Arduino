/*
  CustomChar.cpp - CustomChar for the Transmitter

 Custom Char (Max is 8 [0-7])
 255 is a solid block
 254 is an empty block

  The user must call, one of the funtions after the character creation.
    lcd.home()
      or
    lcd.setCursor(x,x) //   row >    column ^    

  Reference: // https://omerk.github.io/lcdchargen/  
*/

// include core Arduino API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

// include this library's description file
#include "CustomChar.h"

// include description files for other libraries used (if any)
#include <LiquidCrystal_I2C.h>



CustomChar::CustomChar(){
  // initialize this instance's variables

  // do whatever is required to initialize the library
  //CustomChar::setHome(); 
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries
//
// ===========================================
// ===========================================
// ===========================================
// Custom Character for LCD
// ===========================================
// ===========================================
// ===========================================

// Function that handles the creation and setup of instances
void CustomChar::percent(byte percent) {

  if (percent > 100){
    percent = 100;
  }
  
  byte p = percent/12.5;    // 100 / 8 = 12.5;  [char is 8x5 pixels]
  
  for (byte x = 0; x < 8; x++){
    if (x < (8 - p)){
      char0[x] = 0x00;
    }else{
      char0[x] = 0xff;
    }

    lcd.createChar(0,char0);
    lcd.home();
  }
}

void CustomChar::showChar(){
  lcd.print((char)0);
}
