#include "Interconnector.h"

Interconnector::Interconnector() {}

void Interconnector::addMicrocontroller(String name) {
    Microcontroller mcu = { name, {} };
    microcontrollers.push_back(mcu);
}

void Interconnector::addPinToMCU(String mcuName, uint8_t pinNumber, String usage, char axis, uint8_t index) {
    Microcontroller* mcu = findMCU(mcuName);
    if (mcu) {
        Pin pin = { pinNumber, usage, true, axis, index };
        mcu->pins.push_back(pin);
    }
}

void Interconnector::addPinToMCU(String mcuName, uint8_t pinNumber, String usage) {
    Microcontroller* mcu = findMCU(mcuName);
    if (mcu) {
        Pin pin = { pinNumber, usage, false, ' ', 0 };
        mcu->pins.push_back(pin);
    }
}

void Interconnector::addPinToMCU(String mcuName, uint8_t pinNumber) {
    Microcontroller* mcu = findMCU(mcuName);
    if (mcu) {
        Pin pin = { pinNumber, "", false, ' ', 0 };
        mcu->pins.push_back(pin);
    }
}

void Interconnector::addPeripheral(String name) {
    Peripheral peripheral = { name, {} };
    peripherals.push_back(peripheral);
}

void Interconnector::addPinToPeripheral(String peripheralName, uint8_t pinNumber, String usage, char axis, uint8_t index) {
    Peripheral* peripheral = findPeripheral(peripheralName);
    if (peripheral) {
        Pin pin = { pinNumber, usage, true, axis, index };
        peripheral->pins.push_back(pin);
    }
}

void Interconnector::addCH446Q(String id) {
    CH446Q ic = { id, {}, {} };
    ch446qICs.push_back(ic);
}

void Interconnector::setCH446QPin(String id, char axis, uint8_t index, uint8_t pinNumber) {
    CH446Q* ic = findCH446Q(id);
    if (ic) {
        if (axis == 'X') {
            ic->xPins[index] = pinNumber;
        } else if (axis == 'Y') {
            ic->yPins[index] = pinNumber;
        }
    }
}
uint8_t Interconnector::getPin(String mcuName, String usage) {
    Microcontroller* mcu = findMCU(mcuName);
    if (mcu) {
        for (auto& pin : mcu->pins) {
            if (pin.usage == usage) {
                return pin.number;
            }
        }
    }
    return 255; // Return an invalid pin number if not found
}

uint8_t Interconnector::getPeripheralPin(String peripheralName, String usage) {
    Peripheral* peripheral = findPeripheral(peripheralName);
    if (peripheral) {
        for (auto& pin : peripheral->pins) {
            if (pin.usage == usage) {
                return pin.number;
            }
        }
    }
    return 255; // Return an invalid pin number if not found
}

String Interconnector::getMicrocontrollerName(int index) {
    if (index >= 0 && index < microcontrollers.size()) {
        return microcontrollers[index].name;
    }
    return "";
}

String Interconnector::getPeripheralName(int index) {
    if (index >= 0 && index < peripherals.size()) {
        return peripherals[index].name;
    }
    return "";
}

ConnectionPoint Interconnector::getConnectionPoint(String name, uint8_t pinNumber) {
    Microcontroller* mcu = findMCU(name);
    if (mcu) {
        for (auto& pin : mcu->pins) {
            if (pin.number == pinNumber && pin.hasCH446Q) {
                return { pin.axis, pin.index };
            }
        }
    }
    Peripheral* peripheral = findPeripheral(name);
    if (peripheral) {
        for (auto& pin : peripheral->pins) {
            if (pin.number == pinNumber) {
                return { pin.axis, pin.index };
            }
        }
    }
    return { ' ', 0 }; // Return an invalid connection point if not found
}

Microcontroller* Interconnector::findMCU(String name) {
    for (auto& mcu : microcontrollers) {
        if (mcu.name == name) {
            return &mcu;
        }
    }
    return nullptr;
}

Peripheral* Interconnector::findPeripheral(String name) {
    for (auto& peripheral : peripherals) {
        if (peripheral.name == name) {
            return &peripheral;
        }
    }
    return nullptr;
}

CH446Q* Interconnector::findCH446Q(String id) {
    for (auto& ic : ch446qICs) {
        if (ic.id == id) {
            return &ic;
        }
    }
    return nullptr;
}
