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


// https://arduino.stackexchange.com/questions/13389/number-of-elements-in-an-array-char
int Utils::arraySize(const char *data) { 
  const char *p = data; 
  while (*p++); 
  return p-data-1; 
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

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
