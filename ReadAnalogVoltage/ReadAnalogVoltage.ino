
/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

int x = 0;
float arrayA0[] = {99, 0, 0, 0, 0, 0, 0, 0, 0, 99};
float avgA0 = 0;
float arrayA1[] = {99, 1, 2, 3, 4, 5, 6, 7, 8, 99};
float avgA1 = 0;

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  float sensor0Value = analogRead(A0);
  float sensor1Value = analogRead(A1);

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage0 = sensor0Value * (5.0 / 1023.0);
  float voltage1 = sensor1Value * (5.0 / 1023.0);
  // print out the value you read:


// A0 values
  Serial.print("Voltage A0: ");
  Serial.print(voltage0);
  arrayA0[x]=voltage0;
  avgA0=0;
  for (int lp=0;lp<10;lp++)
  {
    avgA0+=arrayA0[lp];
  }
  Serial.print(" avg A0: ");
  Serial.print(avgA0/10);

// A0 values
  Serial.print(" Voltage A1: ");
  Serial.print(voltage1);
  arrayA1[x]=voltage1;
  avgA1=0;
  for (int lp=0;lp<10;lp++)
  {
    avgA1 += arrayA1[lp];
  }
  Serial.print(" avg A1: ");
  Serial.print(avgA1/10.0);

  Serial.println("  <EOT>");

// ready for next round

if (x++>9)
  {
    x=0;
  }

  // Library Location : C:\Users\davidq\Documents\Arduino\libraries\
  // StackArray.zip
  // Found at: http://playground.arduino.cc/Code/StackArray
}
