#ifndef KeyPad_h
#define KeyPad_h

#include "Arduino.h"
class KeyPad {
   public:
		// define public functions here

		void doKeys(int);
		byte getKeyPressed();
		void setNumberOfKeys(byte);
		
		
   private:
		// define private functions here	

};

extern KeyPad keyPad;
#endif