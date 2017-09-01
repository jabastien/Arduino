/*A basic 4 channel transmitter using the nRF24L01 module.*/
/* Like, share and subscribe, ELECTRONOOBS */
/* http://www.youtube/c/electronoobs */

/* First we include the libraries. Download it from 
   my webpage if you donw have the NRF24 library */


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// ===========================================
// RF24
// ===========================================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*Create a unique pipe out. The receiver has to 
  wear the same unique code*/
  
const uint64_t pipeOut = 0xE8E8F0F0E1LL;

RF24 radio(9, 10); // select  CE & CSN  pin

// ===========================================
// I2C LCD
// ===========================================
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);      // Initialization of the book (address, characters, rows)

// ===========================================
// Format Print
// ===========================================
#include <FormatPrint.h>
FormatPrint fmt;

// ===========================================
// CD 405x
// ===========================================
int looping = 0;

// ===========================================
// CD 4051
// ===========================================
#include <CD4051.h>
CD4051 cd4051 = CD4051(4, 5, 6, 8);

int pinSwitchs = 0b00000000;

// ===========================================
// CD4052
// ===========================================
#include <CD4052.h>

CD4052 cd4052 = CD4052(4, 5, A6, A7);

// ===========================================
// Vars
// ===========================================
String deviceInfo = "2.4G Transmitter";
String versionNum = "v1.03";

// ===========================================
// Timing Vars
// ===========================================
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 100;           // interval at which to update screen (milliseconds)

int fps=0;
int cntMillis=0;

// ===========================================
// Misc
// ===========================================
int debugPin=8; // D8

// ===========================================
// My Data
// ===========================================
// The sizeof this struct should not exceed 32 bytes
// This gives us up to 32 8 bits channals
struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
  byte AUX3;
  byte AUX4;
  byte BITS;
};

MyData data;

// ===========================================
// Reset Data
// ===========================================
void resetData() 
{
  //This are the start values of each channal
  // Throttle is 0 in order to stop the motors
  //127 is the middle value of the 10ADC.
    
  data.throttle = 0;
  data.yaw      = 127;
  data.pitch    = 127;
  data.roll     = 127;
  data.AUX1     = 0;
  data.AUX2     = 0;
  data.AUX3     = 0;
  data.AUX4     = 0;
  data.BITS     = 0;
}

// ===========================================
// Serial Debug
// ===========================================
void SerailDebug(){
  Serial.print("TX Throttle: "); Serial.print(data.throttle);  Serial.print("    ");
  Serial.print("TX Yaw: ");      Serial.print(data.yaw);       Serial.print("    ");
  Serial.print("TX Pitch: ");    Serial.print(data.pitch);     Serial.print("    ");
  Serial.print("TX Roll: ");     Serial.print(data.roll);      Serial.print("    ");
  Serial.print("TX Aux1: ");     Serial.print(data.AUX1);      Serial.print("    ");
  Serial.print("TX Aux2: ");     Serial.print(data.AUX2);      Serial.print("\n");  
}

// ===========================================
// Setup
// ===========================================
void setup()
{
  analogReference(EXTERNAL);

  // Debug Serial out
  Serial.begin(115200); //Set the speed to 9600 bauds if you want.
  pinMode(debugPin, INPUT);      // sets the digital pin as input 

  //Start everything up
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  resetData();

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(deviceInfo);
  lcd.setCursor(0, 1);
  lcd.print(versionNum); 
  lcd.setCursor(0, 2);
  printVolts();  
  delay(2000);  
  lcd.clear();    
}

// ===========================================
// Print Volts
// ===========================================
void printVolts(){
    lcd.print("Volts:");
    float sensorValue = (float)analogRead(A0);
    sensorValue *= (5.0 / 1023.0);
    lcd.print(fmt.getFloat(sensorValue, 6, 2));
}
/**************************************************/

// ===========================================
// Map Joystick Values
// ===========================================
// Returns a corrected value for a joystick position that takes into account
// the values of the outer extents and the middle of the joystick range.
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}

// ===========================================
// Update LCD
// ===========================================
void updateLCD(){
    // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.

    lcd.setCursor(0, 2);
    printVolts();    

    if (++cntMillis>=10){
      lcd.setCursor(0, 3);
      lcd.print(fps);
      fps=0;
      cntMillis=0;
    }

//------------------------------------------------------
/*
  // LCD Display
  lcd.setCursor(0, 0);
  lcd.print (" TX-thrtl: ");
  lcd.print(data.throttle);
  lcd.print ("  ");

  lcd.setCursor(0, 1);
  lcd.print (" Tx-yaw  : ");
  lcd.print(data.yaw);
  lcd.print ("  ");      
*/
//------------------------------------------------------     
}

int printInt(int n, String format){
  char c[10];        // long enough to hold complete integer string
  char charBuf[20];
  format.toCharArray(charBuf,20);
  int m = sprintf(c, charBuf, n);    // build integer string using C integer formatters  (m is length, and not used in this code)
  Serial.print(c);   
  return m;
}


// ===========================================
// Loop
// ===========================================
void loop()
{
  //------------------------------------------------------
  // The calibration numbers used here should be measured 
  // for your joysticks till they send the correct values.
  //------------------------------------------------------
  data.throttle = mapJoystickValues( analogRead(A0), 13, 524, 1015, true );
  data.yaw      = mapJoystickValues( analogRead(A1),  1, 505, 1020, true );
  data.pitch    = mapJoystickValues( analogRead(A2), 12, 544, 1021, true );
  data.roll     = mapJoystickValues( analogRead(A3), 34, 522, 1020, true );

  //------------------------------------------------------
  cd4051.setChannel(looping);

  // Get the switch values
  byte pinmask = ~(1<<(looping%8)); 
  byte readmask = (cd4051.digitalReadC()<<(looping%8)); 
  pinSwitchs = (pinSwitchs & pinmask) | readmask;

  //------------------------------------------------------
  //cd4052.setChannel(looping);
  printInt(looping % 4,"<X%1d:");
  printInt(cd4052.analogReadX(),"%4d> ");
  printInt(looping % 4,"<Y%1d:");
  printInt(cd4052.analogReadY(),"%4d> ");

  //------------------------------------------------------
  radio.write(&data, sizeof(MyData));

  //------------------------------------------------------
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      updateLCD();
  }
  
  //------------------------------------------------------
  //------------------------------------------------------
  // Increment looping
  if (++looping >=8){
    looping = 0;  
    }

  // New Line every 4 loops
  if ((looping % 4)==0){
    Serial.println();

    // Print switches
    Serial.print(" ");
    if (false){
      Serial.print(" Pin ");  
      Serial.print(pinmask + 0x100, BIN);
      Serial.print(" Mask ");  
      Serial.print(readmask + 0x100, BIN);
      }
    Serial.print(" Switch ");  
    Serial.print(pinSwitchs + 0x100, BIN);    
    }

  //------------------------------------------------------
  fps++;
}


