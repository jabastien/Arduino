#ifndef TYPES_H_
#define TYPES_H_

// Do not instance variables in this file.  It will create:
//  error: redefinition of 'variable name'
//  sketch\types.h:xx:xx: note: 'variable name' previously declared here

// ===========================================
// Transmission Packages
// ===========================================
struct MyControls {
  const byte packetType = 0x01;
  byte throttle; // A0
  byte yaw;      // A1
  byte roll;     // A2
  byte pitch;    // A3
};

struct MyControlsMap {
  int       Min; // A0
  int       Mid; // A0
  int       Max; // A0
  boolean   Rev;
};

struct MyAux {
  const byte packetType = 0x02;
  byte AUX1;
  byte AUX2;
  byte AUX3;
  byte AUX4;
};

struct MyButtons {
  const byte packetType = 0x03;
  byte swtch;
  byte dip;
  byte menu;
};

// ===========================================
// Volt divide Vars
// ===========================================
struct MyResistorMap {
  // Messure (  vPre -  vPost) / Current
  //         (12.867 - 12.836) / 58.8 =  0.527211 Ohm
  //                    0.031  / 58.8 =  0.527211 Ohm
//double shunt = 0.727211;   // 0.5
//  double shunt = 0.766327;   // 0.5
  uint16_t  shunt = (7663);//*10000);   // 0.5

  // Max resistor size is 32767 witch is 1/2 of 65,535.
  uint16_t Vpre11   = 8042; // 8.2k
  uint16_t Vpre12   = 2638; // 2.7k
  uint16_t Vpst21   = 8014; // 8.2k
  uint16_t Vpst22   = 2637; // 2.7k
  uint16_t V5_31    = 2161; // 2.2k
  uint16_t V5_32    = 3212; // 3.3k
};

// ===========================================
// Display Info
// ===========================================
struct DisplayInfo {
  char * buffer;
  const char * pgmData;   
};

//// ===========================================
//// Editor Data
//// ===========================================
struct MyEditorData {
    boolean setDisplayInfo = false;  
    byte   row[4];      // row > (ROW start pos for the item to edit.
  //byte   col[4];         // column ^ // Not needed, the row[x] -- x = column
  //const  char * pgmData[4]; &address of the pgmem for mask  ( [0] should always be null (title line))
    struct DisplayInfo displayInfo[4];
    void   * pVoid[4];  //  Data element address to edit
    byte   returnTo;
};

#endif /* TYPES_H_ */
