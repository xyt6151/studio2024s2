# Project Summary and Requirements

## Project Overview
The project involves designing a mainboard divided into two groups, each with female pin headers for connecting multiple microcontrollers and peripherals. The purpose is to dynamically route connections using the CH446Q analog crosspoint switch IC. The project has a proof-of-concept (PoC) version and a full-featured version.

### Key Components:
- **Microcontrollers**: Arduino Nano, ESP32
- **Peripherals**: UART, I2C
- **CH446Q**: Used to route connections
- **ESP32-WROOM-32**: Onboard microcontroller for handling UI and serial monitoring

## Proof-of-Concept Version
This version has fewer pins and simpler routing:
- **Microcontrollers**: Arduino Nano, ESP32
- **Peripherals**: Common UART, Common I2C, Onboard ESP32 UART
- **Routing**:
  - SPI is not used in this version
  - UART, I2C, Digital Input/Output, Analog Input
  - Specific CH446Q connection points for each pin

## Pinouts for Microcontrollers used in Proof-of-concept Version

# Proof-of-Concept Microcontroller Pinouts

## Side 1 Microcontroller: Arduino Nano

| Pin Name | Description | Feature 1 | Feature 2 |
| --- | --- | --- | --- |
| D0 | Digital I/O Pin | RX | Serial |
| D1 | Digital I/O Pin | TX | Serial |
| D2 | Digital I/O Pin | External Interrupt | INT0 |
| D3 | Digital I/O Pin | PWM | INT1 |
| D4 | Digital I/O Pin |  |  |
| D5 | Digital I/O Pin | PWM |  |
| D6 | Digital I/O Pin | PWM |  |
| D7 | Digital I/O Pin |  |  |
| D8 | Digital I/O Pin |  |  |
| D9 | Digital I/O Pin | PWM |  |
| D10 | Digital I/O Pin | PWM | SS |
| D11 | Digital I/O Pin | PWM | MOSI |
| D12 | Digital I/O Pin |  | MISO |
| D13 | Digital I/O Pin | PWM | SCK |
| A0 | Analog Input 0 |  |  |
| A1 | Analog Input 1 |  |  |
| A2 | Analog Input 2 |  |  |
| A3 | Analog Input 3 |  |  |
| A4 | Analog Input 4 | SDA | I2C |
| A5 | Analog Input 5 | SCL | I2C |
| A6 | Analog Input 6 |  |  |
| A7 | Analog Input 7 |  |  |
| RST | Reset |  |  |
| 3V3 | 3.3V Output |  |  |
| VIN | Input Voltage |  |  |
| GND | Ground |  |  |
| AREF | Analog Reference |  |  |
| ICSP | MISO | SCK | MOSI |

## Side 2 Microcontroller: ESP32-WROOM-32 based board
This microcontroller is a development board featuring an ESP32-WROOM-32. It is known in online store listings as "Ideaspark ESP32 0.96" OLED Board". 

### Left Side of Microcontroller

| Pin Name | Feature 1 | Feature 2 | Feature 3 |
| --- | --- | --- | --- |
| ENABLE |  |  |  |
| 3V3 |  |  |  |
| GPIO36 | S_VP | RTCIO0 | A0 |
| GPIO39 | S_VN | RTCIO3 | A3 |
| GPIO34 | VDET_1 | RTCIO4 | A6 |
| GPIO35 | VDET_1 | RTCIO5 | A7 |
| GPIO32 | 32K_XP | RTCIO9 | A4 |
| GPIO33 | 32K_XN | RTCIO8 | A5 |
| GPIO25 | DAC1 | RTCIO6 | A18 |
| GPIO26 | DAC2 | RTCIO7 | A19 |
| GPIO27 |  | RTCIO17 | A17 |
| GPIO14 | HSPI_SCK | RTCIO16 | A16 |
| GPIO12 | HSPI_MISO | RTCIO15 | A15 |
| GPIO13 | HSPI_MOSI | RTCIO14 | A14 |
| GND |  |  |  |
| VIN |  |  |  |

### Right Side of Microcontroller

| Pin Name | Feature 1 | Feature 2 | Feature 3 |
| --- | --- | --- | --- |
| GPIO23 | 15 | COPI | VSPI_MOSI |
| GPIO22 | 14 | SCL | OLED-SCL |
| GPIO1 | 13 | TX0 |  |
| GPIO3 | 12 | RX0 |  |
| GPIO21 | 11 | SDA | OLED-SDA |
| GPIO19 | 10 | CIPO | VSPI_MOSI |
| GPIO18 | 9 | SCK | VSPI_SCK |
| GPIO5 | 8 | CS | VSPI_SS |
| GPIO17 | 7 | TX2 |  |
| GPIO16 | 6 | RX2 |  |
| GPIO4 | 5 | A10 |  |
| GPIO2 | 4 | A12 |  |
| GPIO15 | 3 | A13 | HSPI_SS |
| GND | 2 |  |  |
| VIN | 1 |  |  |

## Onboard ESP32: ESP32-WROOM-32 based board
This microcontroller is a development board featuring an ESP32-WROOM-32. It is known in online store listings as "Ideaspark ESP32 0.96" OLED Board". 
Same board and pinout as the ESP32-WROOM-32 based board listed above.


### Key Proof-of-concept Sketch Features:
- **LCD and Button UI**: Navigate menus to select connections
- **Serial Monitor**: Display serial messages from connected microcontrollers
- **CH446Q Control**: Use SPI to send commands to CH446Q for routing

### CH446Q Connection Points for Proof-of-concept version: 
- **Microcontroller 1 UART TX**: X0 
- **Microcontroller 1 UART RX**: X1
- **Microcontroller 2 UART TX**: X2 
- **Microcontroller 2 UART RX**: X3 
- **Microcontroller 1 I2C SCL**: X4 
- **Microcontroller 1 I2C SDA**: X5 
- **Microcontroller 2 I2C SCL**: X6 
- **Microcontroller 2 I2C SDA**: X7 
- **Microcontroller 1 Digital Output 1**: X8
- **Microcontroller 2 Digital Output 2**: X9 
- **Microcontroller 1 Digital Output 2**: X10
- **Microcontroller 2 PWM Output**: X11 
- **Onboard ESP32 DAC Output**: X12 
- **Common UART TX**: Y0 
- **Common UART RX**: Y1 
- **Onboard ESP32 UART TX**: Y2 
- **Onboard ESP32 UART RX**: Y3 
- **Common I2C SCL**: Y4 
- **Common I2C SDA**: Y5 
- **Microcontroller 1 Analog Input**: Y6 
- **Microcontroller 2 Digital Input**: Y7

## Full-Featured Version
This version includes:
- **Additional microcontrollers**: More options compared to PoC
- **SPI support**: Full implementation of SPI peripherals
- **Enhanced routing**: More connection points and advanced routing logic

### Key Features:
- **Complete Menu System**: More options and functionalities
- **Full Peripheral Support**: Includes SPI peripherals along with UART and I2C
- **Advanced CH446Q Routing**: Multiple CH446Q ICs used for complex routing

## Sketch Code for proof-of-concept version
The code includes:
- **LCD and Button Initialization**: For UI
- **SPI Initialization**: For CH446Q control
- **Microcontroller and Peripheral Definitions**: Structs and arrays
- **Menu Navigation and Display**: Functions for handling menu
- **Connection Functions**: For routing connections via CH446Q
- **Serial Monitor Handling**: For displaying serial messages




