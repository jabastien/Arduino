#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_MCP4725.h>

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

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (8)
Adafruit_MCP4725 dac;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


// =============
// Pins
// =============
// SDA = A4
// SCL = A5


// =============================================================================
// =============================================================================
unsigned long startTime = 0;

float mxI = 0.0;
float mxV = 0.0;

float setAmp = 0;
float outAmp = 0;
float setVolt = 0;
float outVolt = 0;

// Measurement CURRENT SET at input with no load
// Current multiplier
// 100 ohm 10W resistor across terminals
// Output volts off
// Set current pot to max
// 0.30048 is current measured on Fluke (400 mA range)
// 0.14568 is voltage measured on Fluke (input pin should match)

// ADC 0
float setCurrentPinOffset = 3.18; // When current pot at zero (0), include sign +/-
float setCurrentPin    = 25;
float setCurrentVolt   =  0.593;
float setCurrentMulti  = (setCurrentVolt / setCurrentPin) * 1000;


// ADC 1
// Measurement CURRENT OUT at input with no load
// same but different PINs
float outCurrentPinOffset  =  4.38; // When current pot at zero (0), include sign +/-
float outCurrentPin   =  52.78666667   ;
float outCurrentVolt  =   0.11715;
float outCurrentMulti =  (outCurrentVolt / outCurrentPin) * 1000;

// ADC 2
// Voltage Set (all values are averaged from Arduino and Voltmeter (1, 2, 5, 10, 20 volt ranges)
float setVoltPinOffset = -5.81/2;  // millaVolts Volts as Read from ADC (not pin)  (diff between fluke and pin read)
float setVoltPin    =  1740.5; //1.44113 + setVoltPinOffset; // Volts 0.710;      //711.56/75 Volts as Read from Volt Meter???
float setVoltVolt   =  10.01;         //10.10100;     // Volts on Volt Meter
float setVoltMulti  = setVoltVolt / setVoltPin;
// ADC 3
// Voltage out
//float outVoltPinOffset = 1.12 / 2; //
//float outVoltPin    =  1907.855  ;
//float outVoltVolt   =  11.38871667;
//float outVoltMulti  = outVoltVolt / outVoltPin;

float outVoltPinOffset = 1.12 / 2; //
float outVoltPin    =  1675.88  ;
float outVoltVolt   =  10.08;
float outVoltMulti  = outVoltVolt / outVoltPin;

// =============================================================================
// =============================================================================

//Initializing LED Pin
// (SETUP PWM)
int led_pin5 = 5;
int led_i5=0;
int led_pin6 = 6;
int led_i6=0;

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

  //lcd.cursor(); // Prints an underscore symbol
  lcd.noCursor(); //Clears the underscore only.
  //lcd.blink();  //Blinking cursor
  lcd.noBlink();  //Turns OFF blinking cursor
  
  //            > ^
  lcd.setCursor(0, 0);
  lcd.print("Q-Bytes World!");
  //            > ^
  lcd.setCursor(0, 1);
  //         1234567890123456789
  lcd.print("P.S.U. - 30V 3A");



  // ===========================================================
  // Init Serial logging
  // ===========================================================
  Serial.begin(57600);
  Serial.println("Hello!");

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");


Serial.print (" (outCurrentMulti * 1000): ");
Serial.println (outCurrentMulti * 1000);


Serial.print (" (setVoltMulti:* 1000): ");
Serial.println (setVoltMulti * 1000);

  // ===========================================================
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
  // ===========================================================

  ads.begin();

  // ===========================================================
  // pause for intro
  // ===========================================================

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x62);
  
  // ===========================================================
  // pause for intro
  // ===========================================================
  delay(1000);

  lcd.clear();
  
  // ===========================================================
  // (SETUP PWM)
  // pause for intro
  // ===========================================================
  //Declaring LED pin as output
  pinMode(led_pin5, OUTPUT);
  pinMode(led_pin6, OUTPUT);

  pinMode(12, OUTPUT);  
  pinMode(13, OUTPUT);  
}

// ===========================================================================================
// ===========================================================================================
// ===========================================================================================
int16_t getAvg(byte port) {
  int32_t sum = 0;
  byte loopSize = 16;

  if (loopSize >= 16)
    loopSize = 16;

  for (byte loop = 0; loop < loopSize; loop++) {
    sum = sum + ads.readADC_SingleEnded(port);
    delay(1);
  }

  int16_t avg = sum / loopSize;
  return avg;
}

// ===========================================================================================
// ===========================================================================================
// ===========================================================================================
  int stepV = 1;
  int32_t setMyI = 0;
  int32_t setMyFF = -1;
void loop(void)
{

  startTime = millis();

  int16_t adc0, adc1, adc2, adc3;

  // ===========================================================================================
  // ===========================================================================================
  // Get setAmp - ADC 0
  // ===========================================================================================
  ads.setGain(GAIN_ONE);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  mxI = 0.125;

  adc0 = getAvg(0);

  Serial.print(" (AIN0: "); Serial.print(adc0 * mxI); Serial.print("mV) ");

  setAmp = (((float)adc0 * mxI) - setCurrentPinOffset) * setCurrentMulti;
  Serial.print(setAmp);
  Serial.print("mI \t");

  // ===========================================================================================
  // Get outAmp - ADC 1
  // ===========================================================================================
  ads.setGain(GAIN_ONE);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  mxI = 0.125;

  adc1 = getAvg(1);

  Serial.print(" (AIN1: "); Serial.print(adc1 * mxI); Serial.print("mV) ");

  outAmp = (((float)adc1 * mxI) - outCurrentPinOffset) * outCurrentMulti;
  Serial.print (outAmp);
  Serial.print("mI  \t");

  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
  // Get setVolt - ADC 2
  // ===========================================================================================
  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  mxV = 0.1875;

  adc2 = getAvg(2);

  Serial.print(" (AIN2: "); Serial.print(adc2 * mxV); Serial.print("mV) ");

  setVolt = ((((float)adc2 * mxV) - setVoltPinOffset) * setVoltMulti);
  Serial.print (setVolt);
  Serial.print("V \t");

  // ===========================================================================================
  // Get Out Volt - ADC 3
  // ===========================================================================================
  //  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  //  mxV = 0.125;
  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  mxV = 0.1875;

  adc3 = getAvg(3);

  Serial.print(" (AIN3: "); Serial.print(adc3 * mxV); Serial.print("mV) ");

  outVolt = ((((float)adc3 * mxV) - outVoltPinOffset) * outVoltMulti);
  Serial.print (outVolt);
  Serial.print("V \t");

  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
  Serial.print(" --> ");
  Serial.print(millis() - startTime);

  Serial.println(" ");

  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
  // LCD print
  lcd.home (); // set cursor to 0,0

  // ===========================================================================================
  // ===========================================================================================
  //            > ^
  lcd.setCursor (0, 0);       // go to start of 1st line
  lcd.print("S: ");

  //            > ^
  lcd.setCursor(0, 1);       // go to start of 2nd line
  lcd.print("O: ");

  // ===========================================================================================
  // ===========================================================================================
  //            > ^
  lcd.setCursor (3, 0);       // go to start of 1st line

  if (setAmp < 0.0)
    setAmp = 0.0;
  lcd.print(fmt.getFloat(setAmp / 1000, 1, 3));
  lcd.print("A ");

  // ===========================================================================================
  //            > ^
  lcd.setCursor (3, 1);       // go to start of 1st line

//  if (outAmp < 0.0)
//    outAmp = 0.0;
//  lcd.print(fmt.getFloat(outAmp / 1000, 1, 3));
//  lcd.print("A ");
lcd.print(setMyI);
lcd.print("   ");
  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================

  //            > ^
  lcd.setCursor(10, 0);       // go to start of 2nd line

  setVolt = ((float)(int(setVolt * 1000))) / 1000;

  if (setVolt < 10.0) {
    if (setVolt < 0.0)
      setVolt = 0.0;
    lcd.print(fmt.getFloat(setVolt, 1, 3));
  }
  else {
    lcd.print(fmt.getFloat(setVolt, 2, 2));
  }

  lcd.print("V");

  // ===========================================================================================

  //            > ^
  lcd.setCursor(10, 1);       // go to start of 2nd line
//
  outVolt = ((float)(int(outVolt * 1000))) / 1000;
  if (outVolt < 10.0) {
    if (outVolt < 0.0)
      outVolt = 0.0;
    lcd.print(fmt.getFloat(outVolt, 1, 3));
  }
  else {
    lcd.print(fmt.getFloat(outVolt, 2, 2));
  }
  lcd.print("V");


  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================
  // (Set PWM)
  led_i5 += 5;
  if (led_i5>255){
    led_i5 = 0;
    led_i6 += 5;
    if (led_i6>255)
      led_i6 = 0;
  }
    
  analogWrite(led_pin5, led_i5);
  analogWrite(led_pin6, led_i6);
    
  // ===========================================================================================
  // ===========================================================================================
  // ===========================================================================================

  lcd.print(millis());

  digitalWrite(12, HIGH); // sets the digital pin 13 on
  digitalWrite(13, HIGH); // sets the digital pin 13 on
  
//  int32_t counter;
//  // Run through the full 12-bit scale for a triangle wave
//  int step = 1;
//
//  // 1 bit = 0.0012210012210012
//  // 982.8 = 1.199 volts = ~3A
//  //  98   = .119 Volt = ~0.3A
//  //  33   =  .04029 = ~0.1A
//  int amp = 10;
//    for (counter = amp; counter > 0; counter-=step)
//  {
//    dac.setVoltage(counter, false);
//  } 
//  delay(150);
//  for (counter = 0; counter < amp; counter+=step)
//  {
//    dac.setVoltage(counter, false);
//  }


// http://www.learnabout-electronics.org/Amplifiers/amplifiers66.php
stepV = 100;
if (setMyI >= 1400)
    setMyFF = -stepV;
    
if (setMyI < stepV)
     setMyFF = +stepV;

setMyI += setMyFF;

  dac.setVoltage(setMyI, false);
Serial.print  ("setMyI: ");
Serial.println(setMyI);
  
  int pause = 500 - (millis() - startTime);
//  Serial.print  ("Pause: ");
//  Serial.println(pause);
  if (pause < 1)
    pause = 1;
  delay(pause);
  
  digitalWrite(12, LOW); // sets the digital pin 13 on
  digitalWrite(13, LOW); // sets the digital pin 13 on
}
