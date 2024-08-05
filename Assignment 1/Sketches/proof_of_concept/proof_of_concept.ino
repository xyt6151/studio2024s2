#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include "Interconnector.h"

// LCD and button definitions
#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_ROWS    2
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

#define BUTTON_BACK   34
#define BUTTON_SELECT 35
#define BUTTON_EXIT   32
#define BUTTON_FORWARD 33

// CH446Q control pins
#define CS_PIN 5  // Chip select pin
#define DAT_PIN 23 // Data pin
#define STB_PIN 18 // Strobe pin
#define RST_PIN 19 // Reset pin

Interconnector inter;

bool mainScreen = true;
bool serialMonitorMode = false;
int currentMenu = 0;
int currentOption = 0;
int selectedMCU = -1;
int selectedPeripheral = -1;

void setup() {
    // Initialize LCD and buttons
    lcd.init();
    lcd.backlight();
    pinMode(BUTTON_BACK, INPUT_PULLUP);
    pinMode(BUTTON_SELECT, INPUT_PULLUP);
    pinMode(BUTTON_EXIT, INPUT_PULLUP);
    pinMode(BUTTON_FORWARD, INPUT_PULLUP);

    // Initialize SPI and CH446Q
    pinMode(CS_PIN, OUTPUT);
    pinMode(DAT_PIN, OUTPUT);
    pinMode(STB_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);

    digitalWrite(CS_PIN, LOW);
    digitalWrite(DAT_PIN, LOW);
    digitalWrite(STB_PIN, LOW);
    digitalWrite(RST_PIN, HIGH);
    delay(10);
    digitalWrite(RST_PIN, LOW);

    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16); // Adjust as necessary
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);

    // Initialize microcontrollers and peripherals using Interconnector
    inter.addMicrocontroller("Arduino Nano");
    inter.addPinToMCU("Arduino Nano", 1, "UART_TX");
    inter.addPinToMCU("Arduino Nano", 0, "UART_RX");
    inter.addPinToMCU("Arduino Nano", 19, "I2C_SCL");
    inter.addPinToMCU("Arduino Nano", 18, "I2C_SDA");
    inter.addPinToMCU("Arduino Nano", 11, "DIGITAL_OUT1");
    inter.addPinToMCU("Arduino Nano", 12, "DIGITAL_OUT2");
    inter.addPinToMCU("Arduino Nano", 6, "ANALOG_IN");

    inter.addMicrocontroller("ESP32");
    inter.addPinToMCU("ESP32", 1, "UART_TX");
    inter.addPinToMCU("ESP32", 3, "UART_RX");
    inter.addPinToMCU("ESP32", 22, "I2C_SCL");
    inter.addPinToMCU("ESP32", 21, "I2C_SDA");
    inter.addPinToMCU("ESP32", 8, "DIGITAL_OUT1");
    inter.addPinToMCU("ESP32", 32, "PWM_OUT");
    inter.addPinToMCU("ESP32", 25, "DAC_OUT");
    inter.addPinToMCU("ESP32", 36, "DIGITAL_IN");

    inter.addCH446Q("CH446Q_1");
    inter.setCH446QPin("CH446Q_1", 'X', 0, 1);
    inter.setCH446QPin("CH446Q_1", 'X', 1, 0);
    inter.setCH446QPin("CH446Q_1", 'X', 4, 19);
    inter.setCH446QPin("CH446Q_1", 'X', 5, 18);
    inter.setCH446QPin("CH446Q_1", 'X', 8, 11);
    inter.setCH446QPin("CH446Q_1", 'X', 10, 12);
    inter.setCH446QPin("CH446Q_1", 'Y', 6, 6);
    inter.setCH446QPin("CH446Q_1", 'X', 2, 1);
    inter.setCH446QPin("CH446Q_1", 'X', 3, 3);
    inter.setCH446QPin("CH446Q_1", 'X', 6, 22);
    inter.setCH446QPin("CH446Q_1", 'X', 7, 21);
    inter.setCH446QPin("CH446Q_1", 'X', 9, 8);
    inter.setCH446QPin("CH446Q_1", 'X', 11, 32);
    inter.setCH446QPin("CH446Q_1", 'X', 12, 25);
    inter.setCH446QPin("CH446Q_1", 'Y', 7, 36);

    // Initialize peripherals
    inter.addPeripheral("Common UART");
    inter.addPinToPeripheral("Common UART", 0, "UART_TX");
    inter.addPinToPeripheral("Common UART", 1, "UART_RX");

    inter.addPeripheral("Common I2C");
    inter.addPinToPeripheral("Common I2C", 4, "I2C_SCL");
    inter.addPinToPeripheral("Common I2C", 5, "I2C_SDA");

    inter.addPeripheral("Onboard ESP32 UART");
    inter.addPinToPeripheral("Onboard ESP32 UART", 2, "UART_TX");
    inter.addPinToPeripheral("Onboard ESP32 UART", 3, "UART_RX");

    Serial.begin(115200); // Initialize serial communication
    displayMainScreen();
}

void loop() {
    if (serialMonitorMode) {
        handleSerialMonitor();
    } else if (mainScreen) {
        displayMainScreen();
    } else {
        handleMenuNavigation();
    }
}

void displayMainScreen() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Main Screen");
    lcd.setCursor(0, 1);
    lcd.print("Select for Menu");

    if (digitalRead(BUTTON_SELECT) == LOW) {
        mainScreen = false;
        currentMenu = 1;
        currentOption = 0;
        displayMenu();
    }
}

void displayMenu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (currentMenu) {
        case 1:
            lcd.print("1. Connect");
            lcd.setCursor(0, 1);
            lcd.print("2. Disconnect");
            lcd.setCursor(0, 2);
            lcd.print("3. Serial Monitor");
            break;
        case 2:
            lcd.print("Select MCU");
            lcd.setCursor(0, 1);
            lcd.print(inter.getMicrocontrollerName(currentOption));
            break;
        case 3:
            lcd.print("Select Peripheral");
            lcd.setCursor(0, 1);
            lcd.print(inter.getPeripheralName(currentOption));
            break;
        case 4:
            lcd.print("Select Connected Pair");
            lcd.setCursor(0, 1);
            // Display connected pairs
            break;
        case 5:
            lcd.print("Select MCU for Serial");
            lcd.setCursor(0, 1);
            lcd.print(inter.getMicrocontrollerName(currentOption));
            break;
    }
}

void handleMenuNavigation() {
    static bool backPressed = false;
    static bool forwardPressed = false;
    static bool selectPressed = false;
    static bool exitPressed = false;

    if (digitalRead(BUTTON_BACK) == LOW) {
        if (!backPressed) {
            currentOption--;
            if (currentOption < 0) {
                currentOption = 1; // Wrap around
            }
            displayMenu();
            backPressed = true;
        }
    } else {
        backPressed = false;
    }

    if (digitalRead(BUTTON_FORWARD) == LOW) {
        if (!forwardPressed) {
            currentOption++;
            if (currentOption > 1) {
                currentOption = 0; // Wrap around
            }
            displayMenu();
            forwardPressed = true;
        }
    } else {
        forwardPressed = false;
    }

    if (digitalRead(BUTTON_SELECT) == LOW) {
        if (!selectPressed) {
            if (currentMenu == 1) {
                currentMenu = 2;
            } else if (currentMenu == 2) {
                selectedMCU = currentOption;
                currentMenu = 3;
            } else if (currentMenu == 3) {
                selectedPeripheral = currentOption;
                connectPeripheral(selectedMCU, selectedPeripheral);
                mainScreen = true;
            } else if (currentMenu == 4) {
                // Handle disconnect
                mainScreen = true;
            } else if (currentMenu == 5) {
                selectedMCU = currentOption;
                connectToSerialMonitor(selectedMCU);
                serialMonitorMode = true;
                mainScreen = false;
                lcd.clear(); // Clear the screen for serial monitor mode
            }
            currentOption = 0;
            displayMenu();
            selectPressed = true;
        }
    } else {
        selectPressed = false;
    }

    if (digitalRead(BUTTON_EXIT) == LOW) {
                if (!exitPressed) {
                            exitPressed = true;
        }
    } else {
        exitPressed = false;
    }
}

void handleSerialMonitor() {
    if (Serial.available() > 0) {
        lcd.clear();
        String message = Serial.readStringUntil('\n');
        for (int i = 0; i < message.length() && i < 32; i++) {
            if (i < 16) {
                lcd.setCursor(i, 0);
            } else {
                lcd.setCursor(i - 16, 1);
            }
            lcd.print(message[i]);
        }
    }

    if (digitalRead(BUTTON_EXIT) == LOW) {
        serialMonitorMode = false;
        mainScreen = true;
        displayMainScreen();
        delay(200);
    }
}

void connectPeripheral(int mcuIndex, int peripheralIndex) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");

    String mcuName = inter.getMicrocontrollerName(mcuIndex);
    String peripheralName = inter.getPeripheralName(peripheralIndex);

    uint8_t mcuPinTX = inter.getPin(mcuName, "UART_TX");
    uint8_t mcuPinRX = inter.getPin(mcuName, "UART_RX");
    uint8_t peripheralPinTX = inter.getPeripheralPin(peripheralName, "UART_TX");
    uint8_t peripheralPinRX = inter.getPeripheralPin(peripheralName, "UART_RX");

    sendXYCommand(inter.getConnectionPoint(mcuName, mcuPinTX), inter.getConnectionPoint(peripheralName, peripheralPinTX), 1);
    sendXYCommand(inter.getConnectionPoint(mcuName, mcuPinRX), inter.getConnectionPoint(peripheralName, peripheralPinRX), 1);

    delay(1000);
}

void connectToSerialMonitor(int mcuIndex) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connecting to Serial...");

    String mcuName = inter.getMicrocontrollerName(mcuIndex);
    String onboardName = "Onboard ESP32 UART";

    uint8_t mcuPinTX = inter.getPin(mcuName, "UART_TX");
    uint8_t mcuPinRX = inter.getPin(mcuName, "UART_RX");
    uint8_t onboardPinTX = inter.getPeripheralPin(onboardName, "UART_TX");
    uint8_t onboardPinRX = inter.getPeripheralPin(onboardName, "UART_RX");

    sendXYCommand(inter.getConnectionPoint(mcuName, mcuPinTX), inter.getConnectionPoint(onboardName, onboardPinTX), 1);
    sendXYCommand(inter.getConnectionPoint(mcuName, mcuPinRX), inter.getConnectionPoint(onboardName, onboardPinRX), 1);

    delay(1000);
}

void sendXYCommand(ConnectionPoint from, ConnectionPoint to, int setOrClear) {
    int fromAddress = (from.type == X ? from.index : from.index + 16);
    int toAddress = (to.type == X ? to.index : to.index + 16);
    uint8_t address = (toAddress << 5) | (fromAddress << 1) | (setOrClear & 0x01);

    digitalWrite(CS_PIN, LOW);
    delayMicroseconds(10);
    SPI.transfer(address);
    delayMicroseconds(10);
    digitalWrite(STB_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(STB_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(CS_PIN, HIGH);
}
