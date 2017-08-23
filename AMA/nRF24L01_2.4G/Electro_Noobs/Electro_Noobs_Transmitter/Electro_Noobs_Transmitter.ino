/*A basic 4 channel transmitter using the nRF24L01 module.*/
/* Like, share and subscribe, ELECTRONOOBS */
/* http://www.youtube/c/electronoobs */

/* First we include the libraries. Download it from 
   my webpage if you donw have the NRF24 library */

//// https://playground.arduino.cc/Main/SoftwareI2CLibrary
//// https://www.arduino.cc/en/Reference/PortManipulation
#define SCL_PIN 2 
#define SCL_PORT PORTD 
#define SDA_PIN 3 
#define SDA_PORT PORTD 
#include <SoftI2CMaster.h>

//#include <SPI.h>

#include <nRF24L01.h>
#include <RF24.h>

int debugPin=8; // D8

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
  byte AUX3;
  byte AUX4;
  byte BITS;
};

MyData data;

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

void setup()
{
//  pinMode(2, INPUT_PULLUP);
//  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  pinMode(debugPin, INPUT);      // sets the digital pin as input 
  
  Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nTransmitter begin");

  analogReference(EXTERNAL);
  
  //Start everything up
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  resetData();

  i2c_init();
  
}

/**************************************************/

// Returns a corrected value for a joystick position that takes into account
// the values of the outer extents and the middle of the joystick range.
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 127);
  else
    val = map(val, middle, upper, 127, 255);
  return ( !reverse ? 255 - val : val );
}



int cnt=0;
int cnt2=0;

extern volatile unsigned long timer0_millis;
unsigned long new_value = 0;

void setMillis(unsigned long new_millis){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}

void loop()
{
    timer0_millis = millis();
    
  // The calibration numbers used here should be measured 
  // for your joysticks till they send the correct values.
  data.throttle = mapJoystickValues( analogRead(A0), 335, 668, 924, false );
  data.yaw      = mapJoystickValues( analogRead(A1), 110, 518, 920, true );
  data.pitch    = mapJoystickValues( analogRead(A2), 130, 520, 910, false );
  data.roll     = mapJoystickValues( analogRead(A3), 136, 522, 927, false );
  //data.AUX1     = digitalRead(7);
  //data.AUX2     = digitalRead(8);
  data.AUX1     = mapJoystickValues( analogRead(A4), 0, 511, 1023, false );;
  data.AUX2     = mapJoystickValues( analogRead(A5), 0, 511, 1023, false );;
  data.AUX3     = mapJoystickValues( analogRead(A6), 0, 511, 1023, false );;
  data.AUX4     = mapJoystickValues( analogRead(A7), 0, 511, 1023, false );;

  //data.AUX5     = 0;//255-cnt;//digitalRead(9);
  //data.AUX4     = 0;//cnt;//digitalRead(10);
  data.BITS = 0;
//  data.BITS     |= digitalRead(0)<<0;
//  data.BITS     |= digitalRead(1)<<1;
  data.BITS     |= digitalRead(2)<<0;
  data.BITS     |= digitalRead(3)<<1;
  data.BITS     |= digitalRead(4)<<2;
  data.BITS     |= digitalRead(5)<<3;
  data.BITS     |= digitalRead(6)<<4;
  data.BITS     |= digitalRead(7)<<5;
  
  
  
  //PORTC; 0;//cnt;
  
   if ((15*2)<cnt2++)
    {
    cnt2=0;
    cnt++;
    if (cnt>=255)
      cnt=0;
    }
 
  0;//data.AUX4     = cnt++;
  if (cnt>250)
  {
    cnt=0;
  }

  
  radio.write(&data, sizeof(MyData));
  
  if (false)
  {
//    Serial.print(" Throttle: ");
    Serial.print(analogRead(A0));
//    Serial.print(" Yaw: ");
    Serial.print(analogRead(A1));
//    Serial.print(" Pitch: ");
    Serial.print(analogRead(A2));
//    Serial.print(" Roll: ");
    Serial.print(analogRead(A3));
//    Serial.print(" AUX 1: ");
    Serial.print(digitalRead(7));
//    Serial.print(" AUX 2: ");
    Serial.print(digitalRead(8));
//    Serial.print(" AUX 3: ");
    Serial.print(digitalRead(9));
//    Serial.print(" AUX 4: ");
    Serial.print(digitalRead(10));
//    Serial.print(" ");
    Serial.println("");
  }
  if (digitalRead(debugPin)==1)
  {

    Serial.print(timer0_millis);
    Serial.print(" ");
  //Change Millis
  setMillis(new_value);
    
//    Serial.print(" Throttle: ");
    Serial.print(data.throttle);
    Serial.print(" ");
    
//    Serial.print(" Yaw: ");
    Serial.print(data.yaw);
    Serial.print(" ");

//    Serial.print(" Pitch: ");    
    Serial.print(data.pitch);
    Serial.print(" ");

//    Serial.print(" Roll: ");
    Serial.print(data.roll);
    Serial.print(" ");
    
//    Serial.print(" AUX 1: ");
    Serial.print(data.AUX1);
    Serial.print(" ");
    
//    Serial.print(" AUX 2: ");
    Serial.print(data.AUX2);
    Serial.print(" ");
    
//    Serial.print(" AUX 3: ");
    Serial.print(data.AUX3);
    Serial.print(" ");
    
//    Serial.print(" AUX 4: ");
    Serial.print(data.AUX4);
    Serial.print(" ");
    
//    Serial.print(" BITS: ");
    Serial.print(data.BITS);
//    Serial.print(" ");

    Serial.println("");

      delay (250);
  }
}
