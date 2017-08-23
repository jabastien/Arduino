/*  
 * Check:  http://www.electronoobs.com/eng_robotica_tut5_2_1.php
 * 
 * 
A basic receiver test for the nRF24L01 module to receive 6 channels send a ppm sum
with all of them on digital pin D2.
Install NRF24 library before you compile
Please, like, share and subscribe on my https://www.youtube.com/c/ELECTRONOOBS
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int debugPin=3; // D3
int noRadioPin=4; // Db
int goodRadioPin=5; // Db

////////////////////// PPM CONFIGURATION//////////////////////////
#define channel_number 9  //set the number of channels
#define sigPin 2  //set PPM signal output pin on the arduino
//#define PPM_FrLen 27000  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_FrLen 31500  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 400  //set the pulse length // DAQ changed to all for more channels
//#define PPM_PulseLen 600  //set the pulse length
//////////////////////////////////////////////////////////////////


int ppm[channel_number];// +1 for BITS field

const uint64_t pipeIn =  0xE8E8F0F0E1LL;

RF24 radio(9, 10);

// The sizeof this struct should not exceed 32 bytes
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
  // 'safe' values to use when no radio input is detected
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2= 0;
  data.AUX3 = 0;
  data.AUX4= 0;
  data.BITS = 0;
  
  setPPMValuesFromData();
}

void setPPMValuesFromData()
{
  ppm[0] = map(data.throttle, 0, 255, 1000, 2000);
  ppm[1] = map(data.yaw,      0, 255, 1000, 2000);
  ppm[2] = map(data.pitch,    0, 255, 1000, 2000);
  ppm[3] = map(data.roll,     0, 255, 1000, 2000);
  ppm[4] = map(data.AUX1,     0, 255, 1000, 2000);
  ppm[5] = map(data.AUX2,     0, 255, 1000, 2000);  
  ppm[6] = map(data.AUX3,     0, 255, 1000, 2000);
  ppm[7] = map(data.AUX4,     0, 255, 1000, 2000);  
  ppm[8] = map(data.BITS,     0, 255, 1000, 2000);//data.BITS;
  }

/**************************************************/

void setupPPM() {
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, 0);  //set the PPM signal pin to the default state (off)

  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;  // compare match register (not very important, sets the timeout for the first interrupt)
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
}

void setup()
{  
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nReceiver begin");
  
  pinMode(debugPin, INPUT);      // sets the digital pin 2 as input
  pinMode (noRadioPin, OUTPUT); // if no RX ready
  digitalWrite(noRadioPin,LOW);
  pinMode (goodRadioPin, OUTPUT); // if no RX ready
  digitalWrite(goodRadioPin,HIGH);

  
    
  resetData();
  setupPPM();
  
  // Set up radio module
  radio.begin();
  radio.setDataRate(RF24_250KBPS); // Both endpoints must have this set the same
  radio.setAutoAck(false);

  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

/**************************************************/

unsigned long lastRecvTime = 0;

void recvData()
{  
  while ( radio.available() ) {        
    radio.read(&data, sizeof(MyData));
    lastRecvTime = millis();
  }
}

/**************************************************/

void loop()
{
  recvData();

  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
    // signal lost?
    resetData();
    digitalWrite(noRadioPin,LOW);
    digitalWrite(goodRadioPin,HIGH);
  }else{
    digitalWrite(noRadioPin,HIGH);
    digitalWrite(goodRadioPin,LOW);
  }
  
  setPPMValuesFromData();

  if (digitalRead(debugPin)==1)
  {
    Serial.print(" Throttle: ");
    Serial.print(data.throttle);
    Serial.print(" Yaw: ");
    Serial.print(data.yaw);
    Serial.print(" Pitch: ");
    Serial.print(data.pitch);
    Serial.print(" Roll: ");
    Serial.print(data.roll);
    Serial.print(" AUX 1: ");
    Serial.print(data.AUX1);
    Serial.print(" AUX 2: ");
    Serial.print(data.AUX2);
    Serial.print(" AUX 3: ");
    Serial.print(data.AUX3);
    Serial.print(" AUX 4: ");
    Serial.print(data.AUX4);
    Serial.print(" BITS: ");
    Serial.print(data.BITS);

    Serial.print(" ");
    Serial.println("");
  }  
}

/**************************************************/

//#error Delete this line befor you cahnge the value (clockMultiplier) below
#define clockMultiplier 2 // set this to 2 if you are using a 16MHz arduino, leave as 1 for an 8MHz arduino

ISR(TIMER1_COMPA_vect){
  static boolean state = true;

  TCNT1 = 0;

  if ( state ) {
    //end pulse
    PORTD = PORTD & ~B00000100; // turn pin 2 off. Could also use: digitalWrite(sigPin,0)
    OCR1A = PPM_PulseLen * clockMultiplier;
    state = false;
  }
  else {
    //start pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    PORTD = PORTD | B00000100; // turn pin 2 on. Could also use: digitalWrite(sigPin,1)
    state = true;

    if(cur_chan_numb >= channel_number) {
      cur_chan_numb = 0;
      calc_rest += PPM_PulseLen;
      OCR1A = (PPM_FrLen - calc_rest) * clockMultiplier;
      calc_rest = 0;
    }
    else {
      OCR1A = (ppm[cur_chan_numb] - PPM_PulseLen) * clockMultiplier;
      calc_rest += ppm[cur_chan_numb];
      cur_chan_numb++;
    }     
  }
}

