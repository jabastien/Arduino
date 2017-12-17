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

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
Menu::Menu(Data * data){
  // initialize this instance's variables
  _data = data;

  // do whatever is required to initialize the library
  _data->setAnalog(2,12);  
  Serial.println("Menu");
  Serial.println(_data->getAnalog(0));
  Serial.println(_data->getAnalog(1));
  Serial.println(_data->getAnalog(2));
  Serial.println(_data->getAnalog(3));
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void Menu::clearMyMenuData(){
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
//  myMenuData.pInt[0] = NULL;
//  myMenuData.pInt[1] = NULL;
//  myMenuData.pInt[2] = NULL;
//  myMenuData.pInt[3] = NULL;
}
 
boolean Menu::isScreenRefreshNeeded(){
  unsigned long currentMillis = millis();

  if (currentMillis > (screenLastRefresh + screenRefresh)){
    screenLastRefresh = currentMillis;
    return true;
  }

 return false  ;
}

void Menu::updateLCD(byte keyPress, int fps) {

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

  // Detect Menu change

  menuChange = false;

  if (menuCurrent != menuSelected) {
    menuChange = true;
//    clearMyEditorData(-1);
    clearMyMenuData();
    returnToCurrent = menuCurrent;
    if (true){
      Serial.print (F("C:"));
      Serial.print (menuCurrent);
      Serial.print (F(" S:"));
      Serial.print (menuSelected);
    }
    if (true){
      Serial.print (F(" Cur:"));
      Serial.print (menuCurrent);
      Serial.print (F(" Sel:"));
      Serial.print (menuSelected);
      Serial.print (F(" RTC:"));
      Serial.print (returnToCurrent);
      Serial.println();
    }

    // Don't clear the screen for FUNCTIONs
    if (menuSelected >= 200 && menuSelected <= 239){
      function = true;
      lcd.blink();
    } else {
      function = false;
      lcd.noBlink();
      lcd.clear();
    }
    
    repeatCount = 0;
    menuCol = 0;
    menuCurrent = menuSelected;
//
//    if (menuCurrent == MAINMENU || menuCurrent >= 250) {
//      lcd.noBlink();
//    } else {
//      lcd.blink();
//    }
  }

  if (function){
    setVisible();
  }

  if (keyPress != 0 ){
    // Key Select/Enter
    if (keyPress == 1) {
      Serial.print (F(" MS1:"));
      Serial.print (menuSelected);
      menuSelected = menuOptions[menuCol];
      Serial.print (F(" MS2:"));
      Serial.println(menuSelected);
    } else {
      // Menu operation
      if (!function){
        if (keyPress == 5) {// up
          if (menuCol > 0)
            menuCol--;
        }
        if (keyPress == 3) {// down
          if (menuCol < (menuSize-1))
            menuCol++;
        }
        if (keyPress == 4) {// right
          if (menuRow < 5)
            menuRow++;
        }
        if (keyPress == 2) {// left
          if (menuRow > 0)
            menuRow--;
        }
    
        if (true){
          Serial.print  (keyPress);
          Serial.print  (F(" R>:"));
          Serial.print  (menuRow);
          Serial.print  (F(" C^:"));
          Serial.println(menuCol);
        }
    
        // Carrot for menu select.
        if (menuCurrent != MAINMENU){
          for (byte b = 1; b<4;b++){
            lcd.setCursor(0, b);//   row >    column ^
            lcd.print (" ");
          }
          if (menuCol > 0){
            lcd.setCursor(0, menuCol);//   row >    column ^
            lcd.print (">");
          }
        }
      
      } else {
        // Function operation
        // Function for Edit
        if (keyPress == 5) {// up
          if (editCol > 0)
            editCol--;
        }
        if (keyPress == 3) {// down
          if (editCol < (menuSize-1))
            editCol++;
        }
        if (keyPress == 4) {// right
          if (editRow < 5)  // Replace '5' with field pattern size (allow moves only to '#' cells)
            editRow++;
        }
        if (keyPress == 2) {// left
          if (editRow > 0)
            editRow--;
        }       
      } 
    }
  }


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

  // Set Repeat Count
  //repeatCount;
  if (++repeatCount > 31) {
    repeatCount = 0;
  }
}

void Menu::setMenu(String menuOpt, byte menuValues[], byte sizeIs) {
  
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

  // Make sure FUNCTIONs don't have a child.
  if (menuValues[0] == FUNCTION && sizeIs > 1) {
    Serial.print  (F("Err: setMenu "));
    Serial.print  (sizeIs);
    Serial.print  (F(" for "));
    Serial.print  (menuOpt);
    sizeIs = 1; // degrade to prevent Array Overflow error
    Serial.print  (F(" funcion s/b = "));
    Serial.println(sizeIs);
  }
  
  // Need to find a way to retain 'menuCol' when returning?
  //  byte tempReturnToCurrent = menuOptions[0];
  
  menuSize = sizeIs;

  // Need to find a way to retain 'menuCol' when returning?

  if (menuValues[0] != FUNCTION){
    // Clear current menu
    memset(menuOptions, 0x00, sizeof(menuOptions)); // for automatically-allocated arrays
    memcpy(menuOptions, menuValues, menuSize);
    Serial.println(F("*** menuValue [0]"));
  } else {  
    if (returnToCurrent != MAINMENU){
      // Clear current menu
      memset(menuOptions, 0x00, sizeof(menuOptions)); // for automatically-allocated arrays
      menuOptions[0] = returnToCurrent;//tempReturnToCurrent;  --- fix this......
      Serial.println(F("*** menuValue [1]"));
      //    }
    } else {
      Serial.println(F("*** menuValue [2]"));
      returnToCurrent = menuOptions[0];
    }
  }

  // Show what we did?
  if (true) {
    Serial.print  (menuOpt);
    Serial.print  (F(" RTC="));
    Serial.print  (returnToCurrent);
 //   Serial.print  (" T/F=");
 //   Serial.print  (returnToCurrent);
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

  // Clear return to current   
  returnToCurrent = MAINMENU;
}

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

  
  uint8_t numb = (int)((double)repeatCount*3.5);
  customChar.percent(numb);
  lcd.setCursor(11, 0); //   row >    column ^
  
  lcd.print(F("Bat:"));  
//  lcd.print(numb);  
  lcd.print(display.outputDigitsU8(numb, digits8));//  lcd.print(display.outputDigitsU16(v5_voltPerBit, volts_0_0xxxxxV));
//  lcd.print(F("  "));
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

  lcd.setCursor(0, 1); //   row >    column ^
  lcd.print(F("Value: "));
//fix  lcd.print  (analog[3]);
  lcd.print(F("   "));

  //  lcd.setCursor(0, 2); //   row >    column ^
  //  lcd.print("Key Down: ");
  //  lcd.print  (keyDown);

  lcd.setCursor(0, 3); //   row >    column ^
  lcd.print(F("Key Pressed: "));
//fix  lcd.print  (keyPress);
}

// -------------------------------------------
void Menu::lcdMenu010() {
  if (repeatCount == 0) {
    setMenu(F("x010"), menuOptions010, membersof(menuOptions010));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("10 -> 11"));
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print(F("10 -> 12"));
    lcd.setCursor(0, 2); //   row >    column ^
    lcd.print(F("10 -> 13"));
    lcd.setCursor(0, 3); //   row >    column ^
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
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print(F("Repeat: "));
  }

  lcd.setCursor(9, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(F(" "));
}

// -------------------------------------------
void Menu::lcdMenu012() {
  if (repeatCount == 0) {
    setMenu(F("x012"), menuOptions012, membersof(menuOptions012));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x12"));
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print(F("Repeat: "));
  }

  lcd.setCursor(9, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(F(" "));
}

void Menu::lcdMenu013() {
  if (repeatCount == 0) {
    setMenu(F("x013"), menuOptions013, membersof(menuOptions013));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x13"));
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print(F("Repeat: "));
  }

  lcd.setCursor(9, 1); //   row >    column ^
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
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x014"));
    lcd.setCursor(0, 1); //   row >    column ^
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
      lcd.setCursor(0, 2); //   row >    column ^
      lcd.print(F("Channel:"));
      lcd.print(F(" xxx"));

      // -------------------------------------
      lcd.setCursor(0, 3); //   row >    column ^
      lcd.print(F("FPS:"));
//fix      lcd.print(fps);  // ~300 has been the average
      lcd.print(F("   GPS: xxx"));

      // -------------------------------------
//fix      fps = 0;
      cntMillis = 0;
    }
//  }
  lcd.setCursor(9, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(F(" "));
}




//===========================================
// Functions
//===========================================
// -------------------------------------------
void Menu::lcdFunc200() { // UInt number edit
  if (repeatCount == 0) {
    setMenu(F("x200"), menuOptions200, membersof(menuOptions200));

//    lcd.setCursor(0, 3); //   row >    column ^
//    lcd.print(F("Int number edit"));
    
  }

    
//  char buffer[10];         //the ASCII of the integer will be stored in this char array
//  itoa((int)changeMe,buffer,10); //(integer, yourBuffer, base)   

//  lcd.blink();
//  lcd.setCursor(5, 2); //   row >    column ^
  lcd.setCursor(5+editRow, 2+editCol);//   row >    column ^
  
//  lcd.print(buffer);
//fix  lcd.setCursor(5 + menuRow, 2); //   row >    column ^

}

// -------------------------------------------
void Menu::lcdFunc201() { //Double number edit
  if (repeatCount == 0) {
    setMenu(F("x201"), menuOptions201, membersof(menuOptions201));
    
//    lcd.setCursor(0, 3); //   row >    column ^
//    lcd.print(F("Double number edit"));
  }
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

//  lcd.setCursor(3 + menuRow, 1); //   row >    column ^
  lcd.setCursor(5+editRow, 2+editCol);//   row >    column ^

}


// -------------------------------------------
void Menu::lcdFunc238() {
  if (repeatCount == 0) {
    setMenu(F("x238"), menuOptions238, membersof(menuOptions238));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x238"));
  }

  // 1234567890123456789012345678901234567890
  // Erase all transmitter data? y/n
  // Factory Reset? Y/N
  lcd.setCursor(9, 1); //   row >    column ^

  // If Y, goto x239
  // If N, goto mainMenu
}

// -------------------------------------------
void Menu::lcdFunc239() {
  if (repeatCount == 0) {
    setMenu(F("x239"), menuOptions239, membersof(menuOptions239));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("x239"));
  }

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

  lcd.setCursor(0, 3);//   row >    column ^
  lcd.print(PGMSTR(lcd_param_lcdInit240_volts));
  
  lcd.setCursor(7, 3);//   row >    column ^
  //lcd.print(display.output_x_xxxV(v5_System * 1000));    

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(v5_System * 100, volts_x_xxxV, 1));
}

// -------------------------------------------
void Menu::lcdInit244() { // Menu buttons
  if (repeatCount == 0) {
    setMenu(F("x244"), menuOptions244, membersof(menuOptions244));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Menu Buttons"));  // Not using these?????
  }
}

// -------------------------------------------
void Menu::lcdInit245() { // Trim
  if (repeatCount == 0) {
    setMenu(F("x245"), menuOptions245, membersof(menuOptions245));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Trim"));
  }
}

// -------------------------------------------
void Menu::lcdInit246() { // Switch
  if (repeatCount == 0) {
    setMenu(F("x246"), menuOptions246, membersof(menuOptions246));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Switch"));
  }
}

// -------------------------------------------
void Menu::lcdInit247() { // Joystick
  if (repeatCount == 0) {
    setMenu(F("x247"), menuOptions247, membersof(menuOptions247));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(F("Joystick"));
  }
}

// -------------------------------------------
void Menu::lcdInit248() { // Shunt ohms
  if (repeatCount == 0) {
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

//int testtest = 16321; 
//int* pint; //pint=(int*)data; ++(*pint);
//int temp;
// -------------------------------------------
void Menu::lcdInit252() {  // V5.0    Regulator Voltage
  if (menuChange){
    myMenuData.row[0] = 1;
    myMenuData.pgmData[0] = volts_x_xxxV;
    myMenuData.pVoid[0] = &_data->getMyResistorMap().shunt;

    Serial.println("--------------------------");
    
    Serial.println("----->     _data->getMyResistorMap().shunt");
    Serial.println(_data->getMyResistorMap().shunt);
    _data->getMyResistorMap().shunt+=20;
    Serial.println(_data->getMyResistorMap().shunt);
    
    /////////////////////////////////////////////////////
    Serial.println("----->     _data->getMyResistorMap().shunt");
    uint16_t pint4 = (uint16_t)_data->getMyResistorMap().shunt;
//    (uint16_t)_data->getMyResistorMap().shunt = (uint16_t)_data->getMyResistorMap().shunt + 300;
_data->getMyResistorMap().shunt+=300;
    Serial.println(pint4);
    Serial.println(_data->getMyResistorMap().shunt);
    
//    /////////////////////////////////////////////////////
//    Serial.println("----->     shunt2");
//    uint16_t shunt2 = _data->getMyResistorMap().shunt;
//    Serial.println(shunt2);
//    shunt2+=222;
//    Serial.println(shunt2);
  
    /////////////////////////////////////////////////////
    Serial.println("----->     _data->getMyResistorMap()");
    MyResistorMap mrm = _data->getMyResistorMap();
    Serial.println(mrm.shunt);
    mrm.shunt+=11;
//    uint16_t yyy = mrm.shunt;
    Serial.println(mrm.shunt);
  
    // ========================================  
    Serial.println("----->     myMenuData.pVoid[0]");
    uint16_t* pint2=(uint16_t*)myMenuData.pVoid[0];
    Serial.println(*pint2);
    *(uint16_t*)myMenuData.pVoid[0] += 10000;
    Serial.println(*pint2);

    uint16_t* pint3=(uint16_t*)myMenuData.pVoid[0];
    Serial.println(*pint3);

   // ========================================  
    Serial.println(PGMSTR(myMenuData.pgmData[0]));
  
    // ========================================  
    //    Serial.println(&myMenuData.pInt[0]);
    //  int* pint3=(int*)myMenuData.pVoid[0];
    //  Serial.println(*pint3);
    
    //  temp = *(int*)myMenuData.pVoid[0];
    //  Serial.println(temp);
    
    // ========================================  
    //    int * xxx2 =  (int) myMenuData.pInt[0];
    //    Serial.println( xxx2 );
    //    Serial.println( &xxx2 );
    
    // ========================================  
    //    int * xxx3 = &testtest;
    //    Serial.println( * xxx3 );
    
    // ========================================  
    //    Serial.println(testtest);

    
    Serial.println("--------------------------");
    Serial.println("--------------------------");
    Serial.println("--------------------------");
  }

  
/*
//  Serial.print("Display Info:  ");
//  Serial.print(displayInfo.buffer);
//  Serial.print(" : ");
//  Serial.print(PGMSTR(displayInfo.pgmData));
// 
//  Serial.println();
  
//myEditorData.col[0] = 0;
//myEditorData.col[1] = 1;
//myEditorData.col[2] = 2;
//myEditorData.col[3] = 3;
  myEditorData.row[0] = 0;
  myEditorData.row[1] = 1;
  myEditorData.row[2] = 2;
  myEditorData.row[3] = 3;
//myEditorData.displayInfo[1] = displayInfo;
  myEditorData.pVoid[1] = &myResistorMap.shunt;;
  myEditorData.returnTo = 255;
  
//  Serial.print("Editor Data:  ");
//  Serial.print(myEditorData.displayInfo[1].buffer);
//  Serial.print(" : ");
//  Serial.print(PGMSTR(myEditorData.displayInfo[1].pgmData));




//  if (myEditorData.setDisplayInfo == true){
//    myEditorData.setDisplayInfo = false;
//    myEditorData.displayInfo[1] = display.TestMethod(myResistorMap.shunt);
//    myEditorData.displayInfo[3] = display.TestMethod(v5_Measured);
//  }
*/
  
  if (repeatCount == 0) {
    setMenu(F("x252"), menuOptions252, membersof(menuOptions252));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit252_5V));

    lcd.setCursor(1, 1); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit252_5Vmes));
    
    lcd.setCursor(1, 3); //   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit252_v5bit));
  }

  lcd.setCursor(13, 1); //   row >    column ^
  //lcd.print(display.output_x_xxxV(v5_Measured));

//fix
//fix
//fix  lcd.print(display.outputDigitsU16(v5_Measured, volts_x_xxxV, 1));
  
  lcd.setCursor(10, 3); //   row >    column ^
//fix  lcd.print(display.outputDigitsU16(v5_voltPerBit, volts_0_0xxxxxV));
  
}

//===========================================
// Startup 
//===========================================
// -------------------------------------------
void Menu::lcdInit253() { // Splash     [no click 'select button' out to 253]
  if (repeatCount == 0) {
    setMenu(F("x253"), menuOptions253, membersof(menuOptions253));    
    lcd.setCursor(0, 0);//   row >    column ^
    lcd.print(PGMSTR(qBytesWorld));
    lcd.setCursor(0, 1);//   row >    column ^
    lcd.print(PGMSTR(deviceInfo));
    lcd.setCursor(0, 2);//   row >    column ^
    lcd.print(PGMSTR(versionNum));
  }


  if (true){ // Can delete this whole if condition when (no EEPROM data) is completed.
    lcd.setCursor(0, 3);//   row >    column ^
    if (repeatCount %2 == 0){// If ODD.
      lcd.print("DAQ finish EEPROM...");
    }else{
      lcd.print("                    ");
    }
  }
  
  if (repeatCount > 10) {//delay(2000);
     // If first time run (no EEPROM data)
    if (true){// DAQ finish this....need to read the EEPROM data to know if it is 1st time
      menuSelected = 252; // Initialize values
    } else {
      menuSelected = 240;   // Go to Control check before Main Menu 
    }
  }
}

// -------------------------------------------
void Menu::lcdInit254() {  // Starting   [click (select) out to 254]
  if (repeatCount == 0) {
    setMenu(F("x254"), menuOptions254, membersof(menuOptions254));
    lcd.init();
    lcd.begin(20,4);
    lcd.backlight();
  //lcd.blink();  //lcd.noBlink();
    
    lcd.setCursor(6, 1);//   row >    column ^
    lcd.print(PGMSTR(lcd_param_lcdInit254_startUp));    
  }
  
  if (repeatCount > 1) { // ~delay(250);
    menuSelected = 253;
  }
}

//===========================================
// Reserved
//===========================================
void Menu::lcdInit255() { // this is an error, 255 is reserved 
    lcd.setCursor(6, 1);//   row >    column ^
    lcd.print(PGMSTR(ERR255));   
    Serial.println(PGMSTR(ERR255));
    while (true){
      }
}

