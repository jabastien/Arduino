#include <SoftWire.h>
#include <AsyncDelay.h>

//SoftWire sw(SDA, SCL);
SoftWire sw(2, 3);

//=============================================

//#include <LiquidCrystal.h>

/*
  LCD i2c
  generator prvocisel (kazde 2 sekundy vypise dalsie v poradi)
 */

//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27,20,2);      // inicializacia kniznice (adresa, znaky, riadky)

void setup()
{  
  Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nSetup begin");


  sw.setTimeout_ms(40);
  sw.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Set how long we are willing to wait for a device to respond
  sw.setTimeout_ms(200);
  
  
      Serial.println(F("lcd.init"));
//  lcd.init();                          // inicializacia LCD
     Serial.println(F("lcd.backlight"));   
//  lcd.backlight();                     // zapnutie podsvietenia
    Serial.println(F("lcd.home"));
//  lcd.home();                          // nastavenie kurzora vlavo hore
    Serial.println(F("lcd done"));

  Serial.println("\nSetup end");
}

int i = 0;
int cislo = 0;
int prime = 0;
int n = 0;

  uint8_t address = 0x27;
  String errors="";
  uint8_t command = 10;
  uint8_t dataLow = 0;
  uint8_t dataHigh = 1;
  uint8_t pec = 0;
void loop()
{

  Serial.println("Loop begin");

//_displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
  // Send command
  errors += sw.startWait(address, SoftWire::writeMode);
  errors += sw.write(LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS);
  
  // Read results
  errors += sw.repeatedStart(address, SoftWire::readMode);
  errors += sw.readThenAck(dataLow);  // Read 1 byte and then send ack
  errors += sw.readThenAck(dataHigh); // Read 1 byte and then send ack
  errors += sw.readThenNack(pec);
  sw.stop();
  

  for (i=2; i<cislo; i++) {
    prime=1;                           // predpokladajme ze je prvocislo
    if (!(cislo % i)) {                // zvysok po deleni je nula, nie je to prvocislo
        prime=0;
  break;                         // nech vyskoci z cyklu a zbytocne uz nerata
    }
  }
  
  if (prime) {                         // vypis prvocisla
    //lcd.home();
    //lcd.print(n);
    //lcd.print(". prvocislo");
    //lcd.setCursor(0, 1);
    //lcd.print(cislo);
     
    delay(250);                       // pre spomalenie vypisu na LCD
    n++;
  }

  cislo++;

  Serial.println("Loop end");  
}
