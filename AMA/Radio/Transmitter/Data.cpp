/*
  Data.h - Data library for Wiring - implementation
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
//#include "HardwareSerial.h"

// include this library's description file
#include "Data.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Data::Data(){
  // initialize this instance's variables
  //value = givenValue;

  // do whatever is required to initialize the library
//  pinMode(13, OUTPUT);
//  Serial.begin(115200);
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

void Data::aux(byte b, int d){
//  Serial.print  (b);
//  Serial.print  (" ");
//  Serial.print  (d);
//  Serial.println();
}


//  myControls.throttle = mapJoystickRange( analogRead(A0), myControlsMapThrottle.Min, myControlsMapThrottle.Mid, myControlsMapThrottle.Max, myControlsMapThrottle.Rev);
//  myControls.yaw      = mapJoystickRange( analogRead(A1), myControlsMapYaw.Min,      myControlsMapYaw.Mid,      myControlsMapYaw.Max,      myControlsMapYaw.Rev);
//  myControls.roll     = mapJoystickRange( analogRead(A2), myControlsMapRoll.Min,     myControlsMapRoll.Mid,     myControlsMapRoll.Max,     myControlsMapRoll.Rev);
//  myControls.pitch    = mapJoystickRange( analogRead(A3), myControlsMapPitch.Min,    myControlsMapPitch.Mid,    myControlsMapPitch.Max,    myControlsMapPitch.Rev);
void Data::setAnalog(byte b, int d){
//  Serial.print  (b);
//  Serial.print  (" ");
//  Serial.print  (d);
//  Serial.println();
  analog[b]=d;
}
int Data::getAnalog(byte b){

//  Serial.print  (b);
//  Serial.print  (" ");

  return analog[b];
}


//// ===========================================
//// Update LCD
//// ===========================================
//uint16_t v5_System     = 0;
//uint16_t v5_Measured   = 4919; //5011;
//uint16_t v5_voltPerBit = (v5_Measured / 1023.0)*1000.0;
//
//double vPre = 0.0;
//double vPst = 0.0;
//double vKey = 0.0;


//  myAux.AUX1 = analog[0];
//  myAux.AUX2 = analog[2];
//  myAux.AUX3 = analog[4];
//  myAux.AUX4 = analog[8];

//  vKey =    v5_voltPerBit * analog[3];                                                                                 // Key
//  vPst =      (((v5_voltPerBit * analog[1]) / myResistorMap.Vpst22) * (myResistorMap.Vpst21 + myResistorMap.Vpst22));  // V Post
//  v5_System = (((v5_voltPerBit * analog[5]) / myResistorMap.V5_32 ) * (myResistorMap.V5_31  + myResistorMap.V5_32 ));  // 5.0V
//  vPre =      (((v5_voltPerBit * analog[7]) / myResistorMap.Vpre12) * (myResistorMap.Vpre11 + myResistorMap.Vpre12));  // V Pre
//
//  // ======================================================

//byte    avgSize = 50;
//double  avgList[50];
//int     avgCnt = 0;
//double  avgSum = 0.0;
//double  avg = 0.0;

//  if (avgCnt >= avgSize) {
//    avgCnt = 0;
//  }
//  avgList[avgCnt++] = (vPre - vPst) * 1000;
//
//  avgSum = 0;
//  for (int lp = 0; lp < avgSize; lp++) {
//    avgSum += avgList[lp];
//  }
//
//  


//// ===========================================
//// Reset
//// ===========================================
//void resetData()
//{
//  //This are the start values of each channal
//  // Throttle is 0 in order to stop the motors
//  //128 is the middle value of the 10 bit ADC.
//
//  myControls.throttle = 0;    // no power
//  myControls.yaw      = MID;  // center control
//  myControls.pitch    = MID;  // center control
//  myControls.roll     = MID;  // center control
//
//  myAux.AUX1     = 0;
//  myAux.AUX2     = 0;
//  myAux.AUX3     = 0;
//  myAux.AUX4     = 0;
//
//  myButtons.swtch = 0;
//  myButtons.dip   = 0;
//  myButtons.menu  = 0;
//}


// ===========================================
void myControlsMapSetIt(MyControlsMap item) {
  item.Min = 0;
  item.Mid = 1023/2;
  item.Max = 1023;
  item.Rev = false;
}

//// ===========================================
//void myControlsMapSet() {
//  myControlsMapSetIt(myControlsMapThrottle);  // A0
//  myControlsMapSetIt(myControlsMapYaw);       // A1
//  myControlsMapSetIt(myControlsMapRoll);      // A2
//  myControlsMapSetIt(myControlsMapPitch);     // A3
//}
//
//// ===========================================
//// ===========================================
//// ===========================================
//// Init contoller
//// ===========================================
//// ===========================================
//// ===========================================
//void initSticksIt(MyControlsMap item) {
//  item.Min = 0;    // A0
//  item.Mid = 512;  // A0
//  item.Max = 1023; // A0
//  item.Rev = false;
//}
//
//void initSticks() {
//  lcd.print(F("Move Throttle up/down"));
//  initSticksIt(myControlsMapThrottle);  // A0
//
//  lcd.print(F("Move Yaw up/down"));
//  initSticksIt(myControlsMapYaw);       // A1
//
//  lcd.print(F("Move Roll up/down"));
//  initSticksIt(myControlsMapRoll);      // A2
//
//  lcd.print(F("Move Pitch up/down"));
//  initSticksIt(myControlsMapPitch);     // A3
//}

// ===========================================
// Map Joystick Values
// ===========================================
// Returns a full-range value for a joystick position that takes into account
// the values of the outer extents and the middle of the joystick range.
int Data::mapJoystickRange(int value, int minimum, int middle, int maximum, bool reverse)
{
  value = constrain(value, minimum, maximum);
  
  if ( value < middle )
    value = map(value, minimum, middle, 0, MID);
  else
    value = map(value, middle, maximum, MID, MAX);
    
  return ( reverse ? MAX - value : value );
}









// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


