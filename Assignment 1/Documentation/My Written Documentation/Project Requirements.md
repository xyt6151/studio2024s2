The project should provide a means to easily prototype two Arduino or ESP32/8266 microcontrollers with serial/I2C/SPI peripherals. Connections between these should be configurable in software with no need for manually connecting these with wires. 

# Ethos
The project should emphasise the use of low-cost components wherever possible, and should be able to be assembled from off-the-shelf components and Arduino/ESP modules. The project will include a miniaturised PCB design that can be manufactured by online PCB/assembly services, but the circuit could also be assembled on a protoboard if necessary, provided that accommodations are made for the 44-pin surface-mount crosspoint switch ICs.

# Features
The final iteration of the project should feature:
### System Platform
- An onboard ESP32 for running the web interface, controlling the crosspoint switch ICs and providing the signal generator output via a DAC pin

### Power
- One central 5V input, supplying all connected devices and capable of being toggled to 3.3V on an individual microcontroller basis for lower-voltage devices

### User Interface
- The onboard ESP32 will run a basic web server providing an intuitive, minimalist interface for configuring signal routing between microcontrollers and peripherals. The server will be provided either via connecting to an existing wifi access point or establishing its own AP if credentials have not been configured. 

### Physical Connections
- The board should accept an input voltage of 5V, supplying each of the sockets in parallel, with a simple physical mechanism (such as a jumper) available to switch one or both of the socket groups between 5V and 3.3V depending on the device requirements
- The physical board layout should establish two groups of sockets, with each group containing one of each type of microcontroller socket (Arduino Nano and a selection of sockets for the most popular ESP32/ESP8266 devices) alongside sockets for peripherals (serial, I2C, SPI)
- An onboard LCD display should be connected in a manner that allows the user to establish a connection to any one of the microcontrollers in order to show serial debug messages on the display