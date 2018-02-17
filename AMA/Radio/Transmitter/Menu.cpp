/*
  Menu.h - Menu library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include core Wiring API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

// include description files for other libraries used (if any)
#include "HardwareSerial.h"

//// include this library's description file
#include "Menu.h"
// ===========================================
// I2C LCD
// ===========================================
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);    // Initialization of the book (address, characters, rows)

/*
 *   0 -   1 = Main Menu(s)
 *         
 *   2 -  49 = Transmitter
 *  50 -  99 = Models
 * 100 - 149 = System (Resistors, Voltages)
 * 150 - 199 = START/INIT
 * 200 - 253 = Functions
 *       254 = Error display
 *       255 = Reserved for FUNCTION switch indicator
 */


// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
Menu::Menu(Data * _data, DataStore * _dataStore){
  // initialize this instance's variables
   data = _data;
   dataStore = _dataStore;
  // do whatever is required to initialize the library

  clearDisplayMask(); // Inital load 
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

// Initialize Display Mask;
void Menu::clearDisplayMask(){

  for (byte b = 0; b <= 3; b++){
      displayMask[b] = DisplayMask();
  } 
}
 
boolean Menu::isScreenRefreshNeeded(){
  unsigned long currentMillis = millis();

  if (currentMillis > (previousScreenRefreshMiilis + intervalScreenRefresh)){
    previousScreenRefreshMiilis = currentMillis;

    return true;
  }

 return false  ;
}

void Menu::updateFPS(){

  cntFPS++;
  
  unsigned long currentMillis = millis();

  if (currentMillis > (previousMillisFPS + intervalFPS)){
      previousMillisFPS = currentMillis;
      showFPS = cntFPS;
      cntFPS = 0;

  #ifdef DEBUG_FPS
  Serial.print  ("FPS: ");
  Serial.println(showFPS);      
  #endif
    }
}

/////////////////////////////////////////////////////////////////////
void Menu::forceMenuChange(byte _menuItem){
  // Make sure FUNCTIONs don't use this method (bad things happen)
  if (_menuItem >= 200) {
    //  Err: setMenu : Don't use for FUNCTIONS"
    error = ERR200;  // Is this a bug >=200
    forceMenuChange(ERR_DISPLAY);
    return;
  }

  menuOptions[0] = _menuItem;
  menuKeyboard(SELECT);
}

void Menu::menuDisplay(){

  // We always display the MENU

  menuCarrotStart = 1;

  // Menu Switch\Case
  switch (menuSelected) {

    // ---------------------------------------
    case 0: //MAINMENU
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions000, membersof(menuOptions000));
      }
      
      lcdMenu000();
      
      break;

    // ---------------------------------------
    case 1: //MAINMENU
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions001, membersof(menuOptions001));
      }

      lcdMenu001();

      menuCarrotStart = 0;

      break;
      
// =======================================
// =======================================
// =======================================
// *   1 -  49 = Transmitter
// =======================================
// =======================================
// =======================================    

  
    // ---------------------------------------
    case 2: //lcdMainVolts();
       if (isMenuChange){ 
        setMenu(menuSelected, menuOptions002, membersof(menuOptions002));
      }
      lcdTx002();      
      break;
      
    // ---------------------------------------
    case 3: //lcdKeyVolts();
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions003, membersof(menuOptions003));
      }    
      lcdTx003();      
      break;
      
    // ---------------------------------------
    case 10:
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions010, membersof(menuOptions010));
      }        
      lcdTx010();
      break;
    // ---------------------------------------
    case 11:
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions011, membersof(menuOptions011));
      }    
      lcdTx011();
      break;
    // ---------------------------------------
    case 12:
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions012, membersof(menuOptions012));
      }    
      lcdTx012();
      break;
    // ---------------------------------------
    case 13:
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions013, membersof(menuOptions013));
      }    
      lcdTx013();
      break;
    // ---------------------------------------
    case 14:
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions014, membersof(menuOptions014));
      }    
      lcdTx014();
      break;

// =======================================
// =======================================
// =======================================
// *  50 -  99 = Models
// =======================================
// =======================================
// =======================================

    // ---------------------------------------
    // ---------------------------------------
    // ---------------------------------------
    // Model Servo switches Mixing etc...

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case 50: // // Pre, Pst & Ref Menu
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions050, membersof(menuOptions050));
      } 
  
      lcdMod050();
      
      break;    

// =======================================
// =======================================
// =======================================
// * 100 - 149 = System (Resistors, Voltages, Switches and Controls values/limits)
// =======================================
// =======================================
// =======================================

// 100 Ohm & Volts
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case 100: // // Pre, Pst & Ref Menu
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions100, membersof(menuOptions100));
      } 
  
      lcdSys100();
      
      break;

// 101 Ohms
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case 101: // // Pre, Pst & Ref Menu
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions101, membersof(menuOptions101));
      } 
  
      lcdSys101();
      
      break;
      
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case 102: // // Pre, Pst & Ref Menu
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions102, membersof(menuOptions102));
      } 
  
      lcdSys102();

      menuCarrotStart = 0;
            
      break;

            
    // ---------------------------------------
    case 104: // Pre 1.1 1.2
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions104, membersof(menuOptions104));
      }    
      
      lcdSys104();
      
      break;      
      
    // ---------------------------------------
    case 105: // Post 2.1 2.2
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions105, membersof(menuOptions105));
      }  
      
      lcdSys105();
      
      break;
      
    // ---------------------------------------
    case 106: // v5.0 3.1 3.2
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions106, membersof(menuOptions106));
      }  
      
      lcdSys106();
      
      break;


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 110: // Shunt
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions110, membersof(menuOptions110));
      }  
      
      lcdSys110();
      
      break;

      
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 112: // Shunt
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions112, membersof(menuOptions112));
      }  
      
      lcdSys112();
      
      break;
      
    // ---------------------------------------
    case 114: // 5.0V reference voltage 
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions114, membersof(menuOptions114));
      } 
           
      lcdSys114();
      
      break;

      
    // ---------------------------------------
    case 116: // Voltage for Pre, Post & V5 Regulator
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions116, membersof(menuOptions116));
      } 
           
      lcdSys116();
      
      break;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 122: // Switch
//  case 124: // Trim
//  case 126: // Buttons
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions122, membersof(menuOptions122));
      }       
      
      lcdSys122();
      
      break;

      
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 130: // Joystick range limits
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions130, membersof(menuOptions130));
      }
      
      lcdSys130();
      
      break;

    // ---------------------------------------
    case 131: // Joystick range limits
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions131, membersof(menuOptions131));
      }

      lcdSys131();
      
      menuCarrotStart = 0;

      break; 


    // ---------------------------------------
    case 134: // THROTTLE - Joystick range limits
    case 135: // YAW      - Joystick range limits
    case 136: // ROLL     - Joystick range limits
    case 137: // PITCH    - Joystick range limits
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions134, membersof(menuOptions134));
      }
      
      editControl = abs(134-menuSelected);

      lcdSys134();
      
      break;
    
    // ---------------------------------------
    case 140: // AUX - Display all
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions140, membersof(menuOptions140));
      } 
           
      lcdSys140();

      menuCarrotStart = 0;
      break;

    // ---------------------------------------
    case 141: // AUX 0 range limits
    case 142: // AUX 1 range limits
    case 143: // AUX 2 range limits
    case 144: // AUX 3 range limits
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions141, membersof(menuOptions141));
      }
      
      editControl = abs(141-menuSelected);

      lcdSys145();
      
      break;  
      
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 149: // Reset all values -> goto 249 after (bool Y/N check).
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions149, membersof(menuOptions149));
      }       
      
      lcdSys149();
      
      break;

// =======================================
// =======================================
// =======================================
// * 150 - 199 = START/INIT
// =======================================
// =======================================
// =======================================
    // ---------------------------------------
    case 150: // Start up
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions150, membersof(menuOptions150));
      }
      
      lcdInit150();    
      
      break;
      
    // ---------------------------------------
    case 151: // Splash
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions151, membersof(menuOptions151));    
      }

      lcdInit151();
      
      break;
      
    // ---------------------------------------
    case 152: // Pre 1.1 1.2 - Resistors
      if (isMenuChange){ 
        setMenu(menuSelected, menuOptions152, membersof(menuOptions152));
      }    
      
      lcdSys104();
      
      break;
      
    // ---------------------------------------
    case 154: // Post 2.1 2.2 - Resistors
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions154, membersof(menuOptions154));
      }  
        
      lcdSys105();
      
      break;
      
    // ---------------------------------------
    case 156: // v5.0 3.1 3.2 
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions156, membersof(menuOptions156));
      }    
      
      lcdSys106();
      
      break;

      
    // ---------------------------------------
    case 162: // Shunt
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions162, membersof(menuOptions162));
      } 
           
      lcdSys112();
      
      break;
      
    // ---------------------------------------
    case 164: // 5.0V reference voltage
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions164, membersof(menuOptions164));
      }  
   
      lcdSys114();
      
      break;

      
    // ---------------------------------------
    case 172: // Switch
//  case 174: // Trim
//  case 176: // Menu
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions172, membersof(menuOptions172));
      } 
         
      lcdSys122();
     
      break;

    // ---------------------------------------
    
    case 182: // Joystick range limits 0
    case 183: // Joystick range limits 1
    case 184: // Joystick range limits 2
    case 185: // Joystick range limits 3
      editControl = abs(182 - menuSelected);

      if (isMenuChange){  
        switch (editControl) {
          // ---------------------------------------
          case 0: //MAINMENU
            setMenu(menuSelected, menuOptions182, membersof(menuOptions182));
            break;
          case 1: //MAINMENU
            setMenu(menuSelected, menuOptions183, membersof(menuOptions183));
            break;
          case 2: //MAINMENU
            setMenu(menuSelected, menuOptions184, membersof(menuOptions184));
            break;
          case 3: //MAINMENU
            setMenu(menuSelected, menuOptions185, membersof(menuOptions185));
            break;
        }    
      }

      lcdSys134();
      
      break;


    // ---------------------------------------
    case 186: // AUX 0 range limits
    case 187: // AUX 1 range limits
    case 188: // AUX 2 range limits
    case 189: // AUX 3 range limits
    
      editControl = abs(186 - menuSelected);

      if (isMenuChange){  
        switch (editControl) {
          // ---------------------------------------
          case 0: //MAINMENU
            setMenu(menuSelected, menuOptions186, membersof(menuOptions186));
            break;
          case 1: //MAINMENU
            setMenu(menuSelected, menuOptions187, membersof(menuOptions187));
            break;
          case 2: //MAINMENU
            setMenu(menuSelected, menuOptions188, membersof(menuOptions188));
            break;
          case 3: //MAINMENU
            setMenu(menuSelected, menuOptions189, membersof(menuOptions189));
            break;
        }    
      }      

      lcdSys145();
      
      break;            

    // ---------------------------------------
    // ---------------------------------------
    // ---------------------------------------
    case 191: // Save to EEPROM
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions191, membersof(menuOptions191));
      }    
      
      lcdInit191();
      
      break;


    // ---------------------------------------
    // ---------------------------------------
    // ---------------------------------------
    case 192: // Control Check
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions192, membersof(menuOptions192));
      }    
      
      lcdInit192();
      
      break;

    // ---------------------------------------
    // ---------------------------------------
    // ---------------------------------------
    case 199: // ERR_DISPLAY
      if (isMenuChange){  
        setMenu(menuSelected, menuOptions199, membersof(menuOptions199));
      }    
      
      lcdInit199();
      
      break;      

// =======================================
// =======================================
// =======================================
// * 200 - 253 = Functions
// =======================================
// =======================================
// =======================================

    // Do NOT go here...look at "funcDisplay(keyPress);"
    // Do NOT go here...look at "funcDisplay(keyPress);"
    // Do NOT go here...look at "funcDisplay(keyPress);"


// =======================================
// =======================================
// =======================================
// Oops
// =======================================
// =======================================
// =======================================    
    default:
      // catch all - N/A
      //Serial.print  (F("Menu not found Error: " ));
      Serial.print  (F("-"));
      Serial.println(menuSelected);
      error = ERR253;
      forceMenuChange(ERR_DISPLAY);
      break;
  }  

}

void Menu::menuKeyboard(byte keyPress){
 
  if (menuAction != doMenu && menuAction != doInit){ // Should not be here if a function is active.
    return;
  }
  
  // If no key pressed, leave
  if (keyPress == NOKEY){
    return;
  }

  // Key Select/Enter (EXIT)
  if (keyPress == SELECT) {

//      keyPress = NOKEY;
//    if (false){
//    Serial.println("doing SELECT");  
//    Serial.print (F(" MS1:"));
//    Serial.print (menuSelected);
//    }
    
    // Do a FUNCTION or next MENU
    if (menuOptions[menuCol] >= 200){
      // Select FUNCTION to be active
      function = menuOptions[menuCol];
      menuAction = doFunc;
      funcChangeCheck();
      
//      if (false){
//        Serial.print (F(" FS2:"));
//        Serial.println(function);
//      }
      
      return;
    } else {
      // Select next MENU to be active
      menuSelected = menuOptions[menuCol];
         
      //// DO CheckMenuChange from here
      menuChangeCheck();
    
//      if (false){
//        Serial.print (F(" MS3:"));
//        Serial.println(menuSelected);
//      }
    }
  }

  // Menu operation
  if (keyPress == UP) {
    if (menuCol > 0)
      menuCol--;            
  }
  if (keyPress == DOWN) {
    if (menuCol < (menuSize-1))
      menuCol++;
  }
  if (keyPress == RIGHT) {
    if (menuRow < 5)
      menuRow++;
  }
  if (keyPress == LEFT) {
    if (menuRow > 0)
      menuRow--;
  }

  // Do we need a carrot?
  if (menuSelected != MAINMENU  && utils.arraySizeBYTE(menuOptions) != 1){// Don't show carrot for MAINMENU
    // Clear prior carrot
    for (byte b = menuCarrotStart; b <= 3 ; b++){
      lcd.setCursor(0, b);//   row >    column ^
      lcd.print (" ");
    }
    // Show new Carrot
    if (menuCol >= (menuCarrotStart)){
      lcd.setCursor(0, menuCol);//   row >    column ^
      lcd.print (">");
    }
  }
  
}

void Menu::menuChangeCheck(){

  if (menuAction != doMenu && menuAction != doInit){ // Should not be here if a function is active.
    return;
  }
  
  if (true){
    Serial.print (F(" Sel:"));
    Serial.print (menuSelected);
    Serial.println();
  }

  lcd.noBlink();
  lcd.clear();
  
  clearDisplayMask();  
  menuCol = 0;  
     
  isMenuChange = true;
  repeatCount = 0;
  menuDisplay();
}

/* define ABC - displayMask.doMaskEdit(LEFT); 
#define ABC
#ifdef ABC
void debugFuncKeyboard(DisplayMask displayMask, MyMenuData myMenuData){

// Need to add pVOid to doMaskInit method
// displayMask.doMaskInit(myMenuData.pgmData[1], '#', 10, pVoid value....);
Serial.println("Init -----------------------------------------------");
  displayMask.doMaskInit(myMenuData.pgmData[1], '#', 14, NULL);
 Serial.println("Init Complete");
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 

  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
Serial.println("Init -----------------------------------------------");
  displayMask.doMaskInit(volts_0_0xxxxxV, '#', 11, NULL);
 Serial.println("Init Complete");
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 

  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT);   
//=================================================
Serial.println("Init -----------------------------------------------");

 displayMask.doMaskInit(digits32, '#', 7, NULL);
 Serial.println("Init Complete");
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 
  
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(RIGHT); 
  displayMask.doMaskEdit(RIGHT); 

  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT); 
  displayMask.doMaskEdit(LEFT);  
}
#endif
*/

void Menu::funcKeyboard(byte keyPress){

  // If not FUNCTION, leave
  if (menuAction != doFunc){ // Should not be here if a MENU is active.
    return;
  }

  // If no key pressed, leave
  if (keyPress == NOKEY ){
    return;
  }     

  // Key Select/Enter (EXIT)
  if (keyPress == SELECT) {
//          keyPress = NOKEY;
//    if (false){
//      Serial.print (F(" FS4:"));
//      Serial.print (function);
//    }
    
    menuCol = 0;
    menuRow = 0;
    
    menuAction = doMenu;
    isMenuChange = true;
    menuChangeCheck();
    
//    if (false){
//      Serial.print (F(" FS5:"));
//      Serial.println(function);
//    }

  return;
  }

}

void Menu::funcChangeCheck(){

  // If not FUNCTION, leave
  if (menuAction != doFunc){ // Should not be here if a MENU is active.
    return;
  }
  
//  if (true){
//    Serial.print (F(" Sel:"));
//    Serial.print (menuSelected);
//    Serial.println();
//  }

  isFuncChange = true;
    
  setVisible();
  lcd.blink();   

  repeatCount = 0;
}

void Menu::funcDisplay(byte _keyPress){

  // If not FUNCTION, leave
  if (menuAction != doFunc){ // Should not be here if a MENU is active.
    return;
  }

//  if (false){
//    Serial.print  ("funcDisplay: ");
//    Serial.println(function);
//  }
 
  switch (function) {
    /*
     *   207 = Byte Signed
     *   208 = Byte Un-signed
     *   215 = int Signed
     *   216 = int Un-signed
     *   232 = long Signed
     *   232 = long Un-signed
     *   
     *   
     *   237 - EEPROM erase
     *   238 - EEPROM Read
     *   239 - EEPROM Write
     *   
     *   240 - Joystick Range set
     *   241 - Aux Range set
     *        *   
     *   25x - Function for check for Factory Reset
     *   25x - Function to do Factory Reset
     */
     
    // ---------------------------------------
    // ------------  Functions  --------------
    // ---------------------------------------
    case 215: // Int number
      lcdFunc215();
      break;
    // ---------------------------------------
    case 216: // Double number
      lcdFunc216(_keyPress);
      break;

    // ---------------------------------------
    case 237: // EEPROM erase      
      lcdFunc237();
      break;
    // ---------------------------------------
    case 238: // EEPROM Read
      lcdFunc238();
      break;
    // ---------------------------------------
    case 239: // EEPROM Write
      lcdFunc239();
      break;

    // ---------------------------------------
    case 240: // Controls Range
      lcdFunc240();
      break;

    // ---------------------------------------
    case 241: // Controls Range
      lcdFunc241();
      break;

      
    // ---------------------------------------
    default:
      // catch all - N/A
      Serial.print  (F("-"));
      Serial.print  (function);
      Serial.print  (F("-"));
      Serial.println(menuSelected);
      error = ERR254;
      forceMenuChange(ERR_DISPLAY);      
      break;    
  }

//  lcd.setCursor(myMenuData.row[menuCol] , menuCol);//   row >    column ^
  lcd.setCursor(displayMask[menuCol].getCourserPos(), menuCol);//   row >    column ^

  isFuncChange = false;
}

void Menu::updateLCD(byte keyPress) {

  menuDisplay();

  if (menuAction == doMenu || menuAction == doInit){
    // MENU mode
    menuKeyboard(keyPress);    
  } else {
    // FUNCTION mode
    funcKeyboard(keyPress);
    funcDisplay(keyPress); 
  }

  if (false){
    Serial.print  ("updateLCD 1 : ");
    Serial.print  ("isMenuChange = ");
    Serial.print  (isMenuChange);
    Serial.print  (" repeatCount = ");
    Serial.println(repeatCount);
  }

  isMenuChange = false;
  
  if (++repeatCount > 31) {
    repeatCount = 0;
  }
  
  if (false){
    if (keyPress != NOKEY){
      Serial.print  ("keyPress ");
      Serial.print  (keyPress);
      Serial.print  (" menuAction ");
      Serial.print  (menuAction);
      Serial.println(" ");
      //printDrmc();
    }
  } 
  
}


/*
void Menu::printDrmc(){
  Serial.print  (" pos> ");
//  Serial.print  (myMenuData.row[menuCol]);
  Serial.print(displayMask[1].getDisplayPos());
  
  Serial.print  (" mc  ");
  Serial.print  (menuCol);  
  Serial.print  (" mr  ");
  Serial.print  (menuRow);  
  
  Serial.println();
}
*/

//void Menu::setMenu(String menuOpt, byte menuValues[], byte sizeIs) {
void Menu::setMenu(byte menuOpt, byte menuValues[], byte sizeIs) {

//  Serial.println(menuOpt);
  
  // Make sure FUNCTIONs don't use this method (bad things happen
  if (menuValues[0] == FUNCTION) {
    Serial.print  (F("-"));
    Serial.println(menuOpt);
    error = ERR252;
    forceMenuChange(ERR_DISPLAY);      
    return;
  }
  
  // Make sure we don't have an error.
  if (sizeIs > sizeof(menuOptions)) {
    Serial.print  (F("-"));
    Serial.print  (sizeIs);
    Serial.print  (F("-"));
    Serial.print  (menuOpt);
//    sizeIs = sizeof(menuOptions);
//    Serial.print  (F("-"));
//    Serial.println(sizeIs);
//    Serial.print  (F("-"));
//    Serial.println(menuOpt);
    error = ERR251;
    forceMenuChange(ERR_DISPLAY);       
    return;
  }
  
  menuSize = sizeIs;

  // Need to find a way to retain 'menuCol' when returning?

  // Clear current menu
  memset(menuOptions, 0x00, sizeof(menuOptions)); // for automatically-allocated arrays
  memcpy(menuOptions, menuValues, menuSize);

//  // Show what we did?
//  if (false) {
//    Serial.print  (menuOpt);
//
//    Serial.print  (F(" Size ["));
//    Serial.print  (menuSize);
//    Serial.print  (F("] menuOptions[...] "));
//    //for (byte loop = 0; loop < sizeof(menuOptions); loop++) {
//    for (byte loop = 0; loop < menuSize; loop++) {
//      Serial.print  (menuOptions[loop]);
//      if ((loop+1) < menuSize){
//        Serial.print  (", ");
//      }
//    }
//    Serial.println();
//  }
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


void Menu::setVisible(){
    lcd.setCursor(15, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_set));
}

void Menu::lcdPrint(byte row, byte col, PGM_P data){
  lcd.setCursor(row, col); //   row >    column ^
  lcd.print(PGMSTR(data));    
}


// ===========================================
// Reserved
// ===========================================
void Menu::lcdMenu000() { // this is an error, 000 is reserved  
  if (isMenuChange){ 
//    lcd.setCursor(0, 0); //   row >    column ^
//    lcd.print(F("Main"));
//    lcd.setCursor(0, 1); //   row >    column ^
//    lcd.print(F("lcdMainVolts: "));
//    lcd.setCursor(0, 2); //   row >    column ^
//    lcd.print(F("lcdKeyVolts: "));  
//    lcd.setCursor(0, 3); //   row >    column ^
//    lcd.print(F("Misc: "));
  }

    lcdPrint(8, 0, lcd_param_lcdSys101_Volts);
    lcdPrint(7, 3, lcd_param_lcdSys000_MainMenu_FPS);
    lcd.print(showFPS);
}

// ===========================================
// Main Menu
// ===========================================
// -------------------------------------------
void Menu::lcdMenu001() {
    if (isMenuChange){ 
          lcdPrint(1, 0, lcd_param_lcdSys000_MainMenu);
          lcdPrint(1, 1, lcd_param_lcdSys001_Xmitter);
          lcdPrint(1, 2, lcd_param_lcdSys001_Models);
          lcdPrint(1, 3, lcd_param_lcdSys001_System);
    }
}


/*
////  double shunt = 0.766327;   // 0.5   
//    pUInt1 = &myResistorMap.shunt; // = (0.766327*10000);   // 0.5
//    pUInt2 = &myResistorMap.shunt;  // = 2638; // 2.7k
//  }
//
//  lcd.setCursor(6, 1); //   row >    column ^
//  lcd.print(display.outputDigitsU16(*pUInt1, ohm_x_xxxxO));

  
//  uint8_t batPercent = (int)((double)repeatCount*3.5);
//  customChar.percent(batPercent);
//  lcd.setCursor(11, 0); //   row >    column ^
//  lcd.print(F("Bat:"));  
//  lcd.print(display.outputDigitsU8(batPercent, digits8));//  lcd.print(display.outputDigitsU16(v5_voltPerBit, volts_0_0xxxxxV));
//  customChar.showChar();

//  lcd.setCursor(16, 3); //   row >    column ^
//  lcd.print(repeatCount);
//  lcd.print(display.outputDigitsU8(repeatCount, digits8));  
//  lcd.print(F(" "));
*/

// ===========================================
// Transmitter Items
// ===========================================
// -------------------------------------------
void Menu::lcdTx002() {

  lcdPrint(0, 0, lcd_param_lcdSys001_Xmitter);
  
  if (isMenuChange){ 
 
  }

//  if (displayMask[menuCol].getIncDirection() != 0 || isMenuChange){
//    // Display measured reference voltage
//    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
//    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
//    
//    // Calculate and display Volt/Bit
//    lcd.setCursor(displayMask[2].getDisplayPos(), 2); //   row >    column ^
//    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[2].getVoidPointer(), displayMask[2].getMaskPMG())); 
//  }

}

// -------------------------------------------
void Menu::lcdTx022() {

  //--------------------
  // Col 0
  //--------------------
  lcd.setCursor(0, 0); //   row >    column ^
  lcd.print(F("PreV: "));

//fix  lcd.print  (v5_voltPerBit * analog[7]);
  lcd.print  ("V   ");

  //Ein = (Eo/R2) * (R1+R2)
//fix  lcd.print (vPre);
  lcd.print  (F("V"));

//  //--------------------
//  // Col 1
//  //--------------------
//  lcd.setCursor(0, 1); //   row >    column ^
//  lcd.print(F("PstV: "));
//
//  lcd.print  (v5_voltPerBit * analog[1]);
//  lcd.print  (F("V   "));
//
//  //Ein = (Eo/R2) * (R1+R2)
//  lcd.print (vPst);
//  lcd.print  (F("V"));
//
//  //--------------------
//  // Col 2
//  //--------------------
//  lcd.setCursor(0, 2); //   row >    column ^
//  lcd.print(F("5.0V: "));
//
//  lcd.print  (v5_voltPerBit * analog[5]);
//  lcd.print  ("V    ");
//
//  //Ein = (Eo/R2) * (R1+R2)
//  lcd.print (v5_System);
//  lcd.print  (F("V"));
//
//  //--------------------
//  // Col3
//  //--------------------
//  lcd.setCursor(0, 3); //   row >    column ^
//  lcd.print(F("Shnt:"));
//
//  lcd.print  (avgSum / avgSize);
//  lcd.print  (F("mV "));
//
//  //Ein = (Eo/R2) * (R1+R2)
//  lcd.print ((avgSum / avgSize) / myResistorMap.shunt);
//  lcd.print  (F("mA"));
}

// -------------------------------------------
void Menu::lcdTx003() {

  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 0); //   row >    column ^
  lcd.print(F("KeyV: "));

//fix  lcd.print  (v5_voltPerBit * analog[3]);
  lcd.print  (F("V "));

  lcd.setCursor(1, 1); //   row >    column ^
  lcd.print(F("Value: "));
//fix  lcd.print  (analog[3]);
  lcd.print(F("   "));

  //  lcd.setCursor(0, 2); //   row >    column ^
  //  lcd.print("Key Down: ");
  //  lcd.print  (keyDown);

  lcd.setCursor(1, 3); //   row >    column ^
  lcd.print(F("Key Pressed: "));
//fix  lcd.print  (keyPress);
}

// -------------------------------------------
void Menu::lcdTx010() {

    lcd.setCursor(1, 0); //   row >    column ^
    lcd.print(F("10 -> 11"));
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(F("10 -> 12"));
    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(F("10 -> 13"));
    lcd.setCursor(1, 3); //   row >    column ^
    lcd.print(F("10 -> 14"));

}

// -------------------------------------------
void Menu::lcdTx011() {

    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x11"));
    lcd.setCursor(1, 1); //   row >    column ^

}

// -------------------------------------------
void Menu::lcdTx012() {

    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x12"));
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(F("Repeat: "));

}

void Menu::lcdTx013() {

    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x13"));
    lcd.setCursor(1, 1); //   row >    column ^

}


// -------------------------------------------
//void lcdMainFlightTime(){
void Menu::lcdTx014() {
  // check to see if it's time to update LCD; that is, if the difference
  // between the current time and last time you updated the LCD is bigger than
  // the interval at which you want to blink the LED.


    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x014"));

//  currentMillis = millis();

//  if (currentMillis - previousMillis >= screenRefresh) {
    // save the last time you blinked the LED
//    previousMillis = currentMillis;

    //    lcd.setCursor(0, 1); //   row >    column ^
    //    printVolts();    //Voltage: xx.xV



    {
      // -------------------------------------
      lcd.setCursor(0, 0); //   row >    column ^
      lcd.print(F("Flight: "));
//      long timeNow = millis();
////
//      int days = timeNow / day ;                                //number of days
//      int hours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
//      int minutes = ((timeNow % day) % hour) / minute ;         //and so on...
//      int seconds = (((timeNow % day) % hour) % minute) / second;
////
////
//char dateFormat[] = "%02d:%02d:%02d:%02d";
//    sprintf(buffer, dateFormat[3], days, hours, minutes, seconds); ///< This has 4 2-digit integers with leading zeros, separated by ":" . The list of parameters, hour, min, sec, provides the numbers the sprintf prints out with.
    lcd.print(millis()/1000);    
    //Serial.println(buffer); ///< You will get something like"01:13:02:09"       

      // -------------------------------------
      lcd.setCursor(1, 2); //   row >    column ^
      lcd.print(F("Channel:"));
      lcd.print(F(" xxx"));

      // -------------------------------------
      lcd.setCursor(1, 3); //   row >    column ^
      lcd.print(F("FPS:"));
      lcd.print(showFPS);  // ~300 has been the average
      lcd.print(F("   GPS: xxx"));

      // -------------------------------------

    }

}

// ===========================================
// Models Items
// ===========================================
// -------------------------------------------
void Menu::lcdMod050() {
  lcdPrint(0, 0, lcd_param_lcdSys001_Models);
}

// ===========================================
// System Items
// ===========================================
// -------------------------------------------
void Menu::lcdSys100() { // SYSTEM - OHMs & Volts / Cntl Range / Factory Reset

  if (isMenuChange){ 
    lcdPrint(0, 0, lcd_param_lcdSys001_System);    
    lcdPrint(1, 1, lcd_param_lcdSys100_OhmsVolts);
    lcdPrint(1, 2, lcd_param_lcdSys100_CntlRange);
    lcdPrint(1, 3, lcd_param_lcdSys100_FactReset);
  } 

}

void Menu::lcdSys101() { // SYSTEM - OHMs & Volts

  if (isMenuChange){ 
    lcdPrint(0, 0, lcd_param_lcdSys100_OhmsVolts);
    lcdPrint(1, 1, lcd_param_lcdSys101_Ohms);
    lcdPrint(1, 2, lcd_param_lcdSys101_Volts);
  } 
}


void Menu::lcdSys102() { // SYSTEM - OHMs

  if (isMenuChange){ 
    lcdPrint(1, 0, lcd_param_lcdSys104_Vpre);
    lcdPrint(1, 1, lcd_param_lcdSys105_Vpst);
    lcdPrint(1, 2, lcd_param_lcdSys106_V5div);
    lcdPrint(1, 3, lcd_param_lcdSys112_Shunt);
  } 
}

// -------------------------------------------
void Menu::lcdSys104() { // Vin pre 1.1 & 1.2 OHMs

  if (isMenuChange){ 
    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    displayMask[1].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().Vpre11);
     data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    displayMask[2].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().Vpre12);
     data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    //displayMask[2].doMaskInit(

    lcdPrint(0, 0, lcd_param_lcdSys104_Vpre);
    lcdPrint(2, 1, lcd_param_lcdSys104_R11);
    lcdPrint(2, 2, lcd_param_lcdSys104_R12);    
  }

  if (displayMask[menuCol].getIncDirection() != 0 || isMenuChange){
    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
    
    // Calculate and display Volt/Bit
    lcd.setCursor(displayMask[2].getDisplayPos(), 2); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[2].getVoidPointer(), displayMask[2].getMaskPMG())); 
  }
  
}

// -------------------------------------------
void Menu::lcdSys105() { // Vin pst 2.1 & 2.2 OHMs

  if (isMenuChange){ 
    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    displayMask[1].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().Vpst21);
     data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    displayMask[2].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().Vpst22);
     data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    //displayMask[2].doMaskInit(


    lcdPrint(0, 0, lcd_param_lcdSys105_Vpst);
    lcdPrint(2, 1, lcd_param_lcdSys105_R21);
    lcdPrint(2, 2, lcd_param_lcdSys105_R22); 
       
  }

  if (displayMask[menuCol].getIncDirection() != 0 || isMenuChange){
    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
    
    // Calculate and display Volt/Bit
    lcd.setCursor(displayMask[2].getDisplayPos(), 2); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[2].getVoidPointer(), displayMask[2].getMaskPMG()));
  }
}

// -------------------------------------------
void Menu::lcdSys106() { // V5.0    3.1 & 3.2 OHMs

  if (isMenuChange){ 
    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    displayMask[1].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().V5_31);
    data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    displayMask[2].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().V5_32);
    data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    //displayMask[2].doMaskInit(

    lcdPrint(0, 0, lcd_param_lcdSys106_V5div);
    lcdPrint(2, 1, lcd_param_lcdSys106_R31);
    lcdPrint(2, 2, lcd_param_lcdSys106_R32); 
  }

  if (displayMask[menuCol].getIncDirection() != 0 || isMenuChange){
    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
    
    // Calculate and display Volt/Bit
    lcd.setCursor(displayMask[2].getDisplayPos(), 2); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[2].getVoidPointer(), displayMask[2].getMaskPMG()));
  }
}


// -------------------------------------------
void Menu::lcdSys110() { // SYSTEM - Volts

  if (isMenuChange){ 
    lcdPrint(0, 0, lcd_param_lcdSys101_Volts);
    lcdPrint(1, 1, lcd_param_lcdSys114_5Vref);
    lcdPrint(1, 2, lcd_param_lcdSys116_Volts); 
  } 
}

// -------------------------------------------
void Menu::lcdSys112() { // Shunt OHMs

  if (isMenuChange){ 

    lcdPrint(0, 0, lcd_param_lcdSys112_Shunt);
    lcdPrint(1, 2, lcd_param_lcdSys112_Rshnt);    
    
    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    displayMask[1].doMaskInit(ohm_x_xxxxO, '#', 12, &data->getMyResistorMap().shunt);
    data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    //displayMask[2].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().V5_32);
    // data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    //displayMask[2].doMaskInit(

  }

  if (displayMask[menuCol].getIncDirection() != 0 || isMenuChange){
    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
  }
  
}

// -------------------------------------------
void Menu::lcdSys114() { // V5.1 Reference voltage

  if (isMenuChange){ 

    lcdPrint(0, 0, lcd_param_lcdSys114_5Vref);
    lcdPrint(1, 1, lcd_param_lcdSys114_5Vmes);
    lcdPrint(1, 3, lcd_param_lcdSys114_v5bit); 
    
    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    displayMask[1].doMaskInit(volts_x_xxxV, '#', 13, &data->getMyVoltageMap().reference);
     data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    //displayMask[2].doMaskInit(

    // 3
    displayMask[3].doMaskInit(volts_0_0xxxxxV, '#', 10, &data->getMyVoltageMap().voltPerBit);
  }

  if (displayMask[menuCol].getIncDirection() != 0 || isMenuChange){
    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG(), 1));
    
    // Calculate and display Volt/Bit
    *(uint16_t*)&data->getMyVoltageMap().voltPerBit = (*(uint16_t*)displayMask[1].getVoidPointer() / 1023.0) * 1000;
    lcd.setCursor(displayMask[3].getDisplayPos(), 3); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[3].getVoidPointer(), displayMask[3].getMaskPMG()));
  }
}

// -------------------------------------------
void Menu::lcdSys116() { // 110 - Voltage for Pre, Post & V5 Regulator 

  if (isMenuChange){ 
    lcdPrint(0, 0, lcd_param_lcdSys116_Volts);
    lcdPrint(0, 1, lcd_param_lcdSys116_Pre);
    lcdPrint(0, 2, lcd_param_lcdSys116_Pst); 
    lcdPrint(0, 3, lcd_param_lcdSys116_V5R); 
  }


    // Raw
    lcd.setCursor(6, 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(data->getPreVolts(true)*10000, volts_x_xxxV));

    lcd.setCursor(6, 2); //   row >    column ^
    lcd.print(display.outputDigitsU16(data->getPstVolts(true)*10000, volts_x_xxxV));

    lcd.setCursor(6, 3); //   row >    column ^
    lcd.print(display.outputDigitsU16(data->getV5Volts(true)*10000, volts_x_xxxV));

    // Calculated
    lcd.setCursor(13, 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(data->getPreVolts(false)*1000, volts_xx_xxV));

    lcd.setCursor(13, 2); //   row >    column ^
    lcd.print(display.outputDigitsU16(data->getPstVolts(false)*1000, volts_xx_xxV));

    lcd.setCursor(13, 3); //   row >    column ^
    lcd.print(display.outputDigitsU16(data->getV5Volts(false)*10000, volts_x_xxxV));    

}

// -------------------------------------------
void Menu::lcdSys140() { // 101 - Aux[0-3]

  if (isMenuChange){ 
    lcdPrint(1, 0, lcd_param_lcdSys140_AUXc);
    lcd.print(" 0");
    lcdPrint(1, 1, lcd_param_lcdSys140_AUXc);
    lcd.print(" 1");
    lcdPrint(1, 2, lcd_param_lcdSys140_AUXc); 
    lcd.print(" 2");    
    lcdPrint(1, 3, lcd_param_lcdSys140_AUXc); 
    lcd.print(" 3");
  }


  lcd.setCursor(13, 0); //   row >    column ^
  lcd.print(display.outputDigitsU16(data->getMyAuxsRangeMap(0).controlRange(), digits8, 2));  

  lcd.setCursor(13, 1); //   row >    column ^
  lcd.print(display.outputDigitsU16(data->getMyAuxsRangeMap(1).controlRange(), digits8, 2));

  lcd.setCursor(13, 2); //   row >    column ^
  lcd.print(display.outputDigitsU16(data->getMyAuxsRangeMap(2).controlRange(), digits8, 2));

  lcd.setCursor(13, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(data->getMyAuxsRangeMap(3).controlRange(), digits8, 2));    

}

// -------------------------------------------
void Menu::lcdSys122() { // Switch  // Trim // Menu buttons
//void Menu::lcdSys124() { // Trim
//void Menu::lcdSys126() { // Menu buttons
  if (isMenuChange){ 

    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    //displayMask[1].doMaskInit(ohm_x_xxxxO, '#', 11, &data->getMySwitchesButtons().switchSW);
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    //displayMask[2].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().V5_32);
    // data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    //displayMask[2].doMaskInit(
    lcdPrint(0,  0, lcd_param_lcdSys134_SwitchesButtons);
    lcdPrint(11, 0, lcd_param_lcdSys122_Pos); 
    lcdPrint(1,  1, lcd_param_lcdSys122_Switch);
    lcdPrint(1,  2, lcd_param_lcdSys124_Trim); 
    lcdPrint(1,  3, lcd_param_lcdSys126_Menu);           
  }

  // Display switches as bin (0's and 1's)
  lcd.setCursor(11, 1); //   row >    column ^
  lcd.print( display.outputBinary( data->getMySwitchesButtons().switchPins));

  lcd.setCursor(11, 2); //   row >    column ^
  lcd.print( display.outputBinary( data->getMySwitchesButtons().trimPins));

  lcd.setCursor(11, 3); //   row >    column ^
  lcd.print( display.outputBinary( data->getMySwitchesButtons().menuPins));
}


    
// -------------------------------------------
void Menu::lcdSys130() { // SYSTEM - Controls for Joystick / Aux / SwitchesButtons

  if (isMenuChange){ 
    lcdPrint(0, 0, lcd_param_lcdSys134_Cntl);
    lcdPrint(1, 1, lcd_param_lcdSys140_AUX);
    lcdPrint(1, 2, lcd_param_common_Joystick); 
    lcdPrint(1, 3, lcd_param_lcdSys134_SwitchesButtons); 
  } 
}

// -------------------------------------------
void Menu::lcdSys131() { // SYSTEM - Controls for Joystick / Aux / SwitchesButtons

  if (isMenuChange){ 
    lcdPrint(1, 0, lcd_param_lcdSys134_Throttle);
    lcdPrint(1, 1, lcd_param_lcdSys134_YAW);
    lcdPrint(1, 2, lcd_param_lcdSys134_ROLL); 
    lcdPrint(1, 3, lcd_param_lcdSys134_PITCH);   
  } 
}

// -------------------------------------------
void Menu::lcdSys134() { // Edit - Joystick range limits  (Find MID point, release stick and press 'Select') Throttle/Yaw/Roll/Pitch

  if (isMenuChange){ 

    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    displayMask[1].doMaskInit(digits8, '#', 11, &data->getMyJoysticksRangeMap(editControl));
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
//    displayMask[2].doMaskInit(joyStickxxxx, '#', 1, &data->getJoyStick(0));
    // data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    displayMask[3].doMaskInit(joyStickxxxx, '#', 1, &data->getMyJoysticksRangeMap(editControl));
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

  } else {
      lcd.noBlink();  
  }

  if (isMenuChange || isFuncChange){    //lcd.print(PGMSTR(lcd_param_common_Joystick));
    lcd.setCursor(0, 0); //   row >    column ^
    switch(editControl){
      case THROTTLE:
        lcd.print(PGMSTR(lcd_param_lcdSys134_Throttle));
        break;
      case YAW:
        lcd.print(PGMSTR(lcd_param_lcdSys134_YAW));
        break;
      case ROLL:
        lcd.print(PGMSTR(lcd_param_lcdSys134_ROLL));
        break;
      case PITCH:
        lcd.print(PGMSTR(lcd_param_lcdSys134_PITCH));
        break;
      }  
             
    }
 
    lcd.setCursor(1, 1); //   row >    column ^
         
    //lcd.print(PGMSTR(lcd_param_common_Joystick));
    if (menuAction == doFunc){

        switch(editControl){
          case THROTTLE:
          case PITCH:
            lcd.print(PGMSTR(lcd_param_common_UD));
            break;
          case YAW:
          case ROLL:
            lcd.print(PGMSTR(lcd_param_common_LR));
            break;
        }         
    } else {
      lcd.print(PGMSTR(lcd_param_common_Set));  
      lcd.print("          ");  
    }
    
    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_MCM));              



  // Display XMIT value as ###
  MyControlsRangeMap myJoysticksRangeMap1 = *(MyControlsRangeMap*)displayMask[1].getVoidPointer();

  lcd.setCursor(16, 1); //   row >    column ^
  lcd.print(display.outputDigitsU16(      
      // data->getJoyStick(myJoysticksRangeMap1)                 , //displayMask[1].getVoidPointer(),      
      // data->getJoyStick(*(MyControlsRangeMap*)displayMask[1].getVoidPointer())                 , //displayMask[1].getVoidPointer(),    
      myJoysticksRangeMap1.controlRange(),
      displayMask[1].getMaskPMG(), 2));

  // ============================================
  MyControlsRangeMap myJoysticksRangeMap3 = *(MyControlsRangeMap*)displayMask[3].getVoidPointer();
  
  // Display CURRENT as ####
  lcd.setCursor(1, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myJoysticksRangeMap3.current, displayMask[3].getMaskPMG(),1) );

  // Display MIN as ####
  lcd.setCursor(6, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myJoysticksRangeMap3.minimum, displayMask[3].getMaskPMG(),1) );

  // Display CENTER as ####
  lcd.setCursor(11, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myJoysticksRangeMap3.center, displayMask[3].getMaskPMG(),1) );

  // Display MAX as ####
  lcd.setCursor(16, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myJoysticksRangeMap3.maximum, displayMask[3].getMaskPMG(),1) );
  
}

// -------------------------------------------
void Menu::lcdSys145() { // Edit - Aux range limits  (Find MID point, release stick and press 'Select')

  if (isMenuChange){ 

     
    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
//    displayMask[1].doMaskInit(digits8, '#', 11, &data->getMyJoysticksRangeMap(editControl));
    displayMask[1].doMaskInit(digits8, '#', 11, &data->getMyAuxsRangeMap(editControl));    
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
//    displayMask[2].doMaskInit(joyStickxxxx, '#', 1, &data->getJoyStick(0));
    // data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    displayMask[3].doMaskInit(joyStickxxxx, '#', 1, &data->getMyAuxsRangeMap(editControl));
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

  } else {
      lcd.noBlink();  
  }

  if (isMenuChange || isFuncChange){    //lcd.print(PGMSTR(lcd_param_common_Joystick));
      lcd.setCursor(0, 0); //   row >    column ^
      lcd.print(PGMSTR(lcd_param_lcdSys140_AUXc));    
      lcd.print(editControl);      
    }
 
    lcd.setCursor(1, 1); //   row >    column ^
    if (menuAction == doFunc){
          lcd.print("Full Range");
    } else {
      lcd.print(PGMSTR(lcd_param_common_Set));  
      lcd.print("          ");  
    }
    
    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_MCM));

  // Display XMIT value as ###
  MyControlsRangeMap myAuxsRangeMap1 = *(MyControlsRangeMap*)displayMask[1].getVoidPointer();

  lcd.setCursor(16, 1); //   row >    column ^
  lcd.print(display.outputDigitsU16(      
      // data->getJoyStick(myAuxsRangeMap1)                 , //displayMask[1].getVoidPointer(),      
      // data->getJoyStick(*(MyControlsRangeMap*)displayMask[1].getVoidPointer())                 , //displayMask[1].getVoidPointer(),    
      myAuxsRangeMap1.controlRange(),
      displayMask[1].getMaskPMG(), 2));

  // ============================================
  MyControlsRangeMap myAyxsRangeMap3 = *(MyControlsRangeMap*)displayMask[3].getVoidPointer();
  
  // Display CURRENT as ####
  lcd.setCursor(1, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myAyxsRangeMap3.current, displayMask[3].getMaskPMG(),1) );

  // Display MIN as ####
  lcd.setCursor(6, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myAyxsRangeMap3.minimum, displayMask[3].getMaskPMG(),1) );

  // Display CENTER as ####
  lcd.setCursor(11, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myAyxsRangeMap3.center, displayMask[3].getMaskPMG(),1) );

  // Display MAX as ####
  lcd.setCursor(16, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myAyxsRangeMap3.maximum, displayMask[3].getMaskPMG(),1) );
  
}

// -------------------------------------------
void Menu::lcdSys149() { // Factory reset - (Erase eeprom).

  if (isMenuChange){ 
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys100_FactReset));

    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys149_FactResetYes));

    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys149_FactResetNo));
  }
}


//===========================================
// Init - Startup 
//===========================================

// -------------------------------------------
void Menu::lcdInit150() {  // Starting   [click (select) out to 150]

    if (isMenuChange){
      digitalWrite(1, LOW); // LED and Sound off
       
      menuAction = doInit;  
  
      lcd.init();
      lcd.begin(20,4);
      lcd.backlight();
      //lcd.blink();
      //lcd.noBlink();
        
      lcdPrint(6, 1, lcd_param_lcdInit150_startUp);
        
      error = 0;
    }
  
  if (repeatCount > 2) { // ~delay(500);
      forceMenuChange(SPLASH); //151
  }
}



// -------------------------------------------
void Menu::lcdInit151() { // Splash     [no click 'select button' out to 151]
    
  if (isMenuChange){ 
  
    menuAction = doInit;

    lcdPrint(0, 0, lcd_param_lcdInit151_qBytesWorld);
    lcdPrint(0, 1, lcd_param_lcdInit151_deviceInfo);
    lcdPrint(0, 2, lcd_param_lcdInit151_versionNum); 
  }

  if (repeatCount > 8) {//delay(2000);       
    // If first time run (no EEPROM data)   
    if (dataStore->isVersionMatch()){
      // Load all EEPROM data
      dataStore->loadFromEEPROM(); 
      // Go to Control check before Main Menu 
      forceMenuChange(CTLCHECK); // 192
    } else {
      // First time run, initialize system
      forceMenuChange(FIRSTINIT); // 152
    }
  }
}

// -------------------------------------------
void Menu::lcdInit191() { // Save EEPROM data

  if (isMenuChange){ 
    lcd.setCursor(2, 2); //   row >    column ^
    //lcd.print(PGMSTR(lcd_param_lcdInit192_controlHome));
    lcd.print("Saving to EEPROM");

    dataStore->saveToEEPROM();
  }
  
  if (repeatCount > 8) {
    // Go to Control check before Main Menu 
    forceMenuChange(CTLCHECK); // 192
  }  
}

// -------------------------------------------
void Menu::lcdInit192() { // Control check

  if (isMenuChange){ 
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit192_controlHome));
  }
  
  // Display switches as bin (0's and 1's)
  lcd.setCursor(0, 1); //   row >    column ^
  lcd.print( display.outputBinary( data->getMySwitchesButtons().switchPins));

  lcd.setCursor(0, 2); //   row >    column ^
  lcd.print( display.outputBinary( data->getMySwitchesButtons().trimPins));
  
  lcd.setCursor(0, 3); //   row >    column ^
  lcd.print( display.outputBinary( data->getMySwitchesButtons().menuPins));
  
  // Display XMIT value as ###
  for (byte b = 0 ; b <= 3; b++){
    // Joystick
    lcd.setCursor(16, b); //   row >    column ^
    lcd.print(display.outputDigitsU16( 
        data->getMyJoysticksRangeMap(b).controlRange(),
        digits8, 2));
    
    // AUX
    lcd.setCursor(11, b); //   row >    column ^
    lcd.print(display.outputDigitsU16( 
        data->getMyAuxsRangeMap(b).controlRange(),
        digits8, 2));  
  }

  if (repeatCount > 16) {
     // If Controls not home, wait.
    if (cntrlHome()){
          forceMenuChange(MAINMENU);      
    }
  } 
  
}

boolean Menu::cntrlHome(){
  byte diff = 10; //Within +/-X of center
  for (byte b = 0; b <= 3; b++){
    if (data->getMyAuxsRangeMap(b).controlRange() != 0){return false;}
    if (data->getMyJoysticksRangeMap(b).controlRange() - diff > 128){return false;}
    if (data->getMyJoysticksRangeMap(b).controlRange() + diff < 128){return false;}
  }

  if (data->getMySwitchesButtons().switchPins != 0){return false;}
  if (data->getMySwitchesButtons().trimPins != 0){return false;}
  if (data->getMySwitchesButtons().menuPins != 0){return false;}
  
  return true;
}

// -------------------------------------------
void Menu::lcdInit199() { // Show Error

    lcd.setCursor(2, 2); //   row >    column ^
    if ((repeatCount/2)%2 == 0){// If ODD.
      // LCD
      lcd.print(PGMSTR(ERR));
      lcd.print(error);      
      // Serial
      Serial.print  (PGMSTR(ERR));
      Serial.println(error);
      // LED/Sound on
      digitalWrite(1, HIGH); // LED and Sound on
    }else{
      lcd.print(F("       "));
      // LED/Sound off
      digitalWrite(1, LOW); // LED and Sound off
    }

  if (repeatCount > 12) { // ~delay(250);
      forceMenuChange(INITMENU); //151
  }    

}


//===========================================
// Functions
//===========================================

// -------------------------------------------
/* void Menu::lcdFunc200() { // BIN

  Serial.println("lcdFunc200");
}
*/

// -------------------------------------------
/* void Menu::lcdFunc201() { // BIN

  Serial.println("lcdFunc201");
}
*/

// -------------------------------------------
/* void Menu::lcdFunc207() { // Sint8_t number

  Serial.println("lcdFunc207");
}
*/

// -------------------------------------------
/*  void Menu::lcdFunc208() { // Sint8_t number

  Serial.println("lcdFunc208");
}
*/

// -------------------------------------------
void Menu::lcdFunc215() { // Sint16_t number

  Serial.println("lcdFunc215");
}

// -------------------------------------------
void Menu::lcdFunc216(byte _keyPress) { // Uint16_t number  (move to lcdFunc215 or lcdFunc216)

  displayMask[menuCol].doMaskEdit(_keyPress); 

  if (displayMask[menuCol].getIncDirection() != 0){
    if (displayMask[menuCol].getMask() != NULL  && displayMask[menuCol].getVoidPointer() != NULL){
//      Serial.print  ("IncDirection ");
//      Serial.print  (displayMask[menuCol].getIncDirection());
//      Serial.print  (" Expo ");
//      Serial.print  (displayMask[menuCol].getExpoValue());

       data->setUint16_tPointer(displayMask[menuCol].getVoidPointer());
//       data->adjUint16_tNumber(displayMask[menuCol].getIncDirection() * displayMask[menuCol].getExpoValue());  // delete-comment this

       data->adjUint16_tNumber(displayMask[menuCol].getIncDirection(), displayMask[menuCol].getExpoFactor());

    } else {
      // Attempt to change number, "displayMask[menuCol].getMask()" or "displayMask[menuCol].getVoidPointer()" is NULL.
      error = ERR216;
      forceMenuChange(ERR_DISPLAY);
    }
  }
  
}

// -------------------------------------------
/* void Menu::lcdFunc231() { // Sint32_t number

  Serial.println("lcdFunc231");
}
*/

// -------------------------------------------
/* void Menu::lcdFunc232() { // Sint32_t number

  Serial.println("lcdFunc232");
}
*/

// -------------------------------------------
void Menu::lcdFunc237() { // EEPROM erase
  
  // 1234567890123456789012345678901234567890
  // Erasing all transmitter data!!!
  // Reseting to Factory!

  lcd.clear();
  lcd.setCursor(9, 1); //   row >    column ^
  lcdPrint(2, 2, lcd_param_lcdInit237_factoryReset); 
  
  // eeprom erease
  dataStore->factoryReset();

//  menuAction = doInit;
//  function = 0;
  Serial.println("INITMENU");
  funcKeyboard(SELECT);
  forceMenuChange(INITMENU);

}

// -------------------------------------------
void Menu::lcdFunc238() { // EEPROM Read 


  // If Y, goto x239
  // If N, goto mainMenu
}

// -------------------------------------------
void Menu::lcdFunc239() { // EEPROM Write
  


  // 1234567890123456789012345678901234567890
  // Erasing all transmitter data!!!
  // Reseting to Factory!
  lcd.setCursor(9, 1); //   row >    column ^

  // Read the eprom to see if it is clear
  if (false){// Read the eprom to see if it is clear
//    dataStore->factoryReset();
  }
  
      error = ERR239;
      forceMenuChange(ERR_DISPLAY);

}

// -------------------------------------------
void Menu::lcdFunc240() { // Joystick Controls Range

  if (isFuncChange){   
   data->getMyJoysticksRangeMap(editControl).setCenter(); 
  }

  data->getMyJoysticksRangeMap(editControl).setMinMax();

  lcdSys134();
  
}

// -------------------------------------------
void Menu::lcdFunc241() { // Aux Controls Range

  if (isFuncChange){
   data->getMyAuxsRangeMap(editControl).setCenter(); 
  }
  
  data->getMyAuxsRangeMap(editControl).setMinMaxCenter(); 
  
  lcdSys145();  
}

//===========================================
// Reserved
//===========================================
void Menu::lcdInit255() { // this is an error, 255 is reserved 
  error = ERR255;  
  forceMenuChange(ERR_DISPLAY);
}

