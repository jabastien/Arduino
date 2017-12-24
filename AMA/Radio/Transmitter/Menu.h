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
#include "Data.h"
#include "Display.h"
#include "DisplayMask.h"

// library interface description
class Menu
{
  // ===========================================
  // user-accessible "public" interface
  // ===========================================
  public:
    //Menu();
    Menu(Data *);

    boolean isScreenRefreshNeeded(void);
    void updateLCD(byte, int);

    void menuDisplay(void);
    void menuChangeCheck(void);
    void menuKeyboard(byte);
    void funcKeyboard(byte);
    void funcChangeCheck(void);
    void funcDisplay(byte);
    
//    void clearMyEditorData(byte);

    void setMenu(String, byte [], byte);
    void setVisible(void);

 
    // ===========================================
    //  *         0 = Reserved
    // ===========================================
    void lcdMenu000(void);

    // ===========================================
    // *   1 -  49 = Transmitter
    // ===========================================
    void lcdMenu001(void);

    // Menu Items
    void lcdMenu002(void);
    void lcdMenu003(void);    
    void lcdMenu010(void);
    void lcdMenu011(void);
    void lcdMenu012(void);
    void lcdMenu013(void);
    void lcdMenu014(void);

    // ===========================================
    // *  50 -  99 = Models
    // ===========================================
    
    
    // ===========================================
    // * 100 - 149 = System (Resistors, Voltages)
    // ===========================================
    void lcdSys102(void); // Vin pre 1.1 & 1.2 ohms
    void lcdSys104(void); // Vin pst 2.1 & 2.2 ohms
    void lcdSys106(void); // V5.0    3.1 & 3.2 ohms

    void lcdSys112(void); // Shunt ohms 
    void lcdSys114(void); // V5.0    Reference

    void lcdSys122(void); // Switch
    void lcdSys124(void); // Trim
    void lcdSys126(void); // Menu buttons

    void lcdSys132(void); // Joystick range limits

    void lcdSys148(void); // System Reset

    
    // ===========================================
    // * 150 - 199 = START/INIT
    // ===========================================
    void lcdInit150(void); // Starting [click (select) out to 254]
    void lcdInit151(void); // Splash   [no click 'select button' out to 151]
    
    void lcdInit192(void); // Control check


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
    void lcdFunc238(void); // 
    void lcdFunc239(void); //
    
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
    
    byte menuSelected = STARTMENU;
    
    byte function = 0;
    boolean isMenuChange = true;
    
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
    // *         0 = Reserved
    // =======================================
    // =======================================
    // ======================================= 
    byte menuOptions000 [0] = {/* Do NOT use: reserved */}; 


    // =======================================
    // =======================================
    // =======================================
    // *   1 -  49 = Transmitter
    // =======================================
    // =======================================
    // =======================================    
    byte menuOptions001 [4] = {MAINMENU, 2, 3, 10};
    
    byte menuOptions002 [1] = {MAINMENU};
    byte menuOptions003 [1] = {MAINMENU};
    
    byte menuOptions010 [5] = {MAINMENU, 11, 12, 13, 14};
    byte menuOptions011 [1] = {10};
    byte menuOptions012 [1] = {10};
    byte menuOptions013 [1] = {10};
    byte menuOptions014 [1] = {10};

    
    // =======================================
    // =======================================
    // =======================================
    // *  50 -  99 = Models
    // =======================================
    // =======================================
    // =======================================


    
    // =======================================
    // =======================================
    // =======================================
    // * 100 - 149 = System (Resistors, Voltages, Switches and Controls values/limits)
    // =======================================
    // =======================================
    // =======================================
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    byte menuOptions100 [4] = {MAINMENU,102,104, 106};  // Pre, Pst & Ref Menu
    //-------------------------------
    byte menuOptions102 [3] = {100,216,216};  // Vin  pre 1.1 & 1.2 ohms
    byte menuOptions104 [3] = {100,216,216};  // Vin  pst 2.1 & 2.2 ohms
    byte menuOptions106 [3] = {100,216,216};  // V5.0 Ref 3.1 & 3.2 ohms


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    byte menuOptions110 [3] = {MAINMENU, 112, 114};      // Shunt & Ref menu
    //-------------------------------
    byte menuOptions112 [2] = {110,216};      // Shunt ohms
    byte menuOptions114 [2] = {110,216};      // V5.0    Reference Voltage 

    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    byte menuOptions120 [4] = {MAINMENU, 122, 124, 126};      // Menu, Trim & Switch Menu.
    //-------------------------------
    byte menuOptions122 [2] = {120,216};      // Switch
    byte menuOptions124 [2] = {120,216};      // Trim
    byte menuOptions126 [2] = {120,216};      // Menu


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    byte menuOptions132 [2] = {MAINMENU,216};      // Joystick range limits

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    byte menuOptions148 [2] = {MAINMENU,149};      // Factory Reset


    // =======================================
    // =======================================
    // =======================================
    // * 150 - 199 = START/INIT
    // =======================================
    // =======================================
    // =======================================
    byte menuOptions150 [1] = {151};                // Starting   [click (select) out to 254]
    byte menuOptions151 [3] = {151,152,CTLCHECK};  // Splash     [no click (select) out to 151]
    
    byte menuOptions152 [3] = {154,216,216};        // Vin pre 1.1 & 1.2 ohms
    byte menuOptions154 [3] = {156,216,216};        // Vin pst 2.1 & 2.2 ohms
    byte menuOptions156 [3] = {162,216,216};        // V5.0    3.1 & 3.2 ohms

    byte menuOptions162 [2] = {164,216};            // Shunt ohms
    byte menuOptions164 [2] = {172,216};            // V5.0    Reference Voltage 

    byte menuOptions172 [2] = {174,216};            // Switch
    byte menuOptions174 [2] = {176,216};            // Trim
    byte menuOptions176 [2] = {182,216};            // Menu

    byte menuOptions182 [2] = {CTLCHECK,216};       // Joystick range limits
    
    byte menuOptions192 [1] = {MAINMENU};           // Control Check (make sure all surfaces & switches are homed. (Prevent flight by mistake)

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
    
    //byte menuOptions238 [1] = {FUNCTION};       // Function for check for Factory Reset
    //byte menuOptions239 [1] = {FUNCTION};       // Function to do Factory Reset
    
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

int fpsShow = 0;
      byte menuOptions[5];
      byte menuSize;

      enum MenuAction {
        doInit,
        doMenu,
        doFunc,
      } menuAction = doInit;

      void printDrmc(void);  // test only, delete this and the method
      void clearDisplayMask(void);
      
      Data * _data;   
      DisplayMask displayMask[4];

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

