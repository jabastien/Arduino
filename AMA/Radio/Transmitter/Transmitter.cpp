/*A basic 16 channel transmitter using the nRF24L01 module based on ELECTRONOOBS. */

/*
 AVR Libc Reference Manual
 http://www.atmel.com/webdoc/avrlibcreferencemanual/index.html
 http://www.atmel.com/webdoc/avrlibcreferencemanual/group__avr__stdlib_1ga060c998e77fb5fc0d3168b3ce8771d42.html
*/




//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <stdlib.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "def.h"
#include "types.h"

#include "CustomChar.h"
#include "Data.h"
#include "Display.h"


CustomChar customChar = CustomChar();
Data data = Data();
Display disp = Display();

// ===========================================
// Vars
// ===========================================


unsigned long  screenRefresh = 1000 / 4; // 4 times per second
unsigned long  screenLastRefresh = 0;


float changeMe = 987.654321;

// require ::: stdlib.h
//char buffer[7];         //the ASCII of the integer will be stored in this char array
//itoa(changeMe,buffer,10); //(integer, yourBuffer, base)   
char buffer[10];  //  Hold The Convert Data


// ===========================================
// Menu
// ===========================================

byte row = 0;
byte col = 0;

byte rowEdit = 0;
byte colEdit = 0;

byte returnToCurrent = MAINMENU;

byte repeatCount = 0;

//// ===========================================
//// Format Print
//// ===========================================
//#include <FormatPrint.h>
////FormatPrint fmt;
//

//
////#include <string.h>


// ===========================================
// Update LCD
// ===========================================
byte menuCurrent  = MAINMENU;
byte menuSelected = 254;

double refV = 5.0115;
double refValue = refV / 1023.0;

double vPre = 0.0;
double vPst = 0.0;
double v5_0 = 0.0;
double vKey = 0.0;

// ===========================================
// Keypad
// ===========================================
#include <KeyPad.h>

//KeyPad keyPad;  // Empty constructor does not require ().
//KeyPad keyPad(); // this is an error
//KeyPad keyPad(2, 5, 10, 200);
KeyPad keyPad(13, 5, 10, 200);

byte keyPress;

// ===========================================
// RF24
// ===========================================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*Create a unique pipe out. The receiver has to wear the same unique code*/

const uint64_t pipeOut = 0xE8E8F0F0E1LL;

//RF24 radio(9, 10); // select  CE & CSN  pin

// ===========================================
// I2C LCD
// ===========================================
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);    // Initialization of the book (address, characters, rows)

// ===========================================
// CD 405x
// ===========================================


// ===========================================
// CD 4051
// ===========================================
#include <CD4051.h>
CD4051 switchCD4051 = CD4051(3, 4, 5, 6);
CD4051 trimCD4051   = CD4051(3, 4, 5, 7);
CD4051 menuCD4051   = CD4051(3, 4, 5, 8);

byte switchPin = 0b00000000;
byte trimPin   = 0b00000000;
byte menuPin   = 0b00000000;

byte pinmask;
byte readmask;

byte digitalLoop = 0;

// ===========================================
// CD4052
// ===========================================
#include <CD4052.h>

CD4052 cd4052 = CD4052(5, 4, A7, A6);

int analog[8];

byte analogLoop = 0;

// ===========================================
// Timing Vars
// ===========================================
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 100;           // interval at which to update screen (milliseconds)

int fps = 0;
int cntMillis = 0;

// ===========================================
// Misc
// ===========================================
//int debugPin=8; // D8

// ===========================================
// My Data
// ===========================================
// The sizeof this struct should not exceed 32 bytes
// This gives us up to 32 8 bits channals



// ===========================================
// Reset
// ===========================================
void resetData()
{
  //This are the start values of each channal
  // Throttle is 0 in order to stop the motors
  //128 is the middle value of the 10 bit ADC.

  myControls.throttle = 0;    // no power
  myControls.yaw      = MID;  // center control
  myControls.pitch    = MID;  // center control
  myControls.roll     = MID;  // center control

  myAux.AUX1     = 0;
  myAux.AUX2     = 0;
  myAux.AUX3     = 0;
  myAux.AUX4     = 0;

  myButtons.swtch = 0;
  myButtons.dip   = 0;
  myButtons.menu  = 0;
}

byte    avgSize = 50;
double  avgList[50];
int     avgCnt = 0;
double  avgSum = 0.0;
double  avg = 0.0;

// ===========================================
// Serial Debug
// ===========================================
void serialDebug() {
  //------------------------------------------------------
  // Print controls
  //------------------------------------------------------
#ifdef DEBUG_MyControls
    Serial.print  (F(" T: "));
    Serial.print  (myControls.throttle);
    Serial.print  (F(" : "));
    Serial.print  (analogRead(A0));

    Serial.print  (F(" Y: "));
    Serial.print  (myControls.yaw);
    Serial.print  (F(" : "));
    Serial.print  (analogRead(A1));

    Serial.print  (F(" R: "));
    Serial.print  (myControls.roll);
    Serial.print  (F(" : "));
    Serial.print  (analogRead(A2));

    Serial.print  (F(" P: "));
    Serial.print  (myControls.pitch);
    Serial.print  (F(" : "));
    Serial.print  (analogRead(A3));

    Serial.println();
#endif  

  // -----------------------------------------------
  // KEY
  //------------------------------------------------------
#ifdef DEBUG_KEY
    Serial.print  ("Key: ");
    Serial.print  (analog[3]);
    Serial.print  ("  ");
    Serial.print  (analog[3] * (refV/1023.0));
    Serial.print  ("V ");

    Serial.println();
#endif  


  //------------------------------------------------------
  // Print CD4051 switches
  //------------------------------------------------------
#ifdef DEBUG_CD4051_MASK
    Serial.print(" Pin ");
    Serial.print(pinmask + 0x100, BIN);
    Serial.print(" Mask ");
    Serial.print(readmask + 0x100, BIN);
    Serial.println();    
#endif
  
#ifdef DEBUG_CD4051
    Serial.print(" Switch: ");
    Serial.print(switchPin + 0x100, BIN);
    Serial.print(" Trim: ");
    Serial.print(trimPin + 0x100, BIN);
    Serial.print(" Menu: ");
    Serial.print(menuPin + 0x100, BIN);
    Serial.println();    
#endif

//------------------------------------------------------
// Print CD4052 analog
//------------------------------------------------------
#ifdef DEBUG_CD4052

char bufferD[30];  //  Hold The Convert Data
char CD4052Format[] = "<X%1d:%1d:%4d> <Y%1d:%1d:%4d> ";

  for (analogLoop = 0 ; analogLoop < 4; analogLoop++) {
    sprintf(bufferD, CD4052Format, 
          analogLoop,  analogLoop * 2     , analog[(analogLoop * 2)    ], 
          analogLoop, (analogLoop * 2) + 1, analog[(analogLoop * 2) + 1]
          ); 
    Serial.print  (bufferD);
  }
    Serial.println("");
    
#endif


//------------------------------------------------------
// Print CD4052 volts (analog)
//------------------------------------------------------

#ifdef DEBUG_CD4052_VOLTS
  // -----------------------------------------------
  // 5 = y2 =   5V
  Serial.print  ("5V: ");
  Serial.print  (analog[5]);
  Serial.print  ("  ");
  Serial.print  (refValue * analog[5]);
  Serial.print  ("V  ");
//Ein = (Eo/R2) * (R1+R2)
  Serial.print  (v5_0);
  Serial.print  ("V ");

  // -----------------------------------------------
  // 7 = y3 = Pre
  Serial.print  (" xxxxx  Pre: ");
  Serial.print  (analog[7]);
  Serial.print  ("  ");
  Serial.print  (refValue * analog[7]);
  Serial.print  ("V  ");
//Ein = (Eo/R2) * (R1+R2)
  Serial.print  (vPre);
  Serial.print  ("V ");

  // -----------------------------------------------
  // 1 = y0 = Post,
  Serial.print  (" xxxxx  Post: ");
  Serial.print  (analog[1]);
  Serial.print  ("  ");
  Serial.print  (refValue * analog[1]);
  Serial.print  ("V  ");
//Ein = (Eo/R2) * (R1+R2)
  Serial.print  (vPst);
  Serial.print  ("V ");

  // -----------------------------------------------
  //I = E / R (R = shunt)
  Serial.print (" Current ");
  Serial.print (avgSum/avgSize);
  Serial.print ("mV ");
  Serial.print ((avgSum/avgSize)/myVoltsMap.shunt);
  Serial.print ("mA");

  // -----------------------------------------------
  Serial.println("");
#endif

///////////////////////////////////////////////////////////////////////
}


// ===========================================
void myControlsMapSetIt(MyControlsMap item) {
  item.Min = 0;
  item.Mid = 0;
  item.Max = 1023;
  item.Rev = false;
}

// ===========================================
void myControlsMapSet() {
  myControlsMapSetIt(myControlsMapThrottle);  // A0
  myControlsMapSetIt(myControlsMapYaw);       // A1
  myControlsMapSetIt(myControlsMapRoll);      // A2
  myControlsMapSetIt(myControlsMapPitch);     // A3
}

// ===========================================
// ===========================================
// ===========================================
// Init contoller
// ===========================================
// ===========================================
// ===========================================
void initSticksIt(MyControlsMap item) {
  item.Min = 0;    // A0
  item.Mid = 512;  // A0
  item.Max = 1023; // A0
  item.Rev = false;
}

void initSticks() {
  lcd.print("Move Throttle up/down");
  initSticksIt(myControlsMapThrottle);  // A0

  lcd.print("Move Yaw up/down");
  initSticksIt(myControlsMapYaw);       // A1

  lcd.print("Move Roll up/down");
  initSticksIt(myControlsMapRoll);      // A2

  lcd.print("Move Pitch up/down");
  initSticksIt(myControlsMapPitch);     // A3
}

//===============================================================================
//===============================================================================
//===============================================================================
//===============================================================================
//int lcdInt(int n, String format){
//char charBuf[10];
//  format.toCharArray(charBuf,10); 
//  int m = sprintf (buffer, charBuf, n);
//  lcd.print(buffer);
//  return m;
//}
//int lcdInt(int n, String format){
//  int m = sprintf (buffer, "%6d", n);
//  lcd.print(buffer);
//  return m;
//}
//int lcdInt(int n, const char format){
//  //    lcd.print(PGMSTR(qBytesWorld));
//  int m = sprintf (buffer, format, n);
//  lcd.print(buffer);
//  return m;
//}
////// ===========================================
////// LCD Print DDDDDD
////// ===========================================
int lcdUnLong6D(unsigned long n){
  Serial.println(n);
  //int m = sprintf (buffer, "%06d", n);
  int m = sprintf (buffer, "%06lu", n);
  lcd.print(buffer);
  return m;
}

//char digit10000   (uint16_t v) {return '0' + v / 10000                   ;}
//char digit1000    (uint16_t v) {return '0' + v / 1000  - (v/10000) * 10;}
//char digit100     (uint16_t v) {return '0' + v / 100   - (v/1000)  * 10;}
//char digit10      (uint16_t v) {return '0' + v / 10    - (v/100)   * 10;}
//char digit1       (uint16_t v) {return '0' + v / 1     - (v/10)    * 10;}

//void lcdprint_uint32(uint32_t v) {
void lcdprint_ulong(unsigned long v) {
  static char line[14] = "-,---,---,---";
  //                      0 2 4 6 8   12
  line[0]  = '0' + v  / 1000000000;
  line[2]  = '0' + v  / 100000000 - (v/1000000000) * 10;
  line[3]  = '0' + v  / 10000000  - (v/100000000)  * 10;
  line[4]  = '0' + v  / 1000000   - (v/10000000)   * 10;
  line[6]  = '0' + v  / 100000    - (v/1000000)    * 10;
  line[7]  = '0' + v  / 10000     - (v/100000)     * 10;
  line[8]  = '0' + v  / 1000      - (v/10000)      * 10;
  line[10] = '0' + v  / 100       - (v/1000)       * 10;
  line[11] = '0' + v  / 10        - (v/100)        * 10;
  line[12] = '0' + v  / 1         - (v/10)         * 10;

  lcd.print(line);  
}
//void lcdprint_uint32(uint32_t v) {
void lcdprint_uint(unsigned int v) {
  static char line[14] = "--,---";
  //                      01 345

  line[0] = '0' + v / 10000;
  line[1] = '0' + v / 1000      - (v/10000)      * 10;
  line[3] = '0' + v / 100       - (v/1000)       * 10;
  line[4] = '0' + v / 10        - (v/100)        * 10;
  line[5] = '0' + v             - (v/10)         * 10;

  lcd.print(line);  
}

////// ===========================================
////// LCD Print NNN.DDD
////// ===========================================
//int printInt(int n, String format){
//

//  char buffer[10];         //the ASCII of the integer will be stored in this char array
//  itoa((int)changeMe,buffer,10); //(integer, yourBuffer, base)
  
////char dateFormat[] = "%02d:%02d:%02d:%02d";
////    sprintf(buffer, dateFormat[3], days, hours, minutes, seconds); ///< This has 4 2-digit integers with leading zeros, separated by ":" . The list of parameters, hour, min, sec, provides the numbers the sprintf prints out with.
////    lcd.print(buffer);    
//    //Serial.println(buffer); ///< You will get something like"01:13:02:09" 
//    
//char format[] = "ddddd";
//      
////  char c[10];        // long enough to hold complete integer string
////  char charBuf[20];
//  format.toCharArray(buffer,10);
//  int m = sprintf(c, buffer, n);    // build integer string using C integer formatters  (m is length, and not used in this code)
//  Serial.print(c);
//  return m;
//}

//// ===========================================
//// LCD Print NNN.DDD
//// ===========================================
void lcdDouble63(double dbl) {
  char *r = dtostrf(dbl, 6, 3, buffer);
//  lcd.print(buffer);
  lcd.print(r);
  lcd.print("V");
//  lcd.print(dtostrf(v5_0, 6, 3, buffer));
//  lcd.print("V");
}
/**************************************************/

// ===========================================
// Map Joystick Values
// ===========================================
// Returns a corrected value for a joystick position that takes into account
// the values of the outer extents and the middle of the joystick range.
int mapJoystickValues(int value, int minimum, int middle, int maximum, bool reverse)
{
  value = constrain(value, minimum, maximum);
  if ( value < middle )
    value = map(value, minimum, middle, 0, MID);
  else
    value = map(value, middle, maximum, MID, MAX);
  return ( reverse ? MAX - value : value );
}

//===============================================================================
//===============================================================================
//===============================================================================
//===============================================================================

//===============================================================================
//===============================================================================
//===============================================================================
//===============================================================================
#define membersof(x) (sizeof(x) / sizeof(x[0]))

// Declare variables
//https://arduino.stackexchange.com/questions/19748/copy-content-of-array
//https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library
//https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library

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


byte menuOptions240 [1] = {MAINMENU};     // Control Check
byte menuOptions244 [2] = {240,201};      // Menu
byte menuOptions245 [2] = {244,201};      // Trim
byte menuOptions246 [2] = {245,201};      // Switch
byte menuOptions247 [2] = {246,201};      // Joystick
byte menuOptions248 [2] = {247,201};      // Shunt ohms
byte menuOptions249 [3] = {248,200,200};  // Vin pre 1.1 & 1.2 ohms
byte menuOptions250 [3] = {249,200,200};  // Vin pst 2.1 & 2.2 ohms
byte menuOptions251 [3] = {250,200,200};  // V5.0    3.1 & 3.2 ohms
byte menuOptions252 [2] = {251,201};      // V5.0    Regulator Voltage 
byte menuOptions253 [1] = {253};          // Splash     [no click (select) out to 253]
byte menuOptions254 [1] = {253};          // Starting   [click (select) out to 254]

byte menuOptions[5];
byte menuSize;

void setMenu(String menuOpt, byte menuValues[], byte sizeIs) {
  
  // Make sure we don't have an error.
  if (sizeIs > sizeof(menuOptions)) {
    Serial.print  ("Err: setMenu ");
    Serial.print  (sizeIs);
    Serial.print  (" for ");
    Serial.print  (menuOpt);
    sizeIs = sizeof(menuOptions); // degrade to prevent Array Overflow error
    Serial.print  (" s/b <= "); // increase " byte menuOptions[x] " size
    Serial.println(sizeIs);
  }

  // Make sure FUNCTIONs don't have a child.
  if (menuValues[0] == FUNCTION && sizeIs > 1) {
    Serial.print  ("Err: setMenu ");
    Serial.print  (sizeIs);
    Serial.print  (" for ");
    Serial.print  (menuOpt);
    sizeIs = 1; // degrade to prevent Array Overflow error
    Serial.print  (" funcion s/b = ");
    Serial.println(sizeIs);
  }
  
  // Need to find a way to retain 'col' when returning?
//  byte tempReturnToCurrent = menuOptions[0];
  
  menuSize = sizeIs;

    // Need to find a way to retain 'col' when returning?

  if (menuValues[0] != FUNCTION){
    // Clear current menu
    memset(menuOptions, 0x00, sizeof(menuOptions)); // for automatically-allocated arrays
    memcpy(menuOptions, menuValues, menuSize);
    Serial.println("*** menuValue [0]");
  } else {    
    if (returnToCurrent != MAINMENU){
      // Clear current menu
      memset(menuOptions, 0x00, sizeof(menuOptions)); // for automatically-allocated arrays
      Serial.println("*** menuValue [1]");
      menuOptions[0] = returnToCurrent;//tempReturnToCurrent;  --- fix this......
      //    }
    } else {
      Serial.println("*** menuValue [2]");
      returnToCurrent = menuOptions[0];
    }
  }

  // Show what we did?
  if (true) {
    Serial.print  (menuOpt);
    Serial.print  (" RTC=");
    Serial.print  (returnToCurrent);
 //   Serial.print  (" T/F=");
 //   Serial.print  (returnToCurrent);
    Serial.print  (" Size [");
    Serial.print  (menuSize);
    Serial.print  ("] menuOptions[...] ");
    //for (byte loop = 0; loop < sizeof(menuOptions); loop++) {
    for (byte loop = 0; loop < menuSize; loop++) {
      Serial.print  (menuOptions[loop]);
      if ((loop+1) < menuSize){
        Serial.print  (", ");
      }
    }
    Serial.println("");
  }

  // Clear return to current   
  returnToCurrent = MAINMENU;
}


// ===========================================
// Reserved
// ===========================================
void lcdMenu000() { // this is an error, 000 is reserved  
  while (true){
    Serial.println("ER000");
  }
}

// ===========================================
// Main Menu
// ===========================================
void lcdMenu001() {
  if (repeatCount == 0) {
setMenu("x001", menuOptions001, membersof(menuOptions001));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Main");
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print("lcdMainVolts: ");
    lcd.setCursor(0, 2); //   row >    column ^
    lcd.print("lcdKeyVolts: ");  
    lcd.setCursor(0, 3); //   row >    column ^
    lcd.print("Misc: ");
    lcd.setCursor(9, 3); //   row >    column ^
    lcd.print("Repeat: ");
  }

  int numb = (int)((double)repeatCount*3.5);
  customChar.percent(numb);
  lcd.setCursor(10, 0); //   row >    column ^
  
  lcd.print("Bat:");  
  customChar.showChar();
  lcd.print(numb);

  lcd.setCursor(17, 3); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(" ");
}

// ===========================================
// lcdMenu01
// ===========================================
void lcdMenu002() {
  if (repeatCount == 0) {
    setMenu("x002", menuOptions002, membersof(menuOptions002));
//    lcd.setCursor(0, 0); //   row >    column ^
//    lcd.print("10 -> 11");
//    lcd.setCursor(0, 1); //   row >    column ^
//    lcd.print("10 -> 12");
//    lcd.setCursor(0, 2); //   row >    column ^
//    lcd.print("10 -> 13");
//    lcd.setCursor(0, 3); //   row >    column ^
//    lcd.print("10 -> 14");
//    lcd.print(" Repeat: ");
  }

  //  lcd.setCursor(17, 1); //   row >    column ^
  //  lcd.print(repeatCount);
  //  lcd.print(" ");
  // -------------------------------------------

  // 0 = x0 = Aux0,
  // 2 = x1 = Aux1,
  // 4 = x2 = Aux2,
  // 6 = x3 = Aux3

  // 1 = y0 = Post,
  // 3 = y1 = Key
  // 5 = y2 = 5V
  // 7 = y3 = Pre

  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 0); //   row >    column ^
  lcd.print("PreV: ");

  lcd.print  (refValue * analog[7]);
  lcd.print  ("V   ");

  //Ein = (Eo/R2) * (R1+R2)
  lcd.print (vPre);
  lcd.print  ("V");

  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 1); //   row >    column ^
  lcd.print("PstV: ");

  lcd.print  (refValue * analog[1]);
  lcd.print  ("V   ");

  //Ein = (Eo/R2) * (R1+R2)
  lcd.print (vPst);
  lcd.print  ("V");

  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 2); //   row >    column ^
  lcd.print("5.0V: ");

  lcd.print  (refValue * analog[5]);
  lcd.print  ("V    ");

  //Ein = (Eo/R2) * (R1+R2)
  lcd.print (v5_0);
  lcd.print  ("V");

  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 3); //   row >    column ^
  lcd.print("Shnt:");

  lcd.print  (avgSum / avgSize);
  lcd.print  ("mV ");

  //Ein = (Eo/R2) * (R1+R2)
  lcd.print ((avgSum / avgSize) / myVoltsMap.shunt);
  lcd.print  ("mA");
}

// ===========================================
// lcdMenu003
// ===========================================
void lcdMenu003() {
  if (repeatCount == 0) {
    setMenu("x003", menuOptions003, membersof(menuOptions003));
//    lcd.setCursor(0, 0); //   row >    column ^
//    lcd.print("10 -> 11");
//    lcd.setCursor(0, 1); //   row >    column ^
//    lcd.print("10 -> 12");
//    lcd.setCursor(0, 2); //   row >    column ^
//    lcd.print("10 -> 13");
//    lcd.setCursor(0, 3); //   row >    column ^
//    lcd.print("10 -> 14");
//    lcd.print(" Repeat: ");
  }

  //  lcd.setCursor(17, 1); //   row >    column ^
  //  lcd.print(repeatCount);
  //  lcd.print(" ");
  //// -------------------------------------------
//void lcdKeyVolts() {
  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 0); //   row >    column ^
  lcd.print(F("KeyV: "));

  lcd.print  (refValue * analog[3]);
  lcd.print  (F("V "));

  lcd.setCursor(0, 1); //   row >    column ^
  lcd.print(F("Value: "));
  lcd.print  (analog[3]);
  lcd.print(F("   "));

  //  lcd.setCursor(0, 2); //   row >    column ^
  //  lcd.print("Key Down: ");
  //  lcd.print  (keyDown);

  lcd.setCursor(0, 3); //   row >    column ^
  lcd.print(F("Key Pressed: "));
  lcd.print  (keyPress);
}

// ===========================================
// lcdMenu10
// ===========================================
void lcdMenu010() {
  if (repeatCount == 0) {
    setMenu("x010", menuOptions010, membersof(menuOptions010));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("10 -> 11");
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print("10 -> 12");
    lcd.setCursor(0, 2); //   row >    column ^
    lcd.print("10 -> 13");
    lcd.setCursor(0, 3); //   row >    column ^
    lcd.print("10 -> 14");
    lcd.print(" Repeat: ");
  }

  //  lcd.setCursor(17, 1); //   row >    column ^
  //  lcd.print(repeatCount);
  //  lcd.print(" ");
}


// ===========================================
// lcdMenu011
// ===========================================
void lcdMenu011() {
  if (repeatCount == 0) {
    setMenu("x011", menuOptions011, membersof(menuOptions011));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("x11");
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print("Repeat: ");
  }

  lcd.setCursor(9, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(" ");
}

// ===========================================
// lcdMenu012
// ===========================================
void lcdMenu012() {
  if (repeatCount == 0) {
    setMenu("x012", menuOptions012, membersof(menuOptions012));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("x12");
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print("Repeat: ");
  }

  lcd.setCursor(9, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(" ");
}

// ===========================================
// lcdMenu013
// ===========================================
void lcdMenu013() {
  if (repeatCount == 0) {
    setMenu("x013", menuOptions013, membersof(menuOptions013));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("x13");
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print("Repeat: ");
  }

  lcd.setCursor(9, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(" ");
}

//===========================================
//lcdMenu014
//===========================================
//void lcdMainFlightTime(){
//void updateFPS(){

long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

void lcdMenu014() {
  // check to see if it's time to update LCD; that is, if the difference
  // between the current time and last time you updated the LCD is bigger than
  // the interval at which you want to blink the LED.

  if (repeatCount == 0)
  {
    setMenu("x014", menuOptions014, membersof(menuOptions014));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("x014");
    lcd.setCursor(0, 1); //   row >    column ^
    lcd.print("Repeat: ");
  }
  currentMillis = millis();

  if (currentMillis - previousMillis >= screenRefresh) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    //    lcd.setCursor(0, 1); //   row >    column ^
    //    printVolts();    //Voltage: xx.xV


    if (cntMillis >= (1000 / screenRefresh))
    {
      // -------------------------------------
      lcd.setCursor(0, 0); //   row >    column ^
      lcd.print("Flight: ");
//      long timeNow = millis();
//
//      int days = timeNow / day ;                                //number of days
//      int hours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
//      int minutes = ((timeNow % day) % hour) / minute ;         //and so on...
//      int seconds = (((timeNow % day) % hour) % minute) / second;
//
//
//char dateFormat[] = "%02d:%02d:%02d:%02d";

//    sprintf(buffer, dateFormat[3], days, hours, minutes, seconds); ///< This has 4 2-digit integers with leading zeros, separated by ":" . The list of parameters, hour, min, sec, provides the numbers the sprintf prints out with.
//    lcd.print(buffer);    
    //Serial.println(buffer); ///< You will get something like"01:13:02:09"       

      // -------------------------------------
      lcd.setCursor(0, 2); //   row >    column ^
      lcd.print("Channel:");
      lcd.print(" xxx");

      // -------------------------------------
      lcd.setCursor(0, 3); //   row >    column ^
      lcd.print("FPS:");
      lcd.print(fps);  // ~300 has been the average
      lcd.print("   GPS: xxx");

      // -------------------------------------
      fps = 0;
      cntMillis = 0;
    }
  }
  lcd.setCursor(9, 1); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(" ");
}

// -------------------------------------------
// -------------------------------------------
// -------------------------------------------
// Int number edit
void lcdFunc200() { // Int number edit
  if (repeatCount == 0) {
    setMenu("x200", menuOptions200, membersof(menuOptions200));
    lcd.setCursor(0, 3); //   row >    column ^
    lcd.print("Int number edit");
  }

//  char buffer[10];         //the ASCII of the integer will be stored in this char array
  itoa((int)changeMe,buffer,10); //(integer, yourBuffer, base)   

  lcd.blink();
  lcd.setCursor(5, 2); //   row >    column ^
  lcd.print(buffer);
  lcd.setCursor(5 + row, 2); //   row >    column ^

}

void lcdFunc201() { //Double number edit
  if (repeatCount == 0) {
    setMenu("x201", menuOptions201, membersof(menuOptions201));
    lcd.setCursor(0, 3); //   row >    column ^
    lcd.print("Double number edit");
  }
  // #include<stdlib.h>
  //  dtostrf(FLOAT,WIDTH,PRECSISION,BUFFER);

  char *r = dtostrf(changeMe, 8, 2, buffer);
  if (true){
    Serial.print  (buffer);
    Serial.print  (" r:");
    Serial.print  (r);
    Serial.println(":");
  }
  lcd.setCursor(3, 1); //   row >    column ^
         
  lcd.print(buffer);

  lcd.setCursor(3 + row, 1); //   row >    column ^
}

// -------------------------------------------
void lcdInit240() { // Control check
  if (repeatCount == 0) {
    setMenu("x240", menuOptions240, membersof(menuOptions240));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Control check");
  }
  if (repeatCount > 3) {//delay(2000);

// DAQ finish this....
// DAQ finish this....
// DAQ finish this....

     // If Controls not home, wait.
    if (true){
      menuSelected = MAINMENU; // Main
    }
  }  
}

// -------------------------------------------
void lcdInit244() { // Menu
  if (repeatCount == 0) {
    setMenu("x244", menuOptions244, membersof(menuOptions244));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Menu");
  }
}

// -------------------------------------------
void lcdInit245() { // Trim
  if (repeatCount == 0) {
    setMenu("x245", menuOptions245, membersof(menuOptions245));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Trim");
  }
}

// -------------------------------------------
void lcdInit246() { // Switch
  if (repeatCount == 0) {
    setMenu("x246", menuOptions246, membersof(menuOptions246));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Switch");
  }
}

// -------------------------------------------
void lcdInit247() { // Joystick
  if (repeatCount == 0) {
    setMenu("x247", menuOptions247, membersof(menuOptions247));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Joystick");
  }
}

// -------------------------------------------
void lcdInit248() { // Shunt ohms
  if (repeatCount == 0) {
    setMenu("x248", menuOptions248, membersof(menuOptions248));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Shunt");
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print("ohms ");      
  }
}

// -------------------------------------------
void lcdInit249() { // Vin pre 1.1 & 1.2 ohms
  if (repeatCount == 0) {
    setMenu("x249", menuOptions249, membersof(menuOptions249));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Vin pre ohms");
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print("1.1 ");    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print("1.2 ");          
  }
}

// -------------------------------------------
void lcdInit250() { // Vin pst 2.1 & 2.2 ohms
  if (repeatCount == 0) {
    setMenu("x250", menuOptions250, membersof(menuOptions250));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Vin post ohms");
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print("2.1 ");    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print("2.2 ");    
  }
}


uint32_t tm=0;
// -------------------------------------------
void lcdInit251() { // V5.0    3.1 & 3.2 ohms
  if (repeatCount == 0) {
    setMenu("x251", menuOptions251, membersof(menuOptions251));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("V5.0 ohm");
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print("3.1 ");    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print("3.2 ");    
  }

  //nx = 65535;  // I know, max resistor size is 65535...
  //lcd.print(disp.outputDigitsU16(nx, true));
unsigned int nx;
nx = 50;
tm+=123;

  disp.outputDigitsU16(nx); 
  lcd.setCursor(6, 1); //   row >    column ^
  lcd.print(disp.outputDigitsS16(nx));
  lcd.setCursor(6, 2); //   row >    column ^

//  int nx1;
//  nx1 = -65539;
//  lcd.print(disp.outputDigitsS16(nx1));

  lcd.print(disp.outputOnTime(millis()));

  lcd.setCursor(6, 3); //   row >    column ^

 long ul = 2147483647;
 lcd.print(disp.outputDigitsS32(ul));

//lcd.print(disp.outputServiceTime(millis()/1000));

//lcd.print(disp.outputServiceTime(4294967294));
}

/*
struct MyVoltsMap {
  // Messure (  vPre -  vPost) / Current
  //         (12.867 - 12.836) / 58.8 =  527.211 mOhm
  //                     0.031 / 58.8 =  527.211 mOhm
  //double shunt = 0.727211;   // 0.5
  double shunt = 0.766327;   // 0.5
  int Vpre11   = 8042; // 8.2k
  int Vpre12   = 2638; // 2.7k
  int Vpst21   = 8014; // 8.2k
  int Vpst22   = 2637; // 2.7k
  int V5_31    = 2161; // 2.2k
  int V5_32    = 3212; // 3.3k
 */
 
// -------------------------------------------
void lcdInit252() {  // V5.0    Regulator Voltage
  if (repeatCount == 0) {
    setMenu("x252", menuOptions252, membersof(menuOptions252));
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("V5.0 volts");
    rowEdit = 2; //   row >    column ^  
    colEdit = 1; //   row >    column ^  
  }

  lcd.setCursor(2, 1); //   row >    column ^
  lcdDouble63(v5_0);//printVolts();   
}


//#define PGMSTR(x) (__FlashStringHelper*)(x)
// -------------------------------------------
void lcdInit253() { // Splash     [no click (select) out to 253]
  if (repeatCount == 0) {
    setMenu("x253", menuOptions253, membersof(menuOptions253));    
    lcd.setCursor(0, 0);//   row >    column ^
    lcd.print(PGMSTR(qBytesWorld));
    lcd.setCursor(0, 1);//   row >    column ^
    lcd.print(PGMSTR(deviceInfo));
    lcd.setCursor(0, 2);//   row >    column ^
    lcd.print(PGMSTR(versionNum));
    lcd.setCursor(0, 3);//   row >    column ^
    lcd.print(PGMSTR(volts));

  }

  lcd.setCursor(7, 3);//   row >    column ^
  lcdDouble63(v5_0);//printVolts();
  
  if (repeatCount > 7) {//delay(2000);

// DAQ finish this....
// DAQ finish this....
// DAQ finish this....

     // If first time run (no EEPROM data)
    if (true){
      menuSelected = 252; // Initialize values
    } else {
      menuSelected = 240;   // Go to Control check befor Main Menu 
    }
  }
}

// -------------------------------------------
void lcdInit254() {  // Starting   [click (select) out to 254]
  if (repeatCount == 0) {
    setMenu("x254", menuOptions254, membersof(menuOptions254));
    lcd.init();
    lcd.begin(20,4);
    lcd.backlight();
  //lcd.blink();
    lcd.noBlink();
    
    lcd.setCursor(0, 0);//   row >    column ^
    lcd.print("Startup");

//    lcd.createChar(0, testChar0);  
//    lcd.createChar(1, testChar1);   
//    lcd.createChar(2, testChar2);   
//    lcd.createChar(3, testChar3);   
//    lcd.createChar(4, testChar4);   
//    lcd.createChar(5, testChar5);   
//    lcd.createChar(6, testChar6);   
//    lcd.createChar(7, testChar7);   
//
//    lcd.home();
//    lcd.setCursor(0,0); //   row >    column ^
  }
  
  if (repeatCount > 1) { // ~delay(250);
    menuSelected = 253;
  }
}

// -------------------------------------------
void lcdInit255() { // this is an error, 255 is reserved 
  while (true){
    Serial.println("ER255");
  }
}

void updateLCD() {
  // Detect Menu change

  if (menuCurrent != menuSelected) {
    Serial.print ("C:");
    Serial.print (menuCurrent);
    Serial.print (" S:");
    Serial.print (menuSelected);
    returnToCurrent = menuCurrent;
    if (true){
      Serial.print (" Cur:");
      Serial.print (menuCurrent);
      Serial.print (" Sel:");
      Serial.print (menuSelected);
      Serial.print (" RTC:");
      Serial.print (returnToCurrent);
      Serial.println();
    }

    // Don't clear the screen for FUNCTIONs
    if (!(menuSelected > 200 && menuSelected <= 239)){
      lcd.clear();
    }
    
    repeatCount = 0;
    col = 0;
    menuCurrent = menuSelected;

    if (menuCurrent == MAINMENU || menuCurrent >= 250) {
      lcd.noBlink();
    } else {
      lcd.blink();
    }
  }

  if (keyPress > 0) {
    if (keyPress == 5) {// up
      if (col > 0)
        col--;
        changeMe += 1.0;
    }
    if (keyPress == 3) {// down
      if (col < (menuSize-1))
        col++;
        changeMe -= 1.0;
    }
    if (keyPress == 4) {// right
      if (row < 5)
        row++;
    }
    if (keyPress == 2) {// left
      if (row > 0)
        row--;
    }    
    
    Serial.print  (keyPress);
    Serial.print  (" R>:");
    Serial.print  (row);
    Serial.print  (" C^:");
    Serial.println(col);

  //  lcd.setCursor(row - 1, col);//   row >    column ^
  }

  if (keyPress == 1) {
    Serial.print (" MS1:");
    Serial.print (menuSelected);
    menuSelected = menuOptions[col];
    Serial.print (" MS2:");
    Serial.println(menuSelected);
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
    // ---------------------------------------
    // ---------------------------------------
    case 200: // Int number edit
      lcdFunc200();
      break;
    // ---------------------------------------
    case 201: // Double number edit
      lcdFunc201();
      break;
    // ---------------------------------------
    // ---------------------------------------
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
      Serial.print  ("Menu not found Error: " );
      Serial.print  (menuSelected);
      Serial.println(" - reset");
      menuSelected = 254;
      //while(true){};
      break;
  }

  // Set Repeat Count
  //repeatCount;
  if (++repeatCount > 31) {
    repeatCount = 0;
  }
}

// ===========================================
// ===========================================
// ===========================================
// Setup
// ===========================================
// ===========================================
// ===========================================

void setup()
{
//  pinMode(2, OUTPUT);
//  digitalWrite (2, LOW);
  analogReference(EXTERNAL);

  // Debug Serial out
  Serial.begin(115200); //Set the speed to 9600 bauds if you want.
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  //  pinMode(debugPin, INPUT);      // sets the digital pin as input

  //Start everything up
  //  radio.begin();
  //  radio.setAutoAck(false);
  //  radio.setDataRate(RF24_250KBPS);
  //  radio.openWritingPipe(pipeOut);
  //  resetData();

  // set levels
  myControlsMapSet();

  // Setup the Min, Mid & Max values for the sticks
  initSticks();

//  // Test code to be deleted
//  // Test code to be deleted
//  // Test code to be deleted

// dtostrf( floatVar, 
//          minStringWidthIncDecimalPoint,
//          numVarsAfterDecimal, 
//          charBuf);
//       dtostrf(x, 10, i, buffer2); // avr-libc function for floats
//       Serial.print(buffer2);
//       Serial.println("");

//sprintf(buffer, "String value: %08d.%02d", (int)changeMe, abs((int)(changeMe*100)%100));
//Serial.println(buffer);
    
//  // Test code to be deleted
//  // Test code to be deleted
//  // Test code to be deleted

  //data.factoryReset();
}

// ===========================================
// ===========================================
// ===========================================
// loop
// ===========================================
// ===========================================
// ===========================================
void loop() {
  //------------------------------------------------------
  // The calibration numbers used here should be measured
  // for your joysticks so they send the correct values.
  //------------------------------------------------------
  myControls.throttle = mapJoystickValues( analogRead(A0), myControlsMapThrottle.Min, myControlsMapThrottle.Mid, myControlsMapThrottle.Max, myControlsMapThrottle.Rev);
  myControls.yaw      = mapJoystickValues( analogRead(A1), myControlsMapYaw.Min,      myControlsMapYaw.Mid,      myControlsMapYaw.Max,      myControlsMapYaw.Rev);
  myControls.roll     = mapJoystickValues( analogRead(A2), myControlsMapRoll.Min,     myControlsMapRoll.Mid,     myControlsMapRoll.Max,     myControlsMapRoll.Rev);
  myControls.pitch    = mapJoystickValues( analogRead(A3), myControlsMapPitch.Min,    myControlsMapPitch.Mid,    myControlsMapPitch.Max,    myControlsMapPitch.Rev);

  //------------------------------------------------------
  // 4051 (3x) Switch address
  //------------------------------------------------------
  for (digitalLoop = 0; digitalLoop < 8 ; digitalLoop++) {
    switchCD4051.setChannel(digitalLoop);

    // Set mask using loop values
    pinmask   = ~(1 << (digitalLoop % 8));

    // Switch
    readmask  = (switchCD4051.digitalReadC() << (digitalLoop % 8));
    switchPin = (switchPin & pinmask) | readmask;

    // Trim
    readmask  = (trimCD4051.digitalReadC() << (digitalLoop % 8));
    trimPin   = (trimPin & pinmask) | readmask;

    // Menu
    readmask  = (menuCD4051.digitalReadC() << (digitalLoop % 8));
    menuPin   = (menuPin & pinmask) | readmask;
  }

  //------------------------------------------------------
  // 4052 (x1) Read Analog
  //------------------------------------------------------
  for (analogLoop = 0 ; analogLoop < 4; analogLoop++) {
    // Switch address for 4052 (1x)
    cd4052.setChannel(analogLoop);
    analog[(analogLoop * 2)    ] = cd4052.analogReadX();
    analog[(analogLoop * 2) + 1] = cd4052.analogReadY();
  }

  myAux.AUX1 = analog[0];
  myAux.AUX2 = analog[2];
  myAux.AUX3 = analog[4];
  myAux.AUX4 = analog[8];

  vPst = (((refValue * analog[1]) / myVoltsMap.Vpst22) * (myVoltsMap.Vpst21 + myVoltsMap.Vpst22));  // V Post
  vKey =    refValue * analog[3];                                                                   // Key
  v5_0 = (((refValue * analog[5]) / myVoltsMap.V5_32 ) * (myVoltsMap.V5_31  + myVoltsMap.V5_32 ));  // 5.0V
  vPre = (((refValue * analog[7]) / myVoltsMap.Vpre12) * (myVoltsMap.Vpre11 + myVoltsMap.Vpre12));  // V Pre

  //
  if (avgCnt >= avgSize) {
    avgCnt = 0;
  }
  avgList[avgCnt++] = (vPre - vPst) * 1000;

  avgSum = 0;
  for (int lp = 0; lp < avgSize; lp++) {
    avgSum += avgList[lp];
  }


  //------------------------------------------------------
  // Send our data
  //  radio.write(&myControls, sizeof(MyControls));


  //------------------------------------------------------
  // Button pressed?
  keyPad.doKeys(analog[3]);
  keyPress = keyPad.getKeyPressed();

  //------------------------------------------------------
  // Inc Frames Per Second
  //------------------------------------------------------
  fps++;

  //------------------------------------------------------
  // Update LCD 1/10 seconds
  //------------------------------------------------------
  unsigned long currentMillis = millis();
  if ((keyPress > 0) || (currentMillis > (screenLastRefresh + screenRefresh))) {
    screenLastRefresh = currentMillis;
    updateLCD();
  }
    else {
      if (false){
        Serial.print  (currentMillis);
        Serial.print  (" ");
        Serial.print  (screenLastRefresh);
        Serial.print  (" ");
        Serial.println(screenRefresh);
      }
    }

  //------------------------------------------------------
  // Serial Debugging
  serialDebug();
}
