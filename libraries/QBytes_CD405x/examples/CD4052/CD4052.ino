#include <CD4052.h>

//CD4052 cd4052 = CD4052();
CD4052 cd4052 = CD4052(4, 5, A6, A7);

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
 * Print and int variable
 */
int printInt(int n, String format){
  char c[10];        // long enough to hold complete integer string
  char charBuf[20];
  format.toCharArray(charBuf,20);
  int m = sprintf(c, charBuf, n);    // build integer string using C integer formatters  (m is length, and not used in this code)
  Serial.print(c);   
  return m;
}

/*
 * 
 * 
 */
void loop() {
      
  // Increment looping
  for (int looping = 0; looping < 4; looping++){
    cd4052.setChannel(looping);
    printInt(looping,"<X%1d:");
    printInt(cd4052.analogReadX(),"%4d> ");
    printInt(looping,"<Y%1d:");
    printInt(cd4052.analogReadY(),"%4d> ");
    }
	
  Serial.println("");
}