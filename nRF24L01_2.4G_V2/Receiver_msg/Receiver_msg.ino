/*

  David Quesenberry
 */

// Stuff
#include <Wire.h>                  // Inclusion of booklets into the program 
#include <EEPROM.h>

// RF
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CNS, CE
const byte address[6] = "00001";

// LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);      // Initialization of the book (address, characters, rows)

//                   1234567890123456 
String deviceInfo = "2.4G Receiver";
String versionNum = "v1.00";

int number = 0;

void setup() 
  {
    // Analog Reference is External
    analogReference(EXTERNAL); // Use the External 3.3V reference for our Aref.
  
    // Serial Communication
    Serial.begin(9600);
    
    Serial.print("Device = ");   
    Serial.println(deviceInfo);   
  
    Serial.print("Version = ");   
    Serial.println(versionNum);   
  
    // EPROM setup
    Serial.print(" EEPROM.length = ");   
    Serial.println(  EEPROM.length());   
  
    // float data from the EEPROM at position 'eeAddress'
  //  EEPROM.get(eeAddressPLA, bedPLA);
  //  EEPROM.get(eeAddressABS, bedABS);
  
    // LCD setup
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(deviceInfo);
    lcd.setCursor(0, 1);
    lcd.print(versionNum);
  
  
    // RF RX setup
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
  
    delay(1000);  
    lcd.clear();
  }

int loopin = 0;
  void loop() 
  {

      if (++loopin >= 10)
      {
        // Send debug info
        Serial.print(" RX: ");
        Serial.print(number++);  
        loopin=0;
        }
    
  
      // =======================================
      // Ready for next round --> new line to console
      if (loopin == 0)
      {
        Serial.println(" "); 
      }

        
    // LCD Display
    lcd.setCursor(0, 0);
    lcd.print (" RX: ");
    lcd.print(number);


  // RF RX read
    if (radio.available()) 
    {
      char text[32] = "";
      radio.read(&text, sizeof(text));
      
      Serial.print("RX: ");
      Serial.print(sizeof(text));
      Serial.println(text);

      lcd.setCursor(0, 1);
      lcd.print (" --> ");
      lcd.print(text); 
    }

       
    // Wait a sec
    delay(250); 
    lcd.clear();
  }


/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CNS, CE
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}

*/
