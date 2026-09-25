#include <LiquidCrystal.h>
//Setting the LCD pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
const int buttonPin = 0;
boolean lastButtonState = LOW;
boolean displayMessage = false;

void setup() {
  pinMode(buttonPin, INPUT);
  //Printing the first message
  lcd.begin(20, 4);
  lcd.setCursor(1, 0);
  lcd.print("Press the button to see the message");
}

void loop() {
  int buttonState = digitalRead(buttonPin);
// Using if loop to create the condition
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;

    if (buttonState == LOW) {
      displayMessage = true;
      lcd.clear();
      lcd.setCursor(1, 0);
      //Printing the message on screen when buttin is pressed
      lcd.print("www.TheEngineering");
      lcd.setCursor(4, 1);
      lcd.print("Projects.com");
    } else {
      displayMessage = false;
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Press the button to see the message");
    }
  }
}
