#ifndef TYPES_H_
#define TYPES_H_

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

#endif /* TYPES_H_ */
