/*
Description

Configures the reference voltage used for analog input (i.e. the value used as the top of the input range). The options are:

DEFAULT: the default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts (on 3.3V Arduino boards)
INTERNAL: an built-in reference, equal to 1.1 volts on the ATmega168 or ATmega328 and 2.56 volts on the ATmega8 (not available on the Arduino Mega)
INTERNAL1V1: a built-in 1.1V reference (Arduino Mega only)
INTERNAL2V56: a built-in 2.56V reference (Arduino Mega only)
EXTERNAL: the voltage applied to the AREF pin (0 to 5V only) is used as the reference.
Syntax

analogReference(type)
 * 
 */

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor


double vStep = 3.2098 / 1023.0;


int R1 =  9956; // 10000; // The source resistor
int R2 =  2986; //  3000; // The grounded resistor
double vRead = 0.0; // The divided voltage
double vActual = 0.0; // Actual voltage 

double iVolt = 0.0; // div 2 read
double iAmp = 0.0; // Amps

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogReference(EXTERNAL);
}


void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.print  (sensorValue);
  
  //
  Serial.print  (" Read: ");
  vRead = sensorValue * vStep;
  Serial.print  (vRead,3);
  
  Serial.print  (" Actual: ");
//vActual = (1.05  / 3000) * (3000 + 10000) = 4.55
  vActual = (vRead / R2  ) * (   R2 + R1);
  Serial.print  (vActual,3);

  //
  Serial.print  (" Amp 0.49: ");
  iVolt = vActual - (vActual - 0.01);  
// difference of shunt (pre/post) value  / shunt
  //iVolt /= 0.49;
  Serial.print  (iVolt / 0.49,4);
  Serial.print  (" Amp 1.0: ");
  Serial.print  (iVolt / 1.0,4);
  Serial.print  (" Amp 10.0: ");
  Serial.println(iVolt / 10.0,4);



//=========================================================
//I = Ei / (R1+R2))
//I = 4.550 V / (10Ω + 3.000 KΩ)
//I = ( 4.550 * ( 10^0 )) / ( ( 10 * ( 10^3 )) + ( 3.000 * ( 10^3 )) )
//I = 4.55 / 13000
//I = ( 350.000 * ( 10^-6 )) 
//I = 350.000 uA
//=========================================================

  // delay the program for 250 milliseconds
  delay(250);
}
