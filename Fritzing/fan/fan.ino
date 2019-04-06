#include <LiquidCrystal.h>

// Fan sens (tach) wire connected to digital_8 port
int fanSens = 8; 

// Fan PWM wire connected to digital_9 port
int fanPWM = 9;

// Middle pin of LM35 connected to analog_A1 port
int tempPin = 1;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void showRPM() {
  unsigned long pulseDuration = pulseIn(fanSens, LOW);
  double frequency = 1000000/pulseDuration;
  lcd.setCursor(5, 1);  // fifth column on the second row
  lcd.print(frequency/2*60);
}

void setup()
{
  pinMode(fanSens, INPUT);
  digitalWrite(fanSens,HIGH);
  lcd.begin(16,2);
  lcd.setCursor(0, 0); // cursor at top left
  lcd.print( "TMP:" );
  lcd.setCursor(0, 1);  // cursor at bottom left
  lcd.print("RPM:");
}

void loop()
{
  float val = analogRead(tempPin); 
  float mv = (val/1024.0)*5000;
  float cel = mv/10; // this is the celcuis

  lcd.setCursor(5, 0); // fifth column on the first row
  lcd.print( cel );
  
  if (cel <= 27.0) 
    analogWrite(fanPWM, 70);   // write value 70 to the fan
  else if (27.0 < cel)
    analogWrite(fanPWM, 220); // write value 220 to the fan

  showRPM();
  delay(500);
}
