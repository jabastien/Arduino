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
#include "utils.h"

#include "CustomChar.h"
#include "Data.h"
#include "Display.h"
#include "DisplayMask.h"

// library interface description
class Menu
{
  Utils utils;
  // ===========================================
  // user-accessible "public" interface
  // ===========================================
  public:
    //Menu();
    Menu(Data *);

    boolean isScreenRefreshNeeded(void);
    //void updateLCD(byte, int);
    void updateLCD(byte);

    void updateFPS(void);
    
    void menuDisplay(void);
    void menuChangeCheck(void);
    void menuKeyboard(byte);

    void forceMenuChange(byte);
    
    void funcKeyboard(byte);
    void funcChangeCheck(void);
    void funcDisplay(byte);
    
    void setMenu(byte, byte [], byte);
    void setVisible(void);

 
    // ===========================================
    // *   0 -   1 = Main Menu(s)
    // ===========================================
    void lcdMenu000(void);
    void lcdMenu001(void);

    // ===========================================
    // *   2 -  49 = Transmitter
    // ===========================================
    void lcdTx002(void);
    void lcdTx003(void);    
    void lcdTx010(void);
    void lcdTx011(void);
    void lcdTx012(void);
    void lcdTx013(void);
    void lcdTx014(void);

    void lcdTx022(void);

    // ===========================================
    // *  50 -  99 = Models
    // ===========================================
    void lcdMod050(void);
    
    
    // ===========================================
    // * 100 - 149 = System (Resistors, Voltages)
    // ===========================================
    void lcdSys100(void); // OHMs & Volts

    void lcdSys101(void); // OHMs & Volts
    
    void lcdSys102(void); // OHMs for Pre, Pst & V5.0    
    void lcdSys104(void); // OHMs Vin pre 1.1 & 1.2 OHMs
    void lcdSys105(void); // OHMs Vin pst 2.1 & 2.2 OHMs
    void lcdSys106(void); // OHMs V5.0    3.1 & 3.2 OHMs

    void lcdSys110(void); // Volts for Shunt & 5V Ref
    void lcdSys112(void); // Volts Shunt OHMs 
    void lcdSys114(void); // Volts V5.0 Reference


    void lcdSys122(void); // Switch / Trim / Menu buttons


    void lcdSys130(void); // Throttle - Joystick range limits (Uses             editJoystick 0)  // s/b 134
    void lcdSys131(void); // Throttle - Left Joystick range limits (Uses             editJoystick 0)  // s/b 134
    void lcdSys132(void); // Throttle - Right Joystick range limits (Uses             editJoystick 0)  // s/b 134

    void lcdSys134(void); // Throttle - Joystick range limits (Uses             editJoystick 0)  // s/b 134
//  void lcdSys135(void); // Yoke     - Joystick range limits (Uses lcdSys134 , editJoystick 1)
//  void lcdSys138(void); // Roll     - Joystick range limits (Uses lcdSys134 , editJoystick 2)
//  void lcdSys139(void); // Pitch    - Joystick range limits (Uses lcdSys134 , editJoystick 3)

    void lcdSys148(void); // System Reset

    
    // ===========================================
    // * 150 - 199 = START/INIT
    // ===========================================
    void lcdInit150(void); // Starting [click (select) out to 254]
    void lcdInit151(void); // Splash   [no click 'select button' out to 151]
    
    void lcdInit192(void); // Control check

    void lcdInit199(void); // Error, restart

    // ===========================================
    // * 200 - 254 = Functions
    // ===========================================
//  void lcdFunc200(void); // Bool T/F
//  void lcdFunc201(void); // Bool Y/N
//  void lcdFunc207(void); //  8 bit Signed
//  void lcdFunc208(byte); //  8 bit Unsigned
    void lcdFunc215(void); // 16 bit Signed
    void lcdFunc216(byte); // 16 bit Unsigned
//  void lcdFunc231(void); // 32 bit Signed
//  void lcdFunc232(byte); // 32 bit Unsigned
    void lcdFunc238(void); // EEPROM Read   --> move to 25x range
    void lcdFunc239(void); // EEPROM Write  --> move to 25x range
    
    void lcdFunc240(void); // Controls Range 
    // ===========================================
    // *       255 = Reserved for FUNCTION switch indicator 
    // ===========================================
    void lcdInit255(void); // this is an error, 255 is reserved 


    // ===========================================
    // ===========================================
    
    CustomChar customChar = CustomChar();
    Display display = Display();


    char buffer[20];  //  Hold The Convert Data (width of the LCD)
    
    byte menuRow = 0;
    byte menuCol = 0;
    
    byte repeatCount = 0;
    
    byte menuSelected = INITMENU;

    byte error;
    
    byte function = 0;
    boolean isMenuChange = true;
    boolean isFuncChange = true;

    //boolean isSetVisable = false;
   
    //===============================================================================
    //===============================================================================
    //===============================================================================
    
    // Declare variables
    //https://arduino.stackexchange.com/questions/19748/copy-content-of-array
    //https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library
    //https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library

    // =======================================
    // =======================================
    // =======================================
    // *         0 = Main Menu(s)
    // =======================================
    // =======================================
    // =======================================
    byte menuOptions000 [1] = {1};
    byte menuOptions001 [4] = {MAINMENU, 2, 50, 100};


    // =======================================
    // =======================================
    // =======================================
    // *   2 -  49 = Transmitter
    //
    // #define MAINMENU  1   // Main Menu
    // #define X_MITTER  2   // Transmitter Main Menu   
    // =======================================
    // =======================================
    // =======================================    
    
    byte menuOptions002 [1] = {MAINMENU};
    byte menuOptions003 [1] = {MAINMENU};
    
    byte menuOptions010 [4] = {MAINMENU, 11, 12, 13};
    byte menuOptions011 [1] = {10};
    byte menuOptions012 [1] = {10};
    byte menuOptions013 [1] = {10};
    byte menuOptions014 [1] = {10};

    
    // =======================================
    // =======================================
    // =======================================
    // *  50 -  99 = Models
    //
    // #define MODEL     50  // Model Main Menu
    // =======================================
    // =======================================
    // =======================================
    byte menuOptions050 [1] = {MAINMENU};
    
    // =======================================
    // =======================================
    // =======================================
    // * 100 - 149 = System (Resistors, Voltages, Switches and Controls values/limits)
    //
    // #define SYSTEM    100 // System Menu
    // =======================================
    // =======================================
    // =======================================
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//===============================
// System - Ohms or Voltage / Control Range / Reset 
byte menuOptions100 [4] = {MAINMENU, 101, 130, 148};
//===============================
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // (101) - Ohms / Switches
  byte menuOptions101 [3] = {SYSTEM, 102, 110};

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // (102) - Ohms
  byte menuOptions102 [4] = {101,104,105, 106};  // Pre, Pst & Ref Menu
  //-------------------------------
    byte menuOptions104 [3] = {102,216,216};  // Vin  pre 1.1 & 1.2 OHMs
    byte menuOptions105 [3] = {102,216,216};  // Vin  pst 2.1 & 2.2 OHMs
    byte menuOptions106 [3] = {102,216,216};  // V5.0 Ref 3.1 & 3.2 OHMs

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // (110) - Shunt / Reference / Voltages
  byte menuOptions110 [4] = {101, 112, 114, 116};
  //-------------------------------
    byte menuOptions112 [2] = {110, 216};      // 110 - Shunt OHMs
    byte menuOptions114 [2] = {110, 216};      // 110 - V5.0    Reference Voltage Measured
    byte menuOptions116 [2] = {110, 216};      // 110 - Voltage for Pre, Post & V5 Regulator 

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //  System - Switch / Trim / Menu.
//  byte menuOptions120 [4] = {SYSTEM, 122, 124, 126};
    //-------------------------------
    byte menuOptions122 [1] = {130};      // Switches * Btns
//    byte menuOptions124 [1] = {120};      // Trim
//    byte menuOptions126 [1] = {120};      // Menu


//===============================
// Control Range Limits (Left/Right)
byte menuOptions130 [4] = {SYSTEM,131,132, 122};      
    
//===============================
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Left (Throttle or Yaw)
    byte menuOptions131 [3] = {130,134,135};  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      byte menuOptions134 [2] = {131,240};      // Throttle
      byte menuOptions135 [2] = {131,240};      // Yaw
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Right (Roll or Pitch)
    byte menuOptions132 [3] = {130,138,139};      
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      byte menuOptions138 [2] = {132,240};      // Roll
      byte menuOptions139 [2] = {132,240};      // Pitch

//===============================
// Reset Menu
byte menuOptions148 [2] = {SYSTEM,149};      // Factory Reset  (149 should be Y/N function)
//===============================

    // =======================================
    // =======================================
    // =======================================
    // * 150 - 199 = START/INIT
    // =======================================
    // =======================================
    // =======================================
    byte menuOptions150 [1] = {INITMENU};           // Starting   [no click (select) out of 150]
    byte menuOptions151 [3] = {SPLASH};             // Splash     [no click (select) out of 151]
    
    byte menuOptions152 [3] = {154,216,216};        // Vin pre 1.1 & 1.2 OHMs
    byte menuOptions154 [3] = {156,216,216};        // Vin pst 2.1 & 2.2 OHMs
    byte menuOptions156 [3] = {162,216,216};        // V5.0    3.1 & 3.2 OHMs

    byte menuOptions162 [2] = {164,216};            // Shunt OHMs
    byte menuOptions164 [2] = {172,216};            // V5.0    Reference Voltage 

    byte menuOptions172 [1] = {182};                // Switches & Btns
//    byte menuOptions174 [1] = {176};                // Trim
//    byte menuOptions176 [1] = {182};                // Menu

    byte menuOptions182 [2] = {183,240};            // Joystick range limits
    byte menuOptions183 [2] = {184,240};            // Joystick range limits
    byte menuOptions184 [2] = {185,240};            // Joystick range limits
    byte menuOptions185 [2] = {CTLCHECK,240};       // Joystick range limits

// Need to show voltages here???? or on the Resister screen???
    
    byte menuOptions192 [1] = {CTLCHECK};           // Control Check (make sure all surfaces & switches are homed. (Prevent flight by mistake) [no click (select) out of 192]
    byte menuOptions199 [1] = {INITMENU};           // Error, run INIT

    // =======================================
    // =======================================
    // =======================================
    // * 200 - 254 = Functions
    // =======================================
    // =======================================
    // =======================================
    //byte menuOptions207 [1] = {FUNCTION};       // Function for number edit
    //byte menuOptions208 [1] = {FUNCTION};       // Function for number edit

    //byte menuOptions215 [1] = {FUNCTION};       // Function for number edit
    //byte menuOptions216 [1] = {FUNCTION};       // Function for number edit

    //byte menuOptions231 [1] = {FUNCTION};       // Function for number edit
    //byte menuOptions232 [1] = {FUNCTION};       // Function for number edit

    //byte menuOptions238 [1] = {FUNCTION};       // Function for EEPROM read
    //byte menuOptions239 [1] = {FUNCTION};       // Function for EEPROM write

    //byte menuOptions240 [1] = {FUNCTION};       // Function to do Control Range settings

    //byte menuOptions25x [1] = {FUNCTION};       // Function for check for Factory Reset
    //byte menuOptions25x [1] = {FUNCTION};       // Function to do Factory Reset

    // =======================================
    // =======================================
    // =======================================
    // * 255 = Reserved for FUNCTION switch indicator
    // =======================================
    // =======================================
    // =======================================  
    byte menuOptions255 [0] = {/* Do NOT use: reserved */};

    

    // ===========================================
    // library-accessible "private" interface
    // ===========================================
    private:

      byte editJoyStick = 0;

      byte menuOptions[4];
      byte menuSize;

      enum MenuAction {
        doInit,
        doMenu,
        doFunc,
      } menuAction = doInit;

      void printDrmc(void);  // test only, delete this and the method
      void clearDisplayMask(void);
      
      Data * data;   
      DisplayMask displayMask[4];

    // ===========================================
    // Screen RefreshTiming Vars
    // ===========================================
    unsigned long  intervalScreenRefresh = 1000 / 4; // 4 times per second
    unsigned long  previousScreenRefreshMiilis = 0;

    // ===========================================
    // Screen RefreshTiming Vars
    // ===========================================
    unsigned long previousMillisFPS = 0;        // will store last time LED was updated
    const unsigned long intervalFPS = 1000;           // interval at which to update screen (milliseconds)
    
    int showFPS = 0;
    int cntFPS  = 0;  

  // ===========================================
  // library-accessible "protected" interface
  // ===========================================
  protected:
  
};

#endif

