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

#include <limits.h> //Access to TYPE sizes (MIN & MAX values)

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Data::Data(){
  // initialize this instance's variables
  //value = givenValue;

  // do whatever is required to initialize the library

}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

// =====================================
// Get the structures
// =====================================


MyControlsRangeMap& Data::getMyControlsRangeMap(byte control){
  return myControlsRangeMap[control];
}

MyVoltageMap& Data::getMyVoltageMap(){
  return myVoltageMap;
}

MyResistorMap& Data::getMyResistorMap(){
  return myResistorMap;
}

MySwitchMap& Data::getMySwitchMap(){
  return mySwitchMap;
}

void Data::setJoyAux(byte b, int i){
  aux[b] = i;
}

int  Data::getJoyAux(byte b){
  return aux[b];
}
    
// =====================================
// uint16_t Methods
// =====================================
uint16_t* pointerUint16_t;
    
void Data::setUint16_tPointer(void * pVoid){
  pointerUint16_t = (uint16_t*)pVoid;
  Serial.print  ("setUint16_tPointer: ");
  Serial.println(*(uint16_t*)pVoid);
}

void Data::setUint16_tNumber(int16_t number){
  *(uint16_t*)pointerUint16_t = number;
  Serial.print  ("setUint16_tNumber: ");
  Serial.println(number);
}

void Data::adjUint16_tNumber(int8_t incDirection, int8_t expoFactor){

  int16_t expoValue = 1;

  // POW
  // POW has a bug (not whole numbers).  It's a float point thing
  // https://ucexperiment.wordpress.com/2016/02/02/floating-point-precision-or-arduino-dont-know-math/
  for (uint8_t i = 0; i < expoFactor; i++){
     expoValue *= 10;
  }

  // Set Sign
  expoValue *= incDirection;

  // Test variable limit exceed size limit, set to MAX or MIN value.
  if (incDirection > 0){
    // Increase test
    if (*(uint16_t*)pointerUint16_t > (*(uint16_t*)pointerUint16_t + expoValue)){
      // Exceeded MAX limit
      *(uint16_t*)pointerUint16_t = USHRT_MAX; // limit.h
    }else{
      *(uint16_t*)pointerUint16_t += expoValue;
    }
  } else {
    // Decrease test
    if (*(uint16_t*)pointerUint16_t < (*(uint16_t*)pointerUint16_t + expoValue)){
      // Exceeded MIN limit
      *(uint16_t*)pointerUint16_t = 0;   // limit.h
    }else{
      *(uint16_t*)pointerUint16_t += expoValue;
    }
  }

  // Print the value
  if (false){
    Serial.print  ("adjUint16_tNumber: ");
    Serial.print  (expoValue);
    Serial.print  ("*(uint16_t*)pointerUint16_t: ");
    Serial.print  (*(uint16_t*)pointerUint16_t);
    Serial.println();
  }
}

// deprecated method (use adjUint16_tNumber(int8_t incDirection, int8_t expoFactor)
void Data::adjUint16_tNumber(int16_t number){

  *(uint16_t*)pointerUint16_t += number;
  Serial.print  ("adjUint16_tNumber: ");
  Serial.println(number);
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

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library


