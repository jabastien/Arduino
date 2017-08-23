//ref:  http://wormfood.net/avrbaudcalc.php


//Setup routine
void setup(){
#if F_CPU >= 20000000L
  #define BAUD_RATE   19200 // Highest rate Avrdude win32 will support
    #elif F_CPU >= 16000000L
      #define BAUD_RATE   76800 // 74880 // Highest rate Avrdude win32 will support
        #elif F_CPU >= 8000000L
          #define BAUD_RATE   38400 // Highest rate Avrdude win32 will support
            #elif   F_CPU >= 1000000L
              #define BAUD_RATE   9600L   // 19200 also supported, but with significant error
                #elif   F_CPU >= 128000L
                  #define BAUD_RATE   4800L   // Good for 128kHz internal RC
                #else
              #define BAUD_RATE 1200L     // Good even at 32768Hz
          #endif

Serial.begin(BAUD_RATE);
Serial.println(F_CPU);
Serial.println(BAUD_RATE);
}

void loop(){}
