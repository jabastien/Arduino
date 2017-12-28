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


*/




