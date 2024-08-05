
## 26/07/2024
- Compiled basic documentation on the CH446Q IC and the requirements of the final product.
- Created a basic Statement of Intent document based on initial writeup of requirements & expectations for the project

## 27/07/2024
- Constructed PCB for housing the CH446Q analog crosspoint switch IC. A breakout board was used in order to avoid surface-mount soldering 44 pins. 
- I am out of stock on pins and sufficiently large PCB protoboard, so these items have been ordered and will arrive on 30/07/2024

## 29/07/2024
- Currently waiting for shipment of basic parts for further construction of the initial working prototype
- Began writing the ESP32 sketch that will run on the onboard ESP32, controlling the UI (web & LCD/buttons) and controlling the CH446Q IC to connect/disconnect pairs of X/Y connection points
- Modified the sketch to omit CH446Q/connection logic in order to use Wokwi to simulate the LCD/button menu system and test how it interacts with information stored in structs
- Gathered list of most popular microcontroller types from online sources. Information will be used to determine layouts of female pin headers for connecting microcontrollers to project mainboard
- Began creation of circuit schematic for full-scale prototype


## 1/08/2024
- Wokwi simulation revealed issues in menu code. Fixes were implemented. 

## 3/08/2024
- Rolled functionality related to CH446Q into a custom Arduino library. This makes adding devices and defining pins/connection points easier and quicker.