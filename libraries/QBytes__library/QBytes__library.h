/*

*/

// ensure this library description is only included once
#ifndef QBytes_library_h
#define QBytes_library_h

// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// library interface description
class QBytes_library{
  // user-accessible "public" interface
  public:
	QBytes_library(void);
	QBytes_library(int _addrA, int _addrB, int _pinX, int _pinY);
	void setChannel(int channel);
	int analogReadX();
	int analogReadY();
	int digitalReadX();
	int digitalReadY();
		
  // library-accessible "private" interface
  private:
	int addrA;
	int addrB;
	int adcX;
	int adcY;
};

#endif //QBytes_library_h
