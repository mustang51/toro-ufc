# STM32F103C8 pin assignments

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


scanlines = 8 rows x 7 columns -> 56 max

scan buttons:

29 keyboard switches    = 29
2 triple lever switches =  4
2 big buttons           =  2
2 master mode           =  2
4 rockers               =  8
4-way hat               =  4
2 push encoders         =  2
total                   = 51 scan buttons

joystick buttons:

joystic axis:

