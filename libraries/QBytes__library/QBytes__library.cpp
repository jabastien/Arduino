/*
 * 
 * 
 */ 
 #if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "QBytes_library.h"
	
/*
 * 
 */
QBytes_library::QBytes_library(){
	QBytes_library(4,5, A6, A7);
}

/*
 * 
 */
QBytes_library::QBytes_library(int _addrA, int _addrB, int _adcX, int _adcY) {

  // store our pins
  addrA = _addrA;
  addrB = _addrB;
  adcX  = _adcX;
  adcY  = _adcY;
  
  //Setup Analog input
  analogReference(DEFAULT); // VCC 0-5v //0 to 1023

  // Setup Digital output
  pinMode(addrA, OUTPUT);	// sets the digital pin as output
  digitalWrite(addrA, LOW);	// sets the pin to 0-low
  pinMode(addrB, OUTPUT);	// sets the digital pin as output
  digitalWrite(addrB, LOW);	// sets the pin to 0-low
}

/*
 * Set address pins
 */
void QBytes_library::setChannel(int channel){
	switch (channel%4){
	  case 0:
	  {
			digitalWrite(addrA, 0);// A - sets the pin
			digitalWrite(addrB, 0);// B - sets the pin

		break;   
	  }
	  case 1:
	  {
			digitalWrite(addrA, 1);// A - sets the pin
			digitalWrite(addrB, 0);// B - sets the pin        
		 
		break;   
	  }
	  case 2:
	  {
			digitalWrite(addrA, 0);// A - sets the pin
			digitalWrite(addrB, 1);// B - sets the pin     
		
		break;   
	  }
	  case 3:
	  {
			digitalWrite(addrA, 1);// A - sets the pin
			digitalWrite(addrB, 1);// B - sets the pin   
		  
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
int QBytes_library::analogReadX(){
	return analogRead(adcX);
}

/*
 * 
 */
int QBytes_library::analogReadY(){
	return analogRead(adcY);
}

/*
 * 
 */
int QBytes_library::digitalReadX(){
	return digitalRead(adcX);
}

/*
 * 
 */
int QBytes_library::digitalReadY(){
	return digitalRead(adcY);
}