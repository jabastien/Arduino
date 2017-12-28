/*
  Utils.h - Utils library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include core Wiring API
//#if defined(ARDUINO) && ARDUINO >= 100
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <stdio.h>
#include <stdarg.h>

// include this library's description file
#include "Utils.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"


extern unsigned int __data_start;
extern unsigned int __data_end;
extern unsigned int __bss_start;
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

/*
 * The free list structure as maintained by the 
 * avr-libc memory allocation routines.
 */
struct __freelist {
  size_t sz;
  struct __freelist *nx;
};

/* The head of the free list structure */
extern struct __freelist *__flp;

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Utils::Utils(){
  // initialize this instance's variables
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries


// https://arduino.stackexchange.com/questions/13389/number-of-elements-in-an-array-char
int Utils::arraySize(PGM_P data) { 
  PGM_P p = data; 
  while (*p++); 
  return p-data-1; 
}

int Utils::countCharacters(PGM_P str, char character){
    PGM_P p = str;
    int count = 0;
    
    do {
      if (*p == character){
        count++;
        }
       } while (*(p++));

    return count;
}

int Utils::freeRam(){
 int free_memory;

 if((int)__brkval == 0){
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
   } else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
    free_memory += freeListSize();
 }
 return free_memory;
}

/* Calculates the size of the free list */
int Utils::freeListSize() {
  struct __freelist* current;
  int total = 0;
  for (current = __flp; current; current = current->nx) {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (int) current->sz;
  }
  return total;
}

void Utils::reverse(char stg [] ){

  byte stgSize = arraySize(stg) - 1; // Array is zero (0) relative
  byte halfSize = (stgSize / 2) + 1; // small performance boost (1/2 loop)
  
  for (byte b = 0; b < halfSize; b++){
    char tmp = stg[b];
    stg[b] = stg[stgSize - b];
    stg[stgSize - b] = tmp;
    }
}

/*
void Utils::ErrorPrint(String errorNum, uint8_t num, ...) {

   Serial.print("errorNum: ");
   Serial.print(errorNum);
// if (num <=0) return 0;   
 if (num <=0) return;   
 int valu;
 int total=0;
  
  //Declare a va_list macro and initialize it with va_start
  va_list argList;
  va_start(argList, num);
  
   for(; num; num--) {
     valu = va_arg(argList, int);
     Serial.print("valu: ");
     Serial.print(valu, DEC);
      total += valu;
     Serial.print("  total: ");
     Serial.println(total);
  }  
  va_end(argList);

  Serial.println(PGMSTR(dashes));
}

float Utils::Print( const char* Format, ... ){
      Serial.println(Format);
      
      va_list Arguments;
      va_start(Arguments, Format);
      
      double FArg;
      int IArg;
      char c ;
      char* s ;
      
      for(int i = 0; Format[i] != '\0'; ++i ){
        switch(Format[i]){
          case 'f':// Float/Double
                  FArg=va_arg(Arguments, double);
                  Serial.print("f: ");
                  Serial.print(FArg);
            break;

            case 'i': // Integer
                  IArg=va_arg(Arguments, int);
                  Serial.print("i:");
                  Serial.print(IArg);
                  break;

            case 's':// String
              
                s = va_arg( Arguments, char * );
                Serial.print(s);
//        //        sprintf(OutMsg,format,s);
//        //        strcpy(format,OutMsg);
//        //        j = strlen(format);
//        //        strcat(format," ");
                break;
//              
              
            case 'c':// character
             
                c = (char) va_arg( Arguments, int );
                Serial.print(c);                
//        //        sprintf(OutMsg,format,c);
//        //        strcpy(format,OutMsg);
//        //        j = strlen(format);
//        //        strcat(format," ");
                break;
                   
            default:
//                Serial.print("?: ");
//                Serial.print(Format[i]);
                break;
              }
      Serial.print("\t");              
      }
      va_end(Arguments);

Serial.println();      
}

extern char *itoa(int, char *, int);

void Utils::myprintf(const char *fmt, ...){
  Serial.println("-myprintf-");
const char *p;
va_list argp;
int i;
char *s;
char fmtbuf[256];

va_start(argp, fmt);

for(p = fmt; *p != '\0'; p++)  {
//  if(*p != '%')
//    {
////    putchar(*p);
//      Serial.print  (*p);
//    continue;
//    }

  switch(*++p)
    {
    case 'c':
      i = va_arg(argp, int);
//      putchar(i);
      Serial.print  (i);
      break;

    case 'd':
      i = va_arg(argp, int);
      s = itoa(i, fmtbuf, 10);
//      fputs(s, stdout);
      Serial.print  (s);
Serial.print(fmtbuf);      
      break;

    case 'i':
      i = va_arg(argp, int);
      s = itoa(i, fmtbuf, 10);
//      fputs(s, stdout);
      Serial.print  (s);
Serial.print(fmtbuf);      
      break;

    case 's':
      s = va_arg(argp, char *);
//      fputs(s, stdout);
      Serial.print  (s);
      break;

    case 'x':
      i = va_arg(argp, int);
      s = itoa(i, fmtbuf, 16);
//      fputs(s, stdout);
      Serial.print  (s);
      break;

    case '%':
//      putchar('%');
      Serial.print  ('%');
      break;
      
    default:
    Serial.print (*p);
    }
  }

va_end(argp);

Serial.println();
}
*/


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

