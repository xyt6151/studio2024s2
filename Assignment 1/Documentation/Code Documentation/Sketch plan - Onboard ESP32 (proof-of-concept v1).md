# Overview

This sketch is for a limited, proof-of-concept version of the project featuring a single CH446Q IC and therefore, fewer possibilities for connecting pins together. The proof-of-concept board features the following:
- Project board has two halves. 
- Each half contains a socket for one microcontroller. Microcontroller in first half is Arduino Nano. Microcontroller in second half is ESP32-WROOM-32. The project board itself includes an onboard ESP32-WROOM-32 which runs the LCD/buttons, CH446Q IC, etc.
- Project board has one common set of female pin headers for Serial/UART and I2C. These can be routed to from either of the microcontrollers.
- Project board has 16x2 I2C LCD and 4 momentary switches (pushbuttons) for menu navigation (Previous, Select, Exit, Forward). Menu allows selection of pins to connect together and selection of serial monitor for displaying microcontroller serial debug messages on LCD.
- Serial monitor functions by connecting onboard ESP32 TX & RX pins to those of one of the microcontrollers under test (MCU on first side or MCU on second side). Messages remain on LCD until the next message is received, with the older message showing on the top line and newer message showing on second line. Any characters in the message past 16 characters are cut off and not displayed. 
- One CH446Q IC is used for connections, operating in serial address mode

# CH446Q X and Y connection points

MCU1: Arduino Nano
MCU2: ESP32-DevKitC

| CH446Q Connection Point | Destination Description      | Microcontroller Pin Name (only applies to Microcontroller Pins) |
| ----------------------- | ---------------------------- | --------------------------------------------------------------- |
| X0                      | MCU1 UART TX                 | IO1                                                             |
| X1                      | MCU1 UART RX                 | IO0                                                             |
| X2                      | MCU2 UART TX                 | GPIO1                                                           |
| X3                      | MCU2 UART RX                 | GPIO3                                                           |
| X4                      | MCU1 I2C SCL                 | A5                                                              |
| X5                      | MCU1 I2C SDA                 | A4                                                              |
| X6                      | MCU2 I2C SCL                 | GPIO22                                                          |
| X7                      | MCU2 I2C SDA                 | GPIO21                                                          |
| X8                      | MCU1 Digital Output Pin 1    | D11                                                             |
| X9                      | MCU2 Digital Output Pin 2    | GPIO8                                                           |
| X10                     | MCU1 Digital Output Pin 2    | D12                                                             |
| X11                     | MCU2 PWM Output Pin          | GPIO32                                                          |
| X12                     | Onboard ESP32 DAC Output Pin | GPIO25                                                          |
| X13                     | NC                           |                                                                 |
| X14                     | NC                           |                                                                 |
| X15                     | NC                           |                                                                 |
| Y0                      | Common UART TX               |                                                                 |
| Y1                      | Common UART RX               |                                                                 |
| Y2                      | Onboard ESP32 UART TX        | GPIO1                                                           |
| Y3                      | Onboard ESP32 UART RX        | GPIO3                                                           |
| Y4                      | Common I2C SCL               |                                                                 |
| Y5                      | Common I2C SDA               |                                                                 |
| Y6                      | MCU1 Analog Input Pin        | A6                                                              |
| Y7                      | MCU2 Digital Input Pin       | GPIO36                                                          |