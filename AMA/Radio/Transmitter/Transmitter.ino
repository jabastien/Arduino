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
// Vars
// ===========================================
String deviceInfo = "2.4G Transmitter";
String versionNum = "v1.04";

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
int digitalLoop = 0;

// ===========================================
// CD 4051
// ===========================================
#include <CD4051.h>
CD4051 switchCD4051 = CD4051(3, 4, 5, 6);
CD4051 trimCD4051   = CD4051(3, 4, 5, 7);
CD4051 menuCD4051   = CD4051(3, 4, 5, 8);

int switchPin = 0b00000000;
int trimPin    = 0b00000000;
int menuPin    = 0b00000000;

byte pinmask;
byte readmask;

// ===========================================
// CD4052
// ===========================================
#include <CD4052.h>

CD4052 cd4052 = CD4052(3, 4, A6, A7);
int analog[8];
int analogLoop = 0;

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
void serialDebug(){

  // New Line every 4 loops
  if (digitalLoop == 0){
    Serial.println();

    // Print switches
    Serial.print(" ");
    if (false){
      Serial.print(" Pin ");  
      Serial.print(pinmask + 0x100, BIN);
      Serial.print(" Mask ");  
      Serial.print(readmask + 0x100, BIN);
      }
    if (false){
      Serial.print(" Switch: ");  
      Serial.print(switchPin + 0x100, BIN);    
      Serial.print(" Trim: ");  
      Serial.print(trimPin + 0x100, BIN);    
      Serial.print(" Menu: ");  
      Serial.print(menuPin + 0x100, BIN);    
      }
    }

  //------------------------------------------------------
  if (false){
    //cd4052.setChannel(digitalLoop); // not required, sharing with cd4051
    printInt(digitalLoop % 4,"<X%1d:");
    printInt(cd4052.analogReadX(),"%4d> ");
    printInt(digitalLoop % 4,"<Y%1d:");
    printInt(cd4052.analogReadY(),"%4d> ");
    }

  if (false){
    Serial.print("TX Throttle: "); Serial.print(data.throttle);  Serial.print("    ");
    Serial.print("TX Yaw: ");      Serial.print(data.yaw);       Serial.print("    ");
    Serial.print("TX Pitch: ");    Serial.print(data.pitch);     Serial.print("    ");
    Serial.print("TX Roll: ");     Serial.print(data.roll);      Serial.print("    ");
    Serial.print("TX Aux1: ");     Serial.print(data.AUX1);      Serial.print("    ");
    Serial.print("TX Aux2: ");     Serial.print(data.AUX2);      Serial.print("\n");  
    }
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
long day = 86400000; // 86400000 milliseconds in a day
long hour = 3600000; // 3600000 milliseconds in an hour
long minute = 60000; // 60000 milliseconds in a minute
long second =  1000; // 1000 milliseconds in a second
void updateLCD(){
  // check to see if it's time to update LCD; that is, if the difference
  // between the current time and last time you updated the LCD is bigger than
  // the interval at which you want to blink the LED.
  currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

    lcd.setCursor(0, 1);
    printVolts();    //Voltage: xx.xV


    if (++cntMillis>=10){
      // -------------------------------------
      lcd.setCursor(0, 0);
      lcd.print("Flight Time: ");
long timeNow = millis();
 
int days = timeNow / day ;                                //number of days
int hours = (timeNow % day) / hour;                       //the remainder from days division (in milliseconds) divided by hours, this gives the full hours
int minutes = ((timeNow % day) % hour) / minute ;         //and so on...
int seconds = (((timeNow % day) % hour) % minute) / second;      
     // lcd.print("MM:SS");
     lcd.print(minutes);
     lcd.print(":");
     lcd.print(seconds);
    
      // -------------------------------------
      lcd.setCursor(0, 2);
      lcd.print("Channel:");
      lcd.print(" xxx");
      
      // -------------------------------------
      lcd.setCursor(0, 3);
      lcd.print("TPS:");
      lcd.print(fps);  // ~350 has been the average
      
      // -------------------------------------
      fps=0;
      cntMillis=0;
    }
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
void loop(){
  //------------------------------------------------------
  // The calibration numbers used here should be measured 
  // for your joysticks till they send the correct values.
  //------------------------------------------------------
  data.throttle = mapJoystickValues( analogRead(A0), 13, 524, 1015, true );
  data.yaw      = mapJoystickValues( analogRead(A1),  1, 505, 1020, true );
  data.pitch    = mapJoystickValues( analogRead(A2), 12, 544, 1021, true );
  data.roll     = mapJoystickValues( analogRead(A3), 34, 522, 1020, true );

  //------------------------------------------------------
  // Switch address for 4051 (3) and 4052 (1)
  switchCD4051.setChannel(digitalLoop);

  // Set mask using loop values
  pinmask = ~(1<<(digitalLoop%8)); 

  // Switch
  readmask = (switchCD4051.digitalReadC()<<(digitalLoop%8)); 
  switchPin = (switchPin & pinmask) | readmask;
  
  // Trim
  readmask = (trimCD4051.digitalReadC()<<(digitalLoop%8)); 
  trimPin = (trimPin & pinmask) | readmask;
  
  // Menu
  readmask = (menuCD4051.digitalReadC()<<(digitalLoop%8)); 
  menuPin = (menuPin & pinmask) | readmask;

  //------------------------------------------------------
  // Read Analog
 // analog[analogLoop]   = cd4052.analogReadX();
 // analog[analogLoop+1] = cd4052.analogReadY();

  //------------------------------------------------------
  // Send our data
  radio.write(&data, sizeof(MyData));

  //------------------------------------------------------
  // Update LCD 1/10 seconds
  updateLCD();
    
  //------------------------------------------------------
  //------------------------------------------------------
  // Increment looping
  if (++digitalLoop >=8){
    digitalLoop = 0;  
    }
    
  if (++analogLoop >=4){
    analogLoop = 0;  
    }
    
  //------------------------------------------------------
  // Serial Debugging 
  serialDebug();
  
  //------------------------------------------------------
  // Increment Frames Per Second
  fps++;
}
