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

// ===========================================
// Vars
// ===========================================
Data data = Data();
DataStore dataStore = DataStore(&data);
Menu menu = Menu(&data, &dataStore);
Utils utils = Utils();

// ===========================================
// Keypad
// ===========================================
#include <KeyPad.h>

//KeyPad keyPad;  // Empty constructor does not require ().
//KeyPad keyPad(); // this is an error
//KeyPad keyPad(2, 5, 10, 200);
KeyPad keyPad(13, 5, 10, 350);

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

//int l=1;
//#define line {Serial.print(l++);Serial.print(" ");}

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

//utils.ErrorPrint("abc",1,1);
//utils.ErrorPrint("zxv",2,1,2);
//utils.ErrorPrint("asf",3,1,2,4);
//
////utils.Print("This is funny, isn't it?", 1, 2, 12.3456, 3, 4, "nice");
//utils.myprintf("This is funny, isn't it?", 1, 2, 12.3456, 3, 4,"YES???");
//utils.Q_printf( "sdc", "This is a string", 29, 'X'); 

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
  data.getMyJoysticksRangeMap(THROTTLE).current  = analogRead(A0);
  data.getMyJoysticksRangeMap(YAW).current       = analogRead(A1);
  data.getMyJoysticksRangeMap(ROLL).current      = analogRead(A2);
  data.getMyJoysticksRangeMap(PITCH).current     = analogRead(A3);

  //------------------------------------------------------
  // 4051 (3x) Switch address
  //------------------------------------------------------
  for (byte digitalLoop = 0; digitalLoop < 8 ; digitalLoop++) {
    switchCD4051.setChannel(digitalLoop);

    // Set mask using loop values
    pinmask   = ~(1 << (digitalLoop % 8));

    // Switch
    readmask  = (switchCD4051.digitalReadC() << (digitalLoop % 8));
    data.getMySwitchesButtons().switchPins = (data.getMySwitchesButtons().switchPins & pinmask) | readmask;
    

    // Trim
    readmask  = (trimCD4051.digitalReadC() << (digitalLoop % 8));
    data.getMySwitchesButtons().trimPins = (data.getMySwitchesButtons().trimPins & pinmask) | readmask;

    // Menu
    readmask  = (menuCD4051.digitalReadC() << (digitalLoop % 8));
    data.getMySwitchesButtons().menuPins = (data.getMySwitchesButtons().menuPins & pinmask) | readmask;
    }

  //------------------------------------------------------
  // 4052 (x1) Read Analog
  //
  // Aux Cntls --- Voltage Divides
  // x0 = Aux0 --- y0 = Post,
  // x1 = Aux1 --- y1 = Key
  // x2 = Aux2 --- y2 = 5V
  // x3 = Aux3 --- y3 = Pre  
  //------------------------------------------------------
  for (byte analogLoop = 0 ; analogLoop < 4; analogLoop++) {
    // Switch address for 4052 (1x)
    cd4052.setChannel(analogLoop);

    // X - AUX values
    data.getMyAuxsRangeMap(analogLoop).current  = cd4052.analogReadX();

    // Y - Volt Values
    data.setVolts(analogLoop, cd4052.analogReadY());
    }

  //  --  MySwitchesButtons
  //myAux.AUX1 = analog[0];
  //myAux.AUX2 = analog[1];
  //myAux.AUX3 = analog[2];
  //myAux.AUX4 = analog[3];

  //------------------------------------------------------
  // Send our data

  // Set Joystick values (0-4) via Range limits  
  //  radio.write(&myControls, sizeof(MyControls));

  //------------------------------------------------------
  // Button pressed?
  keyPad.doKeys(data.getVolts(KEY));
  keyPress = keyPad.getKeyPressed();

  //------------------------------------------------------
  // Inc Frames Per Second
  //------------------------------------------------------
  menu.updateFPS();

  //------------------------------------------------------
  // Update LCD 1/4 seconds
  //------------------------------------------------------

  if (keyPress > 0) {
       menu.updateLCD(keyPress);
  } else {
  if (menu.isScreenRefreshNeeded()) {
       menu.updateLCD(NOKEY);    
    }
  }

  
  //------------------------------------------------------
  // Serial Debugging
  //serialDebug();
}


//  #ifdef NOTDEFINED
//    if(true){
//      Serial.print  ("=== pre-> ");
//      Serial.print  (data.getPreVolts()); // this is for testing.
//      Serial.print  ("V  ");
//      Serial.print  ("=== pst-> ");
//      Serial.print  (data.getPstVolts()); // this is for testing.
//      Serial.print  ("V  ");
//      Serial.print  ("=== v5 -> ");
//      Serial.print  (data.getV5Volts()); // this is for testing.
//      Serial.print  ("V  ");
//  //    Serial.print  ("=== amp-> ");
//  //    Serial.print  (data.getMilliAmps()); // this is for testing.
//  //    Serial.print  ("mA  ");
//      Serial.println();
//  
//      lcd.setCursor(0, 3);//   row >    column ^
//      lcd.print  ("  ");
//      lcd.print((data.getMilliAmps()));
//      lcd.print  ("mA  ");
//  }
//  #endif
