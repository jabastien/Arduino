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
// EEPROM
// ===========================================
#include <EEPROM.h>

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
int menuCurrent  =  -1;
int menuSelected = 255;

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

byte line = 0;


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

// ===========================================
// ===========================================
// ===========================================
// EEPROM
// ===========================================
// ===========================================
// ===========================================
void factoryReset() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

void readEEPROM() {
  int eeAddress = 0;

  EEPROM.get(eeAddress, myVoltsMap);
  eeAddress += sizeof(myVoltsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.

  //
  EEPROM.get(eeAddress, myControlsMapThrottle);
  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
  //  eeAddress += sizeof(myControlsMapThrottle); //Move address to the next byte after MyControlsMap 'myControlsMap'.

  EEPROM.get(eeAddress, myControlsMapYaw);
  eeAddress += sizeof(myControlsMapThrottle); //Move address to the next byte after MyControlsMap 'myControlsMap'.

  EEPROM.get(eeAddress, myControlsMapRoll);
  eeAddress += sizeof(myControlsMapThrottle); //Move address to the next byte after MyControlsMap 'myControlsMap'.

  EEPROM.get(eeAddress, myControlsMapPitch);
  eeAddress += sizeof(myControlsMapThrottle); //Move address to the next byte after MyControlsMap 'myControlsMap'.
}


void writeEEPROM() {
  int eeAddress = 0;

  //
  EEPROM.put(eeAddress, myVoltsMap);
  eeAddress += sizeof(myVoltsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.

  //
  //eeAddress += sizeof(myControlsMapSet);
  EEPROM.put(eeAddress, myControlsMapThrottle);
  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.

  EEPROM.put(eeAddress, myControlsMapYaw);
  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.

  EEPROM.put(eeAddress, myControlsMapRoll);
  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.

  EEPROM.put(eeAddress, myControlsMapPitch);
  eeAddress += sizeof(MyControlsMap); //Move address to the next byte after MyControlsMap 'myControlsMap'.
}

#define membersof(x) (sizeof(x) / sizeof(x[0]))


// Declare variables
//https://arduino.stackexchange.com/questions/19748/copy-content-of-array
//https://arduino.stackexchange.com/questions/21095/how-to-write-array-of-functions-in-arduino-library
byte menuOptions00 [2] = {0, 10};
byte menuOptions10 [5] = {0, 11, 12, 13, 14};

byte menuOptions11 [1] = {10};
byte menuOptions12 [1] = {10};
byte menuOptions13 [1] = {10};
byte menuOptions14 [1] = {10};

byte menuOptions[10];

const byte menuOptions00SIZE = membersof(menuOptions00);
const byte menuOptions10SIZE = membersof(menuOptions10);
const byte menuOptions11SIZE = membersof(menuOptions11);
const byte menuOptions12SIZE = membersof(menuOptions12);
const byte menuOptions13SIZE = membersof(menuOptions13);
const byte menuOptions14SIZE = membersof(menuOptions14);

//const byte menuOptions90SIZE = membersof(menuOptions90);
//  setMenu("mo00", menuOptions00,menuOptions00SIZE);
//  setMenu("mo10", menuOptions10,menuOptions10SIZE );
//  setMenu("mo90", menuOptions90,menuOptions90SIZE );

//#define menuOptions10SIZE (sizeof(menuOptions10) / sizeof(byte))

PROGMEM const String sampleMenu_back = "Back";
PROGMEM const String sampleMenu_exit = "Exit";

PROGMEM const String sampleMenu_2_1_1 = "1 Sub item A";
PROGMEM const String sampleMenu_2_1_2 = "2 Sub item B";

void setMenu(String menuOpt, byte menuValues[], int sizeIs) {
  if (sizeIs > sizeof(menuOptions)) {
    Serial.print  ("Err: setMenu ");
    Serial.print  (sizeIs);
    Serial.print  (" for ");
    Serial.print  (menuOpt);
    sizeIs = sizeof(menuOptions);
    Serial.print  (" s/b <= ");
    Serial.println(sizeIs);
  }

  memset(menuOptions, 0x0, sizeof(menuOptions)); // for automatically-allocated arrays
  memcpy(menuOptions, menuValues, sizeIs);

  if (true) {
    Serial.print  (menuOpt);
    for (byte loop = 0; loop < sizeof(menuOptions); loop++) {
      Serial.print  (menuOptions[loop]);
      Serial.print  (", ");
    }
    Serial.println("");
  }
}

// ===========================================
// Main Menu
// ===========================================
void lcdMain000() {
  if (repeatCount == 0) {
    Serial.print  (" -> lcdMain000");
    lcd.setCursor(0, 0);
    lcd.print("Main");
    lcd.setCursor(0, 1);
    lcd.print("Repeat: ");

    setMenu("mo00", menuOptions00, menuOptions00SIZE);
  }

  lcd.setCursor(9, 1);
  lcd.print(repeatCount);
  lcd.print(" ");

  lcd.setCursor(1, 2);
  lcd.print(sampleMenu_2_1_1);

}

// ===========================================
// lcdMenuX10
// ===========================================
void lcdMenuX10() {
  if (repeatCount == 0) {
    Serial.print  (" -> lcdMenuX10");
    lcd.setCursor(0, 0);
    lcd.print("10 -> 11");
    lcd.setCursor(0, 1);
    lcd.print("10 -> 12");
    lcd.setCursor(0, 2);
    lcd.print("10 -> 13");
    lcd.setCursor(0, 3);
    lcd.print("10 -> 14");
    lcd.print(" Repeat: ");

    setMenu("mo10", menuOptions10, menuOptions10SIZE);
  }

  //  lcd.setCursor(17, 1);
  //  lcd.print(repeatCount);
  //  lcd.print(" ");
}


// ===========================================
// lcdMenuX11
// ===========================================
void lcdMenuX11() {
  if (repeatCount == 0) {
    Serial.print  (" -> lcdMenuX11");
    lcd.setCursor(0, 0);
    lcd.print("x11");
    lcd.setCursor(0, 1);
    lcd.print("Repeat: ");

    setMenu("mo11", menuOptions11, menuOptions11SIZE);
  }

  lcd.setCursor(9, 1);
  lcd.print(repeatCount);
  lcd.print(" ");
}

// ===========================================
// lcdMenuX12
// ===========================================
void lcdMenuX12() {
  if (repeatCount == 0) {
    Serial.print  (" -> lcdMenuX12");
    lcd.setCursor(0, 0);
    lcd.print("x12");
    lcd.setCursor(0, 1);
    lcd.print("Repeat: ");

    setMenu("mo12", menuOptions12, menuOptions12SIZE);
  }

  lcd.setCursor(9, 1);
  lcd.print(repeatCount);
  lcd.print(" ");
}

// ===========================================
// lcdMenuX13
// ===========================================
void lcdMenuX13() {
  if (repeatCount == 0) {
    Serial.print  (" -> lcdMenuX13");
    lcd.setCursor(0, 0);
    lcd.print("x13");
    lcd.setCursor(0, 1);
    lcd.print("Repeat: ");

    setMenu("mo13", menuOptions13, menuOptions13SIZE);
  }

  lcd.setCursor(9, 1);
  lcd.print(repeatCount);
  lcd.print(" ");
}

// ===========================================
// lcdMenuX14
// ===========================================
//void lcdMenuX14(){
////  if (repeatCount == 0)
//  {
//    Serial.print  (" -> lcdMenuX14");
//    lcd.setCursor(0, 0);
//    lcd.print("x14");
//    lcd.setCursor(0, 1);
//    lcd.print("Repeat: ");
//
//    setMenu("mo14", menuOptions14,menuOptions14SIZE);
//  }
//
//  lcd.setCursor(9, 1);
//  lcd.print(repeatCount);
//  lcd.print(" ");
//}


// -------------------------------------------
//////void lcdMainFlightTime(){


long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second


//void updateFPS(){
void lcdMenuX14() {
  // check to see if it's time to update LCD; that is, if the difference
  // between the current time and last time you updated the LCD is bigger than
  // the interval at which you want to blink the LED.

  if (repeatCount == 0)
  {
    Serial.print  (" -> lcdMenuX14");
    lcd.setCursor(0, 0);
    lcd.print("x14");
    lcd.setCursor(0, 1);
    lcd.print("Repeat: ");

    setMenu("mo14", menuOptions14, menuOptions14SIZE);
  }
  //  fps++;
  currentMillis = millis();

  if (currentMillis - previousMillis >= screenRefresh) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    //    lcd.setCursor(0, 1);
    //    printVolts();    //Voltage: xx.xV


    if (++cntMillis >= (1000 / screenRefresh))
    {
      // -------------------------------------
      lcd.setCursor(0, 0);
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
      lcd.setCursor(0, 2);
      lcd.print("Channel:");
      lcd.print(" xxx");

      // -------------------------------------
      lcd.setCursor(0, 3);
      lcd.print("FPS:");
      lcd.print(fps);  // ~350 has been the average
      lcd.print("   GPS: xxx");

      // -------------------------------------
      fps = 0;
      cntMillis = 0;
    }
  }
  lcd.setCursor(9, 1);
  lcd.print(repeatCount);
  lcd.print(" ");
}

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


// -------------------------------------------
void lcdKeyVolts() {
  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 0);
  lcd.print("KeyV: ");

  lcd.print  (refValue * analog[3]);
  lcd.print  ("V ");

  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print  (analog[3]);
  lcd.print("   ");

  //  lcd.setCursor(0, 2);
  //  lcd.print("Key Down: ");
  //  lcd.print  (keyDown);

  lcd.setCursor(0, 3);
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


// -------------------------------------------
void lcdMainVolts() {
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
  lcd.setCursor(0, 0);
  lcd.print("PreV: ");

  lcd.print  (refValue * analog[7]);
  lcd.print  ("V   ");

  //Ein = (Eo/R2) * (R1+R2)
  lcd.print (vPre);
  lcd.print  ("V");

  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 1);
  lcd.print("PstV: ");

  lcd.print  (refValue * analog[1]);
  lcd.print  ("V   ");

  //Ein = (Eo/R2) * (R1+R2)
  lcd.print (vPst);
  lcd.print  ("V");

  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 2);
  lcd.print("5.0V: ");

  lcd.print  (refValue * analog[5]);
  lcd.print  ("V    ");

  //Ein = (Eo/R2) * (R1+R2)
  lcd.print (v5_0);
  lcd.print  ("V");

  //--------------------
  //
  //--------------------
  lcd.setCursor(0, 3);
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

// -------------------------------------------
void lcdInit254() {
  if (repeatCount == 0) {
    Serial.print  (" -> lcdInit254");
    lcd.setCursor(0, 0);
    lcd.print(qBytesWorld);
    lcd.setCursor(0, 1);
    lcd.print(deviceInfo);
    lcd.setCursor(0, 2);
    lcd.print(versionNum);
    lcd.setCursor(0, 3);
    lcd.print("Volts:");
  }

  lcd.setCursor(7, 3);
  printVolts();

  if (repeatCount > 8) { //  //delay(2000);
    menuSelected = 0;
  }
}

// -------------------------------------------
void lcdInit255() {


  //  Serial.print  (" -> lcdInit255");
  lcd.init();
  lcd.backlight();
  //  lcd.blink();
  lcd.noBlink();

  if (repeatCount == 0) {
    Serial.print  (" -> lcdInit255");
    lcd.setCursor(0, 0);
    lcd.print("x255");
    lcd.setCursor(0, 1);
    lcd.print("Repeat: ");

    setMenu("x255", menuOptions14, menuOptions14SIZE);
  }

  menuSelected = 254;
}

void updateLCD() {

  // Detect Menu change
  if (menuCurrent != menuSelected) {
    lcd.clear();
    repeatCount = 0;
    line = 0;
    menuCurrent = menuSelected;

    if (menuSelected == 0 || menuSelected >= 250) {
      lcd.noBlink();
    } else {
      lcd.blink();
    }
  }

  if (keyPress > 0) {

    if (keyPress == 5) {
      if (line > 0)
        line--;
    }

    if (keyPress == 3) {
      if (line <= 3)
        line++;
    }

    Serial.print  (keyPress);
    Serial.print  (" ");
    Serial.println(line);

    lcd.setCursor(0, line);
  }

  if (keyPress == 1) {
    Serial.println(menuOptions[line]);
    menuSelected = menuOptions[line];
  }

  switch (menuSelected) {
    // ---------------------------------------
    case 0:
      lcdMain000();

      break;
    // ---------------------------------------
    case 1:
      lcdMainVolts();
      break;
    // ---------------------------------------
    case 2:
      lcdKeyVolts();
      break;


    // ---------------------------------------
    case 10:
      lcdMenuX10();

      break;
    // ---------------------------------------
    case 11:
      lcdMenuX11();

      break;
    // ---------------------------------------
    case 12:
      lcdMenuX12();

      break;
    // ---------------------------------------
    case 13:
      lcdMenuX13();

      break;
    // ---------------------------------------
    case 14:
      lcdMenuX14();
      //  updateFPS();
      break;

    // ---------------------------------------
    case 254:
      lcdInit254();
      break;
    // ---------------------------------------
    case 255:
      lcdInit255();
      break;
    // ---------------------------------------
    default:
      // catch all - N/A
      Serial.print  ("Menu Error: " );
      Serial.println(menuSelected);
      menuSelected = 255;
      break;
  }

  // Set Repeat Count
  repeatCount++;
  if (repeatCount > 32) {
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

  //Print length of data to run CRC on.
  Serial.print("EEPROM length: ");
  Serial.println(EEPROM.length());


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
  //keyPad.doKeys(analogRead(A0));
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
  //  else {
  //    if (false){
  //      Serial.print  (currentMillis);
  //      Serial.print  (" ");
  //      Serial.print  (screenLastRefresh);
  //      Serial.print  (" ");
  //      Serial.println(screenRefresh);
  //    }
  //  }

  //------------------------------------------------------
  // Serial Debugging
  serialDebug();
}
