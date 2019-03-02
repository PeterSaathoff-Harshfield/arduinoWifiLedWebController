#include <IRremote.h>
#include "Light.h"
#include "Controller.h"

#define POWER 0x00FF629D
#define A 0x00FF22DD
#define B 0x00FF02FD
#define C 0x00FFC23D
#define UP 0x00FF9867
#define DOWN 0x00FF38C7
#define LEFT 0x00FF30CF
#define RIGHT 0x00FF7A85
#define SELECT 0x00FF18E7

int redPin = 6;
int greenPin = 5;
int bluePin = 3;

int receivePin = 10;
IRrecv irReceiver(receivePin);
decode_results results;

Light light(redPin, greenPin, bluePin);

Controller c = Controller();

bool on = true;
int currentColor[3] = {100, 100, 100};

long currentTime = millis();
long lastTime = millis();

void setup() {
  Serial.begin(115200);
  irReceiver.enableIRIn();
}

void loop() {

  if (on) {

    currentTime = millis();
    if (lastTime < currentTime - 20) {
      
      c.update(currentTime);
      
      light.set(c.r, c.g, c.b);
      
      
      // Serial.println(lastTime);
      // Serial.println(currentTime);
      lastTime = millis();
    }
    
    
    
    light.display();
  }
  else {
    light.set(0, 0, 0);
    light.display();
  }
  
  
  
  if (irReceiver.decode(&results)) {

    Serial.print("0x ");
    Serial.println(results.value, HEX);

    buttonHandler(results.value);

    irReceiver.resume();
  }
  
  
}

void buttonHandler(long buttonCode) {
  if (buttonCode == POWER) {
    Serial.println("power");
    on = !on;
  }
  else if (buttonCode == UP) {
    Serial.println("up");
    c.switchMode('u');
  }
  else if (buttonCode == DOWN) {
    Serial.println("down");
    c.switchMode('d');
  }
  else if (buttonCode == LEFT) {
    Serial.println("left");
    c.adjustMode('l');
  }
  else if (buttonCode == RIGHT) {
    Serial.println("right");
    c.adjustMode('r');
  }
  else if (buttonCode == A) {
    Serial.println("A");
  }
  else if (buttonCode == B) {
    Serial.println("B");
  }
  else if (buttonCode == C) {
    Serial.println("C");
  }
  else if (buttonCode == SELECT) {
    Serial.println("enter");
  }
}
