
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include "KeyPad.h"

void KeyPad::printIt(){
	if (false){
		// Display it
		Serial.print  (" ");
		Serial.print  (blocking);
		Serial.print  (" ");
		Serial.print  (pin);
		Serial.print  (" ");
		Serial.print  (numberOfKeys);
		Serial.print  (" ");
		Serial.print  (halfLowAnalog);
		Serial.print  (" ");
		//Serial.print  (lowAnalog);	
		//Serial.print  (" ");
		Serial.print  (intervalBeep);	
		Serial.print  ("");	
		Serial.print  (intervalRepeat);
		Serial.print  ("");	
		Serial.print  (keyUpMillis);		
		Serial.println("");	
	}
}
// ===========================================
// KeyPad empty Constructor
// ===========================================
KeyPad::KeyPad(void)
	: KeyPad(LED_BUILTIN, 5, 10, 250){ // call empty constructor
	//Serial.println("Default Constructor");
	printIt();
}

// ===========================================
// KeyPad Constructor
// ===========================================
//KeyPad::KeyPad(byte _pin=2, byte _numberOfKeys=5, unsigned long _intervalBeep=25 ){  //provide default values?
KeyPad::KeyPad(byte _pin, byte _numberOfKeys, unsigned long _intervalBeep, unsigned long _intervalRepeat ){	
	
	//Serial.println("Constructor");
	
	// Output LED/Sound
	pin = _pin;
	pinMode(pin, OUTPUT);
	digitalWrite (pin, LOW);
	
	// Number of keys
	numberOfKeys = _numberOfKeys;	
	halfLowAnalog = -(1023 / numberOfKeys / 2);
	//lowAnalog     = 1023 / numberOfKeys;
	//halfLowAnalog = lowAnalog / 2;
	
	// Delay for led on after key release
	intervalBeep = _intervalBeep;
	intervalRepeat = _intervalRepeat;
	
	printIt();
}


// ===========================================
// Key Pressed
// ===========================================
byte KeyPad::getKeyPressed(){
	
	// Set return value
	byte rtn = keyPress;
	
	if (rtn > noKey){
		// Clear key Presses (return it only once).
		keyPress = noKey;
		
		keyUpMillis = millis();
		
		digitalWrite(pin, HIGH);   // turn the LED/sound on
		
		// Clear array
		//memset(arr, 0x0, sizeof(arr)); 
		
		blocking = true;
		printIt();
	}
	
	// Return keyPressed
	return rtn;
}

// ===========================================
// Do Keys calculation
// ===========================================
void KeyPad::doKeys(int analogvalue){

	//----------------------------	
	// If KeyPad just released, delay long enough to make sound/show LED and delay for repeat.
	//----------------------------	
	if (blocking){
		// Get the millis since key released.
		int diffMillis = millis() - keyUpMillis;
		
		// turn the LED/sound off
		if(diffMillis > intervalBeep){		  
			digitalWrite(pin, LOW);    
		}
		
		// Allow repeat to work
		if(diffMillis > intervalRepeat) {			
			blocking = false;
		}
		
		// Blocking, so return
		return;
	}

	//----------------------------	
	// Calculate which key is pressed.
	//----------------------------	
	keyDown = map(analogvalue, halfLowAnalog, 1023 + halfLowAnalog, 0, numberOfKeys);

	// Reset loop counter?
	if (++arrCntr >= arrSize){
	  arrCntr = 0;
	}		
	arr[arrCntr] = keyDown;

	eligible = true;
	
	for (byte b = 0; b < arrSize; b++){
		if (keyDown != arr[b]){
			eligible = false;
		}
	}

	//----------------------------	
	// If eligible, make key available.
	//----------------------------	
	if (eligible){
		// Key Up/Released
			keyPress = keyDown;
		} else {
			keyPress = noKey;
	}	
}