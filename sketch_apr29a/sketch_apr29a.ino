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
int attempts = 10;           // counts failed attempts
const int maxAttempts = 10; // max allowed before "lockout"
bool locked = false;        // flag to disable further checks

void setup() {
  Serial.begin(9600);
  Serial.println("Enter 4-digit code, then press #:");
}

void loop() {
  if (locked) {
    // Do nothing if user has failed 10 times
    return;
  }

  char key = keypad.getKey();

  if (key) {
    Serial.print("Pressed: ");
    Serial.println(key);
  }
    if (key == '*') {
      enteredCode = "";
      Serial.println("Code cleared. Try again:");
    }
     
    else if (key == '#') {
       if (enteredCode == secretCode) {
         Serial.println("Access Granted!");
         attempts = 0; // reset attempts if correct
       }  
         
       else {
         attempts++;
         Serial.println("Access Denied!");
         Serial.print("Attempts: ");
         Serial.println(attempts);
       }

       if (attempts >= maxAttempts) {
         Serial.println("User Error, Data Deleting in progress........");
         locked = true;
       }
        enteredCode = ""; // clear for next try
    }

    else if (isDigit(key)) {
      if (enteredCode.length() < 4) {
        enteredCode += key;
      } 
      
      else {
        Serial.println("Already entered 4 digits. Press # or *.");
      }
    }
}

