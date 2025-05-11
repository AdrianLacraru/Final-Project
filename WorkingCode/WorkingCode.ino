#include <Keypad.h>           // Includes the library for the keypad
#include <LiquidCrystal.h>    // Includes the library for the LCD display

// LCD setup: rs, en, d4, d5, d6, d7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);   // Directly connects the LCD setup to the appropriate pins

// Keypad setup
const byte ROWS = 4; //Number of rows
const byte COLS = 4; //Nomber of columns

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

// Create Keypad object using pins connected to Keypad colomns
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password logic
const String password = "1234";   // Required password
String input = "";                // Password typed into by the user

int attempts = 0;           // counts failed attempts
const int maxAttempts = 3;  // max attempts before lockout
bool locked = false;        // lockout

// -------- Function: clearInput -------- //
// Resets the user input and updates LCD to allow retry
void clearInput() {
  input = "";        // Clear input string
  lcd.clear();       // Clear LCD display
  if (!locked) {
    lcd.print("try again:"); // Prompt for retry if not locked
  } 
}

// -------- Function: checkPassword -------- //
// Compares input to the password and updates system accordingly
void checkPassword() {
  lcd.clear();


  if (input == password) {
    lcd.print("Correct");
    attempts = 0;  // Reset attempts on success
    delay(1500);
    lcd.clear();   
    lcd.print("Welcome");  // Show welcome message
    lcd.setCursor(0, 1);   // Move to second line
    lcd.print("Adrian & Jose");
    delay(2000);  // Pause before restart

  } else {        // If input is wrong
    attempts++;   // Increment attempt count
    lcd.print("Incorrect");  // Show error
    delay(1500);
    clearInput(); // Reset input and prompt again

    if (attempts >= maxAttempts) {   // Lock system if max attempts reached
      lcd.clear(); 
      lcd.print("LOCKED OUT"); // Notify user
      lcd.setCursor(0, 1);
      lcd.print("try again in 24h");
      locked = true;      // Set locked status
      delay(86400000);    // 24-hour lockout delay
      clearInput();       // Reset after delay
    }
  }

  delay(2000);  // Delay to give time to read output
}

// -------- Function: setup -------- //
// Runs once when the device powers up
void setup() {
  lcd.begin(8, 2);  // Initialize LCD
  lcd.clear();      // Clear the display
  lcd.print("Enter Password:");  // Initial prompt
}

// -------- Function: loop -------- //
// Repeats continuously; handles keypad input and system logic
void loop() {
  if (locked) return;  // Stop if user is locked out

  char key = keypad.getKey();  // Read key

  if (key) {
    if (key == '*') {    // If a key is pressed
      clearInput();      // If clear key
    } else if (key == '#') {  // Reset input
      checkPassword();        // Check the password
    } else if (input.length() < 4 && isDigit(key)) {
      input += key;   // Add digit to input
      lcd.setCursor(input.length() - 1, 1);  // Set cursor to next position
      lcd.print("*"); // Mask digit with asterisk
    }
  }
}