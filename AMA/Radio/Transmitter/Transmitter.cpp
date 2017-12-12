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

#include "Data.h"
#include "DataStore.h"
#include "Menu.h"

// ===========================================
// Vars
// ===========================================

Data data = Data();
//DataStore dataStore = DataStore(data);
DataStore dataStore = DataStore();
Menu menu = Menu();


MyResistorMap myResistorMap;
MyButtons myButtons;
MyAux myAux;
MyControls myControls;
MyControlsMap myControlsMapThrottle;
MyControlsMap myControlsMapYaw;
MyControlsMap myControlsMapRoll;
MyControlsMap myControlsMapPitch;




// ===========================================
// Update LCD
// ===========================================
uint16_t v5_System     = 0;
uint16_t v5_Measured   = 4919; //5011;
uint16_t v5_voltPerBit = (v5_Measured / 1023.0)*1000.0;

double vPre = 0.0;
double vPst = 0.0;
double vKey = 0.0;

// ===========================================
// Local vars
// ===========================================
int fps = 0;

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



// ===========================================
// CD4052
// ===========================================
#include <CD4052.h>

CD4052 cd4052 = CD4052(5, 4, A7, A6);

int analog[8];



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
  lcd.print(F("Move Throttle up/down"));
  initSticksIt(myControlsMapThrottle);  // A0

  lcd.print(F("Move Yaw up/down"));
  initSticksIt(myControlsMapYaw);       // A1

  lcd.print(F("Move Roll up/down"));
  initSticksIt(myControlsMapRoll);      // A2

  lcd.print(F("Move Pitch up/down"));
  initSticksIt(myControlsMapPitch);     // A3
}

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

// ===========================================
// ===========================================
// ===========================================
// Setup
// ===========================================
// ===========================================
// ===========================================

void setup(){
//  pinMode(2, OUTPUT);
//  digitalWrite (2, LOW);
  analogReference(EXTERNAL);

  // Debug Serial out
  Serial.begin(115200); //Set the speed to 9600 bauds if you want.
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  Serial.println("In setup");
  dataStore = DataStore(data);
  Serial.println("Out setup");
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

  //dataStore.factoryReset();


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
  for (byte digitalLoop = 0; digitalLoop < 8 ; digitalLoop++) {
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
  for (byte analogLoop = 0 ; analogLoop < 4; analogLoop++) {
    // Switch address for 4052 (1x)
    cd4052.setChannel(analogLoop);
    analog[(analogLoop * 2)    ] = cd4052.analogReadX();
    analog[(analogLoop * 2) + 1] = cd4052.analogReadY();
  }

  myAux.AUX1 = analog[0];
  myAux.AUX2 = analog[2];
  myAux.AUX3 = analog[4];
  myAux.AUX4 = analog[8];

  vPst = (((v5_voltPerBit * analog[1]) / myResistorMap.Vpst22) * (myResistorMap.Vpst21 + myResistorMap.Vpst22));  // V Post
  vKey =    v5_voltPerBit * analog[3];                                                                   // Key
  v5_System = (((v5_voltPerBit * analog[5]) / myResistorMap.V5_32 ) * (myResistorMap.V5_31  + myResistorMap.V5_32 ));  // 5.0V
  vPre = (((v5_voltPerBit * analog[7]) / myResistorMap.Vpre12) * (myResistorMap.Vpre11 + myResistorMap.Vpre12));  // V Pre

  // ======================================================
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
  // Update LCD 1/10 seconds
  //------------------------------------------------------
  if (keyPress > 0 || menu.isScreenRefreshNeeded()) {
    menu.updateLCD(keyPress, fps);
    fps = 0;
  }

  //------------------------------------------------------
  // Inc Frames Per Second
  //------------------------------------------------------
  fps++;

  //------------------------------------------------------
  // Serial Debugging
  //serialDebug();
}
