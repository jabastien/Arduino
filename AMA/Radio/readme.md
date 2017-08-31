Requirements:

Transmitter
===========
- 8 Anaglog
  - Throttle
  - Yaw
  - Roll
  - Pitch
  - Aux 1 
  - Aux 2
  - Aux 3
  - Aux 4
- 8 Digital switches
  - landing gear
  - lights
  - take picture
  - record
  - OSD on/off
- 8 Trim buttons increments of 1/1023 (fine adj stored on model)
- 5 Menu (Up, Down, Left, Right & Enter)
- GPS
- Gimbal control (uses 3 of the analog)
- Flight timer
- DTE timer (must be calculated)
- Init setup for:
  - max/min values
  - reverse analog (transmitter input only)

Receiver
========
- Accept all Trasmitter data 
  - 8 analog
  - 8 digital
  - Trim message (stored on eprom)
  - Menu data
- Output to Controller
  - Servo Pulse
  - PPM
  - Raw data (serial data out)
- GPS to Controller for follow & return home if moving

Controller
==========
- GPS
  - Headless (mission)
  - Mission
- Auto takeoff (switch)
- Auto return (switch)
- Auto Land (switch)
- Auto return & land (lost connection)
- Follow-me
  - front
  - rear
  - @ degree
- Altitude Hold
- Sand Box training (limit X, Y & Z movement to xxx meters[xxx 1-20])
- Point of no return (% battery distance to home limiter)

