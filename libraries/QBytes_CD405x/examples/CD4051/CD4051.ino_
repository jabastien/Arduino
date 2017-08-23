#include <CD405x.h>

CD405x cd4051 = CD405x(4,5,6);

/*
 * 
 * 
 */
void setup() {
  // put your setup code here, to run once:

  // Setup communication
  Serial.begin(38400);
  Serial.println("Hello!, testing CD4051 & CD4052");
}

int ADC0=0;
int ADC1=0;
int ADC2=0;
int ADC3=0;

int ADC6_0x = 0;
int ADC7_0y = 0;
int ADC6_1x = 0;
int ADC7_1y = 0;
int ADC6_2x = 0;
int ADC7_2y = 0;
int ADC6_3x = 0;
int ADC7_3y = 0;

int pinSwitchs = 0b00000000;

int looping = 9;

/*
 * 
 * 
 */
void loop() {
  // put your main code here, to run repeatedly:

  ADC0 = analogRead(A0);
  ADC1 = analogRead(A1);
  ADC2 = analogRead(A2);
  ADC3 = analogRead(A3);


switch (looping){
  case 0:
  case 4:
  { //             A  B  C
    cd4051.setPins(0, 0, looping >= 4); // modulus for Odd/Even (0 or 1)(low or high pin)

    ADC6_0x = cd4051.analogRead(A6);
    ADC7_0y = cd4051.analogRead(A7);

    break;   
  }

  case 1:
  case 5:
  { //             A  B  C
    cd4051.setPins(1, 0, looping >= 4); // modulus for Odd/Even (0 or 1)(low or high pin)

    ADC6_1x = cd4051.analogRead(A6);
    ADC7_1y = cd4051.analogRead(A7);         
     
    break;   
  }
  
  case 2:
  case 6:
  { //             A  B  C
    cd4051.setPins(0, 1, looping >= 4); // modulus for Odd/Even (0 or 1)(low or high pin)

    ADC6_2x = cd4051.analogRead(A6);
    ADC7_2y = cd4051.analogRead(A7);      
    
    break;   
  }
  case 3:
  case 7:
  { //             A  B  C
    cd4051.setPins( 1, 1, looping >= 4); // modulus for Odd/Even (0 or 1)(low or high pin)

    ADC6_3x = cd4051.analogRead(A6);
    ADC7_3y = cd4051.analogRead(A7);      
      
    break;   
  }
  default:
  {
    looping = 0;  
    Serial.println("    A0   A1   A2   A3 A60X A70Y A61X A71Y A62X A72Y A63X A73Y x76543210"); 
    Serial.println("  ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== 1========");     
  }
}

  // Get the switch values
  byte pinmask = ~(1<<looping); 
  byte readmask = (digitalRead(8)<<looping); 
//  byte switchmask = ~pinmask
//  byte mask = pinmask | pinSwitchs;
  pinSwitchs = (pinSwitchs & pinmask) | readmask;

//  // Print switches
  Serial.print(" ");
//  Serial.print(" Pin ");  
//  Serial.print(pinmask + 0x100, BIN);
//  Serial.print(" Mask ");  
//  Serial.print(readmask + 0x100, BIN);
//  Serial.print(" Switch ");  
  Serial.print(pinSwitchs + 0x100, BIN);
  
  
  // Increment looping
  looping++;
  if (looping >=8){
    looping = 0;  
    }
      
  Serial.println();
}