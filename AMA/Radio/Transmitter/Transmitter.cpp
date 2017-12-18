/*A basic 16 channel transmitter using the nRF24L01 module based on ELECTRONOOBS. */

/*
 AVR Libc Reference Manual
 http://www.atmel.com/webdoc/avrlibcreferencemanual/index.html
 http://www.atmel.com/webdoc/avrlibcreferencemanual/group__avr__stdlib_1ga060c998e77fb5fc0d3168b3ce8771d42.html
*/

//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

//#include <stdlib.h>
//#include <avr/pgmspace.h>

#include "config.h"
#include "def.h"
#include "types.h"

#include "Data.h"
#include "DataStore.h"
#include "Menu.h"
#include "Utils.h"

// ===========================================
// Local vars
// ===========================================
int fps = 0;

// ===========================================
// Vars
// ===========================================
Data data = Data();
DataStore dataStore = DataStore(&data);  //DataStore dataStore = DataStore();
Menu menu = Menu(&data);
Utils utils = Utils();

// ===========================================
// Keypad
// ===========================================
#include <KeyPad.h>

//KeyPad keyPad;  // Empty constructor does not require ().
//KeyPad keyPad(); // this is an error
//KeyPad keyPad(2, 5, 10, 200);
KeyPad keyPad(13, 5, 10, 200);

byte keyPress;

// ===========================================
// RF24
// ===========================================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*Create a unique pipe out. The receiver has to wear the same unique code*/

const uint64_t pipeOut = 0xE8E8F0F0E1LL;

//RF24 radio(9, 10); // select  CE & CSN  pin

// ===========================================
// CD 405x
// ===========================================

// ===========================================
// CD 4051
// ===========================================
#include <CD4051.h>
CD4051 switchCD4051 = CD4051(3, 4, 5, 6);
CD4051 trimCD4051   = CD4051(3, 4, 5, 7);
CD4051 menuCD4051   = CD4051(3, 4, 5, 8);

byte switchPin = 0b00000000;
byte trimPin   = 0b00000000;
byte menuPin   = 0b00000000;

byte pinmask;
byte readmask;

// ===========================================
// CD4052
// ===========================================
#include <CD4052.h>

CD4052 cd4052 = CD4052(5, 4, A7, A6);

// ===========================================
// Misc
// ===========================================
//int debugPin=8; // D8

// ===========================================
// My packet Data
// ===========================================
// The sizeof this struct should not exceed 32 bytes
// This gives us up to 32 8 bits channals


// ===========================================
// ===========================================
// ===========================================
// Setup
// ===========================================
// ===========================================
// ===========================================
void setup(){
//  pinMode(2, OUTPUT);
//  digitalWrite (2, LOW);
  analogReference(EXTERNAL);

  // Debug Serial out
  Serial.begin(115200); //Set the speed to 9600 bauds if you want.
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  Serial.println(PGMSTR(dashes)); 
  
  Serial.println(PGMSTR(qBytesWorld));
  Serial.println(PGMSTR(deviceInfo));
  Serial.println(PGMSTR(versionNum));
  
  Serial.print  (PGMSTR(freeram));
  Serial.println(utils.freeRam());

  Serial.print  (PGMSTR(eepromSz));
  Serial.println(dataStore.eepromSize()); 
  
  Serial.println(PGMSTR(dashes)); 

  
  //Start everything up
  //  radio.begin();
  //  radio.setAutoAck(false);
  //  radio.setDataRate(RF24_250KBPS);
  //  radio.openWritingPipe(pipeOut);
  //  resetData();
}

// ===========================================
// ===========================================
// ===========================================
// loop
// ===========================================
// ===========================================
// ===========================================
void loop() {
  //------------------------------------------------------
  // The calibration numbers used here should be measured
  // for your joysticks so they send the correct values.
  //------------------------------------------------------
  data.aux(0, analogRead(A0));
  data.aux(1, analogRead(A1));
  data.aux(2, analogRead(A2));
  data.aux(3, analogRead(A3));

  //------------------------------------------------------
  // 4051 (3x) Switch address
  //------------------------------------------------------
  for (byte digitalLoop = 0; digitalLoop < 8 ; digitalLoop++) {
    switchCD4051.setChannel(digitalLoop);

    // Set mask using loop values
    pinmask   = ~(1 << (digitalLoop % 8));

    // Switch
    readmask  = (switchCD4051.digitalReadC() << (digitalLoop % 8));
    switchPin = (switchPin & pinmask) | readmask;

    // Trim
    readmask  = (trimCD4051.digitalReadC() << (digitalLoop % 8));
    trimPin   = (trimPin & pinmask) | readmask;

    // Menu
    readmask  = (menuCD4051.digitalReadC() << (digitalLoop % 8));
    menuPin   = (menuPin & pinmask) | readmask;
  }

  //------------------------------------------------------
  // 4052 (x1) Read Analog
  //------------------------------------------------------
  for (byte analogLoop = 0 ; analogLoop < 4; analogLoop++) {
    // Switch address for 4052 (1x)
    cd4052.setChannel(analogLoop);
    data.setJoystick((analogLoop * 2)    , cd4052.analogReadX());
    data.setJoystick((analogLoop * 2) + 1, cd4052.analogReadY());
  }

  //------------------------------------------------------
  // Send our data
  //  radio.write(&myControls, sizeof(MyControls));

  //------------------------------------------------------
  // Button pressed?
  keyPad.doKeys(data.getJoystick(3));
  keyPress = keyPad.getKeyPressed();

  //------------------------------------------------------
  // Inc Frames Per Second
  //------------------------------------------------------
  fps++;

  //------------------------------------------------------
  // Update LCD 1/10 seconds
  //------------------------------------------------------
  if (keyPress > 0 || menu.isScreenRefreshNeeded()) {
    menu.updateLCD(keyPress, fps);
    fps = 0;
  }

  //------------------------------------------------------
  // Serial Debugging
  //serialDebug();
}
