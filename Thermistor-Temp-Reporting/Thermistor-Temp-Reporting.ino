//Measure NTC 3950 value

//http://www.instructables.com/id/Temperature-Sensor-Tutorial/


// Do this::::
// https://www.embeddedrelated.com/showarticle/91.php
// https://edwardmallon.wordpress.com/2017/04/26/calibrating-oversampled-thermistors-with-an-arduino/

byte NTCPin0 = A0;
float ADCperc0;
float ADCvalue0;

byte NTCPin1 = A1;
float ADCperc1;
float ADCvalue1;


// https://arduinodiy.wordpress.com/2015/11/10/measuring-temperature-with-ntc-the-steinhart-hart-formula/
// Rntc = Rseries * (1023 / ADC - 1); // for pull down
// Rntc = Rseries / (1023 / ADC – 1); // for pull-up configuration

unsigned long R1 = 108300; // Known resistor
unsigned long RX; // Unknown resistance -> NTC3950 (Max 100K)

float VCC = 3.207; //3.3;
float Vo = 0.0;

///////////////////////////////////////////////
// resistance at 25 degrees C
#define THERMISTORNOMINAL 100000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 100000    


void setup()
{
  Serial.begin(9600);

  // https://www.arduino.cc/en/Reference/analogReference
  //analogReference(DEFAULT);
  analogReference(EXTERNAL);

  Serial.print("ADCvalue: ");
  Serial.println(analogRead(A2));
  Serial.println("--------------");  
}

void loop()
{
  // Get the ADC value from the PIN
  ADCvalue0 = analogRead(NTCPin0);
  ADCvalue1 = analogRead(NTCPin1);
  if (false)
  {
    Serial.print("Analog: ");
    Serial.print(ADCvalue0);
    Serial.print(" ");
  }
  
  ADCperc0 = ADCvalue0 / 1023;
  if (false)
  {
    Serial.print("Percent: "); 
    Serial.print(ADCperc0);
    Serial.print(" ");
  }
  
  // ====================================
  // Find Volts
  // ====================================
  Vo = VCC * ADCperc0;
  if (false)
  {  
    Serial.print("Volts: ");
    Serial.print(Vo);
    Serial.print(" ");
  }
  
  // ====================================
  // Find Unknown Resistor
  // ====================================
  if (false)
  {
    //https://en.wikipedia.org/wiki/Voltage_divider
    // RX = R1 * ((VCC / Vo) - 1)
    RX = R1 * ((VCC/Vo)-1);
    Serial.print("Ohms: ");
    Serial.print(RX); 
    Serial.print(" ");
  }

  // ====================================
  // Find Temperature
  // https://learn.adafruit.com/thermistor/using-a-thermistor
  // https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
  // ====================================

  // Temp 0 ----------------------------------------------------
  if (true)
  { //                 R1        Bits
    long resistance = (108830 * (1024 / ADCvalue0 - 1));
    
    // Calk Kelvin
    float result = log (resistance);
    float A = 0.000541774592748;
    float B = 0.000238870735000;
    float C = 0.000000048293022;
    result = 1.0 / (A + (B * result) + (C * result * result * result));
    
    Serial.print("T0-Chamber "); 
    if (false)
    {
      Serial.print(result);
      Serial.print( (char)0xB0);
      Serial.print("K ");
    } 
    // Calc Celsius   
    result = result - 273.15; // Convert to Celsius
    if (true)
    {
      Serial.print(result);
      //Serial.print( (char)0xB0);
      //Serial.print("C");
      Serial.print(" ");
    }   
    // Calc Fahrenheit   
    result = ((result * 9) / 5) +32; // Convert to Fahrenheit
    if (true)
    {    
      Serial.print(result);
      //Serial.print( (char)0xB0);
      //Serial.print( "F");
      Serial.print(" ");
    }
  }
  // Temp 1 ----------------------------------------------------
  if (true)
  { //                 R1        Bits
    long resistance = (108830 * (1024 / ADCvalue1 - 1));
    
    // Calk Kelvin
    float result = log (resistance);
    float A = 0.000541774592748;
    float B = 0.000238870735000;
    float C = 0.000000048293022;
    result = 1.0 / (A + (B * result) + (C * result * result * result));
    
    Serial.print("T1-Bed "); 
    if (false)
    {
      Serial.print(result);
      Serial.print( (char)0xB0);
      Serial.print("K ");
    } 
    // Calc Celsius   
    result = result - 273.15; // Convert to Celsius
    if (true)
    {
      Serial.print(result);
      //Serial.print( (char)0xB0);
      //Serial.print("C");
      Serial.print(" ");
    }   
    // Calc Fahrenheit   
    result = ((result * 9) / 5) +32; // Convert to Fahrenheit
    if (true)
    {    
      Serial.print(result);
      //Serial.print( (char)0xB0);
      //Serial.print( "F");
      Serial.print(" ");
    }
  }

  // ====================================
  // Cleanup/loop again
  // ====================================
  Serial.println("");
  delay(5000);
}
//end program

// https://www.arduino.cc/en/Reference/HomePage
