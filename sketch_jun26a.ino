#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String text = " Kunal Malik Project ! ";

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);

  for (int i = 0; i < text.length(); i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}