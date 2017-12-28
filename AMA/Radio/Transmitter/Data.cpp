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
  
//  if (b == 3){
//    Serial.print  ("setJoyAux ");
//    Serial.print  (b);
//    Serial.print  (" ");
//    Serial.println(aux[b]);
//  }
}


int  Data::getJoyAux(byte b){
//  if (b == 3){
//    Serial.print  ("getJoyAux ");
//    Serial.print  (b);
//    Serial.print  (" ");
//    Serial.println(aux[b]);
//  }
  
  return aux[b];
}

//double Data::getCalcVolts(unsigned int _value, unsigned int R1, unsigned int R2, byte expoFactor){
double Data::getCalcVolts(unsigned int _value, unsigned int R1, unsigned int R2){

//  double expoValue = 1;
//  for (byte b = 0; b < expoFactor; b++){
//      expoValue *= 10;
//  }
  
  double vpb = (double)myVoltageMap.voltPerBit / 1000000.0;  // change 4778 to 0.004778
  double value = _value;

  //       Ein = (Eo/R2) * (R1+R2)
  double   Ein = ((value * vpb) / R2 ) * (R1 + R2);

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

double Data::getPreVolts(){
  return getCalcVolts(aux[7], myResistorMap.Vpre11, myResistorMap.Vpre12);
}

double Data::getPstVolts(){
  return getCalcVolts(aux[1], myResistorMap.Vpst21, myResistorMap.Vpst22);
}

double Data::getV5Volts(){
  return getCalcVolts(aux[5], myResistorMap.V5_31, myResistorMap.V5_32);
}  



double Data::getMilliAmps(){
////  return 0; // getCalcVolts(aux[7], myResistorMap.V5_31, myResistorMap.V5_32);

//  cntE++;
//  if (cntE > sizeE){
//    cntE = 0;
//  }
  
#ifdef DEBUG_CALCVOLTS
  Serial.print  (" pre: ");
  Serial.print  (getPreVolts());

  Serial.print  (" pst: ");
  Serial.print  (getPstVolts());
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
}

  // this is POWER ((((double)avgE * (double)avgE ) * ((double)myResistorMap.shunt )));
//  return (( avgE * avgE ) / (myResistorMap.shunt / 1000000.0));

////////////////////////////// MyVoltageMap
/*
 *   // Voltage Divides
  // 1 = y0 = Post,
  // 3 = y1 = Key
  // 5 = y2 = 5V
  // 7 = y3 = Pre 
*/


 
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



