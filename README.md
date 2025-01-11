# Password-based-circuit-breaker-
# Overview
This project implements a password-protected circuit breaker using an Arduino Uno, a 4x4 keypad, an I2C LCD screen, and a 4-channel relay module. The system is designed to control multiple electrical loads securely, with operations restricted by a user-defined password. The circuit can manage up to four loads and provides the flexibility to lock/unlock the system and turn individual or all loads on/off.

# Features
**Password Protection:**

Requires a password for unlocking the system.
Only the correct password grants access to the control functions.
**Load Control:**

Individual Control: Use the keypad to turn on/off specific loads (1–4).
All On/Off: Turn all loads on (A) or off (B) at once.
Locking Mechanism:

Press C to lock the system. All loads are switched off, and further control requires re-entering the password.
LCD Display:

Provides real-time feedback for password input and load status, enhancing user experience.
Hardware Requirements
Arduino Uno (or compatible board)
4-Channel Relay Module
I2C 16x2 LCD
4x4 Keypad
Electrical Loads (e.g., lights, fans)
Power Supply (suitable for Arduino and relays)

# Connections
Relay Module
Relay Pin	Arduino Pin	Function
IN1	Pin 2	Control Load 1
IN2	Pin 3	Control Load 2
IN3	Pin 4	Control Load 3
IN4	Pin 5	Control Load 4
VCC	5V	Power for the relays
GND	GND	Common ground
Keypad
Keypad Pin	Arduino Pin	Function
R1	Pin 9	Row 1
R2	Pin 8	Row 2
R3	Pin 7	Row 3
R4	Pin 6	Row 4
C1	Pin 5	Column 1
C2	Pin 4	Column 2
C3	Pin 3	Column 3
C4	Pin 2	Column 4
I2C LCD
LCD Pin	Arduino Pin	Function
SDA	A4	I2C Data Line
SCL	A5	I2C Clock Line
VCC	5V	Power for the LCD
GND	GND	Common ground
Code Explanation
The project code is divided into several functional blocks:

# Setup:

Initializes the LCD and sets up the relay pins as outputs.
Starts the system in a locked state (lockSystem function).
**Password Input:**

Prompts the user to enter the password using the keypad.
Validates the input and unlocks the system if the password matches.
Displays appropriate messages for correct and incorrect attempts.
Load Control:

**Allows users to:**
Turn individual loads on/off (1–4 keys).
Turn all loads on (A) or off (B).
Updates the LCD to display the current action.
Locking Mechanism:

Locks the system when C is pressed.
Turns off all loads and clears the password input.
How It Works
**Startup:**

The LCD displays "Enter Password".
The user enters the password using the keypad. Correct input unlocks the system.
**Load Control:**

**While unlocked, users can:**
Press 1–4 to turn on specific loads.
Press A to turn all loads on or B to turn all loads off.
Locking the System:

Pressing C locks the system. All loads are turned off, and further operations require re-entering the password.
