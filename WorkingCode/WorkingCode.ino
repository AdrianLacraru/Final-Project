#include <Keypad.h>           // Includes the library for the keypad
#include <LiquidCrystal.h>    // Includes the library for the LCD display

// LCD setup: rs, en, d4, d5, d6, d7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);   // Directly connects the LCD setup to the appropriate pins

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

// Tells Arduino the character for each key press
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Connects the rows and colons to the appropriate pins
byte rowPins[ROWS] = { A0, A1, A2, A3 };
byte colPins[COLS] = { 5, 4, 3, 2 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password logic
const String password = "1234";   // Required password
String input = "";                // Password typed into by the user

int attempts = 0;           // counts failed attempts
const int maxAttempts = 3;  // max attempts before lockout
bool locked = false;        // lockout

// Function to reset input and prompt user
void clearInput() {
  input = "";
  lcd.clear();
  if (!locked) {
    lcd.print("try again:");
  }
}

// Function to check if entered input is correct
void checkPassword() {
  lcd.clear();
  if (input == password) {
    lcd.print("Correct");
    attempts = 0;  // Reset attempts on success
    delay(1500);
    lcd.clear();
    lcd.print("Welcome");
    lcd.setCursor(0, 1);
    lcd.print("Adrian & Jose");
    delay(2000);

  } else {
    attempts++;
    lcd.print("Incorrect");
    delay(1500);
    clearInput();

    if (attempts >= maxAttempts) {
      lcd.clear();
      lcd.print("LOCKED OUT");
      lcd.setCursor(0, 1);
      lcd.print("try again in 24h");
      locked = true;
      delay(86400000);
      clearInput();
    }
  }

  delay(2000);
}

void setup() {
  lcd.begin(8, 2);  // Initialize LCD
  lcd.clear();
  lcd.print("Enter Password:");
}

void loop() {
  if (locked) return;  // Stop if user is locked out

  char key = keypad.getKey();  // Read key

  if (key) {
    if (key == '*') {
      clearInput();
    } else if (key == '#') {
      checkPassword();
    } else if (input.length() < 4 && isDigit(key)) {
      input += key;
      lcd.setCursor(input.length() - 1, 1);  // Masked input row
      lcd.print("*");
    }
  }
}
