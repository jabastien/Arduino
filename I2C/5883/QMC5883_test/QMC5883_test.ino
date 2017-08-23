#include <Wire.h> //I2C Arduino Library

#define addr 0x0D //I2C Address for The HMC5883

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

  Serial.begin(9600);
  Wire.begin();


  Wire.beginTransmission(addr); //start talking
  Wire.write(0x0B); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x01); // Set the Register
  Wire.endTransmission();
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x09); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x1D); // Set the Register
  Wire.endTransmission();

 // LCD setup
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("QMC5883L");
  lcd.setCursor(0, 1);
  lcd.print("v1.00.01");
  lcd.setCursor(0, 2);
  lcd.print("This one looks good?");

  delay(2500);  
  lcd.clear();
}

void loop() {

  int x, y, z; //triple axis data
  int x1, y1, z1; // triple axis data
  int x2, y2, z2; // triple axis data

  //Tell the HMC what regist to begin writing data into


  Wire.beginTransmission(addr);
  Wire.write(0x00); //start with register 3.
  Wire.endTransmission();

  //Read the data.. 2 bytes for each axis.. 6 total bytes
  /*
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available()) {
    x = Wire.read(); //MSB  x
    x |= Wire.read() << 8; //LSB  x
    z = Wire.read(); //MSB  z
    z |= Wire.read() << 8; //LSB z
    y = Wire.read(); //MSB y
    y |= Wire.read() << 8; //LSB y
  }
*/

  //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available()) {
    x1 = Wire.read(); //MSB  x
    x2 |= Wire.read(); // << 8; //LSB  x
    z1 = Wire.read(); //MSB  z
    z2 |= Wire.read(); // << 8; //LSB z
    y1 = Wire.read(); //MSB y
    y2 |= Wire.read(); // << 8; //LSB y
  }

  x= x1 + (x2<<8);
  y= y1 + (y2<<8);
  z= z1 + (z2<<8);
  
  // Show Values
  Serial.print("  X Value: ");
  Serial.print(x);
  Serial.print("  Y Value: ");
  Serial.print(y);
  Serial.print("  Z Value: ");
  Serial.print(z);



  Wire.beginTransmission(addr);
  Wire.write(0x00); //start with register 3.
  Wire.endTransmission();

  
   // Calculate heading when the magnetometer is level.
  //float headingDegrees = atan2(raw.YAxis, raw.XAxis)*180/3.14+180;;
float s = 1.0f;
  float headingDegrees = atan2(y*s, x*s)*180/PI+180;;

  Serial.print("  Heading: ");
  Serial.print(headingDegrees);

float scale = 0.92f;
float b = atan2(y2*scale,x2*scale);
if (b<0)
  b += (2*3.14f);
  Serial.print("  Bearing: ");
  Serial.print(b);
  
  
  Serial.println();

   lcd.setCursor(0,0);
   lcd.print("Heading ");

   lcd.setCursor(0,1);
   lcd.print("y & x  = ");
   lcd.print(headingDegrees);
   lcd.print("  ");


//==================================================================
s=1.0f;
headingDegrees = atan2(y, z)*180/PI+180;;

  Serial.print("  Bearing: ");
  Serial.print(b);
  
//float heading = atan2(norm.YAxis, norm.XAxis);
   lcd.setCursor(0,2);
   lcd.print("y & z = ");
   lcd.print(headingDegrees);
   lcd.print("  ");

//==================================================================
s=1.0f;
headingDegrees = atan2(z, x)*180/PI+180;;

  Serial.print("  Bearing: ");
  Serial.print(b);
  
//float heading = atan2(norm.YAxis, norm.XAxis);
   lcd.setCursor(0,3);
   lcd.print("z & x = ");
   lcd.print(headingDegrees);
   lcd.print("  ");

  delay(100);
}
