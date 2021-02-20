/* Scroll wheel for 4KBShort
Written By Bruteclaw */

// Includes
#include <Mouse.h>

// Pin Assignment
int encoderCLK = 9;
int encoderDT = 8;
int encoderSW = 7;

// Variables
int counter = 0;
int currentStateCLK;
int lastStateCLK;
unsigned long lastButtonPress = 0;

// Setup
void setup() {
  
  //Pin Initialization
  pinMode (encoderCLK, INPUT);
  pinMode (encoderDT, INPUT);
  pinMode (encoderSW, INPUT);

  // Read Encoders CLK inital state
  lastStateCLK = digitalRead(encoderCLK);

  //initialize mouse control:
  Mouse.begin();

  // Serial Debuging
  //Serial.begin(115200);

}

void loop() {
  
  //Read the current state of CLK
  currentStateCLK = digitalRead(encoderCLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(encoderDT) != currentStateCLK) {
      counter --;
    } else {
      // Encoder is rotating CW so increment
      counter ++;
    }
    
    //Serial Debuging
    /*Serial.print(" | Counter: ");
    Serial.println(counter);*/
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(encoderSW);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      Mouse.click(MOUSE_MIDDLE);
      //Serial Debuggin
      //Serial.println("Button pressed!");
    }

    // Remember last button press event
    lastButtonPress = millis();
  }
  //Move the Scroll Wheel
  Mouse.move(0, 0, counter);

  //Reset Counter for next move
  counter = 0;
  
  // Put in a slight delay to help debounce the reading
  delay(1);
}
