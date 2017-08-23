#include <CD4052.h>

int addr_A = 4;
int addr_B = 5;

int adc_X = A6;
int adc_Y = A7;

//CD4052 cd4052 = CD4052();
CD4052 cd4052 = CD4052(addr_A, addr_B, adc_X, adc_Y);

/*
 * 
 * 
 */
void setup() {
  // Setup communication
  Serial.begin(115200);
  Serial.println("Hello!, testing CD4052");
}

/*
 * 
 * 
 */
void loop() {

  cd4052.setChannel(0);
  Serial.print(cd4052.analogReadX());
  Serial.print(" ");
  Serial.print(cd4052.analogReadY());
  Serial.print(" ");

  cd4052.setChannel(1);
  Serial.print(cd4052.analogReadX());
  Serial.print(" ");
  Serial.print(cd4052.analogReadY());
  Serial.print(" ");

  cd4052.setChannel(2);
  Serial.print(cd4052.analogReadX());
  Serial.print(" ");
  Serial.print(cd4052.analogReadY());
  Serial.print(" ");

  cd4052.setChannel(3);
  Serial.print(cd4052.analogReadX());
  Serial.print(" ");
  Serial.print(cd4052.analogReadY());
  Serial.print(" ------- ");
      
  Serial.println();
}