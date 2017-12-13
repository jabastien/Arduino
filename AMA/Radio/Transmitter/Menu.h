/*
  Menu.h - Menu library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef Menu_h
#define Menu_h

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
#include "config.h"
#include "def.h"
#include "types.h"
#include "CustomChar.h"
#include "Display.h"



// library interface description
class Menu
{
  // ===========================================
  // user-accessible "public" interface
  // ===========================================
  public:
    Menu();
    boolean isScreenRefreshNeeded(void);
    void updateLCD(byte, int);
    void clearMyEditorData(byte);
    void setMenu(String, byte [], byte);
    void setVisible(void);

    // Reserved
    void lcdMenu000(void);

    // Main Menu
    void lcdMenu001(void);

    // Menu Items
    void lcdMenu002(void);
    void lcdMenu003(void);
    
    void lcdMenu010(void);
    void lcdMenu011(void);
    void lcdMenu012(void);
    void lcdMenu013(void);
    void lcdMenu014(void);

    // Functions
    void lcdFunc200(void);
    void lcdFunc201(void);

    // Init 
    void lcdInit240(void);
    void lcdInit244(void);
    void lcdInit245(void);
    void lcdInit246(void);
    void lcdInit247(void);
    void lcdInit248(void);
    void lcdInit249(void);
    void lcdInit250(void);
    void lcdInit251(void);
    void lcdInit252(void);

    // Startup
    void lcdInit253(void);
    void lcdInit254(void);

    // Reserved    
    void lcdInit255(void);

// ===========================================
// Menu
// ===========================================

CustomChar customChar = CustomChar();
Display display = Display();

unsigned int *pUInt1;
unsigned int *pUInt2;

unsigned int *pUInt[4];
void *pVoid[4];



char buffer[20];  //  Hold The Convert Data (width of the LCD)

byte menuRow = 0;
byte menuCol = 0;

byte editRow = 0;
byte editCol = 0;

byte returnToCurrent = MAINMENU;

byte repeatCount = 0;

byte menuCurrent  = MAINMENU;
byte menuSelected = 254;

boolean function = false;

//===============================================================================
//===============================================================================
//===============================================================================

// Declare variables
//https://arduino.stackexchange.com/questions/19748/copy-content-of-array
//https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library
//https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library

//byte menuOptions000 [0] = {}; // Do NOT use: reserved
byte menuOptions001 [4] = {MAINMENU, 2, 3, 10};

byte menuOptions002 [1] = {MAINMENU};
byte menuOptions003 [1] = {MAINMENU};

byte menuOptions010 [5] = {MAINMENU, 11, 12, 13, 14};
byte menuOptions011 [1] = {10};
byte menuOptions012 [1] = {10};
byte menuOptions013 [1] = {10};
byte menuOptions014 [1] = {10};

byte menuOptions200 [1] = {FUNCTION}; // Function for number edit
byte menuOptions201 [1] = {FUNCTION}; // Function for number edit


byte menuOptions240 [1] = {MAINMENU};     // Control Check (make sure all surfaces & switches are homed. (Prevent flight)
byte menuOptions244 [2] = {240,201};      // Menu
byte menuOptions245 [2] = {244,201};      // Trim
byte menuOptions246 [2] = {245,201};      // Switch
byte menuOptions247 [2] = {246,201};      // Joystick
byte menuOptions248 [2] = {247,201};      // Shunt ohms
byte menuOptions249 [3] = {248,200,200};  // V5.0    3.1 & 3.2 ohms
byte menuOptions250 [3] = {249,200,200};  // Vin pst 2.1 & 2.2 ohms
byte menuOptions251 [3] = {250,200,200};  // Vin pre 1.1 & 1.2 ohms
byte menuOptions252 [2] = {251,201};      // V5.0    Regulator Voltage 
byte menuOptions253 [1] = {253};          // Splash     [no click (select) out to 253]
byte menuOptions254 [1] = {253};          // Starting   [click (select) out to 254]
//byte menuOptions255 [0] = {}; // Do NOT use: reserved

byte menuOptions[5];
byte menuSize;

MyEditorData myEditorData;



  // ===========================================
  // library-accessible "private" interface
  // ===========================================
  private:
  //    int value;

// ===========================================
// Timing Vars
// ===========================================
//unsigned long currentMillis = millis();
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 100;           // interval at which to update screen (milliseconds)


int cntMillis = 0;

unsigned long  screenRefresh = 1000 / 4; // 4 times per second
unsigned long  screenLastRefresh = 0;

  // ===========================================
  // library-accessible "protected" interface
  // ===========================================
  protected:
  
};

#endif

