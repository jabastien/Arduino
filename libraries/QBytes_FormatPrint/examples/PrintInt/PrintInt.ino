#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <String.h>
#include <WString.h>

#include <FormatPrint.h>
#include <Formats.h>  //  ==> this must be in the main program
//extern String format9;

FormatPrint fmt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

int cnt = 0;
void loop() {
  // put your main code here, to run repeatedly:

  cnt++;
  fmt.printInt(cnt, format9);
  cnt++;
  fmt.printInt(cnt, format9);

  Serial.println();
}