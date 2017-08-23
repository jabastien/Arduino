/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Temperature Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() 
{
  Serial.begin(9600);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop()
{
  float temp = mpu.readTemperature();

  Serial.print(" Temp = ");
  Serial.print(temp);
  Serial.print("'C    ");

    // T(°F) = T(°C) × 9/5 + 32
  float F = 9.0/5.0;
  Serial.print(((temp * F)+32),1);
  Serial.println("'F");
  
  delay(500);
}

