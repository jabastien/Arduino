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
int fpsShow = 0;
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

int l=1;
#define line {Serial.print(l++);Serial.print(" ");}

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

  Serial.println(); 
  Serial.println(PGMSTR(dashes)); 
  
  Serial.println(PGMSTR(lcd_param_lcdInit151_qBytesWorld));
  Serial.println(PGMSTR(lcd_param_lcdInit151_deviceInfo));
  Serial.println(PGMSTR(lcd_param_lcdInit151_versionNum));
  
  Serial.print  (PGMSTR(freeram));
  Serial.println(utils.freeRam());

  Serial.print  (PGMSTR(eepromSz));
  Serial.println(dataStore.eepromSize()); 
  
  Serial.println(PGMSTR(dashes)); 

  
  //Start Radio
  //  radio.begin();
  //  radio.setAutoAck(false);
  //  radio.setDataRate(RF24_250KBPS);
  //  radio.openWritingPipe(pipeOut);

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
  data.getMyControlsRangeMap(0).current = analogRead(A0);
  data.getMyControlsRangeMap(1).current = analogRead(A1);
  data.getMyControlsRangeMap(2).current = analogRead(A2);
  data.getMyControlsRangeMap(3).current = analogRead(A3);

  //------------------------------------------------------
  // 4051 (3x) Switch address
  //------------------------------------------------------
  for (byte digitalLoop = 0; digitalLoop < 8 ; digitalLoop++) {
    switchCD4051.setChannel(digitalLoop);

    // Set mask using loop values
    pinmask   = ~(1 << (digitalLoop % 8));

    // Switch
    readmask  = (switchCD4051.digitalReadC() << (digitalLoop % 8));
    data.getMySwitchMap().switchPins = (data.getMySwitchMap().switchPins & pinmask) | readmask;
    

    // Trim
    readmask  = (trimCD4051.digitalReadC() << (digitalLoop % 8));
    data.getMySwitchMap().trimPins = (data.getMySwitchMap().trimPins & pinmask) | readmask;

    // Menu
    readmask  = (menuCD4051.digitalReadC() << (digitalLoop % 8));
    data.getMySwitchMap().menuPins = (data.getMySwitchMap().menuPins & pinmask) | readmask;
    }

  //------------------------------------------------------
  // 4052 (x1) Read Analog
  //
  // Aux Controls
  // 0 = x0 = Aux0,
  // 2 = x1 = Aux1,
  // 4 = x2 = Aux2,
  // 6 = x3 = Aux3
  //
  // Voltage Divides
  // 1 = y0 = Post,
  // 3 = y1 = Key
  // 5 = y2 = 5V
  // 7 = y3 = Pre  
  //------------------------------------------------------
  for (byte analogLoop = 0 ; analogLoop < 4; analogLoop++) {
    // Switch address for 4052 (1x)
    cd4052.setChannel(analogLoop);
    data.setJoyAux((analogLoop * 2)    , cd4052.analogReadX());
    data.setJoyAux((analogLoop * 2) + 1, cd4052.analogReadY());
    }


  //  --  MySwitchMap
  //myAux.AUX1 = analog[0];
  //myAux.AUX2 = analog[2];
  //myAux.AUX3 = analog[4];
  //myAux.AUX4 = analog[8];

  //------------------------------------------------------
  // Send our data

  // Set Joystick values (0-4) via Range limits  
  //  radio.write(&myControls, sizeof(MyControls));

  //------------------------------------------------------
  // Button pressed?
  keyPad.doKeys(data.getJoyAux(3));
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
