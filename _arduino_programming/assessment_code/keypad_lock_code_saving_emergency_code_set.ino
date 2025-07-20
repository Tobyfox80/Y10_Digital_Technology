#include <EEPROM.h>
void setup() {
  EEPROM.update(0, 4);
  EEPROM.update(1, 0);
  EEPROM.update(2, 0);
  EEPROM.update(3, 0);
  EEPROM.update(4, 0);
  Serial.begin(9600);
  Serial.println("digitamount");
  Serial.print(EEPROM.read(0));
  Serial.println("digit1");
  Serial.print(EEPROM.read(1));
  Serial.println("digit2");
  Serial.print(EEPROM.read(2));
  Serial.println("digit3");
  Serial.print(EEPROM.read(3));
  Serial.println("digit4");
  Serial.print(EEPROM.read(4));
}
void loop() {
  
}

