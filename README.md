# Final-Project
Objectif: I want to type a PIN into a keypad, and I will be informed on if the PIN typed in is correct or not, and after a certain amount of failed attempts, the system will lock down for a period of time.


## Components:
Arduino Uno

Keypad (Membrane Switch)

LCD display (LCD 1602 Module)

## Basic Assembly Diagram

![image](https://github.com/user-attachments/assets/02fbb1ba-434a-4bf1-bad0-2385b1f60566)



### Connect the LCD module:
•	RS to Digital Pin 7

•	EN to Digital Pin 8

•	D4 to Digital Pin 9

•	D5 to Digital Pin 10

•	D6 to Digital Pin 11

•	D7 to Digital Pin 12

•	VSS to GND

•	VDD to 5V

•	VO to 1kΩ resistor to GND

•	RW to GND

•	A (Backlight +) to 5V

•	K (Backlight -) to GND


### Analog-ins-Keypad

ROWS to A0, A1, A2, A3

COLS to D5, D4, D3, D2

![image](https://github.com/user-attachments/assets/528eccf3-1be1-4738-8b87-899a2bf92ea0)
