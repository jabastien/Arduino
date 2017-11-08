const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)


//#define INT1V1
#define EXT3V3
//#define EXT5V0

void setup() {

#if defined( INT1V1 )
  analogReference(INTERNAL);
#endif

#if defined( EXT3V3 ) || defined( EXT5V0 )
  analogReference(EXTERNAL);
#endif

  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);

  // print the results to the Serial Monitor:
  Serial.print  ("sensor = ");
  Serial.print  (sensorValue);
  Serial.print  ("\t map output = ");
  Serial.print  (outputValue);

#if defined( INT1V1 ) //  analogReference(INTERNAL);
  Serial.print  ("\t INT 1.1 volt = ");
  Serial.print  (sensorValue * (1.1000/1023.0));  
#endif

#if defined( EXT3V3 ) //  analogReference(EXTERNAL);
  Serial.print  ("\t INT 3.3 volt = ");
  Serial.print  (sensorValue * (3.2707/1023.0));
#endif

#if defined( EXT5V0 ) //  analogReference(EXTERNAL);
  Serial.print  ("\t INT 5.0 volt = ");
  Serial.print  (sensorValue * (4.6090/1023.0));
#endif

if (sensorValue == 1023){
    Serial.print  (" -- Over voltage???");
}

Serial.println("");
  
  // wait 50 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(100);
}
