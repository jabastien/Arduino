
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
		Serial.print  (pin);
		Serial.print  (" ");
		Serial.print  (numberOfKeys);
		Serial.print  (" ");
		Serial.print  (halfLowAnalog);
		Serial.print  (" ");
		Serial.print  (lowAnalog);	
		Serial.print  (" ");
		Serial.print  (interval);	
		Serial.println("");	
	}
}
// ===========================================
// KeyPad empty Constructor
// ===========================================
KeyPad::KeyPad(void)
	: KeyPad(LED_BUILTIN, 5, 100) // call empty constructor
{
	//Serial.println("Default Constructor");
	printIt();
}

// ===========================================
// KeyPad Constructor
// ===========================================
//KeyPad::KeyPad(byte _pin=2, byte _numberOfKeys=5, unsigned long _interval=25 ){
KeyPad::KeyPad(byte _pin, byte _numberOfKeys, unsigned long _interval ){	
	
	//Serial.println("Constructor");
	
	// Output LED/Sound
	pin = _pin;
	pinMode(pin, OUTPUT);
	digitalWrite (pin, LOW);
	
	// Number of keys
	numberOfKeys = _numberOfKeys;	
	halfLowAnalog = 1023 / numberOfKeys / 2;
	lowAnalog     = 1023 / numberOfKeys;
	
	// Delay for led on after key release
	interval = _interval;

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
		
		previousMillis = millis();
		digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
		
		// Clear array
		memset(arr, 0x0, sizeof(arr)); 
		
		printIt();
	}
	
	// Return keyPressed
	return rtn;
}

// ===========================================
// Do Keys calculation
// ===========================================
void KeyPad::doKeys(int analogvalue){
//printIt();
	//----------------------------	
	// If KeyPad just released, delay long enough to make sound and show LED.
	//----------------------------	
	if (digitalRead(pin) == HIGH);
	{
	  //unsigned long currentMillis = millis();
      if(millis() - previousMillis > interval) 
		{		  
			digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
		} else {
			// Wait for led/sound off
			return;
		}
	}

	//----------------------------	
	// Calculate if key was released.
	//----------------------------	
	if (eligible && analogvalue < halfLowAnalog){
		// Key Up/Released
		if (keyDown == arrAvg){
			keyPress = keyDown;
		} else {
			keyPress = noKey;
		}
		// Clear array
		//memset(arr, 0x0, sizeof(arr));  
	} 
	
	//----------------------------	
	// Reset loop counter?
	//----------------------------	
	if (++arrCntr >= arrSize){
	  arrCntr = 0;
	}

	//----------------------------	
	// Calculate which key is pressed.
	//----------------------------	
	keyDown = map(analogvalue, -(halfLowAnalog), 1023 - halfLowAnalog, 0, numberOfKeys);

	arr[arrCntr] = keyDown;

	eligible = true;
	
	arrAvg = 0;
	for (byte b = 0; b < arrSize; b++){
		arrAvg  += arr[b];
		if (keyDown != arr[b]){
			eligible = false;
		}
	}
	arrAvg /= arrSize;

	//----------------------------	
	//reset, if nothing good can happen
	//----------------------------	
	// if (keyDown < arrAvg){
		// // Clear array
		// memset(arr, 0x0, sizeof(arr));  
		// keyDown = noKey;	
		// keyPress = noKey;	
		// Serial.println("< clr"); 		
	// }
}