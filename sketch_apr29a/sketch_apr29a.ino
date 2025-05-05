#include <Keypad.h>   //The library to use the keypad

//const is a keyword that is specific to a variable and is constant
const byte ROWS = 4; //The four rows
const byte COLS = 4; //The four columns

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


const int Password_Length = 4; //length of our password

String PASSKEY;//holds value

String Master = "1234";//Password



void setup() {
  
  Serial.begin(9600);
}

void loop() {
  //Get Key value when pressed
  char customkey = customKeypad.getKey();

 
  




// 3 - print if it is ok or not

 if(Master = "1234"){
  Serial.println("Correct, you may enter");
 }
 else {
  Serial.println("Incorrect");
 }


  


}