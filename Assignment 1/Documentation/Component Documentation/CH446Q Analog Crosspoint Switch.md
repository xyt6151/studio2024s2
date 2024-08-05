# Overview

This IC is an analog crosspoint switch, enabling the establishment of electrical connections by sending commands via serial to the IC. The switch matrix is 8x16, allowing connections to be made between any of the "X" pins (X0-X15) and any of the "Y" pins (Y0-Y7). Due to the relatively high on-state resistance and relatively low maximum through current of the switches and switch matrix, this IC is appropriate for switching signals, and is unsuitable for switching power connections.


# Relevant Electrical Characteristics
A selection of electrical characteristics applicable to the use case of this project

### Recommended Levels

**Recommended Min. Operating Voltage (VDD):** 4V
**Recommended Max. Operating Voltage (VDD):** 13.2V

**Min. Recommended Operating Voltage (VEE):** -8.8V
**Max. Recommended Operating Voltage (VEE):** 0V

### Absolute Maximum Ratings

**VDD Supply Voltage when VEE=GND=0V:** -0.5 - 16V (MAX)

**Min. Voltage on analog signal input/output pin when VDD >= GND >= VEE:** VEE - 0.5V
**Max. Voltage on analog signal input/output pin when VDD >= GND >= VEE:** VDD + 0.5V

**Min. Voltage on digital signal input/output pin:** GND - 0.5V
**Max. Voltage on digital signal input/output pin:** VDD + 0.5V

**Continuous through current of single analog switch:** Max. 15mA
**Continuous through current of ALL analog switches:** Max. 100mA


### Analog Switch ON Resistance

- **When temperature = 25 degrees C and VDD-VEE=12V**: 45-65 ohm
- **When temperature = 25 degrees C and VDD-VEE=5V:** 120-185 ohm


# Pins

The following is pin information taken from the datasheet and displayed in a clarified manner.

| Pin Number        | Pin Name | Type                       | Pin Description                                                                                                                                                 |
| ----------------- | -------- | -------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 38                | VDD      | POWER                      | POSITIVE SUPPLY (4 to 13.2V)                                                                                                                                    |
| 12                | GND      | POWER                      | COMMON GROUND (0V)                                                                                                                                              |
| 16                | VEE      | POWER                      | NEGATIVE SUPPLY (-8.8V to 0V)                                                                                                                                   |
| 41                | RST      | INPUT                      | EXTERNAL MANUAL RESET INPUT, ACTIVE AT 'HIGH' LEVEL                                                                                                             |
| 10                | P/-S     | INPUT                      | ADDR INPUT MODE SELECTION: <br>'High' level: Parallel input mode<br>'Low' level: Serial input mode                                                              |
| 36                | DAT      | INPUT                      | In serial address mode: <br>Serial data input and switch data input<br>In parallel address mode:<br>Switch data input<br><br>On at high level, off at low level |
| 14                | STB      | INPUT                      | STROBE PULSE INPUT<br>ACTIVE AT HIGH LEVEL                                                                                                                      |
| 34                | CS/CK    | INPUT                      | In serial address mode:<br>Serial clock input, active on rising edge<br>In parallel address mode:<br>Chip selection mode, active at high level                  |
| 43, 18, 19, 42    | AX0~AX3  | INPUT                      | In serial address mode: <br>Unused, GND must be directly connected.<br>In parallel address mode:<br>Port X selected address input<br>                           |
| 20, 21, 40        | AY0~AY2  | INPUT                      | In serial address mode:<br>Unused, GND must be directly connected.<br>In parallel address mode:<br>Port Y selected address input                                |
| 31                | X0       | ANALOG SIGNAL INPUT/OUTPUT | Port X0 of 8x16 matrix                                                                                                                                          |
| 30                | X1       | ANALOG SIGNAL INPUT/OUTPUT | Port X1 of 8x16 matrix                                                                                                                                          |
| 29                | X2       | ANALOG SIGNAL INPUT/OUTPUT | Port X2 of 8x16 matrix                                                                                                                                          |
| 28                | X3       | ANALOG SIGNAL INPUT/OUTPUT | Port X3 of 8x16 matrix                                                                                                                                          |
| 27                | X4       | ANALOG SIGNAL INPUT/OUTPUT | Port X4 of 8x16 matrix                                                                                                                                          |
| 26                | X5       | ANALOG SIGNAL INPUT/OUTPUT | Port X5 of 8x16 matrix                                                                                                                                          |
| 3                 | X6       | ANALOG SIGNAL INPUT/OUTPUT | Port X6 of 8x16 matrix                                                                                                                                          |
| 4                 | X7       | ANALOG SIGNAL INPUT/OUTPUT | Port X7 of 8x16 matrix                                                                                                                                          |
| 5                 | X8       | ANALOG SIGNAL INPUT/OUTPUT | Port X8 of 8x16 matrix                                                                                                                                          |
| 6                 | X9       | ANALOG SIGNAL INPUT/OUTPUT | Port X9 of 8x16 matrix                                                                                                                                          |
| 7                 | X10      | ANALOG SIGNAL INPUT/OUTPUT | Port X10 of 8x16 matrix                                                                                                                                         |
| 8                 | X11      | ANALOG SIGNAL INPUT/OUTPUT | Port X11 of 8x16 matrix                                                                                                                                         |
| 25                | X12      | ANALOG SIGNAL INPUT/OUTPUT | Port X12 of 8x16 matrix                                                                                                                                         |
| 24                | X13      | ANALOG SIGNAL INPUT/OUTPUT | Port X13 of 8x16 matrix                                                                                                                                         |
| 1                 | X14      | ANALOG SIGNAL INPUT/OUTPUT | Port X14 of 8x16 matrix                                                                                                                                         |
| 2                 | X15      | ANALOG SIGNAL INPUT/OUTPUT | Port X15 of 8x16 matrix                                                                                                                                         |
| 33                | Y0       | ANALOG SIGNAL INPUT/OUTPUT | Port Y0 of 8x16 matrix                                                                                                                                          |
| 35                | Y1       | ANALOG SIGNAL INPUT/OUTPUT | Port Y1 of 8x16 matrix                                                                                                                                          |
| 37                | Y2       | ANALOG SIGNAL INPUT/OUTPUT | Port Y2 of 8x16 matrix                                                                                                                                          |
| 39                | Y3       | ANALOG SIGNAL INPUT/OUTPUT | Port Y3 of 8x16 matrix                                                                                                                                          |
| 17                | Y4       | ANALOG SIGNAL INPUT/OUTPUT | Port Y4 of 8x16 matrix                                                                                                                                          |
| 15                | Y5       | ANALOG SIGNAL INPUT/OUTPUT | Port Y5 of 8x16 matrix                                                                                                                                          |
| 13                | Y6       | ANALOG SIGNAL INPUT/OUTPUT | Port Y6 of 8x16 matrix                                                                                                                                          |
| 11                | Y7       | ANALOG SIGNAL INPUT/OUTPUT | Port Y7 of 8x16 matrix                                                                                                                                          |
| 9, 22, 23, 32, 44 | N.C.     | IDLE PIN                   | Unused pins, do not connect                                                                                                                                     |
