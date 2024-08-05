This document lists the microcontroller types supported by the project and the pinouts for each. The project mainboard will be divided into two groups, each with a pin header "socket" for each of the listed microcontrollers.

## Onboard ESP32-WROOM-32
Used for controlling the system, including the crosspoint switch ICs, web server, and LCD/buttons. Only the pins for Serial/UART, I2S, DAC output and PWM output will be routable via the crosspoint switch system. This enables monitoring of serial messages from other microcontrollers, as well as sound-related functionality and custom outputs to peripherals through the use of arbitrary/preset waveforms (DAC) and PWM signals with adjustable duty cycle, frequency, phase & resolution (1-16bit).

### DAC
DAC

### Serial/UART


### PWM



## Microcontroller List

#### Arduino
- Arduino Nano
- Arduino Pro Micro

#### ESP8266
- NodeMCU
- WeMos D1 Mini

#### ESP32
- ESP32 DevKitC
- ESP32-WROOM-32

## Arduino Nano
#### SPI
MISO:
MOSI:
CS/SS:
SCK:
#### I2C
SDA:
SCK:
#### Serial UART
TX:
RX:
### 
## Arduino Pro Micro


## NodeMCU


## WeMos D1 Mini


## ESP32 DevKitC


## ESP32-WROOM-32
