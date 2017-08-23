#include <SPI.h>
 
/*
AD7705     Arduino
Vcc             =>5V
GND          => GND
DOUT        =>D12(MISO)
DIN            =>D11(MOSI)
RST           =>5V
SCK           =>D13(CLK)
CS             =>D10
DRDY        -NotConnectedf*/
//#include 
// Pin setup
#define CS        (10)

// COMM Register
#define DRDY_BIT      (0x80)
//**************************
#define COMM_REG      (0x00)
#define SETUP_REG     (0x10)
#define CLOCK_REG     (0x20)
#define DATA_REG      (0x30)
#define OFFSET_REG    (0x60)
#define GAIN_REG      (0x70)
//**************************
#define READ          (0x08)
#define WRITE         (0x00)
//**************************
#define STBY          (0x04)
//**************************
#define AIN1          (0x00)
#define AIN2          (0x01)

// SETUP Register
#define OP_NORMAL   (0x00)
#define OP_SELF_CAL (0x40)
#define OP_ZS_CAL   (0x80)
#define OP_FS_CAL   (0xC0)
//************************
#define GAIN_1      (0x00)
#define GAIN_2      (0x08)
#define GAIN_4      (0x10)
#define GAIN_8      (0x18)
#define GAIN_16     (0x20)
#define GAIN_32     (0x28)
#define GAIN_64     (0x30)
#define GAIN_128    (0x38)
//************************
#define BIPOLAR     (0x00)
#define UNIPOLAR    (0x04)
//************************
#define BUF_OFF     (0x00)
#define BUF_ON      (0x02)
//************************
#define FSYNC_OFF   (0x00)
#define FSYNC       (0x01)
//************************

// CLOCK Register
#define CLKDIS (0x10)
#define CLKDIV (0x08)
#define CLK    (0x04)
//*******************
#define SPS_20 (0x00)//Samples Per Second
#define SPS_25 (0x01)
#define SPS_100 (0x02)
#define SPS_200 (0x03)
#define SPS_50 (0x04)
#define SPS_60 (0x05)
#define SPS_250 (0x06)
#define SPS_500 (0x07) //SPS

int sensorPin0 = A0;
int sensorPin1 = A1;
void setup()
{
  Serial.begin(115200);
  digitalWrite(CS, 1);
  SPI.begin();


  digitalWrite(CS, 0);

  SPI.transfer(AIN1 | WRITE | SETUP_REG);//Calibration AIN1
  SPI.transfer(GAIN_1 | UNIPOLAR | OP_SELF_CAL);
  while (dataReady()) {}
  SPI.transfer(AIN2 | WRITE | SETUP_REG);//Calibration AIN2
  SPI.transfer(GAIN_1 | UNIPOLAR | BUF_OFF | FSYNC_OFF | OP_SELF_CAL);
  while (dataReady()) {}
  SPI.transfer( WRITE | CLOCK_REG); // Clock register
  SPI.transfer(CLKDIV | SPS_500);//too noisy @500 sps use higher gain to eliminate

  digitalWrite(CS, 1);

  Serial.println("INIT complete");


  unsigned int data = 0;
  digitalWrite(CS, 0);
  SPI.transfer(COMM_REG | READ);
  data = SPI.transfer(0x00);
  digitalWrite(CS, 1);
  Serial.print("C0MM Register==>"); Serial.println(data, BIN);

  digitalWrite(CS, 0);
  SPI.transfer(SETUP_REG | READ);
  data = SPI.transfer(0x00);
  digitalWrite(CS, 1);
  Serial.print("SETUP Register==>"); Serial.println(data, BIN);

  digitalWrite(CS, 0); // enable device
  SPI.transfer(CLOCK_REG | READ);
  data = SPI.transfer(0x00);
  digitalWrite(CS, 1); // release device
  Serial.print("CLOCK Register==>"); Serial.println(data, BIN);
  delay(2000);
}

void loop()
{
  unsigned int data = 0;

  while (dataReady()) {}
  digitalWrite(CS, 0);
  SPI.transfer(AIN2 | DATA_REG | READ);
  //takest a loooooong time to switch channels!!!
 /*   if(millis()<10000){
      SPI.transfer(AIN1 | DATA_REG | READ);
    }else{
       SPI.transfer(AIN2 | DATA_REG | READ);
    }*/

  data = SPI.transfer(0x00) << 8 | SPI.transfer(0x00);

  //if (data != 0x00 && data != 0xFFF){
  digitalWrite(CS, 1);
  Serial.print(millis() / 1000.); Serial.print("    "); 

  Serial.print(  analogRead(sensorPin0)); Serial.print(" x "); 
  Serial.print(  analogRead(sensorPin1)); Serial.print("    "); 
  

  Serial.print(data);Serial.print("    "); 
  Serial.print(data / 65535.*5000., 2); 

  Serial.println();

    delay(100);
  //}
}

boolean dataReady() {
  digitalWrite(CS, 0);
  SPI.transfer(COMM_REG | READ);
  return SPI.transfer(0x00)&DRDY_BIT == 0x00;
}





