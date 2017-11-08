const int  buttonPin = A0;   
int buttonstateCounter = 0;
int lastanalogvalue = 0;
int analogvalue = 0;
int difference;
long previousMillis = 0; 
long interval = 250;

void setup() {
 // initialize the button pin as a input:
 pinMode(buttonPin, INPUT);
 Serial.begin(115200);
}


void loop() {     

 analogvalue = analogRead(buttonPin); // read the pushbutton input pin
 difference = abs(lastanalogvalue - analogvalue);
 if (difference > 5 ) { // button has either been pressed or released
 
//     buttonstateCounter++;
//     if (buttonstateCounter % 2 != 0)// button pressed, take value
//    {
      unsigned long currentMillis = millis();
      if(currentMillis - previousMillis > interval) 
      {
        previousMillis = currentMillis;
        
        if (analogvalue > 102){          
          Serial.print   (analogRead(buttonPin));
          Serial.print   ("   ");
          Serial.println (analogvalue); 
        } else {
          
        }
      }
 //   }         
 lastanalogvalue = analogvalue;  
 }
}
