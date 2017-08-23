// Reference:::https://forum.arduino.cc/index.php?topic=215334.0

// Two options exist for debugging to improve performance.  Both require a #define
// Option 1 - Code looks better but still executes the NOOP and any calculations within ("DEBUGMACRO")
// Option 2 - Code not as nice, but executes only code outside the DEBUGGLAG

// =========================================================================
// Option #1
// Create a macro
// =========================================================================
//#define DEBUGMACRO   //If you comment this line, the DPRINT & DPRINTLN lines are defined as blank.

#ifdef DEBUGMACRO    //Macros are usually in all capital letters.
  #define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
  #define DPRINT(...)     //now defines a blank line - NOOP
  #define DPRINTLN(...)   //now defines a blank line - NOOP
#endif

// =========================================================================
// Option #2
// Flip flag
// =========================================================================
//#define DEBUGFLAG

void setup() {
#if (defined(DEBUGMACRO) || defined(DEBUGFLAG)) // Option 1 or 2;
  Serial.begin(115200);
  Serial.println("Starting");
#endif

}

double num = 3.3;
void loop() {

  // Option #1
  DPRINT("DEBUGMACRO ");
  DPRINT(num);
  DPRINTLN(" LN");
  
  // Option #2
  #ifdef DEBUGFLAG
    Serial.print("DEBUGFLAG ");
    Serial.print(num + 11.1);
    Serial.println(" LN");
  #endif

}
