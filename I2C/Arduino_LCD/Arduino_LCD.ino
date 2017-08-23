/*
  Arduino LCD shield
  pouziva kniznicu LiquidCrystal
  vypis casu a stlaceneho tlacidla
 */

#include <LiquidCrystal.h>           // zahrnutie kniznice do programu

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // inicializacia kniznice pre Arduino LCD shield

int analog_hodnota;                  // tlacidla su pripojene na analogovy pin A0

void setup() {

  lcd.begin(16, 2);                  // nastavenie poctu znakov a poctu riadkov
  
  lcd.setCursor(0,0);                // presun kurzoru na zaciatok horneho riadka
  lcd.print("LCD Shield");           // vypis textoveho retazca na LCD
  lcd.setCursor(0,1);                // presun kurzoru na zaciatok dolneho riadka
  lcd.print("Tlacidlo");
}

void loop() {

  lcd.setCursor(12,0);               // presun kurzoru na 12-ty znak horneho riadka
  lcd.print(millis()/1000);          // vypis casu na LCD

  analog_hodnota = analogRead (A0);  // nacitanie hodnoty tlacidla na pine A0

  lcd.setCursor(10,1);               // presun kurzoru na 10-ty znak spodneho riadka
  
  if (analog_hodnota < 60) {         // test stlaceneho tlacidla a jeho vypis na LCD
    lcd.print("Right ");
  }
  else if (analog_hodnota < 200) {
    lcd.print("Up    ");
  }
  else if (analog_hodnota < 400) {
    lcd.print("Down  ");
  }
  else if (analog_hodnota < 600) {
    lcd.print("Left  ");
  }
  else if (analog_hodnota < 800) {
    lcd.print("Select");
  }
  else lcd.print ("      ");         // nic nebolo stlacene
}
