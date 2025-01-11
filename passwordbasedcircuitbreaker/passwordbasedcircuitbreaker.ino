#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Define Keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};   // Connect keypad rows to these Arduino pins
byte colPins[COLS] = {5, 4, 3, 10};  // Column 3 is now assigned to pin 10

// Initialize Keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD address to 0x27 for a 20x4 display

// Define Relay Pins
const byte relayPins[] = {A0, A1, A2, A3}; // Analog pins for digital output to relays
bool relayStates[] = {false, false, false, false}; // Initial states of relays
bool isLocked = true; // Initial lock state

// Password Setup
const char* password = "1234"; // Change this to your desired password
char input[5];
byte inputPos = 0;

void setup() {
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");

  // Initialize Relays
  for (byte i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW); // Ensure all relays start off
  }
}

void loop() {
  char key = kpd.getKey();

  if (key) {
    if (isLocked) {
      // Password Input
      if (key == '#') {
        input[inputPos] = '\0'; // Null terminate
        if (strcmp(input, password) == 0) {
          isLocked = false;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Unlocked. Use 1-4");
          lcd.setCursor(0, 1);
          lcd.print("A for All, B for None");
          lcd.setCursor(0, 2);
          lcd.print("C to Lock, again.");
          inputPos = 0; // Reset for next unlock
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong Password!");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter Password:");
        }
        inputPos = 0; // Reset input position
      } else if (key == '*') {
        if (inputPos > 0) {
          inputPos--;
          input[inputPos] = '\0'; // Remove last character
        }
      } else if (inputPos < 4) {
        input[inputPos++] = key;
        input[inputPos] = '\0'; // Ensure null termination
        lcd.setCursor(inputPos, 1);
        lcd.print("*"); // Display * for each input character
      }
    } else {
      // Actions when Unlocked
      if (key >= '1' && key <= '4') {
        byte relayIndex = key - '1'; // Convert '1' to 0, '2' to 1, etc.
        relayStates[relayIndex] = !relayStates[relayIndex];
        digitalWrite(relayPins[relayIndex], relayStates[relayIndex] ? HIGH : LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Relay ");
        lcd.print(key);
        lcd.print(relayStates[relayIndex] ? " ON" : " OFF");
      } else if (key == 'A') {
        for (byte i = 0; i < 4; i++) {
          relayStates[i] = true;
          digitalWrite(relayPins[i], HIGH);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("All Relays ON");
      } else if (key == 'B') {
        for (byte i = 0; i < 4; i++) {
          relayStates[i] = false;
          digitalWrite(relayPins[i], LOW);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("All Relays OFF");
      } else if (key == 'C') {
        isLocked = true;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("System Locked");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:");
      }
    }
  }
}
