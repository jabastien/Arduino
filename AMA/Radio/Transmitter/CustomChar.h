/*
  CustomChar.h - 
*/

// ensure this library description is only included once
#ifndef CUSTOMCHAR_H
#define CUSTOMCHAR_H

// include types & constants of Wiring core API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd; // Varaible initialized outside my class.

// ====================================
// library interface description
// ====================================
class CustomChar
{
  // ====================================
  // user-accessible "public" interface
  // ====================================
  public:
    CustomChar(void);
    void percent(byte);
    void showChar(void);

  // ====================================
  // library-accessible "private" interface
  // ====================================
  private:
    byte char0[8] = {0x1f, 0x00, 0x0a, 0x04, 0x0a, 0x00, 0x11, 0x1f};
    
  // ====================================
  // library-accessible "protected" interface
  // ====================================
  protected:
  
};


#endif

/*
 Usage:
    lcd.createChar(0, testChar0);  
    lcd.createChar(1, testChar1);   
    lcd.createChar(2, testChar2);   
    lcd.createChar(3, testChar3);   
    lcd.createChar(4, testChar4);   
    lcd.createChar(5, testChar5);   
    lcd.createChar(6, testChar6);   
    lcd.createChar(7, testChar7);   

    lcd.home();
    lcd.setCursor(0,0); //   row >    column ^
*/

/*
// Sample ways to create a custom charactor.

  byte  testChar0[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // = 254 (empty)
  byte  testChar0[8] = {0x1f, 0x00, 0x0a, 0x04, 0x0a, 0x00, 0x11, 0x1f};
  byte  testChar1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f};
  byte  testChar2[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f};
  byte  testChar3[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f};
  byte  testChar4[8] = {0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f};
  byte  testChar5[8] = {0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
  byte  testChar6[8] = {0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
  byte  testChar7[8] = {0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
  byte  testChar7[8] = {0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}; // = 255 (full)

  byte testChar7[8] = {
  0b01110,
  0b11011,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11111,
  0b11111
};

  byte  testChar[8] = {0x00, 0x00, 0x0a, 0x00, 0x04, 0x11, 0x0e, 0x00}; // smile
  byte  testChar[8] = {  // degree F
      B01000,
      B10100,
      B01000,
      B00000,
      B00111,
      B00100,
      B00110,
      B00100
    };
*/
