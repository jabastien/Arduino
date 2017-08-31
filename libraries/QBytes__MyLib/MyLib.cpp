#include "Arduino.h"
#include "MyLib.h"

int MyLibClass::addem(int a, int b) {
   int result = a + b;
   return result;
}

int MyLibClass::subem(int a, int b) {
	int result = a - b;
   return result;
}

int MyLibClass::multem(int a, int b) {
   int result = a * b;
   return result;
}

MyLibClass MyLib;