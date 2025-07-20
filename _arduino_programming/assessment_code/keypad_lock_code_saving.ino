//add hints
//lights?
//servo for actual lock?
//make a safe thing out of mdf or smth, laser cut
//solder final thing together at home ehehehehe
//can use for assessment, document what i have here before making changes 
#include <LiquidCrystal.h>
#include <EEPROM.h>  //code is stored here
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int digitamount = EEPROM.read(0);
int currentdigit = 0;
int correctdigits = 0;
bool locked = true;
bool settingcode = false;
int input = 10;
int digitsset = 0;
void setup() {
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Enter Code");
  delay(1000);
  lcd.clear();
}
void loop() {
  int keyset1 = analogRead(A3);  // read the resistor arrays
  int keyset2 = analogRead(A2);
  int keyset3 = analogRead(A1);
  int keyset4 = analogRead(A0);
  // keyset1 declaration. repeat for others, then build functions
  if (keyset1 == 1023) {
    input = 3;
  } else if (keyset1 >= 990 && keyset1 <= 1010) {
    input = 2;
  } else if (keyset1 >= 505 && keyset1 <= 515) {
    input = 1;
  } else if (keyset2 == 1023) {
    input = 6;
  } else if (keyset2 >= 990 && keyset2 <= 1010) {
    input = 5;
  } else if (keyset2 >= 505 && keyset2 <= 515) {
    input = 4;
  } else if (keyset3 == 1023) {
    input = 9;
  } else if (keyset3 >= 990 && keyset3 <= 1010) {
    input = 8;
  } else if (keyset3 >= 505 && keyset3 <= 515) {
    input = 7;
  } else if (keyset4 == 1023) {  // check if code is correct or lock box when unlocked
    lcd.clear();
    lcd.setCursor(0, 0);
    if (currentdigit == digitamount && correctdigits == digitamount) {  // if correct
      locked = false;
      lcd.print("Code correct!");
      // move servo
      delay(1000);
    } else if (locked == false && settingcode == false) {  // if pressing when unlocked
      locked = true;
      lcd.print("Box locked!");
      // move servo to locked
      delay(1000);
      lcd.clear();
      lcd.print("Enter Code");
      delay(1000);
      lcd.clear();
    } else if (settingcode == true) {  // if attempting to lock when setting code then failsafe
      lcd.print("Set A Code First");
      delay(1000);
      lcd.clear();
      EEPROM.update(0, 4);
      digitamount = 4;
      EEPROM.update(1, 0);
      EEPROM.update(2, 0);
      EEPROM.update(3, 0);
      EEPROM.update(4, 0);
    } else {  // if not correct
      lcd.print("Wrong code!");
      delay(1000);
      lcd.clear();
      lcd.print("Enter Code");
      delay(1000);
      lcd.clear();
    }
    input = 10;
    correctdigits = 0;
    currentdigit = 0;
  } else if (keyset4 >= 990 && keyset4 <= 1010) {  // setting a code
    if (locked == false) {
      if (settingcode == false) {
        settingcode = true;
        lcd.clear();
        lcd.print("Set A Code!");
        delay(1000);
        lcd.clear();
      } else if (digitsset >= 4) {  // if code is valid
        settingcode = false;
        lcd.clear();
        lcd.print("Code Set!");
        delay(1000);
        lcd.clear();
        digitamount = digitsset;
        EEPROM.update(0, digitamount);
      } else {  // if invalid code
        lcd.clear();
        lcd.print("Invalid Code!");
        delay(1000);
        lcd.clear();
        EEPROM.update(0, 4);
        digitamount = 4;
        EEPROM.update(1, 0);
        EEPROM.update(2, 0);
        EEPROM.update(3, 0);
        EEPROM.update(4, 0);
      }
    } else {
      lcd.clear();
      lcd.print("Unlock First!");
      delay(1000);
      lcd.clear();
      lcd.print("Enter Code");
      delay(1000);
      lcd.clear();
    }
    digitsset = 0;
    currentdigit = 0;
    correctdigits = 0;
    delay(300);
  } else if (keyset4 >= 505 && keyset4 <= 515) {
    input = 0;
  } else {
    input = 10;
  }
  if (input != 10) {
    if (settingcode == false) {
      if (input == EEPROM.read(currentdigit + 1)) {
        correctdigits++;
      }
    } else if (settingcode == true) {
      digitsset++;
      digitamount++;
      EEPROM.update(currentdigit + 1, input);
      EEPROM.update(currentdigit + 2, 255);
    }
    lcd.print(input);
    Serial.println("start");
    Serial.println(EEPROM.read(currentdigit + 1));
    Serial.println(currentdigit);
    Serial.println(correctdigits);
    Serial.println(digitamount);
    currentdigit++;
    Serial.println("break");
    Serial.println(currentdigit);
    Serial.println(correctdigits);
    Serial.println(digitamount);
    Serial.println(EEPROM.read(currentdigit + 1));
    Serial.println(EEPROM.read(0));
    delay(300);
  }
}
