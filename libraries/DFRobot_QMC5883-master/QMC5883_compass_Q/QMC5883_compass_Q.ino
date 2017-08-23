/*!
 * @file QMC5883_compass.cpp
 * @brief The program shows how to realize the function compass.When the program runs, please spin QMC5883 freely to accomplish calibration.
 * @n 3-Axis Digital Compass IC
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2017
 * @copyright	GNU Lesser General Public License
 *
 * @author [dexian.huang](952838602@qq.com)
 * @version  V1.0
 * @date  2017-7-3
 */

#include <Wire.h>
#include <DFRobot_QMC5883.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

DFRobot_QMC5883 compass;

void setup()
{
  Serial.begin(9600);
  while (!compass.begin())
  {
    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
    delay(500);
  }

    if(compass.isHMC()){
        Serial.println("Initialize HMC5883");
        compass.setRange(HMC5883L_RANGE_1_3GA);
        compass.setMeasurementMode(HMC5883L_CONTINOUS);
        compass.setDataRate(HMC5883L_DATARATE_15HZ);
        compass.setSamples(HMC5883L_SAMPLES_8);
    }
   else if(compass.isQMC()){
        Serial.println("Initialize QMC5883");
        compass.setRange(QMC5883_RANGE_2GA);
        compass.setMeasurementMode(QMC5883_CONTINOUS); 
        compass.setDataRate(QMC5883_DATARATE_50HZ);
        compass.setSamples(QMC5883_SAMPLES_8);
   }
   
 // LCD setup
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  if (compass.isHMC())
  {
    lcd.print("HMC5883L");
  }
  else
    if (compass.isQMC())
      {
      lcd.print("QMC5883");
      }
    else
      {
      lcd.print("Not found");
      }
  lcd.setCursor(0, 1);
  lcd.print("v1.00.01");
  lcd.setCursor(0, 2);
  lcd.print("This one looks good?");

  delay(2500);  
  lcd.clear();
  
  }
void loop()
{
  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0){
    heading += 2 * PI;
  }

  if (heading > 2 * PI){
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180/M_PI; 

  // Output
  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();

//==========================================
   lcd.setCursor(0,0);
   lcd.print("Heading ");
   lcd.print(heading);

   lcd.setCursor(0,1);
   lcd.print("Degress = ");
   lcd.print(headingDegrees);
   lcd.print("  ");

/*
//==================================================================
float s=1.0f;
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
*/  
  delay(100);
}