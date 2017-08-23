/*A basic 4 channel transmitter using the nRF24L01 module.*/
/* Like, share and subscribe, ELECTRONOOBS */
/* http://www.youtube/c/electronoobs */

/* First we include the libraries. Download it from 
   my webpage if you donw have the NRF24 library */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);      // Initialization of the book (address, characters, rows)
String deviceInfo = "2.4G Transmitter";
String versionNum = "v1.01";

/*Create a unique pipe out. The receiver has to 
  wear the same unique code*/
  
const uint64_t pipeOut = 0xE8E8F0F0E1LL;

RF24 radio(9, 10); // select  CSN  pin

// The sizeof this struct should not exceed 32 bytes
// This gives us up to 32 8 bits channals
struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
};

MyData data;

void resetData() 
{
  //This are the start values of each channal
  // Throttle is 0 in order to stop the motors
  //127 is the middle value of the 10ADC.
    
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2 = 0;
}

void setup()
{
  Serial.begin(250000); //Set the speed to 9600 bauds if you want.

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


  delay(1000);  
  lcd.clear();     
}

/**************************************************/

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

void loop()
{
  // The calibration numbers used here should be measured 
  // for your joysticks till they send the correct values.
  data.throttle = mapJoystickValues( analogRead(A0), 13, 524, 1015, true );
  data.yaw      = mapJoystickValues( analogRead(A1),  1, 505, 1020, true );
  data.pitch    = mapJoystickValues( analogRead(A2), 12, 544, 1021, true );
  data.roll     = mapJoystickValues( analogRead(A3), 34, 522, 1020, true );
  data.AUX1     = digitalRead(7);
  data.AUX2     = digitalRead(8);

  radio.write(&data, sizeof(MyData));

    // LCD Display
    lcd.setCursor(0, 0);
    lcd.print (" TX-thrtl: ");
    lcd.print(data.throttle);
    lcd.print ("  ");

    lcd.setCursor(0, 1);
    lcd.print (" Tx-yaw  : ");
    lcd.print(data.yaw);
    lcd.print ("  ");      

Serial.print("TX Throttle: "); Serial.print(data.throttle);  Serial.print("    ");
Serial.print("TX Yaw: ");      Serial.print(data.yaw);       Serial.print("    ");
Serial.print("TX Pitch: ");    Serial.print(data.pitch);     Serial.print("    ");
Serial.print("TX Roll: ");     Serial.print(data.roll);      Serial.print("    ");
Serial.print("TX Aux1: ");     Serial.print(data.AUX1);      Serial.print("    ");
Serial.print("TX Aux2: ");     Serial.print(data.AUX2);      Serial.print("\n");
}
 
