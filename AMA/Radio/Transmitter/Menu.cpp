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
 *   1 -  49 = Transmitter
 *  50 -  99 = Model
 * 100 - 149 = System (Resistors, Voltages)
 * 200 - 254 = Functions
 *       255 = Reserved
 */


// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
Menu::Menu(Data * data){
  // initialize this instance's variables
  _data = data;

  // do whatever is required to initialize the library
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void Menu::clearMyMenuData(){
//Serial.println("clearMyMenuData");  
  myMenuData.row[0] = 0;
  myMenuData.row[1] = 0;
  myMenuData.row[2] = 0;
  myMenuData.row[3] = 0;
  myMenuData.pgmData[0] = NULL;
  myMenuData.pgmData[1] = NULL;
  myMenuData.pgmData[2] = NULL;
  myMenuData.pgmData[3] = NULL;
  myMenuData.pVoid[0] = NULL;
  myMenuData.pVoid[1] = NULL;
  myMenuData.pVoid[2] = NULL;
  myMenuData.pVoid[3] = NULL;
}
 
boolean Menu::isScreenRefreshNeeded(){
  unsigned long currentMillis = millis();

  if (currentMillis > (screenLastRefresh + screenRefresh)){
    screenLastRefresh = currentMillis;
    return true;
  }

 return false  ;
}

/////////////////////////////////////////////////////////////////////
uint16_t deltaNumber = 0;
  
void Menu::menuDisplay(){

  // We always display the MENU

  // Menu Switch\Case
  switch (menuSelected) {
    // ---------------------------------------
    case 1: //MAINMENU
      lcdMenu001();
      break;
    // ---------------------------------------
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
    case 14:      //  updateFPS();
      lcdMenu014();
      break;

    // ---------------------------------------
    // -----------   Functions   -------------
    // ---------------------------------------
    // Do NOT go here...
    // Do NOT go here...
    // Do NOT go here...

    // ---------------------------------------
    // -----------  Initialize   -------------
    // ---------------------------------------
    case 240: // Control Check
      lcdInit240();
      break;
    // ---------------------------------------
    case 244: // Joysticks
      lcdInit244();
      break;
    // ---------------------------------------
    case 245: // Shitch
      lcdInit245();
      break;
    // ---------------------------------------
    case 246: // Trim
      lcdInit246();
      break;
    // ---------------------------------------
    case 247: // Menu
      lcdInit247();
      break;
    // ---------------------------------------
    case 248: // Shunt
      lcdInit248();
      break;
    // ---------------------------------------
    case 249: // Pre 1.1 1.2
      lcdInit249();
      break;
    // ---------------------------------------
    case 250: // Post 2.1 2.2
      lcdInit250();
      break;
    // ---------------------------------------
    case 251: // v5.0 3.1 3.2
      lcdInit251();
      break;
    // ---------------------------------------
    case 252: // 5.0V reg voltage
      lcdInit252();
      break;
    // ---------------------------------------
    case 253: // Splash
      lcdInit253();
      break;
    // ---------------------------------------
    case 254: // Start up
      lcdInit254();    
      break;
    // ---------------------------------------
    default:
      // catch all - N/A
      Serial.print  (F("Menu not found Error: " ));
      Serial.print  (menuSelected);
      Serial.println(" - reset");
      menuSelected = 254;
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
    if (menuOptions[menuCol] >= 200 && menuOptions[menuCol] < 239){
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
  
  clearMyMenuData();
  menuCol = 0;  
     
  isMenuChange=true;
  repeatCount = 0;
  menuDisplay();
}

void Menu::funcKeyboard(byte keyPress){
  
  // If not FUNCTION, leave
  if (menuAction != doFunc){ // Should not be here if a MENU is active.
    return;
  }

  // If no key pressed, leave
  if (keyPress == NOKEY ){
    deltaNumber = 0;    
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
    editCol = 0;
    editRow = 0;
    
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
    myMenuData.row[1] = 12;
    myMenuData.pgmData[1] = volts_x_xxxV;
    myMenuData.pVoid[1] = &_data->getMyResistorMap().shunt;
 */
 
//  Serial.println("=================================================");
//  char buffer[20];
//  sprintf_P(buffer, PSTR("%S") , mask);
//  edit.doMaskEdit(keyPress , buffer); 
//  Serial.println("=================================================");
//  const char * pttr = myMenuData.pgmData[1];
//  edit.doMaskEdit(keyPress , pttr, '#',0); 

//volts_0_0xxxxxV[] = " 0.0#####V";
//digits32
//ohm_xx_xxxO[] = {'#','#','.','#','#','#',char(244),char(0)};

//#define ABC
#ifdef ABC
// edit.doMaskInit(myMenuData.pgmData[1], '#', 10);
Serial.println("Init -----------------------------------------------");
  edit.doMaskInit(myMenuData.pgmData[1], '#', 13);
 Serial.println("Init Complete");
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 

  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
Serial.println("Init -----------------------------------------------");
  edit.doMaskInit(volts_0_0xxxxxV, '#', 12);
 Serial.println("Init Complete");
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 

  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT);   
//=================================================
Serial.println("Init -----------------------------------------------");

 edit.doMaskInit(digits32, '#', 7);
 Serial.println("Init Complete");
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 
  
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(RIGHT); 
  edit.doMaskEdit(RIGHT); 

  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
  edit.doMaskEdit(LEFT); 
#endif
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

  setVisible();
  lcd.blink();    
}

void Menu::funcDisplay(){

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
     */
     
    // ---------------------------------------
    // ------------  Functions  --------------
    // ---------------------------------------
    case 200: // Int number edit
      lcdFunc200();
      break;
    // ---------------------------------------
    case 201: // Double number edit
      lcdFunc201();
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
    default:
      // catch all - N/A
      Serial.print  (F("Function not found Error: " ));
      Serial.print  (function);
      Serial.println(" - reset");
      menuSelected = 254;
      break;    
  }

  // edit format

  lcd.setCursor(myMenuData.row[menuCol] , menuCol);//   row >    column ^
}

void Menu::updateLCD(byte keyPress, int fps) {

  menuDisplay();

  if (menuAction == doMenu || menuAction == doInit){
    // MENU mode
    menuKeyboard(keyPress);    
  } else {
    // FUNCTION mode
    funcKeyboard(keyPress);
    funcDisplay(); 
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
  Serial.print  (myMenuData.row[menuCol]);

  Serial.print  (" mc  ");
  Serial.print  (menuCol);  
  Serial.print  (" mr  ");
  Serial.print  (menuRow);  
  
  Serial.print  (" ec  ");
  Serial.print  (editCol);
  Serial.print  (" er  ");
  Serial.print  (editRow);
  
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

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

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
    setMenu(F("x001"), menuOptions001, membersof(menuOptions001));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Main"));
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print(F("lcdMainVolts: "));
    lcd.setCursor(0, 2); //   row >    column ^
    lcd.print(F("lcdKeyVolts: "));  
    lcd.setCursor(0, 3); //   row >    column ^
    lcd.print(F("Misc: "));
    lcd.setCursor(9, 3); //   row >    column ^
    lcd.print(F("Repeat: "));
  }

////  double shunt = 0.766327;   // 0.5   
//    pUInt1 = &myResistorMap.shunt; // = (0.766327*10000);   // 0.5
//    pUInt2 = &myResistorMap.shunt;  // = 2638; // 2.7k
//  }
//
//  lcd.setCursor(6, 1); //   row >    column ^
//  lcd.print(display.outputDigitsU16(*pUInt1, ohm_x_xxxxO));

  
  uint8_t batPercent = (int)((double)repeatCount*3.5);
  customChar.percent(batPercent);
  lcd.setCursor(11, 0); //   row >    column ^
  lcd.print(F("Bat:"));  
  lcd.print(display.outputDigitsU8(batPercent, digits8));//  lcd.print(display.outputDigitsU16(v5_voltPerBit, volts_0_0xxxxxV));
  customChar.showChar();

  lcd.setCursor(16, 3); //   row >    column ^
//  lcd.print(repeatCount);
  lcd.print(display.outputDigitsU8(repeatCount, digits8));  
//  lcd.print(F(" "));
}

// ===========================================
// Main Items
// ===========================================
// -------------------------------------------
void Menu::lcdMenu002() {
  if (repeatCount == 0) {
    setMenu(F("x002"), menuOptions002, membersof(menuOptions002));
  }


  // 0 = x0 = Aux0,
  // 2 = x1 = Aux1,
  // 4 = x2 = Aux2,
  // 6 = x3 = Aux3

  // 1 = y0 = Post,
  // 3 = y1 = Key
  // 5 = y2 = 5V
  // 7 = y3 = Pre

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
    setMenu(F("x003"), menuOptions003, membersof(menuOptions003));
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
    setMenu(F("x010"), menuOptions010, membersof(menuOptions010));
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
    setMenu(F("x011"), menuOptions011, membersof(menuOptions011));
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
    setMenu(F("x012"), menuOptions012, membersof(menuOptions012));
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
    setMenu(F("x013"), menuOptions013, membersof(menuOptions013));
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
//void updateFPS(){
void Menu::lcdMenu014() {
  // check to see if it's time to update LCD; that is, if the difference
  // between the current time and last time you updated the LCD is bigger than
  // the interval at which you want to blink the LED.

  if (repeatCount == 0)
  {
    setMenu(F("x014"), menuOptions014, membersof(menuOptions014));
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


//    if (cntMillis >= (1000 / screenRefresh))
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
//fix      lcd.print(fps);  // ~300 has been the average
      lcd.print(F("   GPS: xxx"));

      // -------------------------------------
//fix      fps = 0;
      cntMillis = 0;
    }
//  }
  lcd.setCursor(10, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(F(" "));
}

//===========================================
// Functions
//===========================================
// -------------------------------------------
void Menu::lcdFunc200() { // UInt number edit
//  if (repeatCount == 0) {
//    setMenu(F("x200"), menuOptions200, membersof(menuOptions200));
//  }

  if (myMenuData.pVoid[1] != NULL){
    // Display measured voltage
    lcd.setCursor(myMenuData.row[1], 1); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)myMenuData.pVoid[1], volts_x_xxxV, 1));
  }
  if (myMenuData.pVoid[3] != NULL){
    // Calculate and display Volt/Bit
    lcd.setCursor(myMenuData.row[3], 3); //   row >    column ^
    lcd.print(display.outputDigitsU16(*(uint16_t*)myMenuData.pVoid[3], volts_0_0xxxxxV));
  }
  Serial.println("lcdFunc200");
}


// MS1:252 MS2:201

// -------------------------------------------
void Menu::lcdFunc201() { //Double number edit
//  if (repeatCount == 0) {
//    setMenu(F("x201"), menuOptions201, membersof(menuOptions201));
//  }
  // #include<stdlib.h>
  //  dtostrf(FLOAT,WIDTH,PRECSISION,BUFFER);

//  char *r = dtostrf(changeMe, 8, 2, buffer);
//  if (true){
//    Serial.print  (buffer);
//    Serial.print  (" r:");
//    Serial.print  (r);
//    Serial.println(":");
//  }
//  lcd.setCursor(3, 1); //   row >    column ^
//lcd.print(buffer);


////if (myMenuData.pVoid[1] != NULL){
////    // Display measured voltage
////    lcd.setCursor(myMenuData.row[1], 1); //   row >    column ^
////    lcd.print(display.outputDigitsU16(*(uint16_t*)myMenuData.pVoid[1], volts_x_xxxV, 1));
////  }
////  
////  if (myMenuData.pVoid[3] != NULL){
////    // Calculate and display Volt/Bit
////    lcd.setCursor(myMenuData.row[3], 3); //   row >    column ^
////    lcd.print(display.outputDigitsU16(*(uint16_t*)myMenuData.pVoid[3], volts_0_0xxxxxV));
////  }



  //    _data->setUint16_tPointer(myMenuData.pVoid[1]);
  if (deltaNumber != 0){
    if (myMenuData.pVoid[1] != NULL){
      _data->adjUint16_tNumber(deltaNumber);
      Serial.println("lcdFunc201");
    } else {
      Serial.println("myMenuData.pVoid[1] = NULL");  
    }
  }
  
}


// -------------------------------------------
void Menu::lcdFunc238() {

//  if (repeatCount == 0) {
//    setMenu(F("x238"), menuOptions238, membersof(menuOptions238));
//    lcd.setCursor(0, 0); //   row >    column ^
//    lcd.print(F("x238"));
//  }

  // 1234567890123456789012345678901234567890
  // Erase all transmitter data? y/n
  // Factory Reset? Y/N
//  lcd.setCursor(9, 1); //   row >    column ^
  lcd.setCursor(myMenuData.row[menuCol] + editRow, 1 + editCol);//   row >    column ^

  // If Y, goto x239
  // If N, goto mainMenu
}

// -------------------------------------------
void Menu::lcdFunc239() {
//  if (repeatCount == 0) {
//    setMenu(F("x239"), menuOptions239, membersof(menuOptions239));
//    lcd.setCursor(0, 0); //   row >    column ^
//    lcd.print(F("x239"));
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
    menuSelected = 254;
  }

  // exit to x254
}


//===========================================
// Init
//===========================================
// -------------------------------------------
void Menu::lcdInit240() { // Control check
  if (repeatCount == 0) {
    // load data pointers
  }

  if (repeatCount == 0) {
    setMenu(F("x240"), menuOptions240, membersof(menuOptions240));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Control check"));
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
  lcd.print(PGMSTR(lcd_param_lcdInit240_volts));
  
  lcd.setCursor(8, 3);//   row >    column ^
  //lcd.print(display.output_x_xxxV(v5_System * 1000));    

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(v5_System * 100, volts_x_xxxV, 1));
}

// -------------------------------------------
void Menu::lcdInit244() { // Menu buttons
  if (repeatCount == 0) {
    // load data pointers
  }

  if (repeatCount == 0) {
    setMenu(F("x244"), menuOptions244, membersof(menuOptions244));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Menu Buttons"));  // Not using these?????
  }
}

// -------------------------------------------
void Menu::lcdInit245() { // Trim
  if (repeatCount == 0) {
    // load data pointers
  }

  if (repeatCount == 0) {
    setMenu(F("x245"), menuOptions245, membersof(menuOptions245));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Trim"));
  }
}

// -------------------------------------------
void Menu::lcdInit246() { // Switch
  if (repeatCount == 0) {
    // load data pointers
  }

  if (repeatCount == 0) {
    setMenu(F("x246"), menuOptions246, membersof(menuOptions246));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Switch"));
  }
}

// -------------------------------------------
void Menu::lcdInit247() { // Joystick
  if (repeatCount == 0) {
    // load data pointers
  }
  
  if (repeatCount == 0) {
    setMenu(F("x247"), menuOptions247, membersof(menuOptions247));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Joystick"));
  }
}

// -------------------------------------------
void Menu::lcdInit248() { // Shunt ohms
  if (repeatCount == 0) {
    // load data pointers
    setMenu(F("x248"), menuOptions248, membersof(menuOptions248));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Shunt"));
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print(F("ohms "));    

//  double shunt = 0.766327;   // 0.5   

//fix
//fix
//fix    pUInt1 = &myResistorMap.shunt; // = (0.766327*10000);   // 0.5

//fix
//fix
//fix    pUInt2 = &myResistorMap.shunt;  // = 2638; // 2.7k
  }

  lcd.setCursor(6, 1); //   row >    column ^

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(*pUInt1, ohm_x_xxxxO));
  lcd.setCursor(6, 2); //   row >    column ^

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(*pUInt2, ohm_x_xxxxO));
}

// -------------------------------------------
void Menu::lcdInit249() { // V5.0    3.1 & 3.2 ohms
  if (repeatCount == 0) {
    setMenu(F("x249"), menuOptions249, membersof(menuOptions251));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("5V ohm divider"));
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print(F("3.1 "));    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print(F("3.2 "));    


//fix
//fix
//fix    pUInt1 = &myResistorMap.V5_31;  //   = 2161; // 2.2k   

//fix
//fix
//fix    pUInt2 = &myResistorMap.V5_32;  //   = 3212; // 3.3k 
  }

  lcd.setCursor(6, 1); //   row >    column ^

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(*pUInt1, ohm_xx_xxxO));
  lcd.setCursor(6, 2); //   row >    column ^

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(*pUInt2, ohm_xx_xxxO));
}

// -------------------------------------------
void Menu::lcdInit250() { // Vin pst 2.1 & 2.2 ohms
  if (repeatCount == 0) {
    setMenu(F("x250"), menuOptions250, membersof(menuOptions250));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Vin post ohms"));
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print(F("2.1 "));    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print(F("2.2 "));    
  

//fix
//fix
//fix    pUInt1 = &myResistorMap.Vpst21;  // = 8014; // 8.2k

//fix
//fix
//fix    pUInt2 = &myResistorMap.Vpst22;  // = 2637; // 2.7k 
  }

  lcd.setCursor(6, 1); //   row >    column ^

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(*pUInt1, ohm_xx_xxxO));
  lcd.setCursor(6, 2); //   row >    column ^

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(*pUInt2, ohm_xx_xxxO));

}

// -------------------------------------------
void Menu::lcdInit251() { // Vin pre 1.1 & 1.2 ohms

  if (isMenuChange){
    // load data pointers
    myMenuData.row[1] = 12;
    myMenuData.pgmData[1] = volts_x_xxxV;
    myMenuData.pVoid[1] = &_data->getMyResistorMap().shunt;

    myMenuData.row[2] = 12;
    myMenuData.pgmData[2] = volts_x_xxxV;
    myMenuData.pVoid[2] = &_data->getMyResistorMap().shunt;

   // ========================================  
//    Serial.println(PGMSTR(myMenuData.pgmData[0]));
//    
//    Serial.println("----->     adjUint16_tNumber");
//    Serial.println(*(uint16_t*)myMenuData.pVoid[0]);
    _data->setUint16_tPointer(myMenuData.pVoid[1]);

//    _data->adjUint16_tNumber(1);
//    Serial.println(*(uint16_t*)myMenuData.pVoid[0]);
  }  
  
  if (repeatCount == 0) {
    setMenu(F("x251"), menuOptions251, membersof(menuOptions251));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Vin pre ohms"));
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print(F("1.1 "));    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print(F("1.2 "));          
  

//fix
//fix
//fix    pUInt1 = &myResistorMap.Vpre11;  // = 8042; // 8.2k

//fix
//fix
//fix    pUInt2 = &myResistorMap.Vpre12;  // = 2638; // 2.7k
  }

  lcd.setCursor(6, 1); //   row >    column ^

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(*pUInt1, ohm_xx_xxxO));
  lcd.setCursor(6, 2); //   row >    column ^

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(*pUInt2, ohm_xx_xxxO));
}

// -------------------------------------------
void Menu::lcdInit252() {  // V5.0    Regulator Reference

  if (isMenuChange){ 
    // load data pointers
    myMenuData.row    [1] = 13;
    myMenuData.pgmData[1] = volts_x_xxxV;
    myMenuData.pVoid  [1] = &_data->getMyVoltageMap().reference;

    myMenuData.row    [3] = 10;
    myMenuData.pgmData[3] = volts_0_0xxxxxV;
    myMenuData.pVoid  [3] = &_data->getMyVoltageMap().voltPerBit;


//  // test test test
//  // test test test
//  // test test test
//  // test test test
//  // test test test
//  (*(uint16_t*)myMenuData.pVoid[1]) = (*(uint16_t*)myMenuData.pVoid[1]) + 1;
  // daqdaqdaqdaq
//    Serial.println("----->     adjUint16_tNumber");
//    Serial.println(*(uint16_t*)myMenuData.pVoid[0]);
    _data->setUint16_tPointer(myMenuData.pVoid[1]);
//    _data->adjUint16_tNumber(1);
    }
  
  if (repeatCount == 0) {
    setMenu(F("x252"), menuOptions252, membersof(menuOptions252));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit252_5Vref));

    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit252_5Vmes));
    
    lcd.setCursor(1, 3); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit252_v5bit));
  }

 // Display measured reference voltage
  lcd.setCursor(myMenuData.row[1], 1); //   row >    column ^
  lcd.print(display.outputDigitsU16(*(uint16_t*)myMenuData.pVoid[1], volts_x_xxxV, 1));

  // Calculate and display Volt/Bit
  *(uint16_t*)&_data->getMyVoltageMap().voltPerBit = (*(uint16_t*)myMenuData.pVoid[1] / 1023.0) * 1000;
  lcd.setCursor(myMenuData.row[3], 3); //   row >    column ^
  lcd.print(display.outputDigitsU16(*(uint16_t*)myMenuData.pVoid[3], volts_0_0xxxxxV));
}

//===========================================
// Startup 
//===========================================
// -------------------------------------------
void Menu::lcdInit253() { // Splash     [no click 'select button' out to 253]

  menuAction = doInit;

  if (isMenuChange){  
    // load data pointers
  }
  
  if (repeatCount == 0) 
  {
    setMenu(F("x253"), menuOptions253, membersof(menuOptions253));    
    lcd.setCursor(0, 0);//   row >    column ^
    lcd.print(PGMSTR(qBytesWorld));
    lcd.setCursor(0, 1);//   row >    column ^
    lcd.print(PGMSTR(deviceInfo));
    lcd.setCursor(0, 2);//   row >    column ^
    lcd.print(PGMSTR(versionNum));
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
        menuKeyboard(DOWN);  //menuSelected = 240; // Go to Control check before Main Menu 
    }
    menuAction = doMenu;
    menuKeyboard(SELECT);
  }
}

// -------------------------------------------
void Menu::lcdInit254() {  // Starting   [click (select) out to 254]
  
  menuAction = doInit;  

  if (isMenuChange){  
    // load data pointers
  }
    
  if (repeatCount == 0) {
    setMenu(F("x254"), menuOptions254, membersof(menuOptions254));
    lcd.init();
    lcd.begin(20,4);
    lcd.backlight();
  //lcd.blink();  //lcd.noBlink();
    
    lcd.setCursor(6, 1);//   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit254_startUp));    
  }
  
  if (repeatCount > 2) { // ~delay(250);
      menuKeyboard(SELECT);
  }
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



