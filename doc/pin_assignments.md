## Key matrix

[How does a key matrix work?](https://en.wikipedia.org/wiki/Keyboard_matrix_circuit)

Buttons to scan in the matrix:

* 29 keyboard switches (29)
* 4 rockers (8)
* 1 four-way hat (4)
* 2 triple lever switches (4)
* 2 big buttons (2)
* 2 master mode (2)
* 2 extra unconnected (2)

Total: 51 scan buttons

We will use 8 rows and 7 columns, giving a total of 56 possible buttons.

Rotary encoder buttons will be kept out of the matrix, as the KY-040 designs connect the pushbutton to ground irreversibly.

## Matrix layout

In order to reduce the number of cables and soldering, some switches will be grouped.

The keyboard switches will be grouped into four small PCBs, named: NPAD, LPAD, RPAD and HPAD.

The distribution of rows and columns is as follows:

          R1    R2    R3    R4    R5    R6    R7    R8
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C1 |HPAD |HPAD |HPAD |HPAD |HPAD |HPAD |HPAD |     |
        | F1  | F2  | F3  | F4  | F5  | F6  | ON  |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C2 |NPAD |NPAD |NPAD |NPAD |NPAD |NPAD |NPAD |NPAD |
        |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C3 |NPAD |NPAD |NPAD |NPAD |BIG1 |BIG2 |XTRA1|XTRA2|
        |  9  |  0  | C   | E   |     |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C4 |LPAD |LPAD |LPAD |LPAD |LPAD |     |     |     |
        | F1  | F2  | F3  | F4  | F5  |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C5 |RPAD |RPAD |RPAD |RPAD |RPAD |A/A  |A/G  |     |
        | F1  | F2  | F3  | F4  | F5  |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C6 |RKR1 |RKR1 |RKR2 |RKR2 |RKR3 |RKR3 |RKR4 |RKR4 |
        | UP  | DN  | UP  | DN  | UP  | DN  | UP  | DN  |
        +-----+-----+-----+-----+-----+-----+-----+-----+
     C7 |LVR1 |LVR1 |LVR2 |LVR2 | HAT | HAT | HAT | HAT |
        | UP  | DN  | UP  | DN  |  N  |  S  |  W  |  E  |
        +-----+-----+-----+-----+-----+-----+-----+-----+

* NPAD: numerical pad
* LPAD: left function buttons
* RPAD: right function buttons
* HPAD: bottom horizontal function buttons
* RKRx: rocker buttons
* LVRx: on-off-on lever switches
* HAT : 4-way hat

## Connectors needed

### Hand soldered

* J1, HAT

          C7    R5    R6    R7    R8
        +-----+-----+-----+-----+-----+-----+
        | HAT | HAT | HAT | HAT | HAT |     |
        | CMN |  N  |  S  |  W  |  E  |     |
        +-----+-----+-----+-----+-----+-----+

* J2, RKR1/2

          C6    R1    R2    C6    R3    R4
        +-----+-----+-----+-----+-----+-----+
        |RKR1 |RKR1 |RKR1 |RKR2 |RKR2 |RKR2 |
        | CMN | UP  | DN  | CMN | UP  | DN  |
        +-----+-----+-----+-----+-----+-----+

* J3, RKR3/4

          C6    R5    R6    C6    R7    R8
        +-----+-----+-----+-----+-----+-----+
        |RKR3 |RKR3 |RKR3 |RKR4 |RKR4 |RKR4 |
        | CMN | UP  | DN  | CMN | UP  | DN  |
        +-----+-----+-----+-----+-----+-----+

* J4, LVR1/2

          C7    R1    R2    C7    R3    R4
        +-----+-----+-----+-----+-----+-----+
        |LVR1 |LVR1 |LVR1 |LVR2 |LVR2 |LVR2 |
        | CMN | UP  | DN  | CMN | UP  | DN  |
        +-----+-----+-----+-----+-----+-----+

* J5, A/A, A/G, BIG1

          C5    R6    C5    R7    C3    R5
        +-----+-----+-----+-----+-----+-----+
        | A/A | A/A | A/G | A/G |BIG1 |BIG1 |
        |  1  |  2  |  1  |  2  |  1  |  2  |
        +-----+-----+-----+-----+-----+-----+

* J6, BIG2, XTRA1/2

          C3    R6    C3    R7    C3    R8
        +-----+-----+-----+-----+-----+-----+
        |BIG2 |BIG2 |XTRA1|XTRA1|XTRA2|XTRA2|
        |  1  |  2  |  1  |  2  |  1  |  2  |
        +-----+-----+-----+-----+-----+-----+

* J11, POTS1-3

           1     2     3     4     5     6     7     8     9    10
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        | POT3| POT3| POT3| POT2| POT2| POT2| POT1| POT1| POT1|     |
        | GND |  S  | VCC | GND |  S  | VCC | GND |  S  | VCC |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+

* J12, POTS4-6

           1     2     3     4     5     6     7     8     9    10
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        | POT6| POT6| POT6| POT5| POT5| POT5| POT4| POT4| POT4|     |
        | GND |  S  | VCC | GND |  S  | VCC | GND |  S  | VCC |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+

* J13, ROTARY1

           1     2     3     4     5     6
        +-----+-----+-----+-----+-----+-----+
        |REN1 |REN1 |REN1 |REN1 |REN1 |     |
        |  C  |  D  |  SW | VCC | GND |     |
        +-----+-----+-----+-----+-----+-----+

* J14, ROTARY2

           1     2     3     4     5     6
        +-----+-----+-----+-----+-----+-----+
        |REN2 |REN2 |REN2 |REN2 |REN2 |     |
        |  C  |  D  |  SW | VCC | GND |     |
        +-----+-----+-----+-----+-----+-----+

* J16, USB

           1     2     3     4
        +-----+-----+-----+-----+
        |VUSB | GND |USBD-|USBD+|
        |     |     |     |     |
        +-----+-----+-----+-----+

Total: 67 connections

### PCB to PCB bridges

* J7, NPAD

          C2    C3    R1    R2    R3    R4    R5    R6    R7    R8
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
        |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  | 10  |
        |     |     |     |     |     |     |     |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+

* J8, HPAD

          C1    R1    R2    R3    R4    R5    R6    R7
        +-----+-----+-----+-----+-----+-----+-----+-----+
        |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |
        |     |     |     |     |     |     |     |     |
        +-----+-----+-----+-----+-----+-----+-----+-----+

* J9, LPAD

          C4    R1    R2    R3    R4    R5
        +-----+-----+-----+-----+-----+-----+
        |  1  |  2  |  3  |  4  |  5  |  6  |
        |     |     |     |     |     |     |
        +-----+-----+-----+-----+-----+-----+

* J10, RPAD

          C5    R1    R2    R3    R4    R5
        +-----+-----+-----+-----+-----+-----+
        |  1  |  2  |  3  |  4  |  5  |  6  |
        |     |     |     |     |     |     |
        +-----+-----+-----+-----+-----+-----+

Total: 30 connections


## Rest of connections

* 6 analog axis, two frontal and four lateral.
* 2 rotary encoders, with push.

## Joystick buttons and axis

* Key switches: 1 - 29
* 4 rockers: 30 - 41
* 4 way hat: 42, 43, 44, 45, 46
* 2 triple levers: 47, 48, 49, 50, 51, 52
* 2 big buttons: 53, 54, 55, 56
* 2 extra buttons: 57, 58, 59, 60
* 2 master mode: 61, 62
* 2 rotary encoders: 63, 64, 65, 66, 67, 68
* 6 axis: 69 - 80


## STM32F103C8 pin assignments

![alt_text](https://github.com/mustang51/toro-ufc/blob/main/doc/Bluepillpinout.gif?raw=true)

           +--------------+
    REN1-C |  PB12  GND   | N/A
    REN1-D |  PB13  GND   | N/A
    REN2-C |  PB14  3V3   | N/A
    REN2-D |  PB15  RST   | N/A
    COL7   |  PA08  PB11  | ROW1
    COL6   |  PA09  PB10  | ROW2
    COL5   |  PA10  PB01  | ROW3
    USB-   |  PA11  PB00  | ROW4
    USB+   |  PA12  PA07  | ROW6
    COL4   |  PA15  PA06  | ROW5
    COL3   |  PB03  PA05  | POT6
    COL2   |  PB04  PA04  | POT5
    COL1   |  PB05  PA03  | POT4
    SCL    |  PB06  PA02  | POT1
    SDA    |  PB07  PA01  | POT2
    ROW7   |  PB08  PA00  | POT3
    ROW8   |  PB09  PC15  | REN1-S
    USB5V  |  5V    PC14  | REN2-S
    N/A    |  GND   PC13  | LED
    N/A    |  3V3   VBAT  | N/A
           +--------------+
             3  PA  PA  G
             V  13  14  N
             3          D


PB03 is being used for TRACE SWO, debug functionality. disableDebugPorts() must be invoked to use it as a normal GPIO.
