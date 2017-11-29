#ifndef types_h
  #define types_h

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
//  MyControls myControls;
  
  struct MyControlsMap {
    int       Min; // A0
    int       Mid; // A0
    int       Max; // A0
    boolean   Rev;
  };
//  MyControlsMap myControlsMapThrottle;
//  MyControlsMap myControlsMapYaw;
//  MyControlsMap myControlsMapRoll;
//  MyControlsMap myControlsMapPitch;
  
  struct MyAux {
    const byte packetType = 0x02;
    byte AUX1;
    byte AUX2;
    byte AUX3;
    byte AUX4;
  };
//  MyAux myAux;
  
  struct MyButtons {
    const byte packetType = 0x03;
    byte swtch;
    byte dip;
    byte menu;
  };
//  MyButtons myButtons;
  
  // ===========================================
  // Volt divide Vars
  // ===========================================
  struct MyResistorMap {
    // Messure (  vPre -  vPost) / Current
    //         (12.867 - 12.836) / 58.8 =  0.527211 Ohm
    //                    0.031  / 58.8 =  0.527211 Ohm
  //double shunt = 0.727211;   // 0.5
  //  double shunt = 0.766327;   // 0.5
    unsigned int  shunt = (0.766327*10000);   // 0.5
  
    // Max resistor size is 32767 witch is 1/2 of 65,535.
    unsigned int Vpre11   = 8042; // 8.2k
    unsigned int Vpre12   = 2638; // 2.7k
    unsigned int Vpst21   = 8014; // 8.2k
    unsigned int Vpst22   = 2637; // 2.7k
    unsigned int V5_31    = 2161; // 2.2k
    unsigned int V5_32    = 3212; // 3.3k
  };
//  MyResistorMap myResistorMap;
  
  // ===========================================
  // Editor Data
  // ===========================================
  struct MyEditor {
      byte row[4];      // row > (Start pos for the item to edit.
  //  byte col[4];         // column ^
      char * mask[4];   // & of the pgmem (0 shuld always be null (title line))
      void * pVoid[4];  //  Data element address to edit
  };
//  MyEditor myEditor;


#endif /* types_h */
