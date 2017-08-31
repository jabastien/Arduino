
#include <LiquidCrystal_I2C.h>

/*
  LCD i2c
  generator prvocisel (kazde 2 sekundy vypise dalsie v poradi)
 */


#include <Wire.h>                  // zahrnutie kniznic do programu
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20, 4);      // inicializacia kniznice (adresa, znaky, riadky)


unsigned long i,                       // premenna cyklu
              cislo=2,                 // cislo, ktore testujeme, ci je prvocislo
              n=1;                     // poradie vypisovaneho prvocisla

boolean prime=1;                       // 0-false, 1-true


void setup()
{
  lcd.init();                          // inicializacia LCD
  lcd.backlight();                     // zapnutie podsvietenia
  lcd.home();                          // nastavenie kurzora vlavo hore
}


void loop()
{
  
  for (i=2; i<cislo; i++) {
    prime=1;                           // predpokladajme ze je prvocislo
    if (!(cislo % i)) {                // zvysok po deleni je nula, nie je to prvocislo
        prime=0;
  break;                         // nech vyskoci z cyklu a zbytocne uz nerata
    }
  }
  
  if (prime) {                         // vypis prvocisla
    lcd.home();
    lcd.print(n);
    lcd.print(". prvocislo");
    lcd.setCursor(0, 1);
    lcd.print(cislo);
     
    delay(250);                       // pre spomalenie vypisu na LCD
    n++;
  }

  cislo++;
}
