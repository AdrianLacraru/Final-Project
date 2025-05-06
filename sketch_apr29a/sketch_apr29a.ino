#include <Keypad.h>  //The library to use the keypad

//const is a keyword that is specific to a variable and is constant
const byte ROWS = 4;  //The four rows
const byte COLS = 4;  //The four columns

//defining the symbols of the botton keypads
char hexakeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { A0, A1, A2, A3 };  //Connecting to row pinouts of keypad
byte colPins[COLS] = { 5, 4, 3, 2 };      //connecting the column pinouts of  keypad

//Initialize NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexakeys), rowPins, colPins, ROWS, COLS);


const String correctCode = "1234";  //The 4 digit code that will grant access
String inputCode = "";


void setup() {
  Serial.begin(9600);  //Setting up the serial monitor for troubleshooting/debugging
}

void loop() {
  //Get Key value when pressed
  char key = customKeypad.getKey();


  if (key != NO_KEY) {
    Serial.print("Key Pressed: "); //Command to the user
    Serial.println(key);
  }

  if (key == '#') {  // '#' = submit

    if (inputCode == correctCode) {
      Serial.println("Access Granted!"); //when code is right
    } 

    else {
      Serial.println("Access Denied!"); //When code is wrong
    }
    inputCode = "";         // reset input
   
  }
    else if (key == '*') {  // '*' = clear
      inputCode = "";
      Serial.println("Input Cleared.");
    } 

  else if (isDigit(key)) {
  }  

    if (inputCode.length() < 4) { //if a number between 0-9 are pressed and input is less than 4 charactors it will be outputed
      inputCode += key;
    }
  
}
