#include "Mode.h"

class White: public Mode {
private:
  
  int brightness;
  
public:
  White() : Mode() {
    brightness = 100;
  }
  
  ~White() {}
  
  void get(long now, int rgb[]) {
    for (int i = 0; i < 3; i++) {
      rgb[i] = brightness;
    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      brightness -= 16;
    }
    else if (direction == 'r') {
      brightness += 16;
    }
  
    if (brightness < 0) {
      brightness = 0;
    }
    else if (brightness > 255) {
      brightness = 255;
    }
  
    Serial.print("white level: ");
    Serial.println(brightness);
  }
  
  
};