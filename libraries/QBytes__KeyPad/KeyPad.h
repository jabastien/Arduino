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

		unsigned long keyUpMillis = 0; 
		unsigned long intervalBeep = 25; // beep
		unsigned long intervalRepeat = 250; // repeat

		byte arr [5]	= {0, 0, 0, 0, 0};
		byte arrSize	= sizeof( arr ) / sizeof( byte );
		byte arrCntr	= 0;	// Max value 255

		byte keyDown	= 0;	// Max value 255
		byte keyPress	= 0;	// Max value 255
		byte noKey		= 0;	// Max value 255

		byte numberOfKeys = 5;	// Max value 255

		int	 lowAnalog    ;// = 1023 / numberOfKeys;
		int	 halfLowAnalog;// = 1023 / numberOfKeys / 2;
		
		byte pin;
		
		boolean eligible = true;
		boolean blocking = false;
  /*
   * protected members / functions / class variables
   */
    protected:		

};

#endif