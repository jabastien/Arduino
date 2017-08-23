/*

  David Quesenberry
  http://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
  
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
LiquidCrystal_I2C lcd(0x27,16,4);      // Initialization of the book (address, characters, rows)

//                   1234567890123456 
String deviceInfo = "2.4G Transmitter";
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
  
  
    // RF TX Setup
     radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
  
    // Wait a sec.
    delay(1000);  
    lcd.clear();
  }


  void loop() 
  {
    // Send debug info    
    Serial.print(" TX: ");
    Serial.print(number++);  

    // LCD Display
    lcd.setCursor(0, 0);
    lcd.print (" TX: ");
    lcd.print(number);

    // =======================================
    // Ready for next round --> new line to console
    Serial.println(" "); 

    // RF TX Send
    const char text[] = "Hello World";
    radio.write(&text, sizeof(text));
    delay(1000);  
  }


/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
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
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}
*/
