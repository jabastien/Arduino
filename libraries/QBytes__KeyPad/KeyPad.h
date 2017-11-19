#ifndef KeyPad_h
#define KeyPad_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class KeyPad {
  /*
   * public members / functions / class variables
   */	
   public:

		KeyPad(void);
		KeyPad(byte, byte, unsigned long, unsigned long);
		
		void printIt();
		void doKeys(int);
		byte getKeyPressed();

  /*
   * private members / functions / class variables
   */		
   private:

		unsigned long keyUpMillis;		// Time from key release
		int intervalBeep;		// beep
		int intervalRepeat ;	// repeat

		byte arr [5];
		byte arrSize = sizeof( arr ) / sizeof( byte );
		byte arrCntr;		// Max value 255

		byte keyDown;		// Max value 255
		byte keyPress;		// Max value 255
		byte noKey;			// Max value 255

		byte numberOfKeys;	// Max value 255

		int	 halfLowAnalog;
		
		byte pin;
		
		boolean eligible;
		boolean blocking;
  /*
   * protected members / functions / class variables
   */
    protected:		

};

#endif