void setup() {
  // initialize serial ports
  Serial.begin(9600);    // USB serial port 0
//  Serial1.begin(9600);   // serial port 1
//  Serial2.begin(9600);   // serial port 2
//  Serial3.begin(9600);   // serial port 3

  Serial.println("Serial Ports 0-3");
}

byte rx_byte = 0;        // stores received byte

void loop() {
  // check for data byte on USB serial port
  if (Serial.available()) {
    // get byte from USB serial port
    rx_byte = Serial.read();
    // send byte to serial port 0?
    Serial.write(rx_byte); // echo it back
  }

  





}
