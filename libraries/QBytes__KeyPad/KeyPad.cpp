
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "KeyPad.h"

unsigned long previousMillis = 0; 
unsigned long interval = 25;

byte arr [5]	= {0, 0, 0, 0, 0};
byte arrSize	= sizeof( arr ) / sizeof( byte );
byte arrCntr	= 0;	// Max value 255
int  arrAvg		= 0;

byte keyDown	= 0;	// Max value 255
byte keyPress	= 0;	// Max value 255
byte noKey		= 0;	// Max value 255

byte numberOfKeys = 5;	// Max value 255

int	 lowAnalog     = 1023 / numberOfKeys;
int	 halfLowAnalog = 1023 / numberOfKeys / 2;

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
		digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
	}
	
	// Return keyPressed
	return rtn;
}

// ===========================================
// Set Number of Keys
// ===========================================
void KeyPad::setNumberOfKeys(byte keys){
	numberOfKeys = keys;
	lowAnalog     = 1023 / numberOfKeys;
	halfLowAnalog = 1023 / numberOfKeys / 2;
}

// ===========================================
// Do Keys calculation
// ===========================================
void KeyPad::doKeys(int analogvalue){

	//----------------------------	
	// If KeyPad just released, delay long enough to make sound and show LED.
	//----------------------------	
	if (digitalRead(2) == HIGH);
	{
	  //unsigned long currentMillis = millis();
      if(millis() - previousMillis > interval) 
		{		  
			digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
		} else {
			// Wait for led/sound off
			return;
		}
	}

	//----------------------------	
	// Calculate if key was released.
	//----------------------------	
	if (analogvalue < halfLowAnalog){
		// Key Up/Released
		if (keyDown == arrAvg){
			keyPress = keyDown;
		}
		// Clear array
		memset(arr, 0x0, sizeof(arr));  
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

	arrAvg = 0;
	for (byte b = 0; b < arrSize; b++){
		arrAvg  += arr[b];
	}
	arrAvg /= arrSize;

	//----------------------------	
	//reset, if nothing good can happen
	//----------------------------	
	if (keyDown < arrAvg){
		// Clear array
		memset(arr, 0x0, sizeof(arr));  
		keyDown = noKey;	
		keyPress = noKey;	
		//Serial.println("<"); 		
	}

	/*
	Serial.print  (analogvalue); 
	Serial.print  (" "); 
	Serial.print  (halfLowAnalog); 
	Serial.print  (" "); 
	Serial.print  (arrAvg); 
	Serial.print  (" "); 
	Serial.print  (keyDown); 
	Serial.print  (" "); 
	Serial.print  (keyPress); 
	Serial.println(""); 
	*/	
}

// ===========================================
// ===========================================
// ===========================================
KeyPad keyPad;