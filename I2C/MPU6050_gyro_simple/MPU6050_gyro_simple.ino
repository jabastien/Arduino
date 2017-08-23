/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Simple Gyroscope Example.
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

  // Initialize MPU6050
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_250DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();
  mpu.calibrateGyro(2);
    
  // If you want, you can set gyroscope offsets
   mpu.setGyroOffsetX(62);
   mpu.setGyroOffsetY(-16);
   mpu.setGyroOffsetZ(24);


  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(10);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  // Check settings
  checkSettings();
}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:        ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:      ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Gyroscope:         ");
  switch(mpu.getScale())
  {
    case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
  } 
  
  Serial.print(" * Gyroscope offsets: ");
  Serial.print(mpu.getGyroOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getGyroOffsetZ());
  
  Serial.println();
}

char *ftoa(char *a, double f, int precision)
{
 long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};
 
 char *ret = a;
 long heiltal = (long)f;
 itoa(heiltal, a, 10);
 while (*a != '\0') a++;
 *a++ = '.';
 long desimal = abs((long)((f - heiltal) * p[precision]));
 itoa(desimal, a, 10);
 return ret;
}

void printInt(float num)
{
  int number = (int)num;

  lcd.print(" ");
  
  if (number >= 0)
  {
    lcd.print(" "); // no neg sign
  }

  if (abs(number) <10)
    lcd.print(" ");
    
  if (abs(number) <100)
    lcd.print(" ");
    
  if (abs(number) <1000)
    lcd.print(" ");
    
  lcd.print(number);
}

void printNumber(float num, int prec)
{
  char numOut[10];
  //  ftoa(char *a, double f, int precision)
  ftoa(numOut,num,prec);
  if (num >= 0.0)
  {
    lcd.print(" ");
  }
    
  lcd.print(" ");
  lcd.print(numOut);
}


void loop()
{
//   lcd.clear();
    
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();

/*
  Serial.print(" Xraw = ");
  Serial.print(rawGyro.XAxis);
  Serial.print(" Yraw = ");
  Serial.print(rawGyro.YAxis);
  Serial.print(" Zraw = ");
  Serial.print(rawGyro.ZAxis);

  Serial.print("      ");

  Serial.print(" Xnorm = ");
  Serial.print(normGyro.XAxis);
  Serial.print(" Ynorm = ");
  Serial.print(normGyro.YAxis);
  Serial.print(" Znorm = ");
  Serial.print(normGyro.ZAxis);
*/

  lcd.setCursor(0,0);
//lcd.print("12345678901234567890");
  lcd.print("       X     Y     Z");
  
  lcd.setCursor(0,1);
  lcd.print("Ra");
  printInt(rawGyro.XAxis);
  printInt(rawGyro.YAxis);
  printInt(rawGyro.ZAxis);
  
  lcd.setCursor(0,2);
  lcd.print("Na");
  printInt(normGyro.XAxis);
  printInt(normGyro.YAxis);
  printInt(normGyro.ZAxis);

  float temp = mpu.readTemperature();
  
//  Serial.print(" Temp = ");
//  Serial.print(temp);
//  Serial.println(" *C");

  lcd.setCursor(0,3);
  lcd.print("Temp ");
  //lcd.print(temp);
  printNumber(temp,1);
  lcd.print("C  ");

  // T(°F) = T(°C) × 9/5 + 32
  float F = 9.0/5.0;
  printNumber(((temp * F)+32),1);
  lcd.print("F");
  delay(10);
}


