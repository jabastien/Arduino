/* My todo's

X - chreat this file

2 - finish start/init screens
    X - r1.1
    X - r2.1
    X - r3.1
    
    X - shunt
    X - reference

    X - switch
    X - trim
    X - menu
  
    X - turn display bytes (01100011) as a return from Display.cpp  

    X - analog range for sticks (min/ctr/max)
      - joystick range
        - THROTTLE
        - YAW
        - PITCH
        - ROLL

? - Make Switch, Trim, & Menu into a re-usable method like JoyStick
    It's already a Struct (MySwitchMap).
  
5 - create key/volt display in System (after joystick and before control check) 

6 = control check (execute to ensure switch and joystick are NOT flight enabled.)


? Try UNION for xxx.xx

  
    
3 - build menus
    = Trans
    = Model
    = System

   - bug in menu, able to arrow down one (1) when no items are available

4 - u8/s8 number display
  - can we use sprintf instead of role your own

7 - collect var volts and test voltage

8 - transmit data
  
  - packets.h or common.h for transmit structs.

9 - why tps < 144 (was +300)
    = 1 bit  (1) per loop
    = 2 bits (1) % mod   (0-7 collect, 8 calculate, 9 tx)
 
10 - receiver to PC

?X - need a 5.0 zener diode for VRef (using post diode input voltage 6-12v)
  http://www.electronics-tutorials.ws/diode/diode_7.html

? - See what can be made a generic methods
  
? - black box receiver to show data
 
? - black box channel scanner

11 - math & alarms
      = min FPS > 120
      = bat volts > 6.0v  

12 - alarms class?

13 - makes switches as LMH (requires 2 bits).

14 - setup dead zone

15 - reduce size of Display.cpp & Display.h













 */
