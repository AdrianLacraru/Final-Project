#include <Keypad.h>

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Code logic
String secretCode = "2580";
String enteredCode = "";
int attempts = 0;           // counts failed attempts
const int maxAttempts = 10; // max allowed before "lockout"
bool locked = false;        // flag to disable further checks

void setup() {
  Serial.begin(9600);
  Serial.println("Enter 4-digit code, then press #:");
}

void loop() {
  if (!locked) {
    char key = keypad.getKey();
    if (key) {
      handleKeyPress(key);
    }
  }
}

// ========== FUNCTIONS ==========
// Handles a single key press
void handleKeyPress(char key) {
  Serial.print("Pressed: ");
  Serial.println(key);

  if (key == '*') {
    enteredCode = "";
    Serial.println("Code cleared. Try again:");
  }
  else if (key == '#') {
    checkCode();
  }
  else if (isDigit(key)) {
    if (enteredCode.length() < 4) {
      enteredCode += key;
    } else {
      Serial.println("Already entered 4 digits. Press # or *.");
    }
  }
}

// Checks if the entered code is correct
void checkCode() {
  if (enteredCode == secretCode) {
    Serial.println("Access Granted!");
    attempts = 0;
  } else {
    attempts++;
    Serial.println("Access Denied!");
    Serial.print("Attempts: ");
    Serial.println(attempts);

    if (attempts >= maxAttempts) {
      lockSystem();
    }
  }
  enteredCode = ""; // reset code after check
}

// Locks the system after too many failed attempts
void lockSystem() {
  Serial.println("User Error, Data Deleting in progress");
  locked = true;
}