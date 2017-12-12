/*


// ===========================================
// ===========================================
// ===========================================
// Serial Debug
// ===========================================
// ===========================================
// ===========================================
void serialDebug() {
  //------------------------------------------------------
  // Print controls
  //------------------------------------------------------
#ifdef DEBUG_MyControls
    Serial.print  (F(" T: "));
    Serial.print  (myControls.throttle);
    Serial.print  (F(" : "));
    Serial.print  (analogRead(A0));

    Serial.print  (F(" Y: "));
    Serial.print  (myControls.yaw);
    Serial.print  (F(" : "));
    Serial.print  (analogRead(A1));

    Serial.print  (F(" R: "));
    Serial.print  (myControls.roll);
    Serial.print  (F(" : "));
    Serial.print  (analogRead(A2));

    Serial.print  (F(" P: "));
    Serial.print  (myControls.pitch);
    Serial.print  (F(" : "));
    Serial.print  (analogRead(A3));

    Serial.println();
#endif  

  // -----------------------------------------------
  // KEY
  //------------------------------------------------------
#ifdef DEBUG_KEY
    Serial.print  ("Key: ");
    Serial.print  (analog[3]);
    Serial.print  ("  ");
    Serial.print  (analog[3] * (v5_Measured/1023.0));
    Serial.print  ("V ");

    Serial.println();
#endif  


  //------------------------------------------------------
  // Print CD4051 switches
  //------------------------------------------------------
#ifdef DEBUG_CD4051_MASK
    Serial.print(" Pin ");
    Serial.print(pinmask + 0x100, BIN);
    Serial.print(" Mask ");
    Serial.print(readmask + 0x100, BIN);
    Serial.println();    
#endif
  
#ifdef DEBUG_CD4051
    Serial.print(" Switch: ");
    Serial.print(switchPin + 0x100, BIN);
    Serial.print(" Trim: ");
    Serial.print(trimPin + 0x100, BIN);
    Serial.print(" Menu: ");
    Serial.print(menuPin + 0x100, BIN);
    Serial.println();    
#endif

//------------------------------------------------------
// Print CD4052 analog
//------------------------------------------------------
#ifdef DEBUG_CD4052

char bufferD[30];  //  Hold The Convert Data
char CD4052Format[] = "<X%1d:%1d:%4d> <Y%1d:%1d:%4d> ";

  for (byte analogLoop = 0 ; analogLoop < 4; analogLoop++) {
    sprintf(bufferD, CD4052Format, 
          analogLoop,  analogLoop * 2     , analog[(analogLoop * 2)    ], 
          analogLoop, (analogLoop * 2) + 1, analog[(analogLoop * 2) + 1]
          ); 
    Serial.print  (bufferD);
  }
    Serial.println("");
    
#endif


//------------------------------------------------------
// Print CD4052 volts (analog)
//------------------------------------------------------

#ifdef DEBUG_CD4052_VOLTS
  // -----------------------------------------------
  // 5 = y2 =   5V
  Serial.print  ("5V: ");
  Serial.print  (analog[5]);
  Serial.print  ("  ");
  Serial.print  (v5_voltPerBit * analog[5]);
  Serial.print  ("V  ");
//Ein = (Eo/R2) * (R1+R2)
  Serial.print  (v5_System);
  Serial.print  ("V ");

  // -----------------------------------------------
  // 7 = y3 = Pre
  Serial.print  (" xxxxx  Pre: ");
  Serial.print  (analog[7]);
  Serial.print  ("  ");
  Serial.print  (v5_voltPerBit * analog[7]);
  Serial.print  ("V  ");
//Ein = (Eo/R2) * (R1+R2)
  Serial.print  (vPre);
  Serial.print  ("V ");

  // -----------------------------------------------
  // 1 = y0 = Post,
  Serial.print  (" xxxxx  Post: ");
  Serial.print  (analog[1]);
  Serial.print  ("  ");
  Serial.print  (v5_voltPerBit * analog[1]);
  Serial.print  ("V  ");
//Ein = (Eo/R2) * (R1+R2)
  Serial.print  (vPst);
  Serial.print  ("V ");

  // -----------------------------------------------
  //I = E / R (R = shunt)
  Serial.print (" Current ");
  Serial.print (avgSum/avgSize);
  Serial.print ("mV ");
  Serial.print ((avgSum/avgSize)/(myResistorMap.shunt);
  Serial.print ("mA");

  // -----------------------------------------------
  Serial.println("");
#endif

///////////////////////////////////////////////////////////////////////
}


*/







//
//Serial.print (v5_voltPerBit);
//Serial.print (" ");
//Serial.print (analog[5]);
//Serial.print (" ");
//Serial.print (myResistorMap.V5_31);
//Serial.print (" ");
//Serial.print (myResistorMap.V5_32);
//Serial.print (" ");
//Serial.print ((((v5_voltPerBit * analog[5]) / myResistorMap.V5_32 ) * (myResistorMap.V5_31  + myResistorMap.V5_32 )));
//Serial.print (" ");
//
//Serial.println();
  //
