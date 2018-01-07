#ifndef TYPES_H_
#define TYPES_H_


/*  *** Do not instance variables in this file.  It will create: ***
  error: redefinition of 'variable name'
  sketch\types.h:xx:xx: note: 'variable name' previously declared here
*/
// ===========================================
// Transmission Packages
// ===========================================
struct MyJoysticks {
  const byte packetType = 0x01;
  byte throttle; // A0
  byte yaw;      // A1
  byte roll;     // A2
  byte pitch;    // A3
};

struct MyAux {
  const byte packetType = 0x02;
  byte AUX0;
  byte AUX1;
  byte AUX2;
  byte AUX3;
};

struct MySwitchesButtons {
  const byte packetType = 0x03;
  byte switchPins;
  byte trimPins;
  byte menuPins;
};

// ===========================================
// Control Range Map
// ===========================================
struct MyControlsRangeMap {
  int       current;           // Current 10 bit value from Analog port
  int       minimum = INT_MIN; // Min 10 bit value from Analog port
  int       center  = INT_MID; // is this really center????
  int       maximum = INT_MAX; // Max 10 bit value from Analog port
  boolean   reverse = false;

// -------------------------------------------
// Centering Joystick
// -------------------------------------------
  void setCenter(){
    minimum = INT_MAX;  
    center = current;  
    maximum = INT_MIN;  
    }

// -------------------------------------------
// Set Min Max Values
// -------------------------------------------
  void setMinMax(){
    minimum = min(current, minimum);
    maximum = max(current, maximum);
    }

// -------------------------------------------
// Set Min Max Values
// -------------------------------------------
  void setMinMaxCenter(){
    minimum = min(current, minimum);
    maximum = max(current, maximum);
    center  = minimum + ((maximum - minimum) / 2);
    }

// -------------------------------------------
// Map Joystick Values for MyJoysticks
// -------------------------------------------
// Returns a full-range value for a joystick position that takes into account
// the values of the outer extremes and the center of the joystick.
  byte controlRange(){
    int value = constrain(current, minimum, maximum);
    
    if ( value < center )
      value = map(value, minimum, center, BYTE_MIN, BYTE_MID);
    else
      value = map(value, center, maximum, BYTE_MID, BYTE_MAX);
      
    return ( reverse ? BYTE_MAX - value : value );
  }    
  
};

// ===========================================
// Volt divide Vars
// Max votage size is 65,535.
// ===========================================
struct MyVoltageMap {
  // Measured reference voltage
  uint16_t reference = 5030; // = 5.000V
  
  // Calculated fields voltPerBit = (reg / 1023)
  uint16_t voltPerBit = 4897; // My messured value 0.004897
  
  // Calculated fields read from CD4052  
  uint16_t vPre  = 3157; // 12.871V measured and 3.1570V post volt/div
  uint16_t vPst  = 3154; // 12.839V measured and 3.1546V post volt/div
  uint16_t v50   = 2949; //  4.916V measured and 2.9496V post volt/div
  };

// ===========================================
// Volt divide Vars
// ===========================================
struct MyResistorMap {
// Messure (  vPre -  vPost) / Current
//         (12.867 - 12.836) / 58.8 =  0.527211 Ohm
//                    0.031  / 58.8 =  0.527211 Ohm
//  double shunt = 0.727211;   // 0.5
//  double shunt = 0.766327;   // 0.5
//  uint16_t  shunt = 7663;//*10000);   // 0.5
//  uint16_t  shunt = 5595;//*10000);   // 0.5
  uint16_t  shunt = 6880;//*10000);   // 0.5

  // Max resistor size is 65,535.
  uint16_t Vpre11   = 8042; // 8.2k
  uint16_t Vpre12   = 2638; // 2.7k
  
  uint16_t Vpst21   = 8014; // 8.2k
  uint16_t Vpst22   = 2637; // 2.7k
  
  uint16_t V5_31    = 2161; // 2.2k
  uint16_t V5_32    = 3212; // 3.3k
};

#endif /* TYPES_H_ */

