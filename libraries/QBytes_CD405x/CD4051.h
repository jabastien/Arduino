/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// ensure this library description is only included once
#ifndef CD4051_h
#define CD4051_h

// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// library interface description
class CD4051{
  /*
   * public members / functions / class variables
   */
  public:
	CD4051(void);
	CD4051(int _addrA, int _addrB, int _addrC, int _pinC);
	void setChannel(int channel);
	int analogReadC();
	int digitalReadC();

  /*
   * private members / functions / class variables
   */	
  private:
	int addrA;
	int addrB;
	int addrC;
	int pinC;
	
  /*
   * protected members / functions / class variables
   */
    protected:	
};

#endif //CD4051_h
