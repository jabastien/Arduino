/* My todo's

X - chreat this file

X - finish start/init screens
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
      x- joystick range
        x- THROTTLE
        x- YAW
        x- PITCH
        x- ROLL
    
2 = display all input voltages...prior to control check...
    x pre (this is the battery)
    x post
    x AMPS
    - key  (add to voltages screen)
    x aux 0
    x aux 1
    x aux 2
    x aux 3
            
X - control check (execute to ensure switch and joystick are NOT flight enabled.)

X - build menus
    x= Trans
    x= Model
    x= System

X - cleanup all 'err', turn into PRGMEM vars and document data.
      increased size from 18,800 to 20,056...(1,256)

X  - bug in menu, able to arrow down one (1) when no items are available (Bug no longer found)

X - Make Switch, Trim, & Menu into a re-usable method like JoyStick
    It's already a Struct (MySwitchesButtons).
  
5 - create key/volt display in System (after joystick and before control check) 

? Try UNION for xxx.xx

4 - u8/s8 number display
  - can we use sprintf instead of roll your own

7 - collect var volts and test voltage

8 - transmit data  
  - packets.h or common.h for transmit structs.

X - why tps < 144 (was +300)  (Update, FPS is now 575 on main menu.)
    = 1 bit  (1) per loop
    = 2 bits (1) % mod   (0-7 collect, 8 calculate, 9 tx)
 
10 - receiver to PC

?X - need a 5.0 zener diode for VRef (using post diode input voltage 6-12v)
  http://www.electronics-tutorials.ws/diode/diode_7.html

? - black box receiver to show data
 
? - black box channel scanner

11 - math & alarms
      = min FPS > 120
      = bat volts > 6.0v  

12 - alarms class?

13 - makes switches as LMH (requires 2 bits).

14 - setup dead zone

? - See what can be made a generic methods
  
15 - reduce size of Display.cpp & Display.h

16 - remove Serial.print to reduce size (may be able to ture into #define DEBUG_.....

? - Add to Transmitter
    - Channel Scan
    - Channel Set
    - Dead Zone
    - Expo
    - GPS
    - Mission Plan

? - Add to Model
    - Dip SW (reverse)
    - Mix
    - PDI (Drone Settings)
    - Type
      - Plane
      - Drone
      - Copter
    - Copy
    -Paste













 */

