## STM32F103C8 pin assignments

![alt_text](https://github.com/mustang51/toro-ufc/blob/main/doc/Bluepillpinout.gif?raw=true)

           +--------------+
    ROT1-D |  PB12  GND   | N/A
    ROT1-C |  PB13  GND   | N/A
    ROT0-D |  PB14  3V3   | N/A
    ROT0-C |  PB15  RST   | N/A
           |  PA08  PB11  | ROW6
    COL7   |  PA09  PB10  | ROW5
    COL6   |  PA10  PB01  | ROW4
    USB-   |  PA11  PB00  | ROW3
    USB+   |  PA12  PA07  | ROW2
    COL5   |  PA15  PA06  | ROW1
    COL4   |  PB03  PA05  | POT6
    COL3   |  PB04  PA04  | POT5
    COL2   |  PB05  PA03  | POT4
           |  PB06  PA02  | POT3
    COL1   |  PB07  PA01  | POT2
    ROW8   |  PB08  PA00  | POT1
    ROW7   |  PB09  PC15  | OSC OUT ?
    USB5V  |  5V    PC14  | OSC IN  ?
    N/A    |  GND   PC13  | LED
    N/A    |  3V3   VBAT  | N/A
           +--------------+
             3  PA  PA  G
             V  13  14  N
             3          D

## Key matrix

scanlines = 8 rows x 7 columns -> 56 max

scan buttons:

* 29 keyboard switches (29)
* 2 triple lever switches (4)
* 2 big buttons (2)
* 2 master mode (2)
* 4 rockers (8)
* 4-way hat (4)
* 2 big lateral buttons (2)

Total: 51 scan buttons

## Matrix layout

          R1    R2    R3    R4    R5    R6    R7    R8
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C1 |NPAD |NPAD |NPAD |NPAD |NPAD |NPAD |NPAD |NPAD |
        |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C2 |NPAD |NPAD |NPAD |NPAD | HAT | HAT | HAT | HAT |
        |  9  |  0  | C   | E   |  N  |  S  |  W  |  E  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C3 |LPAD |LPAD |LPAD |LPAD |LPAD |BIG1 |BIG2 |     |
        | F1  | F2  | F3  | F4  | F5  |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C4 |RPAD |RPAD |RPAD |RPAD |RPAD |A/A  |A/G  |     |
        | F1  | F2  | F3  | F4  | F5  |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C5 |HPAD |HPAD |HPAD |HPAD |HPAD |HPAD |HPAD |     |
        | F1  | F2  | F3  | F4  | F5  | F6  | ON  |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C6 |RKR1 |RKR1 |RKR2 |RKR2 |RKR3 |RKR3 |RKR4 |RKR4 |
        | UP  | DN  | UP  | DN  | UP  | DN  | UP  | DN  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C7 |LVR1 |LVR1 |LVR2 |LVR2 |BIG3 |BIG4 |     |     |
        | UP  | DN  | UP  | DN  |     |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+

* NPAD: numerical pad
* LPAD: left function buttons
* RPAD: right function buttons
* HPAD: bottom horizontal function buttons
* RKRx: rocker buttons
* LVRx: on-off-on lever switches
* HAT : 4-way hat

## Connectors needed

### Circuit to circuit bridges

* NPAD: C1 - C2, R1 - R8 (10)
* LPAD: C3, R1 - R5       (6)
* RPAD: C4, R1 - R5       (6)
* HPAD: C5, R1 - R7       (8)

Total: 30 connections

### Hand soldered

* HAT : C2, R5 - R8 (5)
* RKR1: C6, R1 - R2 (3)
* RKR2: C6, R3 - R4 (3)
* RKR3: C6, R5 - R6 (3)
* RKR4: C6, R7 - R8 (3)
* LVR1: C7, R1 - R2 (3)
* LVR2: C7, R3 - R4 (3)
* A/A : C4, R6      (2)
* A/G : C4, R7      (2)
* BIG1: C3, R6      (2)
* BIG2: C3, R7      (2)
* BIG3: C7, R5      (2)
* BIG4: C7, R6      (2)

Total: 35 connections

## Rest of connections

* 6 analog axis, two frontal and four lateral.
* 2 rotary encoders, with push.

## Joystick buttons and axis

TBD

