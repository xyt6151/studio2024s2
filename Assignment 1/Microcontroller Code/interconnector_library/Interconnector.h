#ifndef INTERCONNECTOR_H
#define INTERCONNECTOR_H

#include <Arduino.h>
#include <vector>

// Structure to hold pin information
struct Pin {
    uint8_t number;
    String usage;
    bool hasCH446Q;
    char axis; // 'X' or 'Y'
    uint8_t index;
};

// Structure to hold microcontroller information
struct Microcontroller {
    String name;
    std::vector<Pin> pins;
};

// Structure to hold peripheral information
struct Peripheral {
    String name;
    std::vector<Pin> pins;
};

// Structure to hold CH446Q connection information
struct CH446Q {
    String id;
    uint8_t xPins[16];
    uint8_t yPins[16];
};

class Interconnector {
public:
    Interconnector();
    void addMicrocontroller(String name);
    void addPinToMCU(String mcuName, uint8_t pinNumber, String usage, char axis, uint8_t index);
    void addPinToMCU(String mcuName, uint8_t pinNumber, String usage);
    void addPinToMCU(String mcuName, uint8_t pinNumber);
    void addPeripheral(String name);
    void addPinToPeripheral(String peripheralName, uint8_t pinNumber, String usage, char axis, uint8_t index);
    void addCH446Q(String id);
    void setCH446QPin(String id, char axis, uint8_t index, uint8_t pinNumber);
    uint8_t getPin(String mcuName, String usage);
    uint8_t getPeripheralPin(String peripheralName, String usage);
    String getMicrocontrollerName(int index);
    String getPeripheralName(int index);
    ConnectionPoint getConnectionPoint(String name, uint8_t pinNumber);

private:
    std::vector<Microcontroller> microcontrollers;
    std::vector<Peripheral> peripherals;
    std::vector<CH446Q> ch446qICs;
    Microcontroller* findMCU(String name);
    Peripheral* findPeripheral(String name);
    CH446Q* findCH446Q(String id);
};

#endif
struct ConnectionPoint {
    char type; // 'X' or 'Y'
    uint8_t index;
};

#endif
