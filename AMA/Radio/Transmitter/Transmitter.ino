/*A basic 4 channel transmitter using the nRF24L01 module.*/
/* Like, share and subscribe, ELECTRONOOBS */
/* http://www.youtube/c/electronoobs */

/* First we include the libraries. Download it from
   my webpage if you donw have the NRF24 library */

//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif


// ===========================================
// Format Print
// ===========================================
#include <FormatPrint.h>
FormatPrint fmt;

byte repeatCount = 0;

//#include <string.h>

// ===========================================
// Vars
// ===========================================
String qBytesWorld = "Q-Bytes World";
String deviceInfo  = "2.4G Transmitter";
String versionNum  = "v1.10";

unsigned long  screenRefresh = 1000 / 4; // 4 times per second
unsigned long  screenLastRefresh = 0;

// ===========================================
// Update LCD
// ===========================================
byte menuCurrent  = 000;
byte menuSelected = 254;

double refV = 5.0115;
double refValue = refV / 1023.0;

double vPre = 0.0;
double vPst = 0.0;
double v5_0 = 0.0;
double vKey = 0.0;

// ===========================================
// Volt divide Vars
// ===========================================

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
};
MyVoltsMap myVoltsMap;


// ===========================================
// Keypad
// ===========================================
#include <KeyPad.h>

//KeyPad keyPad;  // Empty constructor does not require ().
//KeyPad keyPad(); // this is an error
KeyPad keyPad(2, 5, 10, 200);

byte keyPress;

// ===========================================
// Menu
// ===========================================

byte row = 0;
byte col = 0;

byte rowEdit = 0;
byte colEdit = 0;

byte returnToCurrent = 0;

byte function = 255;

// ===========================================
// RF24
// ===========================================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*Create a unique pipe out. The receiver has to
  wear the same unique code*/

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
// Custom Char (Max is 8 [0-7])
// 255 is a solid block
// 254 is an empty block
/*
//  The user must call, one of the funtions 
      lcd.home()or lcd.setCursor(x,x) //   row >    column ^
      after the character creation.
*/
// ===========================================
// Sequence must be
// /// lcd.createChar(0,testChar0);
// /// lcd.createChar(1,testChar1);
// /// 
// /// lcd.home();
// /// 
// /// lcd.print((char)0);
// /// lcd.print((char)1);
// 
// https://omerk.github.io/lcdchargen/

//byte  testChar0[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // = 254 (empty)
  byte  testChar0[8] = {0x1f, 0x00, 0x0a, 0x04, 0x0a, 0x00, 0x11, 0x1f};
  byte  testChar1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f};
  byte  testChar2[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f};
  byte  testChar3[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f};
  byte  testChar4[8] = {0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f};
  byte  testChar5[8] = {0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
  byte  testChar6[8] = {0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
  byte  testChar7[8] = {0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
//byte  testChar7[8] = {0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f}; // = 255 (full)

//  byte testChar7[8] = {
//  0b01110,
//  0b11011,
//  0b10001,
//  0b10001,
//  0b10001,
//  0b11111,
//  0b11111,
//  0b11111
//};

//  byte  testChar[8] = {0x00, 0x00, 0x0a, 0x00, 0x04, 0x11, 0x0e, 0x00}; // smile
//  byte  testChar[8] = {  // degree F
//      B01000,
//      B10100,
//      B01000,
//      B00000,
//      B00111,
//      B00100,
//      B00110,
//      B00100
//    };


struct MyControls {
  const byte packetType = 0x01;
  byte throttle; // A0
  byte yaw;      // A1
  byte roll;     // A2
  byte pitch;    // A3
};
MyControls myControls;

struct MyControlsMap {
  int       Min; // A0
  int       Mid; // A0
  int       Max; // A0
  boolean   Rev;
};

MyControlsMap myControlsMapThrottle;
MyControlsMap myControlsMapYaw;
MyControlsMap myControlsMapRoll;
MyControlsMap myControlsMapPitch;

struct MyAux {
  const byte packetType = 0x02;
  byte AUX1;
  byte AUX2;
  byte AUX3;
  byte AUX4;
};
MyAux myAux;

struct MyButtons {
  const byte packetType = 0x03;
  byte swtch;
  byte dip;
  byte menu;
};
MyButtons myButtons;

// ===========================================
// Reset
// ===========================================
void resetData()
{
  //This are the start values of each channal
  // Throttle is 0 in order to stop the motors
  //127 is the middle value of the 10ADC.

  myControls.throttle = 0;    // no power
  myControls.yaw      = 127;  // center control
  myControls.pitch    = 127;  // center control
  myControls.roll     = 127;  // center control

  myAux.AUX1     = 0;
  myAux.AUX2     = 0;
  myAux.AUX3     = 0;
  myAux.AUX4     = 0;

  myButtons.swtch = 0;
  myButtons.dip   = 0;
  myButtons.menu  = 0;
}

byte    avgSize = 100;
double  avgList[100];
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
  if (false) {
    Serial.print  (" T: ");
    Serial.print  (myControls.throttle);
    Serial.print  (" : ");
    Serial.print  (analogRead(A0));

    Serial.print  (" Y: ");
    Serial.print  (myControls.yaw);
    Serial.print  (" : ");
    Serial.print  (analogRead(A1));

    Serial.print  (" R: ");
    Serial.print  (myControls.roll);
    Serial.print  (" : ");
    Serial.print  (analogRead(A2));

    Serial.print  (" P: ");
    Serial.print  (myControls.pitch);
    Serial.print  (" : ");
    Serial.print  (analogRead(A3));

    //    // -----------------------------------------------
    //    // KEY
    //    Serial.print  ("Key: ");
    //    Serial.print  (analog[3]);
    //    Serial.print  ("  ");
    //    Serial.print  (analog[3] * (refV/1023.0));
    //    Serial.print  ("V ");

    Serial.println("");
  }



  //------------------------------------------------------
  // Print CD4051 switches
  //------------------------------------------------------
  if (false) {
    Serial.print(" Pin ");
    Serial.print(pinmask + 0x100, BIN);
    Serial.print(" Mask ");
    Serial.print(readmask + 0x100, BIN);
  }
  if (false) {
    Serial.print(" Switch: ");
    Serial.print(switchPin + 0x100, BIN);
    Serial.print(" Trim: ");
    Serial.print(trimPin + 0x100, BIN);
    Serial.print(" Menu: ");
    Serial.print(menuPin + 0x100, BIN);
  }
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

//int printInt(int n, String format){
//  char c[10];        // long enough to hold complete integer string
//  char charBuf[20];
//  format.toCharArray(charBuf,20);
//  int m = sprintf(c, charBuf, n);    // build integer string using C integer formatters  (m is length, and not used in this code)
//  Serial.print(c);
//  return m;
//}

// ===========================================
// Print Volts
// ===========================================
void printVolts() {
  //  float sensorValue = (float)analogRead(A0);
  //  sensorValue *= (5.0 / 1023.0);
  //lcd.print(fmt.getFloat(sensorValue, 6, 3));
  lcd.print(fmt.getFloat(v5_0, 6, 3));
  lcd.print("V");
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
    value = map(value, minimum, middle, 0, 128);
  else
    value = map(value, middle, maximum, 128, 255);
  return ( reverse ? 255 - value : value );
}

//===============================================================================
//===============================================================================
//===============================================================================
//===============================================================================
// -------------------------------------------
//void lcdInit253() {
//  if (repeatCount == 0) {
//    setMenu("x253", menuOptions252, menuOptions252SIZE);
//    lcd.setCursor(0, 0); //   row >    column ^
//    lcd.print("Pre Ohms");    
//  }
//
//  if (row>0){
//    returnToCurrent = true;
//  }
//  
//  // test print custom char.
//  lcd.setCursor(3, 3);  //   row >    column ^
//   
//  lcd.print((char)0);
//  lcd.print((char)254);
//  lcd.print((char)1);
//  lcd.print((char)2);
//  lcd.print((char)3);
//  lcd.print((char)4);
//  lcd.print((char)5);
//  lcd.print((char)6);
//  lcd.print((char)7);
//  lcd.print((char)255);
//}
//===============================================================================
//===============================================================================
//===============================================================================
//===============================================================================
#define membersof(x) (sizeof(x) / sizeof(x[0]))

// Declare variables
//https://arduino.stackexchange.com/questions/19748/copy-content-of-array
//https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library
byte menuOptions000 [4] = {0, 1, 2, 10};

byte menuOptions001 [1] = {000};
byte menuOptions002 [1] = {000};

byte menuOptions010 [5] = {000, 011, 012, 013, 014};
byte menuOptions011 [1] = {010};
byte menuOptions012 [1] = {010};
byte menuOptions013 [1] = {010};
byte menuOptions014 [1] = {010};

byte menuOptions200 [1] = {function}; // Function for number edit
byte menuOptions201 [1] = {function}; // Function for number edit


byte menuOptions244 [2] = {000,201};      // Menu
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

const byte menuOptions000SIZE = membersof(menuOptions000);

const byte menuOptions001SIZE = membersof(menuOptions001);
const byte menuOptions002SIZE = membersof(menuOptions002);

const byte menuOptions010SIZE = membersof(menuOptions010);
const byte menuOptions011SIZE = membersof(menuOptions011);
const byte menuOptions012SIZE = membersof(menuOptions012);
const byte menuOptions013SIZE = membersof(menuOptions013);
const byte menuOptions014SIZE = membersof(menuOptions014);

const byte menuOptions200SIZE = membersof(menuOptions200);
const byte menuOptions201SIZE = membersof(menuOptions201);

const byte menuOptions244SIZE = membersof(menuOptions244);
const byte menuOptions245SIZE = membersof(menuOptions245);
const byte menuOptions246SIZE = membersof(menuOptions246);
const byte menuOptions247SIZE = membersof(menuOptions247);
const byte menuOptions248SIZE = membersof(menuOptions248);
const byte menuOptions249SIZE = membersof(menuOptions249);
const byte menuOptions250SIZE = membersof(menuOptions250);
const byte menuOptions251SIZE = membersof(menuOptions251);
const byte menuOptions252SIZE = membersof(menuOptions252);
const byte menuOptions253SIZE = membersof(menuOptions253);
const byte menuOptions254SIZE = membersof(menuOptions254);

//const byte menuOptions90SIZE = membersof(menuOptions90);
//setMenu("mo00", menuOptions00,menuOptions00SIZE);


//#define menuOptions10SIZE (sizeof(menuOptions10) / sizeof(byte))

//PROGMEM const String sampleMenu_back = "Back";
//PROGMEM const String sampleMenu_exit = "Exit";
//
//PROGMEM const String sampleMenu_2_1_1 = "1 Sub item A";
//PROGMEM const String sampleMenu_2_1_2 = "2 Sub item B";

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

  // Make sure functions don't have a child.
  if (menuValues[0] == function && sizeIs > 1) {
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

  if (menuValues[0] != function){
    // Clear current menu
    memset(menuOptions, 0x00, sizeof(menuOptions)); // for automatically-allocated arrays
    memcpy(menuOptions, menuValues, menuSize);
//    Serial.println("*** menuValue [0]");
  } else {    
    if (returnToCurrent != 0){
      // Clear current menu
      memset(menuOptions, 0x00, sizeof(menuOptions)); // for automatically-allocated arrays
//      Serial.println("*** menuValue [1]");
      menuOptions[0] = returnToCurrent;//tempReturnToCurrent;  --- fix this......
      //    }
    } else {
//      Serial.println("*** menuValue [2]");
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
  returnToCurrent = 0;
}

// ===========================================
// Main Menu
// ===========================================
void lcdMainX000() {
  if (repeatCount == 0) {
    setMenu("x000", menuOptions000, menuOptions000SIZE);
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

  lcd.setCursor(17, 3); //   row >    column ^
  lcd.print(repeatCount);
  lcd.print(" ");
}

// ===========================================
// lcdMenuX01
// ===========================================
void lcdMenuX001() {
  if (repeatCount == 0) {
    setMenu("x001", menuOptions001, menuOptions001SIZE);
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

  if (false) {
    printCD4052();
  }

  if (false) {
    //    printCD4052Volts();
  }



}

// ===========================================
// lcdMenuX02
// ===========================================
void lcdMenuX002() {
  if (repeatCount == 0) {
    setMenu("x002", menuOptions002, menuOptions002SIZE);
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
  lcd.print("KeyV: ");

  lcd.print  (refValue * analog[3]);
  lcd.print  ("V ");

  lcd.setCursor(0, 1); //   row >    column ^
  lcd.print("Value: ");
  lcd.print  (analog[3]);
  lcd.print("   ");

  //  lcd.setCursor(0, 2); //   row >    column ^
  //  lcd.print("Key Down: ");
  //  lcd.print  (keyDown);

  lcd.setCursor(0, 3); //   row >    column ^
  lcd.print("Key Pressed: ");
  lcd.print  (keyPress);


  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  if (false) {
    printCD4052();
  }

  if (keyPress == 1) {
    menuSelected = 0;
  }

}

// ===========================================
// lcdMenuX10
// ===========================================
void lcdMenuX010() {
  if (repeatCount == 0) {
    setMenu("x010", menuOptions010, menuOptions010SIZE);
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
// lcdMenuX11
// ===========================================
void lcdMenuX011() {
  if (repeatCount == 0) {
    setMenu("x011", menuOptions011, menuOptions011SIZE);
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
// lcdMenuX12
// ===========================================
void lcdMenuX012() {
  if (repeatCount == 0) {
    setMenu("x012", menuOptions012, menuOptions012SIZE);
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
// lcdMenuX13
// ===========================================
void lcdMenuX013() {
  if (repeatCount == 0) {
    setMenu("x013", menuOptions013, menuOptions013SIZE);
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
//lcdMenuX014
//===========================================
//void lcdMainFlightTime(){
//void updateFPS(){

long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second

void lcdMenuX014() {
  // check to see if it's time to update LCD; that is, if the difference
  // between the current time and last time you updated the LCD is bigger than
  // the interval at which you want to blink the LED.

  if (repeatCount == 0)
  {
    setMenu("x014", menuOptions014, menuOptions014SIZE);
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


    if (++cntMillis >= (1000 / screenRefresh))
    {
      // -------------------------------------
      lcd.setCursor(0, 0); //   row >    column ^
      lcd.print("Flight: ");
      long timeNow = millis();

      int days = timeNow / day ;                                //number of days
      int hours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
      int minutes = ((timeNow % day) % hour) / minute ;         //and so on...
      int seconds = (((timeNow % day) % hour) % minute) / second;
      // lcd.print("MM:SS");
      //fmt.printInt(days,"%2d:");
      lcd.print(days);
      lcd.print(":");
      lcd.print(hours);
      lcd.print(":");
      lcd.print(minutes);
      lcd.print(":");
      lcd.print(seconds);
      lcd.print(" ");

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
    setMenu("x200", menuOptions200, menuOptions200SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Int number edit");
  }

  lcd.blink();
  lcd.setCursor(row+1, col+4); //   row >    column ^
}

void lcdFunc201() { //Double number edit
  if (repeatCount == 0) {
    setMenu("x201", menuOptions201, menuOptions201SIZE);
    lcd.setCursor(0, 3); //   row >    column ^
    lcd.print("Double number edit");
  }

  lcd.blink();
  lcd.setCursor(row+1, col+4); //   row >    column ^
}

// -------------------------------------------
void lcdInit244() { // Menu
  if (repeatCount == 0) {
    setMenu("x244", menuOptions244, menuOptions244SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Menu");
  }
}

// -------------------------------------------
void lcdInit245() { // Trim
  if (repeatCount == 0) {
    setMenu("x245", menuOptions245, menuOptions245SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Trim");
  }
}

// -------------------------------------------
void lcdInit246() { // Switch
  if (repeatCount == 0) {
    setMenu("x246", menuOptions246, menuOptions246SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Switch");
  }
}

// -------------------------------------------
void lcdInit247() { // Joystick
  if (repeatCount == 0) {
    setMenu("x247", menuOptions247, menuOptions247SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Joystick");
  }
}

// -------------------------------------------
void lcdInit248() { // Shunt ohms
  if (repeatCount == 0) {
    setMenu("x248", menuOptions248, menuOptions248SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Shunt");
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print("ohms ");      
  }
}

// -------------------------------------------
void lcdInit249() { // Vin pre 1.1 & 1.2 ohms
  if (repeatCount == 0) {
    setMenu("x249", menuOptions249, menuOptions249SIZE);
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
    setMenu("x250", menuOptions250, menuOptions250SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("Vin post ohms");
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print("2.1 ");    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print("2.2 ");    
  }
}

// -------------------------------------------
void lcdInit251() { // V5.0    3.1 & 3.2 ohms
  if (repeatCount == 0) {
    setMenu("x251", menuOptions251, menuOptions251SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("V5.0 ohm");
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print("3.1 ");    
    lcd.setCursor(2, 2); //   row >    column ^
    lcd.print("3.2 ");    
  }
}

// -------------------------------------------
void lcdInit252() {  // V5.0    Regulator Voltage
  if (repeatCount == 0) {
    setMenu("x252", menuOptions252, menuOptions252SIZE);
    lcd.setCursor(0, 0); //   row >    column ^
    lcd.print("V5.0 volts");
    lcd.setCursor(2, 1); //   row >    column ^
    lcd.print("V ");       
  }

  rowEdit = 0; //   row >    column ^  
  colEdit = 0; //   row >    column ^  
  
  // test print custom char.
  //lcd.setCursor(3, 3); //   row >    column ^
   
}

// -------------------------------------------
void lcdInit253() { // Splash     [no click (select) out to 253]
  if (repeatCount == 0) {
    setMenu("x253", menuOptions253, menuOptions253SIZE);    
    lcd.setCursor(0, 0);//   row >    column ^
    lcd.print(qBytesWorld);
    lcd.setCursor(0, 1);//   row >    column ^
    lcd.print(deviceInfo);
    lcd.setCursor(0, 2);//   row >    column ^
    lcd.print(versionNum);
    lcd.setCursor(0, 3);//   row >    column ^
    lcd.print("Volts:");
  }

  lcd.setCursor(7, 3);//   row >    column ^
  printVolts();

  if (repeatCount > 7) {//delay(2000);

// DAQ finish this....
// DAQ finish this....
// DAQ finish this....

     // If first time run (no EEPROM data)
    if (true){
      menuSelected = 252; // Initialize values
    } else {
      menuSelected = 0;   // Go to Main Menu
    }
  }
}

// -------------------------------------------
void lcdInit254() {  // Starting   [click (select) out to 254]
  if (repeatCount == 0) {
    setMenu("x254", menuOptions254, menuOptions254SIZE);
    lcd.init();
    lcd.begin(20,4);
    lcd.backlight();
  //lcd.blink();
    lcd.noBlink();
    
    lcd.setCursor(0, 0);//   row >    column ^
    lcd.print("Startup");

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
  }
  
  if (repeatCount > 1) { // ~delay(250);
    menuSelected = 253;
  }
}

// -------------------------------------------
void lcdInit255() { // this is an error, 255 if for FUNCTIONS  
  while (true){
    Serial.println("ER255");
  }
}

void updateLCD() {
  // Detect Menu change

  if (menuCurrent != menuSelected) {
    returnToCurrent = menuCurrent;
    if (false){
      Serial.print ("Cur ");
      Serial.print (menuCurrent);
      Serial.print ("Sel ");
      Serial.print (menuSelected);
      Serial.print ("RTC ");
      Serial.print (returnToCurrent);
      Serial.println();
    }

    if (!(menuSelected >200 && menuSelected < 240)){// Don't clear the screen
      lcd.clear();
    }
    repeatCount = 0;
    col = 0;
    menuCurrent = menuSelected;

    if (menuCurrent == 0 || menuCurrent >= 250) {
      lcd.noBlink();
    } else {
      lcd.blink();
    }
  }

  if (keyPress > 0) {
    if (keyPress == 5) {// up
      if (col > 0)
        col--;
    }
    if (keyPress == 3) {// down
      if (col < (menuSize-1))
        col++;
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
//    Serial.println(menuOptions[col]);
    menuSelected = menuOptions[col];
  }

  switch (menuSelected) {
    // ---------------------------------------
    case 000:
      lcdMainX000();
      break;
    // ---------------------------------------
    case 001: //lcdMainVolts();
      lcdMenuX001();      
      break;
    // ---------------------------------------
    case 002: //lcdKeyVolts();
      lcdMenuX002();      
      break;
    // ---------------------------------------
    case 010:
      lcdMenuX010();
      break;
    // ---------------------------------------
    case 011:
      lcdMenuX011();
      break;
    // ---------------------------------------
    case 012:
      lcdMenuX012();
      break;
    // ---------------------------------------
    case 013:
      lcdMenuX013();
      break;
    // ---------------------------------------
    case 014:      //  updateFPS();
      lcdMenuX014();
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
      break;
  }

  // Set Repeat Count
  //repeatCount;
  if (++repeatCount > 31) {
    repeatCount = 0;
  }
}


// -------------------------------------------
// -------------------------------------------
//------------------------------------------------------
// Print CD4052 analog
//------------------------------------------------------
void printCD4052() {
  for (analogLoop = 0 ; analogLoop < 4; analogLoop++) {
    fmt.printInt(analogLoop, "<X%1d:");
    fmt.printInt(analogLoop * 2, "%1d:");
    fmt.printInt(analog[(analogLoop * 2)    ], "%4d> ");
    fmt.printInt(analogLoop, "<Y%1d:");
    fmt.printInt((analogLoop * 2) + 1, "%1d:");
    fmt.printInt(analog[(analogLoop * 2) + 1], "%4d> ");
  }
  //  Serial.println("");
}

//------------------------------------------------------
// Print CD4052 volts (analog)
//------------------------------------------------------

//void printCD4052Volts(){
//  // -----------------------------------------------
//  // 5 = y2 =   5V
//  Serial.print  ("5V: ");
//  Serial.print  (analog[5]);
//  Serial.print  ("  ");
//  Serial.print  (refValue * analog[5]);
//  Serial.print  ("V  ");
////Ein = (Eo/R2) * (R1+R2)
//  Serial.print  (v5_0);
//  Serial.print  ("V ");
//
//  // -----------------------------------------------
//  // 7 = y3 = Pre
//  Serial.print  (" xxxxx  Pre: ");
//  Serial.print  (analog[7]);
//  Serial.print  ("  ");
//  Serial.print  (refValue * analog[7]);
//  Serial.print  ("V  ");
////Ein = (Eo/R2) * (R1+R2)
//  Serial.print  (vPre);
//  Serial.print  ("V ");
//
//  // -----------------------------------------------
//  // 1 = y0 = Post,
//  Serial.print  (" xxxxx  Post: ");
//  Serial.print  (analog[1]);
//  Serial.print  ("  ");
//  Serial.print  (refValue * analog[1]);
//  Serial.print  ("V  ");
////Ein = (Eo/R2) * (R1+R2)
//  Serial.print  (vPst);
//  Serial.print  ("V ");
//
//  // -----------------------------------------------
//  //I = E / R (R = shunt)
//  Serial.print (" Current ");
//  Serial.print (avgSum/avgSize);
//  Serial.print ("mV ");
//  Serial.print ((avgSum/avgSize)/myVoltsMap.shunt);
//  Serial.print ("mA");
//
////  Serial.println("");
//}


// ===========================================
// ===========================================
// ===========================================
// Setup
// ===========================================
// ===========================================
// ===========================================
void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite (2, LOW);
  analogReference(EXTERNAL);

  // Debug Serial out
  Serial.begin(115200); //Set the speed to 9600 bauds if you want.
  //  pinMode(debugPin, INPUT);      // sets the digital pin as input

//  //Print length of data to run CRC on.
//  Serial.print("EEPROM length: ");
//  Serial.println(EEPROM.length());


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
