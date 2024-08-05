#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD and button definitions
#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_ROWS    2
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

#define BUTTON_BACK   34
#define BUTTON_SELECT 35
#define BUTTON_EXIT   32
#define BUTTON_FORWARD 33

// Enum for connection point type
enum PointType {
  X,
  Y
};

// Struct for connection point
struct ConnectionPoint {
  PointType type;
  int index;
}; // Added missing semicolon

// Struct for pin
struct Pin {
  ConnectionPoint connectionPoint;
  bool connected;
  String connectedTo;
}; // Added missing semicolon

// Struct for microcontroller
struct Microcontroller {
  String name;
  Pin pins[16];
}; // Added missing semicolon

// Struct for peripheral
struct Peripheral {
  String name;
  Pin pins[8];
}; // Added missing semicolon

// Arrays to store microcontrollers and peripherals
Microcontroller microcontrollers[6];
Peripheral spiPeripherals[6];
Peripheral i2cPeripherals[6];
Peripheral uartPeripherals[6];
Microcontroller onboardESP32;

bool mainScreen = true;
bool serialMonitorMode = false;
int currentMenu = 0;
int currentOption = 0;
int selectedMCU = -1;
int selectedPeripheral = -1;
int selectedPin = -1;

void setup() {
  // Initialize LCD and buttons
  lcd.init();
  lcd.backlight();
  pinMode(BUTTON_BACK, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_EXIT, INPUT_PULLUP);
  pinMode(BUTTON_FORWARD, INPUT_PULLUP);

  // Initialize onboard ESP32 pins
  onboardESP32.name = "ESP32";
  for (int i = 0; i < 2; i++) { // Only consider the first two pins for serial (TX/RX)
    onboardESP32.pins[i].connectionPoint.type = (i == 0) ? X : Y;
    onboardESP32.pins[i].connectionPoint.index = i;
    onboardESP32.pins[i].connected = false;
    onboardESP32.pins[i].connectedTo = "";
  }

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
      lcd.print(microcontrollers[currentOption].name);
      break;
    case 3:
      lcd.print("Select Peripheral");
      lcd.setCursor(0, 1);
      lcd.print(getPeripheralName(currentOption));
      break;
    case 4:
      lcd.print("Select Connected Pair");
      lcd.setCursor(0, 1);
      // Display connected pairs
      break;
    case 5:
      lcd.print("Select MCU for Serial");
      lcd.setCursor(0, 1);
      lcd.print(microcontrollers[currentOption].name);
      break;
  }
}

String getPeripheralName(int option) {
  // Return the appropriate peripheral name based on the current selection
  if (currentMenu == 3) return spiPeripherals[option].name;
  else if (currentMenu == 4) return i2cPeripherals[option].name;
  else if (currentMenu == 5) return uartPeripherals[option].name;
  return "";
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
        currentOption = 5; // Wrap around
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
      if (currentOption > 5) {
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
        selectedPin = 0; // Start with the first pin
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
      if (currentMenu > 1) {
        currentMenu--;
      } else {
        mainScreen = true;
      }
      currentOption = 0;
      displayMenu();
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

  Peripheral* peripheral = nullptr;
  if (currentMenu == 3) peripheral = &spiPeripherals[peripheralIndex];
  else if (currentMenu == 4) peripheral = &i2cPeripherals[peripheralIndex];
  else if (currentMenu == 5) peripheral = &uartPeripherals[peripheralIndex];

  for (int i = 0; i < 8; i++) {
    if (!microcontrollers[mcuIndex].pins[i].connected && !peripheral->pins[i].connected) {
      microcontrollers[mcuIndex].pins[i].connected = true;
      microcontrollers[mcuIndex].pins[i].connectedTo = peripheral->name;
      peripheral->pins[i].connected = true;
      peripheral->pins[i].connectedTo = microcontrollers[mcuIndex].name;

      sendXYCommand(microcontrollers[mcuIndex].pins[i].connectionPoint, peripheral->pins[i].connectionPoint, 1);
    }
  }

  delay(1000);
}

void connectToSerialMonitor(int mcuIndex) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to Serial...");

  for (int i = 0; i < 2; i++) { // Only consider the first two pins for serial (TX/RX)
    if (!microcontrollers[mcuIndex].pins[i].connected && !onboardESP32.pins[i].connected) {
      microcontrollers[mcuIndex].pins[i].connected = true;
      microcontrollers[mcuIndex].pins[i].connectedTo = onboardESP32.name;
      onboardESP32.pins[i].connected = true;
      onboardESP32.pins[i].connectedTo = microcontrollers[mcuIndex].name;

      sendXYCommand(microcontrollers[mcuIndex].pins[i].connectionPoint, onboardESP32.pins[i].connectionPoint, 1);
    }
  }

  delay(1000);
}

void sendXYCommand(ConnectionPoint from, ConnectionPoint to, int setOrClear) {
  int fromAddress = (from.type == X ? from.index : from.index + 16);
  int toAddress = (to.type == X ? to.index : to.index + 16);
  uint8_t address = (toAddress << 5) | (fromAddress << 1) | (setOrClear & 0x01);

  // Simulate SPI communication with debug prints
  Serial.print("SPI Command: ");
  Serial.println(address, BIN);
}
