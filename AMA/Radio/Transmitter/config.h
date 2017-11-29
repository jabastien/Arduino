#ifndef config_h
#define config_h

/*************************************************************************************************/
/****           CONFIGURABLE PARAMETERS                                                       ****/
/*************************************************************************************************/

/* this file consists of several sections to create a working combination you must at least make your choices in section 1.

 */

/* Notes:
 * 1. parameters marked with (*)  in the comment are stored in eeprom and can be changed via serial monitor or LCD.
 * 2. parameters marked with (**) in the comment are stored in eeprom and can be changed via the GUI
 */


/*************************************************************************************************/
/*****************                                                                 ***************/
/****************  SECTION  1 - BASIC SETUP                                                *******/
/*****************                                                                 ***************/
/*************************************************************************************************/

  /**************************    Model types    ****************************/



  /********************************************************************/
  /****           battery voltage monitoring                       ****/
  /********************************************************************/  
    //#define VBAT              // uncomment this line to activate the vbat code
    #define VBATSCALE       131 // (*) (**) change this value if readed Battery voltage is different than real voltage
    #define VBATNOMINAL     126 //          12.6V full battery nominal voltage - only used for lcd.telemetry
    #define VBATLEVEL_WARN1 107 // (*) (**) 10.7V
    #define VBATLEVEL_WARN2  99 // (*) (**) 9.9V
    #define VBATLEVEL_CRIT   93 // (*) (**) 9.3V - critical condition: if vbat ever goes below this value, permanent alarm is triggered
    #define NO_VBAT          16 // Avoid beeping without any battery
    #define VBAT_OFFSET       0 // offset in 0.1Volts, gets added to voltage value  - useful for zener diodes





/*************************************************************************************************/
/****           END OF CONFIGURABLE PARAMETERS                                                ****/
/*************************************************************************************************/

#endif /* config_h */
