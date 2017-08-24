/*
 * 
 * 
 */ 
 #if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "CD4051.h"
	
/*
 * 
 */
CD4051::CD4051(){
	CD4051(4, 5, 6, 8);
}

/*
 * 
 */
CD4051::CD4051(int _addrA, int _addrB, int _addrC, int _pinC) {

  // store our pins
  addrA = _addrA;
  addrB = _addrB;
  addrC = _addrC;
  pinC  = _pinC;
  
  //Setup Analog input
  analogReference(DEFAULT); // VCC 0-5v //0 to 1023

  // Setup Digital output
  pinMode(addrA, OUTPUT);	// sets the digital pin as output
  digitalWrite(addrA, LOW);	// sets the pin to 0-low
  pinMode(addrB, OUTPUT);	// sets the digital pin as output
  digitalWrite(addrB, LOW);	// sets the pin to 0-low
  pinMode(addrC, OUTPUT);	// sets the digital pin as output
  digitalWrite(addrC, LOW);	// sets the pin to 0-low
}

/*
 * Set address pins
 */
void CD4051::setChannel(int channel){
	switch (channel%8){
	  case 0:
	  {
			digitalWrite(addrA, 0);// A - sets the pin
			digitalWrite(addrB, 0);// B - sets the pin
			digitalWrite(addrC, 0);// C - sets the pin
		break;   
	  }
	  case 1:
	  {
			digitalWrite(addrA, 1);// A - sets the pin
			digitalWrite(addrB, 0);// B - sets the pin        
			digitalWrite(addrC, 0);// C - sets the pin
		break;   
	  }
	  case 2:
	  {
			digitalWrite(addrA, 0);// A - sets the pin
			digitalWrite(addrB, 1);// B - sets the pin     
			digitalWrite(addrC, 0);// C - sets the pin		
		break;   
	  }
	  case 3:
	  {
			digitalWrite(addrA, 1);// A - sets the pin
			digitalWrite(addrB, 1);// B - sets the pin   
			digitalWrite(addrC, 0);// C - sets the pin		  
		break;   
	  }
	  case 4:
	  {
			digitalWrite(addrA, 0);// A - sets the pin
			digitalWrite(addrB, 0);// B - sets the pin
			digitalWrite(addrC, 1);// C - sets the pin
		break;   
	  }
	  case 5:
	  {
			digitalWrite(addrA, 1);// A - sets the pin
			digitalWrite(addrB, 0);// B - sets the pin        
			digitalWrite(addrC, 1);// C - sets the pin
		break;   
	  }
	  case 6:
	  {
			digitalWrite(addrA, 0);// A - sets the pin
			digitalWrite(addrB, 1);// B - sets the pin     
			digitalWrite(addrC, 1);// C - sets the pin		
		break;   
	  }
	  case 7:
	  {
			digitalWrite(addrA, 1);// A - sets the pin
			digitalWrite(addrB, 1);// B - sets the pin   
			digitalWrite(addrC, 1);// C - sets the pin		  
		break;   
	  }	  
	  default:
	  {
		Serial.println("error, your doing it wrong!!!");     
	  }
	}
}

/*
 * 
 */
int CD4051::analogReadC(){
	return analogRead(pinC);
}

/*
 * 
 */
int CD4051::digitalReadC(){
	return digitalRead(pinC);
}
