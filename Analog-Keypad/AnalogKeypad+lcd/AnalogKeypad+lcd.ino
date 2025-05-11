#include <Keypad.h>   //The library to use the keypad
#include <LiquidCrystal.h>  // Include the LiquidCrystal library for the LCD

//const is a keyword that is specific to a variable and is constant
const byte ROWS = 4; //The four rows
const byte COLS = 4; //The four columns

// Define the LCD pin connections: RS, Enable, Data4, Data5, Data6, Data7
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//defining the symbols of the botton keypads
char hexakeys [ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};  //Connecting to row pinouts of keypad
byte colPins[COLS] = {5, 4, 3, 2};  //connecting the column pinouts of  keypad

//Initialize NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexakeys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.begin(8, 2); // Initialize LCD type (x columns, y rows)
  Serial.begin(9600); // Start Serial Monitor for debugging output
}

void loop() {
  //Get Key value when pressed
  char customkey = customKeypad.getKey();

  if (customkey) {
    lcd.print(customkey);
    Serial.println("Correct, Welcome");
  }
}