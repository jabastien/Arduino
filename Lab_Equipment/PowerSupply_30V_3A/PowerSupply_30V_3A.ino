#include <Wire.h>
#include <Adafruit_ADS1015.h>

//Library version:1.1
#include <LiquidCrystal_I2C.h>
// https://playground.arduino.cc/Code/LCDAPI

#include <FormatPrint.h>
FormatPrint fmt;

//==============================================
// Data Sheets
//==============================================
// ADS1115    - http://www.ti.com/lit/ds/symlink/ads1115.pdf
// LM324      - http://www.ti.com/lit/ds/symlink/lm324-n.pdf
//==============================================

Adafruit_ADS1115 ads;     /* Use this for the 16-bit version */
// Adafruit_ADS1015 ads;  /* Use this for the 12-bit version */

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


// =============
// Pins
// =============
// SDA = A4
// SCL = A5


void setup(void) 
{
  // ===========================================================
  // initialize the lcd 
  // ===========================================================
  lcd.init();
  lcd.init();

  // Print a intro message to the LCD.
  lcd.backlight();
  //lcd.setBacklight(LOW);      // Backlight off
  lcd.setBacklight(HIGH);     // Backlight on

  //            > ^
  lcd.setCursor(0,0);
  lcd.print("Q-Bytes World!");
  //            > ^
  lcd.setCursor(0,1);
  //         1234567890123456789
  lcd.print("P.S.U. - 30V 3A");



  // ===========================================================
  // Init Serial logging  
  // ===========================================================
  Serial.begin(57600);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();

  // ===========================================================
  // pause for intro
  // ===========================================================
  delay(1000);

  lcd.clear();
  //lcd.cursor(); // Prints an underscore symbol 
  lcd.noCursor(); //Clears the underscore only.
  //lcd.blink();  //Blinking cursor
  lcd.noBlink();  //Turns OFF blinking cursor

}


unsigned long startTime = 0;

float mxI=0.0;
float mxV=0.0;

float setAmp = 0;
float outAmp = 0;
float setVolt = 0;
float outVolt = 0;

// Measurement at input with no load
float multiOffset=0.03688; //0.0155; // When current pot at zero (0)
// Current multiplier
// 100 ohm 10W resistor across terminals
// Set current pot to max
// 0.30048 is current measured on Fluke (400 mA range) 
// 0.14568 is voltage measured on Fluke (input pin should match) 
//float multiI = 0.30048/(0.14568-multiOffset);
float multiI = 0.32433/(0.17625 - multiOffset);

//
float multiV = 30.001/4.3192;

int num = 0;
  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
int16_t getAvg(byte port){
  int32_t sum = 0;
  byte loopSize = 16;

  if (loopSize >= 16)
    loopSize = 16;
    
  for (byte loop = 0; loop < loopSize; loop++){
    sum = sum + ads.readADC_SingleEnded(port);
    delay(1);
  }
  
  int16_t avg = sum / loopSize;
  return avg;
}

// ===========================================================================================
// ===========================================================================================
// ===========================================================================================
void loop(void) 
{
  startTime = millis();
  
  int16_t adc0, adc1, adc2, adc3;

  // ===========================================================================================
  // ===========================================================================================
  // Get Set Amp
  // ===========================================================================================
  ads.setGain(GAIN_ONE);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  mxI = 0.125;

  adc0 = getAvg(0);

  Serial.print(" (AIN0: "); Serial.print(adc0 * mxI); Serial.print("mV) ");

  setAmp = (((float)adc0*mxI)-(multiOffset*1000))*multiI;
  Serial.print(setAmp);
  Serial.print("mI \t");
  
  // ===========================================================================================
  // Get Out Amp
  // ===========================================================================================
  ads.setGain(GAIN_TWOTHIRDS);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  mxI = 0.1875;
 
  adc1 = getAvg(1);

outAmp = adc1 * mxI;
//if (val < 0.0)
//  val = 0.0;
  Serial.print(" (AIN1: "); Serial.print(outAmp); Serial.print("mV) ");

  Serial.print (((float)adc1*mxI)*multiI); 
  Serial.print("mI  \t"); 


  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
  // Get Set Volt
  // ===========================================================================================

  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  mxV = 0.1875;
  
  adc2 = getAvg(2);
//  if (adc2 < min2)
//    min2 = adc2/2;
    
  setVolt = ((float)adc2*mxV)*multiV/1000;
  Serial.print(" (AIN2: "); Serial.print(adc2 * mxV); Serial.print("mV) ");
  Serial.print (setVolt); 
  Serial.print("V "); 
   
  Serial.print("\t"); 



  // ===========================================================================================
  // Get Out Volt
  // ===========================================================================================
//  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
//  mxV = 0.125;
  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  mxV = 0.1875;

  
  //adc3 = ads.readADC_SingleEnded(3);
  adc3 = getAvg(3);
//  if (adc3<min3)
//    min3 = adc3/2;

  outVolt = ((float)adc3*mxV)*multiV/1000;
  Serial.print(" (AIN3: "); Serial.print(adc3 * mxV); Serial.print("mV) ");
  Serial.print (outVolt); 
  Serial.print("V "); 

      
  Serial.print("\t"); 

  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
  Serial.print(" --> "); 
  Serial.print(millis()-startTime);
  
  Serial.println(" ");
  
  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
  // LCD print
  lcd.home (); // set cursor to 0,0
  
  // ===========================================================================================
  // ===========================================================================================
  lcd.setCursor (0,0);        // go to start of 1st line
  lcd.print("S: ");

  if (setAmp < 0.0)
    setAmp = 0.0;
  lcd.print(fmt.getFloat(setAmp/1000, 1, 3));
  lcd.print("A ");

  // ===========================================================================================
  
  setVolt = ((float)(int(setVolt * 1000))) / 1000; 
  
  if (setVolt< 10.0){
    if (setVolt < 0.0)
      setVolt = 0.0;
    lcd.print(fmt.getFloat(setVolt, 1, 3));
  }
  else{
    lcd.print(fmt.getFloat(setVolt, 2, 2));    
  }

  lcd.print("V");  

  // ===========================================================================================
  // ===========================================================================================
  //            > ^
  lcd.setCursor(0,1);        // go to start of 2nd line
  lcd.print("O: ");
  if (outAmp < 0.0)
    outAmp = 0.0;
  lcd.print(fmt.getFloat(outAmp/1000, 1, 3));
  lcd.print("A ");
  
  // ===========================================================================================
  outVolt = ((float)(int(outVolt * 1000))) / 1000; 
  if (outVolt < 10.0){
    if (outVolt < 0.0)
      outVolt = 0.0;
    lcd.print(fmt.getFloat(outVolt, 1, 3));
  }
  else{
    lcd.print(fmt.getFloat(outVolt, 2, 2));    
  }
  lcd.print("V");  

  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================

  //lcd.print(millis());
  delay(500-(millis()-startTime));

}
