#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include "DummyInterconnector.h"

// LCD and button definitions
#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_ROWS    2
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

#define BUTTON_BACK   34
#define BUTTON_SELECT 35
#define BUTTON_EXIT   32
#define BUTTON_FORWARD 33

// Dummy Interconnector instance
DummyInterconnector inter;

bool mainScreen = true;
bool serialMonitorMode = false;
int currentMenu = 1;  // Start at menu 1
int currentOption = 0;
int selectedMCU = -1;
int selectedPeripheral = -1;

bool displayNeedsUpdate = true;
bool debugMode = true;

volatile bool backButtonPressed = false;
volatile bool selectButtonPressed = false;
volatile bool exitButtonPressed = false;
volatile bool forwardButtonPressed = false;

void IRAM_ATTR handleBackButtonISR() {
    backButtonPressed = true;
}

void IRAM_ATTR handleSelectButtonISR() {
    selectButtonPressed = true;
}

void IRAM_ATTR handleExitButtonISR() {
    exitButtonPressed = true;
}

void IRAM_ATTR handleForwardButtonISR() {
    forwardButtonPressed = true;
}

void setup() {
    // Initialize LCD and buttons
    lcd.init();
    lcd.backlight();
    pinMode(BUTTON_BACK, INPUT_PULLUP);
    pinMode(BUTTON_SELECT, INPUT_PULLUP);
    pinMode(BUTTON_EXIT, INPUT_PULLUP);
    pinMode(BUTTON_FORWARD, INPUT_PULLUP);

    Serial.begin(115200);

    // Initialize microcontrollers and peripherals using DummyInterconnector
    inter.addMicrocontroller("Arduino Nano");
    inter.addPinToMCU("Arduino Nano", 1, "UART_TX", 'X', 0);
    inter.addPinToMCU("Arduino Nano", 0, "UART_RX", 'X', 1);
    inter.addPinToMCU("Arduino Nano", 19, "I2C_SCL", 'X', 4);
    inter.addPinToMCU("Arduino Nano", 18, "I2C_SDA", 'X', 5);
    inter.addPinToMCU("Arduino Nano", 11, "DIGITAL_OUT1", 'X', 8);
    inter.addPinToMCU("Arduino Nano", 12, "DIGITAL_OUT2", 'X', 10);
    inter.addPinToMCU("Arduino Nano", 6, "ANALOG_IN");

    inter.addMicrocontroller("ESP32");
    inter.addPinToMCU("ESP32", 1, "UART_TX", 'X', 2);
    inter.addPinToMCU("ESP32", 3, "UART_RX", 'X', 3);
    inter.addPinToMCU("ESP32", 22, "I2C_SCL", 'X', 6);
    inter.addPinToMCU("ESP32", 21, "I2C_SDA", 'X', 7);
    inter.addPinToMCU("ESP32", 8, "DIGITAL_OUT1", 'X', 9);
    inter.addPinToMCU("ESP32", 32, "PWM_OUT", 'X', 11);
    inter.addPinToMCU("ESP32", 25, "DAC_OUT", 'X', 12);
    inter.addPinToMCU("ESP32", 36, "DIGITAL_IN", 'Y', 7);

    inter.addCH446Q("CH446Q_1");

    // Initialize peripherals and their mapping
    inter.addPeripheral("Common UART");
    inter.addPinToPeripheral("Common UART", 0, "UART_TX", 'Y', 0);
    inter.addPinToPeripheral("Common UART", 1, "UART_RX", 'Y', 1);

    inter.addPeripheral("Common I2C");
    inter.addPinToPeripheral("Common I2C", 4, "I2C_SCL", 'Y', 4);
    inter.addPinToPeripheral("Common I2C", 5, "I2C_SDA", 'Y', 5);

    inter.addPeripheral("Onboard ESP32 UART");
    inter.addPinToPeripheral("Onboard ESP32 UART", 2, "UART_TX", 'Y', 2);
    inter.addPinToPeripheral("Onboard ESP32 UART", 3, "UART_RX", 'Y', 3);

    // Attach interrupts
    attachInterrupt(digitalPinToInterrupt(BUTTON_BACK), handleBackButtonISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_SELECT), handleSelectButtonISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_EXIT), handleExitButtonISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_FORWARD), handleForwardButtonISR, FALLING);

    displayMainScreen();
    if (debugMode) Serial.println("Setup complete");
}

void loop() {
    if (backButtonPressed) {
        handleBackButton();
        backButtonPressed = false;
        if (debugMode) Serial.println("Back button pressed");
    }
    if (selectButtonPressed) {
        handleSelectButton();
        selectButtonPressed = false;
        if (debugMode) Serial.println("Select button pressed");
    }
    if (exitButtonPressed) {
        handleExitButton();
        exitButtonPressed = false;
        if (debugMode) Serial.println("Exit button pressed");
    }
    if (forwardButtonPressed) {
        handleForwardButton();
        forwardButtonPressed = false;
        if (debugMode) Serial.println("Forward button pressed");
    }

    if (serialMonitorMode) {
        handleSerialMonitor();
    } else if (mainScreen) {
        displayMainScreen();
    } else {
        handleMenuNavigation();
    }
}

void displayMainScreen() {
    if (displayNeedsUpdate) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Main Screen");
        lcd.setCursor(0, 1);
        lcd.print("Select for Menu");
        displayNeedsUpdate = false;
    }
}

void displayMenu() {
    if (displayNeedsUpdate) {
        if (debugMode) Serial.println("Displaying menu");
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
            default:
                if (debugMode) Serial.println("Invalid menu option");
                break;
        }
        displayNeedsUpdate = false;
    }
}
void handleMenuNavigation() {
    if (currentMenu == 1) {
        // Navigate through the main menu
        if (currentOption == 0) {
            currentMenu = 2; // Select MCU
            currentOption = 0;
        } else if (currentOption == 1) {
            currentMenu = 4; // Disconnect
            currentOption = 0;
        } else if (currentOption == 2) {
            currentMenu = 5; // Serial Monitor
            currentOption = 0;
        }
        displayNeedsUpdate = true;
    } else if (currentMenu == 2 || currentMenu == 3 || currentMenu == 4 || currentMenu == 5) {
        displayMenu();
    }
}

void handleBackButton() {
    currentOption--;
    if (currentOption < 0) {
        currentOption = 1; // Wrap around
    }
    displayNeedsUpdate = true;
    displayMenu();
}

void handleSelectButton() {
    if (currentMenu == 1) {
        currentMenu = 2;
    } else if (currentMenu == 2) {
        selectedMCU = currentOption;
        currentMenu = 3;
    } else if (currentMenu == 3) {
        selectedPeripheral = currentOption;
        connectPeripheral(selectedMCU, selectedPeripheral);
        resetMenu();
    } else if (currentMenu == 4) {
        selectedPeripheral = currentOption;
        disconnectPeripheral(selectedMCU, selectedPeripheral);
        resetMenu();
    } else if (currentMenu == 5) {
        selectedMCU = currentOption;
        connectToSerialMonitor(selectedMCU);
        serialMonitorMode = true;
        mainScreen = false;
        displayNeedsUpdate = true;
        lcd.clear(); // Clear the screen for serial monitor mode
    }
}

void handleExitButton() {
    if (currentMenu > 1) {
        currentMenu--;
    } else {
        mainScreen = true;
    }
    currentOption = 0;
    displayNeedsUpdate = true;
    displayMenu();
}

void handleForwardButton() {
    currentOption++;
    if (currentOption > 1) {
        currentOption = 0; // Wrap around
    }
    displayNeedsUpdate = true;
    displayMenu();
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

    if (exitButtonPressed) {
        serialMonitorMode = false;
        mainScreen = true;
        displayNeedsUpdate = true;
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

    if (debugMode) {
        Serial.println("Connecting " + mcuName + " UART_TX to " + peripheralName + " UART_TX");
        Serial.println("Connecting " + mcuName + " UART_RX to " + peripheralName + " UART_RX");
    }

    delay(1000);
}

void disconnectPeripheral(int mcuIndex, int peripheralIndex) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Disconnecting...");

    String mcuName = inter.getMicrocontrollerName(mcuIndex);
    String peripheralName = inter.getPeripheralName(peripheralIndex);

    uint8_t mcuPinTX = inter.getPin(mcuName, "UART_TX");
    uint8_t mcuPinRX = inter.getPin(mcuName, "UART_RX");
    uint8_t peripheralPinTX = inter.getPeripheralPin(peripheralName, "UART_TX");
    uint8_t peripheralPinRX = inter.getPeripheralPin(peripheralName, "UART_RX");

    if (debugMode) {
        Serial.println("Disconnecting " + mcuName + " UART_TX from " + peripheralName + " UART_TX");
        Serial.println("Disconnecting " + mcuName + " UART_RX from " + peripheralName + " UART_RX");
    }

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

    if (debugMode) {
        Serial.println("Connecting " + mcuName + " UART_TX to " + onboardName + " UART_TX");
        Serial.println("Connecting " + mcuName + " UART_RX to " + onboardName + " UART_RX");
    }

    delay(1000);
}

void resetMenu() {
    currentMenu = 1;
    mainScreen = true;
    displayNeedsUpdate = true;
    displayMainScreen();
}
