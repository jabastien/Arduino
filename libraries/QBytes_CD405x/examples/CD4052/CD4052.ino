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
      
  // Increment looping
  for (int looping = 0; looping <= 4; looping ++){
	  cd4052.setChannel(looping);
	  Serial.print(cd4052.analogReadX());
	  Serial.print(" ");
	  Serial.print(cd4052.analogReadY());
	  Serial.print(" "); 
    }
	
  Serial.println("=====");
}