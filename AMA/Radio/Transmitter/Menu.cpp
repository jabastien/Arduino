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
 *         0 = Reserved
 *         
 *   1 -  49 = Transmitter
 *  50 -  99 = Models
 * 100 - 149 = System (Resistors, Voltages)
 * 150 - 199 = START/INIT
 * 200 - 254 = Functions
 * 
 *       255 = Reserved for FUNCTION switch indicator
 */


// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
Menu::Menu(Data * _data){
  // initialize this instance's variables
   data = _data;

  // do whatever is required to initialize the library

  clearDisplayMask(); // Inital load 
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

// Initialize Display Mask;
void Menu::clearDisplayMask(){
  displayMask[0] = DisplayMask();
  displayMask[1] = DisplayMask();
  displayMask[2] = DisplayMask();
  displayMask[3] = DisplayMask();  
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

      if (true){
        Serial.print  ("FPS: ");
        Serial.println(showFPS);      
      }
    }
}

/////////////////////////////////////////////////////////////////////
  
void Menu::menuDisplay(){

  // We always display the MENU

  // Menu Switch\Case
  switch (menuSelected) {

// =======================================
// =======================================
// =======================================
// *   1 -  49 = Transmitter
// =======================================
// =======================================
// =======================================    
    // ---------------------------------------
    case 1: //MAINMENU
      lcdMenu001();
      break;
    // ---------------------------------------
    // Choose Transmitter, Models, System
    case 2: //lcdMainVolts();
      lcdMenu002();      
      break;
    // ---------------------------------------
    case 3: //lcdKeyVolts();
      lcdMenu003();      
      break;
    // ---------------------------------------
    case 10:
      lcdMenu010();
      break;
    // ---------------------------------------
    case 11:
      lcdMenu011();
      break;
    // ---------------------------------------
    case 12:
      lcdMenu012();
      break;
    // ---------------------------------------
    case 13:
      lcdMenu013();
      break;
    // ---------------------------------------
    case 14:
      lcdMenu014();
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

// =======================================
// =======================================
// =======================================
// * 100 - 149 = System (Resistors, Voltages, Switches and Controls values/limits)
// =======================================
// =======================================
// =======================================

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case 100: // // Pre, Pst & Ref Menu
//      lcdInit100();
      Serial.println("fix 100");
      break;
    // ---------------------------------------
    case 102: // Pre 1.1 1.2
      if (isMenuChange){ 
        setMenu(F("x102"), menuOptions102, membersof(menuOptions102));
      }    
      lcdSys102();
      break;      
    // ---------------------------------------
    case 104: // Post 2.1 2.2
      if (isMenuChange){ 
        setMenu(F("x104"), menuOptions104, membersof(menuOptions104));
      }  
      lcdSys104();
      break;
    // ---------------------------------------
    case 106: // v5.0 3.1 3.2
      if (isMenuChange){ 
        setMenu(F("x106"), menuOptions106, membersof(menuOptions106));
      }  
      lcdSys106();
      break;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 112: // Shunt
      if (isMenuChange){ 
        setMenu(F("x112"), menuOptions112, membersof(menuOptions112));
      }  
      lcdSys112();
      break;
    // ---------------------------------------
    case 114: // 5.0V reference voltage 
      if (isMenuChange){ 
        setMenu(F("x114"), menuOptions114, membersof(menuOptions114));
      }      
      lcdSys114();
      break;
      
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 122: // Switch
      if (isMenuChange){ 
        setMenu(F("x122"), menuOptions122, membersof(menuOptions122));
      }       
      lcdSys122();
      break;
    // ---------------------------------------
    case 124: // Trim ?? should this be under MODEL????? what would we do here????
      if (isMenuChange){ 
        setMenu(F("x124"), menuOptions124, membersof(menuOptions124));
      }       
      lcdSys124();
      break;
    // ---------------------------------------
    case 126: // Menu
      if (isMenuChange){ 
        setMenu(F("x126"), menuOptions126, membersof(menuOptions126));
      }       
      lcdSys126();
      break;
      
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 131: // Joystick range limits
      if (isMenuChange){ 
        setMenu(F("x131"), menuOptions131, membersof(menuOptions131));
      }
      
      editJoyStick = 0;

      lcdSys132();
      break;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 132: // Joystick range limits
      if (isMenuChange){ 
        setMenu(F("x132"), menuOptions132, membersof(menuOptions132));
      }
      
      editJoyStick = 1;

      lcdSys132();
      break;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 133: // Joystick range limits
      if (isMenuChange){ 
        setMenu(F("x133"), menuOptions133, membersof(menuOptions133));
      }
      
      editJoyStick = 2;

      lcdSys132();
      break;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 134: // Joystick range limits
      if (isMenuChange){ 
        setMenu(F("x134"), menuOptions134, membersof(menuOptions134));
      }
      
      editJoyStick = 3;

      lcdSys132();
      break;
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ---------------------------------------
    case 148: // Reset all values -> goto 249 after (bool Y/N check).
      if (isMenuChange){ 
        setMenu(F("x148"), menuOptions148, membersof(menuOptions148));
      }       
      lcdSys148();
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
        setMenu(F("x150"), menuOptions150, membersof(menuOptions150));
      }
      
      lcdInit150();    
      break;
    // ---------------------------------------
    case 151: // Splash
      if (isMenuChange){  
        setMenu(F("x151"), menuOptions151, membersof(menuOptions151));    
      }

      lcdInit151();
      break;

      
    // ---------------------------------------
    case 152: // Pre 1.1 1.2 - Resistors
      if (isMenuChange){ 
        setMenu(F("x152"), menuOptions152, membersof(menuOptions152));
      }    
      lcdSys102();
      break;
    // ---------------------------------------
    case 154: // Post 2.1 2.2 - Resistors
      if (isMenuChange){  
        setMenu(F("x154"), menuOptions154, membersof(menuOptions154));
      }    
      lcdSys104();
      break;
    // ---------------------------------------
    case 156: // v5.0 3.1 3.2 
      if (isMenuChange){  
        setMenu(F("x156"), menuOptions156, membersof(menuOptions156));
      }    
      lcdSys106();
      break;

      
    // ---------------------------------------
    case 162: // Shunt
      if (isMenuChange){  
        setMenu(F("x162"), menuOptions162, membersof(menuOptions162));
      }      
      lcdSys112();
      break;
    // ---------------------------------------
    case 164: // 5.0V reference voltage
      if (isMenuChange){  
        setMenu(F("x164"), menuOptions164, membersof(menuOptions164));
      }      
      lcdSys114();
      break;

      
    // ---------------------------------------
    case 172: // Switch
      if (isMenuChange){  
        setMenu(F("x172"), menuOptions172, membersof(menuOptions172));
      }    
      lcdSys122();
      break;
    // ---------------------------------------
    case 174: // Trim
      if (isMenuChange){  
        setMenu(F("x174"), menuOptions174, membersof(menuOptions174));
      }    
      lcdSys124();
      break;
    // ---------------------------------------
    case 176: // Menu
      if (isMenuChange){  
        setMenu(F("x176"), menuOptions176, membersof(menuOptions176));
      }    
      lcdSys126();
      break;

      
    // ---------------------------------------
    case 182: // Joystick range limits
      if (isMenuChange){  
        setMenu(F("x182"), menuOptions182, membersof(menuOptions182));
      }
      
      editJoyStick = 0;

      lcdSys132();
      break;
    // ---------------------------------------
    case 183: // Joystick range limits
      if (isMenuChange){  
        setMenu(F("x183"), menuOptions183, membersof(menuOptions183));
      }
      
      editJoyStick = 1;

      lcdSys132();
      break;
    // ---------------------------------------
    case 184: // Joystick range limits
      if (isMenuChange){  
        setMenu(F("x184"), menuOptions184, membersof(menuOptions184));
      }
      
      editJoyStick = 2;

      lcdSys132();
      break;
    // ---------------------------------------
    case 185: // Joystick range limits
      if (isMenuChange){  
        setMenu(F("x185"), menuOptions185, membersof(menuOptions185));
      }
      
      editJoyStick = 3;

      lcdSys132();
      break;            

      
    // ---------------------------------------
    // ---------------------------------------
    // ---------------------------------------
    case 192: // Control Check
      if (isMenuChange){  
        setMenu(F("x192"), menuOptions192, membersof(menuOptions192));
      }    
      lcdInit192();
      break;


// =======================================
// =======================================
// =======================================
// * 200 - 254 = Functions
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
      Serial.print  (F("Menu not found Error: " ));
      Serial.print  (menuSelected);
      Serial.println(F(" - reset"));
      menuSelected = STARTMENU;
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
    
    if (false){
    Serial.println("doing SELECT");  
    Serial.print (F(" MS1:"));
    Serial.print (menuSelected);
    }
    
    // Do a FUNCTION or next MENU
    if (menuOptions[menuCol] >= 200){
      // Select FUNCTION to be active
      function = menuOptions[menuCol];
      menuAction = doFunc;
      funcChangeCheck();
      
      if (false){
        Serial.print (F(" FS2:"));
        Serial.println(function);
      }
      
      return;
    } else {
      // Select next MENU to be active
      menuSelected = menuOptions[menuCol];
         
      //// DO CheckMenuChange from here
      menuChangeCheck();
    
      if (false){
        Serial.print (F(" MS3:"));
        Serial.println(menuSelected);
      }
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
  if (menuAction != doInit){
    if (menuSelected != MAINMENU){// Don't show carrot for MAINMENU
      // Clear prior carrot
      for (byte b = 1; b <= 3 ; b++){
        lcd.setCursor(0, b);//   row >    column ^
        lcd.print (" ");
      }
      // Show new Carrot
      if (menuCol > 0){
        lcd.setCursor(0, menuCol);//   row >    column ^
        lcd.print (">");
      }
    }
  }
  
}

void Menu::menuChangeCheck(){

  if (menuAction != doMenu && menuAction != doInit){ // Should not be here if a function is active.
    return;
  }
  
  if (false){
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
    if (false){
      Serial.print (F(" FS4:"));
      Serial.print (function);
    }
    
    menuCol = 0;
    menuRow = 0;
//    editCol = 0;
//    editRow = 0;
    
    menuAction = doMenu;
    isMenuChange = true;
    menuChangeCheck();
    
    if (false){
      Serial.print (F(" FS5:"));
      Serial.println(function);
    }

  return;
  } 

/*
  #ifdef ABC
  debugFuncKeyboard(displayMask, myMenuData);  // this may not work?? Need menuCol
  #endif
*/
  
}

void Menu::funcChangeCheck(){

  // If not FUNCTION, leave
  if (menuAction != doFunc){ // Should not be here if a MENU is active.
    return;
  }
  
  if (true){
    Serial.print (F(" Sel:"));
    Serial.print (menuSelected);
    Serial.println();
  }

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

  if (false){
    Serial.print  ("funcDisplay: ");
    Serial.println(function);
  }
 
  switch (function) {
    /*
     *   207 = Byte Signed
     *   208 = Byte Un-signed
     *   215 = int Signed
     *   216 = int Un-signed
     *   232 = long Signed
     *   232 = long Un-signed
     *   
     *   238 - EEPROM Read
     *   239 - EEPROM Write
     *   
     *   240 - Control Range set
     *   
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
    default:
      // catch all - N/A
      Serial.print  (F("Function not found Error: " ));
      Serial.print  (function);
      Serial.println(F(" - reset"));
      menuSelected = STARTMENU;
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
  
  if (true){
    if (keyPress != NOKEY){
      Serial.print  ("keyPress ");
      Serial.print  (keyPress);
      Serial.print  (" menuAction ");
      Serial.print  (menuAction);
      printDrmc();
    }
  } 
}

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

void Menu::setMenu(String menuOpt, byte menuValues[], byte sizeIs) {
  
  // Make sure FUNCTIONs don't use this method (bad things heppen
  if (menuValues[0] == FUNCTION) {
    Serial.print  (F("Err: setMenu : Don't use for FUNCTIONS"));
    return;
  }
  
  // Make sure we don't have an error.
  if (sizeIs > sizeof(menuOptions)) {
    Serial.print  (F("Err: setMenu "));
    Serial.print  (sizeIs);
    Serial.print  (F(" for "));
    Serial.print  (menuOpt);
    sizeIs = sizeof(menuOptions); // degrade to prevent Array Overflow error
    Serial.print  (F(" s/b <= ")); // increase " byte menuOptions[x] " size
    Serial.println(sizeIs);
  }
  
  menuSize = sizeIs;

  // Need to find a way to retain 'menuCol' when returning?

  // Clear current menu
  memset(menuOptions, 0x00, sizeof(menuOptions)); // for automatically-allocated arrays
  memcpy(menuOptions, menuValues, menuSize);

  // Show what we did?
  if (false) {
    Serial.print  (menuOpt);

    Serial.print  (F(" Size ["));
    Serial.print  (menuSize);
    Serial.print  (F("] menuOptions[...] "));
    //for (byte loop = 0; loop < sizeof(menuOptions); loop++) {
    for (byte loop = 0; loop < menuSize; loop++) {
      Serial.print  (menuOptions[loop]);
      if ((loop+1) < menuSize){
        Serial.print  (", ");
      }
    }
    Serial.println();
  }
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


void Menu::setVisible(){
    lcd.setCursor(15, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_set));
}

// ===========================================
// Reserved
// ===========================================
void Menu::lcdMenu000() { // this is an error, 000 is reserved  
    lcd.setCursor(6, 1);//   row >    column ^
    lcd.print(PGMSTR(ERR000));    
    Serial.println(PGMSTR(ERR000));
    while (true){
      }
}

// ===========================================
// Main Menu
// ===========================================
// -------------------------------------------
void Menu::lcdMenu001() {
  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Main"));
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print(F("lcdMainVolts: "));
    lcd.setCursor(0, 2); //   row >    column ^
    lcd.print(F("lcdKeyVolts: "));  
    lcd.setCursor(0, 3); //   row >    column ^
    lcd.print(F("Misc: "));
    lcd.setCursor(7, 3); //   row >    column ^
    lcd.print(F("Repeat: "));
    lcd.print(showFPS);
    lcd.print("  ");
  }

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
}

// ===========================================
// Transmitter Items
// ===========================================
// -------------------------------------------
void Menu::lcdMenu002() {
  if (repeatCount == 0) {
  }




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
void Menu::lcdMenu003() {
  if (repeatCount == 0) {
  }

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
void Menu::lcdMenu010() {
  if (repeatCount == 0) {
    lcd.setCursor(1, 0); //   row >    column ^
    lcd.print(F("10 -> 11"));
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(F("10 -> 12"));
    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(F("10 -> 13"));
    lcd.setCursor(1, 3); //   row >    column ^
    lcd.print(F("10 -> 14"));
    lcd.print(F(" Repeat: "));
  }

  //  lcd.setCursor(17, 1); //   row >    column ^
  //  lcd.print(repeatCount);
  //  lcd.print(" ");
}

// -------------------------------------------
void Menu::lcdMenu011() {
  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x11"));
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(F("Repeat: "));
  }

  lcd.setCursor(10, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(F(" "));
}

// -------------------------------------------
void Menu::lcdMenu012() {
  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x12"));
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(F("Repeat: "));
  }

  lcd.setCursor(10, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(F(" "));
}

void Menu::lcdMenu013() {
  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x13"));
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(F("Repeat: "));
  }

  lcd.setCursor(10, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(" ");
}


// -------------------------------------------
//void lcdMainFlightTime(){
void Menu::lcdMenu014() {
  // check to see if it's time to update LCD; that is, if the difference
  // between the current time and last time you updated the LCD is bigger than
  // the interval at which you want to blink the LED.

  if (repeatCount == 0)
  {
//    lcd.setCursor(0, 0); //   row >    column ^
//    lcd.print(F("x014"));
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(F("Repeat: "));
  }
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
//  }
  lcd.setCursor(10, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(F(" "));
}

// ===========================================
// Models Items
// ===========================================


// ===========================================
// System Items
// ===========================================
// -------------------------------------------
void Menu::lcdSys102() { // Vin pre 1.1 & 1.2 ohms

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

  }
  
  if (repeatCount == 0) {

    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys102_Vpre));
    
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys102_R11));    
    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys102_R12));          
  }

  if (displayMask[menuCol].getIncDirection() != 0 || repeatCount == 0){
    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
    
    // Calculate and display Volt/Bit
    lcd.setCursor(displayMask[2].getDisplayPos(), 2); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[2].getVoidPointer(), displayMask[2].getMaskPMG())); 
  }
  
}

// -------------------------------------------
void Menu::lcdSys104() { // Vin pst 2.1 & 2.2 ohms

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

  }

  if (repeatCount == 0) {

    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys104_Vpst));
    
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys104_R21));    
    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys104_R22));         
  }

  if (displayMask[menuCol].getIncDirection() != 0 || repeatCount == 0){

    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
    
    // Calculate and display Volt/Bit
    lcd.setCursor(displayMask[2].getDisplayPos(), 2); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[2].getVoidPointer(), displayMask[2].getMaskPMG()));
  }
}

// -------------------------------------------
void Menu::lcdSys106() { // V5.0    3.1 & 3.2 ohms

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

  }

  if (repeatCount == 0) {

    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys106_V5div));
    
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys106_R31));    
    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys106_R32));            
  }

  if (displayMask[menuCol].getIncDirection() != 0 || repeatCount == 0){

    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
    
    // Calculate and display Volt/Bit
    lcd.setCursor(displayMask[2].getDisplayPos(), 2); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[2].getVoidPointer(), displayMask[2].getMaskPMG()));
  }
}


// -------------------------------------------
void Menu::lcdSys112() { // Shunt ohms

  if (isMenuChange){ 

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

  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys112_Shunt));
    
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys112_Rshnt));         
  }

  if (displayMask[menuCol].getIncDirection() != 0 || repeatCount == 0){

    // Display measured reference voltage
    lcd.setCursor(displayMask[1].getDisplayPos(), 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)displayMask[1].getVoidPointer(), displayMask[1].getMaskPMG()));
  }
  
}

// -------------------------------------------
void Menu::lcdSys114() { // V5.0 Reference voltage

  if (isMenuChange){ 
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
  
  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys114_5Vref));

    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys114_5Vmes));
    
    lcd.setCursor(1, 3); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys114_v5bit));
  }

  if (displayMask[menuCol].getIncDirection() != 0 || repeatCount == 0){
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
void Menu::lcdSys122() { // Switch

  if (isMenuChange){ 

    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    //displayMask[1].doMaskInit(ohm_x_xxxxO, '#', 11, &data->getMySwitchMap().switchSW);
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    //displayMask[2].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().V5_32);
    // data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    //displayMask[2].doMaskInit(

  }


  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys122_Switch));
    
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Digits));              

    lcd.setCursor(11, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Pos));         

    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Values));              
  }
 
    // Display switches as bin (0's and 1's)
    lcd.setCursor(11, 2); //   row >    column ^
    lcd.print( display.outputBinary( data->getMySwitchMap().switchPins));
}

// -------------------------------------------
void Menu::lcdSys124() { // Trim
  
  if (isMenuChange){ 

    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    //displayMask[1].doMaskInit(ohm_x_xxxxO, '#', 11, &data->getMySwitchMap().trimBTN);
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    //displayMask[2].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().V5_32);
    // data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    //displayMask[2].doMaskInit(

  }

  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys124_Trim));
    
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Digits));              

    lcd.setCursor(11, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Pos));         

    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Values));       
  }

    // Display switches as bin (0's and 1's)
    lcd.setCursor(11, 2); //   row >    column ^
    lcd.print( display.outputBinary( data->getMySwitchMap().trimPins));

}

// -------------------------------------------
void Menu::lcdSys126() { // Menu buttons
  if (isMenuChange){ 

    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    //displayMask[1].doMaskInit(ohm_x_xxxxO, '#', 11, &data->getMySwitchMap().menuSW);
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
    //displayMask[2].doMaskInit(ohm_xx_xxxO, '#', 12, &data->getMyResistorMap().V5_32);
    // data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    //displayMask[2].doMaskInit(

  }


  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdSys126_Menu));
    
    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Digits));              

    lcd.setCursor(11, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Pos));         

    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_Values));        
  }
  
  // Display switches as bin (0's and 1's)
  lcd.setCursor(11, 2); //   row >    column ^
  lcd.print( display.outputBinary( data->getMySwitchMap().menuPins));

}


// -------------------------------------------
void Menu::lcdSys132() { // Joystick range limits  (Find MID point, release stick and press 'Select')

  if (isMenuChange){ 

    // load DisplayMask[0-3] data pointers

    // 0
    //displayMask[0].doMaskInit(

    // 1
    displayMask[1].doMaskInit(digits8, '#', 11, &data->getMyControlsRangeMap(editJoyStick));
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

    // 2
//    displayMask[2].doMaskInit(joyStickxxxx, '#', 1, &data->getJoyStick(0));
    // data->setUint16_tPointer(displayMask[2].getVoidPointer());

    // 3
    displayMask[3].doMaskInit(joyStickxxxx, '#', 1, &data->getMyControlsRangeMap(editJoyStick));
    // data->setUint16_tPointer(displayMask[1].getVoidPointer());

  } else {
      lcd.noBlink();  
  }

  if (isMenuChange || isFuncChange){    //lcd.print(PGMSTR(lcd_param_common_Joystick));
    lcd.setCursor(0, 0); //   row >    column ^
    switch(editJoyStick){
      case 0:
        lcd.print(PGMSTR(lcd_param_lcdSys132_Throttle));
        break;
      case 1:
        lcd.print(PGMSTR(lcd_param_lcdSys132_YAW));
        break;
      case 2:
        lcd.print(PGMSTR(lcd_param_lcdSys132_ROLL));
        break;
      case 3:
        lcd.print(PGMSTR(lcd_param_lcdSys132_PITCH));
        break;
      }    
    }
    
    lcd.setCursor(1, 1); //   row >    column ^
        
    //lcd.print(PGMSTR(lcd_param_common_Joystick));
    if (menuAction == doFunc){

        switch(editJoyStick){
          case 0:
          case 3:
            lcd.print(PGMSTR(lcd_param_common_UD));
            break;
          case 1:
          case 2:
            lcd.print(PGMSTR(lcd_param_common_LR));
            break;
        }         
    } else {
      lcd.print(PGMSTR(lcd_param_common_Set));  
      lcd.print("          ");  
    }
    
    lcd.setCursor(1, 2); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_common_MMM));              



  // Display XMIT value as ###
  MyControlsRangeMap myControlsRangeMap1 = *(MyControlsRangeMap*)displayMask[1].getVoidPointer();

  lcd.setCursor(16, 1); //   row >    column ^
  lcd.print(display.outputDigitsU16(      
      // data->getJoyStick(myControlsRangeMap1)                 , //displayMask[1].getVoidPointer(),      
      // data->getJoyStick(*(MyControlsRangeMap*)displayMask[1].getVoidPointer())                 , //displayMask[1].getVoidPointer(),    
      myControlsRangeMap1.joystickRange(),
      displayMask[1].getMaskPMG(), 2));

  // ============================================
  MyControlsRangeMap myControlsRangeMap3 = *(MyControlsRangeMap*)displayMask[3].getVoidPointer();
  
  // Display CURRENT as ####
  lcd.setCursor(1, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myControlsRangeMap3.current, displayMask[3].getMaskPMG(),1) );

  // Display MIN as ####
  lcd.setCursor(6, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myControlsRangeMap3.minimum, displayMask[3].getMaskPMG(),1) );

  // Display CENTER as ####
  lcd.setCursor(11, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myControlsRangeMap3.center, displayMask[3].getMaskPMG(),1) );

  // Display MAX as ####
  lcd.setCursor(16, 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(myControlsRangeMap3.maximum, displayMask[3].getMaskPMG(),1) );
  
}

// -------------------------------------------
void Menu::lcdSys148() { // Reset
  if (repeatCount == 0) {
    // load data pointers
  }
  
  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Reset"));
  }
}



//===========================================
// Init - Startup 
//===========================================

// -------------------------------------------
void Menu::lcdInit150() {  // Starting   [click (select) out to 150]
  
  menuAction = doInit;  
    
  if (repeatCount == 0) {
    lcd.init();
    lcd.begin(20,4);
    lcd.backlight();
  //lcd.blink();  //lcd.noBlink();
    
    lcd.setCursor(6, 1);//   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit150_startUp));    
  }
  
  if (repeatCount > 2) { // ~delay(250);
      menuKeyboard(SELECT);
  }
}

// -------------------------------------------
void Menu::lcdInit151() { // Splash     [no click 'select button' out to 151]

  menuAction = doInit;

  if (repeatCount == 0) 
  {
    lcd.setCursor(0, 0);//   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit151_qBytesWorld));
    lcd.setCursor(0, 1);//   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit151_deviceInfo));
    lcd.setCursor(0, 2);//   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit151_versionNum));
  }

  if (true){ // Can delete this condition when (no EEPROM data) is completed.
    lcd.setCursor(0, 3);//   row >    column ^
    if ((repeatCount/2)%2 == 0){// If ODD.
      lcd.print("Finish EEPROM...");
    }else{
      lcd.print("                ");
    }
  }
  
  if (repeatCount > 12) {//delay(2000);    
     // If first time run (no EEPROM data)
    if (true){// DAQ finish this..(assume first time)..need to read the EEPROM data to know if it is 1st time
        menuKeyboard(DOWN);  // menuSelected = 252; // Initialize values
    } else {
        menuKeyboard(DOWN);
        menuKeyboard(DOWN);  //menuSelected = CTLCHECK = 192; // Go to Control check before Main Menu 
    }
    menuAction = doMenu;
    menuKeyboard(SELECT);
  }
}


// -------------------------------------------
void Menu::lcdInit192() { // Control check
  if (repeatCount == 0) {
    // load data pointers
  }

  if (repeatCount == 0) {
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit192_controlCheck));
  }
  if (repeatCount > 3) {//delay(2000);

// DAQ finish this....
// DAQ finish this....
// DAQ finish this....

     // If Controls not home, wait.
    if (false){
      menuSelected = MAINMENU; // Main
    }
  } 

  lcd.setCursor(1, 3);//   row >    column ^
  lcd.print(PGMSTR(lcd_param_lcdInit192_volts));

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
      Serial.print  ("IncDirection ");
      Serial.print  (displayMask[menuCol].getIncDirection());
      Serial.print  (" Expo ");
      Serial.print  (displayMask[menuCol].getExpoValue());

       data->setUint16_tPointer(displayMask[menuCol].getVoidPointer());
//       data->adjUint16_tNumber(displayMask[menuCol].getIncDirection() * displayMask[menuCol].getExpoValue());  // delete-comment this

       data->adjUint16_tNumber(displayMask[menuCol].getIncDirection(), displayMask[menuCol].getExpoFactor());

      Serial.println();
    } else {
      // Attempt to change number, "displayMask[menuCol].getMask()" or "displayMask[menuCol].getVoidPointer()" is NULL.
      Serial.println(PGMSTR(ERR216_0));
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
void Menu::lcdFunc238() { // T/F

//  if (repeatCount == 0) {
//  }

  // 1234567890123456789012345678901234567890
  // Erase all transmitter data? y/n
  // Factory Reset? Y/N
//  lcd.setCursor(9, 1); //   row >    column ^
//  lcd.setCursor(myMenuData.row[menuCol] + editRow, 1 + editCol);//   row >    column ^

  // If Y, goto x239
  // If N, goto mainMenu
}

// -------------------------------------------
void Menu::lcdFunc239() { // Y/N
//  if (repeatCount == 0) {
//  }

  // 1234567890123456789012345678901234567890
  // Erasing all transmitter data!!!
  // Reseting to Factory!
  lcd.setCursor(9, 1); //   row >    column ^

  // Read the eprom to see if it is clear
  if (false){// Read the eprom to see if it is clear
//    dataStore.factoryReset();
  }
  
  if (repeatCount > 1) { // ~delay(250);
    menuSelected = STARTMENU;
  }

  // exit to xSTARTMENU
}

// -------------------------------------------
void Menu::lcdFunc240() { // Controls Range

  if (isFuncChange){   
   data->getMyControlsRangeMap(editJoyStick).setCenter(); 
  }

   data->getMyControlsRangeMap(editJoyStick).setMinMax();

  lcdSys132();
  
//  if (repeatCount == 0) {  }
  
}

//===========================================
// Reserved
//===========================================
void Menu::lcdInit255() { // this is an error, 255 is reserved 
  lcd.setCursor(6, 1);//   row >    column ^
  lcd.print(PGMSTR(ERR255));   
  Serial.println(PGMSTR(ERR255));

  digitalWrite(1, HIGH); // LED and Sound on
  while (true){
    }
}

