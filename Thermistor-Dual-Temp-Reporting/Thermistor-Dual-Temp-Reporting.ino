/*
  3D printer chamber cooler based on NTC 3950 100K Thermistor
  David Quesenberry
 */

/*  C =   F 
 * 20 =  68
 * 30 =  86
 * 40 = 104
 * 50 = 122
 * 60 = 140
 * 70 = 158
 * 80 = 176
 */

 /*
  * range Chamber
  * PLA 20-70
  * ABS 30-80
  * 
  */

 /*
  * range Bed
  * PLA  40-60
  * ABS 100-110
  * 
  */

#include <Wire.h>                  // Inclusion of booklets into the program 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27,16,2);      // Initialization of the book (address, characters, rows)

//                   1234567890123456 
String deviceInfo = "Chamber Temp ctl";
String versionNum = "1.12v";

int ThermistorPin0 = 0;
int ThermistorPin1 = 1;

int V2, V3;
float setPLA, setABS;
int temp;
int fanOn=0;

float tempChamber, tempBed, tempTest;


const int ledPin2 = 2; // the digital pin number of the LED

const byte ledPin13 = 13;
const byte interruptPin3 = 3;
volatile byte ledState13 = HIGH;

int eeAddressPLA = 0;
int eeAddressABS = 4;

float bedPLA = 0.0f; // 4 bytes
float bedABS = 0.0f; // 4 bytes

typedef enum BedState{
  NA = 0,
  PLA = 1,
  ABS = 2
} ;
BedState bedState = NA;

typedef enum ButtonState{
  CHANGED = 0, // Button pressed
  COMPLETE = 1 // Button no change
} ;
ButtonState buttonState = COMPLETE;

typedef enum ButtonTask{
    ShowTemp = 0,
    ShowPLATempSet = 1,
    ShowABSTempSet = 2,
    ShowVolts = 3,
    EndList
} ;
ButtonTask buttonTask = ShowVolts;

int btnHoldCnt = 0;

boolean blinkMe = false;
int blinkRate = 0;

void setup() 
  {
  analogReference(EXTERNAL); // Use the External 3.3V reference for our Aref.
  // ledPin is the FAN & LED
  pinMode(ledPin2, OUTPUT);

  // Turn fan on
  digitalWrite(ledPin2, HIGH);

  Serial.begin(9600);
  
  Serial.print("Device = ");   
  Serial.println(deviceInfo);   

  Serial.print("Version = ");   
  Serial.println(versionNum);   

  Serial.print(" EEPROM.length = ");   
  Serial.println(  EEPROM.length());   

  // float data from the EEPROM at position 'eeAddress'
  EEPROM.get(eeAddressPLA, bedPLA);
  EEPROM.get(eeAddressABS, bedABS);

  Serial.print(" bedPLA: ");
  Serial.println(bedPLA);
  Serial.print(" bedABS: ");
  Serial.println(bedABS); 
  
  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(deviceInfo);
  lcd.setCursor(0, 1);
  lcd.print(versionNum);

  delay(2000);  
  lcd.clear();

  // button
  pinMode(ledPin2, OUTPUT);
  // pinMode(buttonPin,INPUT);
  pinMode(interruptPin3, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(interruptPin3), doInterrupt, RISING  );
  attachInterrupt(digitalPinToInterrupt(interruptPin3), doInterrupt, FALLING);

  doButtonPushed();
  buttonTask = ShowVolts;
  doShow(); 
  
  delay(1000);  

  buttonTask = ShowTemp;
  lcd.clear();
  }

  void doInterrupt()
  {// https://www.arduino.cc/en/Reference/AttachInterrupt
    
    digitalWrite(ledPin13, ledState13);
    ledState13 = !ledState13;

    buttonState=CHANGED;
    btnHoldCnt=0;
  }
  
  float farenheit(float celcius)
  {
    return (celcius * 9.0)/ 5.0 + 32.0; 
  }


//https://www.ametherm.com/thermistor/ntc-thermistor-beta
//https://www.ametherm.com/thermistor/ntc-thermistor-beta
  float readCelcius(int pin_therm, int res_fixed, int res_therm)
  {//https://arduino.stackexchange.com/questions/36299/what-difference-makes-resistance-of-thermistors
    float reading;         // hold thermistor resistance
    float stein;           // hold calculated temp

    int therm_nom = 25;    // nominal thermistor temp
    
    //int therm_b = 4184;  // thermistor B coefficient
    //int therm_b = 4178;  // thermistor B coefficient
    int therm_b = 3950;    // thermistor B coefficient
    reading = analogRead(pin_therm);
    reading = (1023 / (1023-reading)) - 1;
    reading = res_fixed / reading;
    
    // apply the S-H equation
    stein = reading / res_therm;    // (R/Ro)
    stein = log(stein);             // ln(R/Ro)
    stein /= therm_b;               // 1/B * ln(R/Ro)
    //stein += 1.0 / (25.0 + 273.15); // + (1/To)
    stein += 1.0 / (therm_nom + 273.15); // + (1/To)
    stein = 1.0 / stein;            // Invert
    stein -= 273.15;                // convert to C
    
    if (false)
    {
      Serial.print("steinhart ");
      Serial.print(stein);
      Serial.print(" oC  ");
      Serial.print(farenheit(stein));
      Serial.println(" oF  <--");
      
      lcd.setCursor(0, 0);
      lcd.print(stein);
      lcd.setCursor(0, 1);
      lcd.print(farenheit(stein));
    }
      return stein;
  }
  ////
  ////
  ////http://reprap.org/wiki/Thermistor
  ////
  ////
  void loop() 
  {
    //https://www.ametherm.com/blog/thermistors/thermistor-beta-calculations?gclid=CjwKEAjwqcHLBRCq5uHTpLL12FISJAD6PgDI7PUelqebb3Mq68kOafGomkBC-xiba4nzZgRa9Jo8QRoCrgzw_wcB
    //https://www.ametherm.com/thermistor/ntc-thermistor-beta
    //http://www.ametherm.com/thermistor/ntc-thermistor-calculating-the-temperature-coefficient-of-a-thermistor

    //https://www.thermistor.com/calculators?r=sheccr
    //https://www.google.com/search?q=thermistor+calculator&rlz=1C1CHZL_enUS729US729&oq=thermister+cal&aqs=chrome.1.69i57j0l5.5316j0j8&sourceid=chrome&ie=UTF-8

    //Temp 0 - Chamber
    tempChamber = readCelcius(ThermistorPin0, 99960, 100000);
  
    // Temp 1 - Bed
    tempBed = readCelcius(ThermistorPin1, 100220, 101000);//101700);

    /*                        using
     * < 40          == NA     < 40
     * >= 40 & < 60  == PLA    < 80
     * >= 100        == ABS    >=80
     */
    if (tempBed < 40)
    {
      // bed not on
      tempTest=100; // Don't ever turn on, unless we have a problem
      bedState = NA;
      Serial.print("Bed Off ");   
    }
        else if (tempBed < 80)
        {
          // bed at PLA level
          tempTest = bedPLA;
          bedState = PLA;
          Serial.print("Bed PLA ");   
        }
        else
        {
          // bed at ABS level
          tempTest = bedABS;
          bedState = ABS;
          Serial.print("Bed ABS ");   
        }
        
    Serial.print(" tempTest ");
    Serial.print(tempTest);
    
    if (bedState == NA)
    {
      digitalWrite(ledPin2, 0);   // turn the LED/Fan off (Low is the Chamber hotter than bed)
      Serial.print(" fanOn=2 Fan N/A ");   
      fanOn=2;   
    }
    else
    {
      if ((tempChamber) <= tempTest) // Test for Chamber hot enough
        {
        digitalWrite(ledPin2, 0);   // turn the LED/Fan off (Low is the Chamber hotter than bed)
        Serial.print(" fanOn=0 Fan off "); 
        fanOn=0; 
        }
      else
        {
        digitalWrite(ledPin2, 1);   // turn the LED/Fan on (High is the Bed hotter than Chamber)
        Serial.print(" fanOn=1 Fan on "); 
        fanOn=1; 
        }
    }
    
    // =======================================

    doShow();
  
    // =======================================
    // Ready for next round --> new line to console
    Serial.println(" "); 
    
    // =======================================
    // Wait for next loop --> delay(1000);  
//    for (int loop = 0; loop<100;loop++)
    for (int loop = 0; loop<25;loop++)
    {
       // Button pushed?
        if (buttonState == CHANGED)
        {
          doButtonPushed();
          doShow();
        }

     // Voltage issue?
        if (blinkMe)
        {
          // blink
          blinkRate++;
          if (blinkRate>100)
          {
            blinkRate=0;      
          }
          
           if (blinkRate<=50)
             lcd.display();
            else      
             lcd.noDisplay();
        }
       delay(10);  
    }
  }

  void doButtonPushed()
  {
    int btn = digitalRead(interruptPin3);
    btn = !btn;

    if (btn) // button still held
      {
      btnHoldCnt++;
      if (btnHoldCnt > 20)
        {
        if (buttonTask == ShowPLATempSet)
            {
            EEPROM.put(eeAddressPLA, setPLA);
            bedPLA = setPLA;
            Serial.print("-setPLA-");
            Serial.print(bedPLA);
            }
        if (buttonTask == ShowABSTempSet)            
            {
            EEPROM.put(eeAddressABS, setABS);
            bedABS = setABS;
            Serial.print("-setABS-");
            Serial.print(bedABS);
            }    
         buttonState=COMPLETE;
         return;    
        }
      else
        return;
     }
    
    buttonState=COMPLETE;

    blinkMe = false;
    lcd.clear();
    lcd.display();

    int ndx = (int) buttonTask;
    ++ndx;
    buttonTask = ndx;
    
    if (buttonTask >= EndList)
    {
      buttonTask=ShowTemp;
    }
  }

  void doShow()
  {
    // 0 = ShowTemp
    // 1 = ShowTempSet
    // 2 = ShowVolts
        
      if (buttonTask==ShowTemp)
        doShowTemp();
      else if (buttonTask==ShowPLATempSet)
          doShowPLATempSet();
      else if (buttonTask==ShowABSTempSet)
          doShowABSTempSet();
        else
          doShowVolts();    
  }
  
  void doShowTemp()
  {    
    // Main Menu
    lcd.setCursor(0, 0);
    if (bedState == PLA)
      lcd.print("   Bed Chamb PLA");
    else if (bedState == ABS)
      lcd.print("   Bed Chamb ABS");
    else
      lcd.print("   Bed Chamb Fan");

    //tempBed
    lcd.setCursor(1, 1);
    if (tempBed<100.0)
      lcd.print(" ");      
    lcd.print(tempBed,1); // vypis retazca textu
    Serial.print(" -- Bed: "); 
    Serial.print(tempBed);
    Serial.print(" C ");  
        
    //tempChamber
    lcd.setCursor(7, 1);
    if (tempChamber<100.0)
      lcd.print(" ");      
    lcd.print(tempChamber,1);// one decimal
    Serial.print(" -- Chamber: "); 
    Serial.print(tempChamber);
    Serial.print(" C");   
  
    lcd.setCursor(13,1);
    if (fanOn == 1)
      lcd.print("On ");
     else if (fanOn == 0)
      lcd.print("Off");
     else
      lcd.print("N/A");
  }

  float v3Math = 3.3f / 1023.0f;
  float tempRange = 40/1023.0f;
  void doShowPLATempSet()
  {
    // PLA Menu
    lcd.setCursor(0, 0);
    lcd.print(" Last  New   PLA");

    temp = analogRead(6);
    setPLA = (float)20+(temp*tempRange);

    lcd.setCursor(1, 1);
    lcd.print(bedPLA,1); // Writing a text string
    lcd.setCursor(6, 1);
    lcd.print(setPLA,1); // Writing a text string
    lcd.setCursor(11, 1);
    lcd.print("20-60"); // Writing a text string
  }

  void doShowABSTempSet()
  {
    // ABS Menu
    lcd.setCursor(0, 0);
    lcd.print(" Last  New   ABS");
  
    temp = analogRead(7);
    setABS = (float)30+(temp*tempRange);
  
    lcd.setCursor(1, 1);
    lcd.print(bedABS,1); // Writing a text string
    lcd.setCursor(6, 1);
    lcd.print(setABS,1); // Writing a text string
    lcd.setCursor(11, 1);
    lcd.print("30-70"); // Writing a text string
  }
  
  float calcVolts(int x,float R1,float R2)
  {
  float Eo = (float)x * v3Math;
  return (float) (Eo/R2)*(R1+R2);
  }
 
  void doShowVolts()
 {
  // Menu
  lcd.setCursor(0, 0);
  lcd.print("Volts Input Reg.");

  // input volts
  V2 = analogRead(2);
  Serial.print(" V2 ");
  Serial.print(V2);

  lcd.setCursor(6, 1);
  float VoltInput = calcVolts(V2,47000.0f,12000.0f);
  lcd.print(VoltInput,1); // Writing a text string

  // 5V supply
  V3 = analogRead(3);
  Serial.print(" V3 ");
  Serial.print(V3);  

  lcd.setCursor(12, 1);
  float Volt5 = calcVolts(V3,47000.0f,12000.0f);
  lcd.print(Volt5,2); // Writing a text string

  lcd.setCursor(0, 1);
  if (Volt5 < 5.0f)
  {
    lcd.print("BAD!");
    blinkMe=true;
  }
  else
  {
    lcd.print("Good");
    blinkMe=false;
  }
}

