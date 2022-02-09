## Key matrix

[How does a key matrix work?](https://en.wikipedia.org/wiki/Keyboard_matrix_circuit)

Buttons to scan in the matrix:

* 29 keyboard switches (29)
* 4 rockers (8)
* 1 four-way hat (4)
* 2 triple lever switches (4)
* 2 big buttons (2)
* 2 big lateral buttons (2)
* 2 master mode (2)

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
     C3 |NPAD |NPAD |NPAD |NPAD |BIG1 |BIG2 |BIG3 |BIG4 |
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

* J1

  * HAT : C7, R5 - R8 (5)

* J2

  * RKR1: C6, R1 - R2 (3)
  * RKR2: C6, R3 - R4 (3)

* J3

  * RKR3: C6, R5 - R6 (3)
  * RKR4: C6, R7 - R8 (3)

* J4

  * LVR1: C7, R1 - R2 (3)
  * LVR2: C7, R3 - R4 (3)

* J5

  * A/A : C5, R6      (2)
  * A/G : C5, R7      (2)
  * BIG1: C3, R5      (2)

* J6

  * BIG2: C3, R6      (2)
  * BIG3: C3, R7      (2)
  * BIG4: C3, R8      (2)

Total: 35 connections

### PCB to PCB bridges

* J7

  * NPAD: C2 - C3, R1 - R8 (10)

* J8

  * HPAD: C1, R1 - R7       (8)

* J9

  * LPAD: C4, R1 - R5       (6)

* J10

  * RPAD: C5, R1 - R5       (6)

Total: 30 connections


## Rest of connections

* 6 analog axis, two frontal and four lateral.
* 2 rotary encoders, with push.

## Joystick buttons and axis

TBD

## STM32F103C8 pin assignments

![alt_text](https://github.com/mustang51/toro-ufc/blob/main/doc/Bluepillpinout.gif?raw=true)

           +--------------+
    REN1-D |  PB12  GND   | N/A
    REN1-C |  PB13  GND   | N/A
    REN2-D |  PB14  3V3   | N/A
    REN2-C |  PB15  RST   | N/A
    COL7   |  PA08  PB11  | ROW6
    COL6   |  PA09  PB10  | ROW5
    COL5   |  PA10  PB01  | ROW4
    USB-   |  PA11  PB00  | ROW3
    USB+   |  PA12  PA07  | ROW2
    COL4   |  PA15  PA06  | ROW1
    COL3   |  PB03  PA05  | POT6
    COL2   |  PB04  PA04  | POT5
    COL1   |  PB05  PA03  | POT4
    SCL    |  PB06  PA02  | POT3
    SDA    |  PB07  PA01  | POT2
    ROW8   |  PB08  PA00  | POT1
    ROW7   |  PB09  PC15  | REN1-S
    USB5V  |  5V    PC14  | REN2-S
    N/A    |  GND   PC13  | LED
    N/A    |  3V3   VBAT  | N/A
           +--------------+
             3  PA  PA  G
             V  13  14  N
             3          D


