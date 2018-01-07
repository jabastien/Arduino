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


MyControlsRangeMap& Data::getMyJoysticksRangeMap(byte control){
  return myJoysticksRangeMap[control];
}

MyControlsRangeMap& Data::getMyAuxsRangeMap(byte control){
  return myAuxsRangeMap[control];
}

MyVoltageMap& Data::getMyVoltageMap(){
  return myVoltageMap;
}

MyResistorMap& Data::getMyResistorMap(){
  return myResistorMap;
}

MySwitchesButtons& Data::getMySwitchesButtons(){
  return mySwitchesButtons;
}

void Data::setVolts(byte b, int i){
  volts[b] = i;

#ifdef DEBUG_Volts  
  if (true){
    Serial.print  ("setVolts ");
    Serial.print  (b);
    Serial.print  (" ");
    Serial.println(volts[b]);
  }
#endif
}

int  Data::getVolts(byte b){
#ifdef DEBUG_Volts
  if (true){
    Serial.print  ("getVolts ");
    Serial.print  (b);
    Serial.print  (" ");
    Serial.println(volts[b]);
  }
#endif

  return volts[b];
}


//double Data::getCalcVolts(unsigned int _value, unsigned int R1, unsigned int R2, byte expoFactor){
double Data::getCalcVolts(unsigned int _value, unsigned int R1, unsigned int R2, boolean raw){

//  double expoValue = 1;
//  for (byte b = 0; b < expoFactor; b++){
//      expoValue *= 10;
//  }
  
  double vpb = (double)myVoltageMap.voltPerBit / 1000000.0;  // change 4778 to 0.004778
  double value = _value;

  
  //       Ein = (Eo/R2) * (R1+R2)
  double   Ein = 0;

  if (raw){
    Ein = value * vpb;
  }else{
    Ein = ((value * vpb) / R2 ) * (R1 + R2);
  }
#ifdef DEBUG_CALCVOLTS
  if (false){
    if (false){
      Serial.print  ("  10Bit: ");
      Serial.print  (_value);
      Serial.print  ("  VPB:  ");
      Serial.print  (myVoltageMap.voltPerBit);
      Serial.print  ("  R1: ");
      Serial.print  (R1);
      Serial.print  ("  R2: ");
      Serial.print  (R2);
    }
    Serial.print  ("  Actual: ");
    Serial.print  (value * vpb);
    Serial.print  ("V  Vin: ");
    Serial.print  (Ein);
    Serial.print ("V  ");
  }
#endif

//  return (Ein * expoValue);
  return Ein;
}

double Data::getPreVolts(boolean raw){
  return getCalcVolts(volts[PRE], myResistorMap.Vpre11, myResistorMap.Vpre12, raw);
}

double Data::getPstVolts(boolean raw){
  return getCalcVolts(volts[POST], myResistorMap.Vpst21, myResistorMap.Vpst22, raw);
}

double Data::getV5Volts(boolean raw){
  return getCalcVolts(volts[V5], myResistorMap.V5_31, myResistorMap.V5_32, raw);
}  


double Data::getMilliAmps(){

  /*
////  return 0; // getCalcVolts(volts[7], myResistorMap.V5_31, myResistorMap.V5_32);

//  cntE++;
//  if (cntE > sizeE){
//    cntE = 0;
//  }
  
#ifdef DEBUG_CALCVOLTS_PP
//  Serial.print  (" : ");
//  Serial.print  (getPreVolts());
//
//  Serial.print  (" : ");
//  Serial.print  (getPstVolts());
  Serial.print  (" POST: ");
  Serial.print  (volts[POST]);

  Serial.print  (" PRE: ");
  Serial.print  (volts[PRE]);

  Serial.print  (" bit diff: ");
  Serial.print  (volts[PRE] - volts[POST]);
        
  Serial.print  (" bit diff: ");
  Serial.print  ((volts[PRE] - volts[1])*myResistorMap.shunt);
    // Voltage
  
  Serial.print  (" diff: ");
  Serial.print  ((getPreVolts() - getPstVolts())*100);
  Serial.println();
#endif

//  listE[cntE] = (getPreVolts() - getPstVolts());
avgE = (getPreVolts() - getPstVolts());
  
//#ifdef DEBUG_CALCVOLTS
//  Serial.print  (" vDif: ");
//  Serial.print  (listE[cntE]);
//#endif
//
//  avgE = 0;
//  for (int i = 0; i<sizeE; i++){
//    avgE += listE[i];
//  }
//
//  
//#ifdef DEBUG_CALCVOLTS
//  Serial.print  (" avgE-sizeE: ");
//  Serial.print  (avgE);
//#endif
//  avgE /= sizeE;

  
#ifdef DEBUG_CALCVOLTS
  Serial.print  (" avgE/sizeE: ");
  Serial.print  (avgE*1000);
#endif
  double avgE2 = avgE / ((double)myResistorMap.shunt/10000000.0);

    
#ifdef DEBUG_CALCVOLTS
  Serial.print  ("mV avgE: ");
  Serial.print  (avgE2);

  Serial.print  ("mA  pwr: ");
  Serial.print  (((avgE2*avgE2)/myResistorMap.shunt)*1000);
  Serial.print  ("mW");
  
  Serial.println();
#endif
  
  return avgE2 ;
*/

return 70.3; // I know this is the answer currently, need to work on later....
// This is expensive code, takes 5% of program space.
//   23186
//   21698
// ==========
//    1488 bytes....
}

// this is POWER ((((double)avgE * (double)avgE ) * ((double)myResistorMap.shunt )));
//  return (( avgE * avgE ) / (myResistorMap.shunt / 1000000.0));

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
    
#ifdef DEBUG_CALCVOLTS
  if (false){
    Serial.print  ("adjUint16_tNumber: ");
    Serial.print  (expoValue);
    Serial.print  ("*(uint16_t*)pointerUint16_t: ");
    Serial.print  (*(uint16_t*)pointerUint16_t);
    Serial.println();
  }
#endif
  
}

// deprecated method (use adjUint16_tNumber(int8_t incDirection, int8_t expoFactor)
void Data::adjUint16_tNumber(int16_t number){

  *(uint16_t*)pointerUint16_t += number;
  Serial.print  ("adjUint16_tNumber: ");
  Serial.println(number);
}

//  vKey =    v5_voltPerBit * analog[3];                                                                                 // Key


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library



