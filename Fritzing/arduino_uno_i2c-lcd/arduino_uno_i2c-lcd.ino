#include <LiquidCrystal_I2C_AvrI2C.h>
LiquidCrystal_I2C_AvrI2C lcd(0x27, 16, 2);
void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop()
{
  lcd.clear();
  delay(1000);
  lcd.print("Hello, world!"); //İlk satıra yazalım
  lcd.setCursor(0, 1);
  lcd.print("mutlu aysu"); //İkinci satıra yazalım
  delay(1000);
}
