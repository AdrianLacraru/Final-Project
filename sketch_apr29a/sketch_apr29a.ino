#include <Keypad.h>  // Include the Keypad library to use 4x4 matrix keypad

// ========== Keypad Configuration ==========

// Define number of rows and columns on the keypad
const byte ROWS = 4;
const byte COLS = 4;

// Define the layout of keys on the 4x4 keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Define which Arduino pins are connected to the rows and columns
byte rowPins[ROWS] = {A0, A1, A2, A3}; // Connect keypad rows to analog pins A0–A3
byte colPins[COLS] = {5, 4, 3, 2};     // Connect keypad columns to digital pins 5–2

// Create keypad object from the Keypad library
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ========== Code Logic Variables ==========

String secretCode = "2580"; // The correct 4-digit code
String enteredCode = "";    // Stores the user-entered code

int attempts = 0;              // Counts the number of failed attempts
const int maxAttempts = 10;    // Maximum allowed failed attempts
bool locked = false;           // System lock status after too many failed attempts

// ========== Arduino Setup ==========

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  Serial.println("Enter 4-digit code, then press #:"); // Prompt user
}

// ========== Main Loop ==========

void loop() {
  // Only run the keypad logic if system is not locked
  if (!locked) {
    char key = keypad.getKey(); // Read key press from keypad

    if (key) { // If a key was actually pressed
      handleKeyPress(key); // Process that key press
    }
  }
}

// ========== Function: Handle Key Press ==========

void handleKeyPress(char key) {
  Serial.print("Pressed: ");
  Serial.println(key);

  if (key == '*') {
    // '*' clears the entered code
    enteredCode = "";
    Serial.println("Code cleared. Try again:");
  } 
  else if (key == '#') {
    // '#' submits the entered code for checking
    checkCode();
  } 
  else if (isDigit(key)) {
    // If a digit is pressed, add to entered code (up to 4 digits)
    if (enteredCode.length() < 4) {
      enteredCode += key;
    } else {
      Serial.println("Already entered 4 digits. Press # to submit or * to clear.");
    }
  }
}

// ========== Function: Check Code ==========

void checkCode() {
  if (enteredCode == secretCode) {
    // If entered code matches the secret, grant access
    Serial.println("Access Granted!");
    attempts = 0; // Reset attempt counter on success
  } else {
    // If code is incorrect, deny access and increment attempt counter
    attempts++;
    Serial.println("Access Denied!");
    Serial.print("Attempts: ");
    Serial.println(attempts);

    // Lock system if max attempts reached
    if (attempts >= maxAttempts) {
      lockSystem();
    }
  }

  // Clear entered code for next attempt
  enteredCode = "";
}

// ========== Function: Lock System ==========

void lockSystem() {
  Serial.println("User Error, Data Deleting in progress"); // Final message
  locked = true; // Prevent any further input
}