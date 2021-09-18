#include <LiquidCrystal.h>

// Custom character definitions
byte jtChar[8] = { 0b11100,0b01000,0b01000,0b11000,0b00111,0b00010,0b00010,0b00010 };
byte eeChar[8] = { 0b01000,0b10100,0b11100,0b10010,0b01101,0b00111,0b00100,0b00011 };
byte rcChar[8] = { 0b11000,0b10100,0b11000,0b10100,0b00011,0b00100,0b00100,0b00011 };
byte ohChar[8] = { 0b01100,0b10010,0b10010,0b01100,0b00000,0b00101,0b00111,0b00101 };
byte mChar[8]  = { 0b01010,0b10101,0b10101,0b10101,0b00000,0b00000,0b00000,0b00000 };
byte eChar[8]  = { 0b00100,0b01010,0b01110,0b01000,0b00110,0b00000,0b00000,0b00000 };

// Potentiometer pin number
int potentiometer = 14;

// Pins for LCD module control
int VE = 2;
int rs = 3;
int rw = 4;
int enable = 5;
int d0 =  6; int d1 =  7; int d2 =  8; int d3 =  9;
int d4 = 10; int d5 = 11; int d6 = 12; int d7 = 13;

// Create LiquidCrystal object for managing LCD
LiquidCrystal lcd(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);

void setup() {
  // Data out through contrast pin
  pinMode(VE, OUTPUT);
  // Data in from potentiometer pin
  pinMode(potentiometer, INPUT);

  // Start LCD and add custom characters
  lcd.begin(16,2);
  lcd.createChar(0, jtChar);
  lcd.createChar(1, eeChar);
  lcd.createChar(2, rcChar);
  lcd.createChar(3, ohChar);
  lcd.createChar(4, mChar);
  lcd.createChar(5, eChar);
  
  // Print "Join Tech Club!" starting from top-left corner
  lcd.setCursor(0, 0);
  lcd.print("Join Tech Club!");

  // Print @JEROMETECH starting from bottom-left corner using custom characters
  lcd.setCursor(0, 1);
  lcd.print("@");
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.write(byte(4));
  lcd.write(byte(5));

  // Start serial and set timeout to 2 ms so that the potentiometer is responsive while giving time for new bytes to be sent
  Serial.begin(9600);
  Serial.setTimeout(2);
}



int contrast = 30;
bool useSerialNumbers = false; // Tracks whether contrast should be set by serial input or potentiometer

void loop() {
  // Reset temp and check for input
  int temp = 0;
  temp = Serial.parseInt();

  // If temp is a positive number, set contrast to temp
  if(temp > 0)
  {
    contrast = temp;
    useSerialNumbers = true;
  }
  // If temp is -1, go back to using potentiometer for contrast
  else if(useSerialNumbers && temp == -1)
    useSerialNumbers = false;
  // If temp is -2, set first line to user input
  else if(temp == -2)
  {
    // Clear first line
    lcd.setCursor(0,0);
    lcd.print("                ");
    
    // Wait for input and show rolling dots
    int dotCount = 0;
    while(Serial.available() == 0)
    {
      dotCount++;
      // After 3 dots, clear line
      if(dotCount == 3)
      {
        dotCount = 0;
        lcd.setCursor(0,0);
        lcd.print("   ");
        lcd.setCursor(0,0);
      }

      // Print dot and wait 1 second
      lcd.print(".");
      delay(1000);
    }

    // Print input, if any
    lcd.setCursor(0,0);
    lcd.print(Serial.readStringUntil('\n'));
  }

  // Get potentiometer's value
  int potVal = analogRead(potentiometer) * 0.22;
  // Write relevant contrast value to contrast pin
  analogWrite(VE, useSerialNumbers ? contrast : potVal);
  
  delay(1);
}
