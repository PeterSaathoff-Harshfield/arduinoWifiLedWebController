#include "Mode.h"

class RedPulse: public Mode {
private:
  
public:
  RedPulse() : Mode() {
    
  }
  
  void get(long now, int rgb[]) {
    int step = (now/300) % 140;
    if (step < 70) {
      rgb[0] = step;
    }
    else {
      rgb[0] = 140 - step;
    }
    if (rgb[0] == 0) {
      rgb[0] = 1;
    }
    rgb[1] = 0;
    rgb[2] = 0;
  }
  
  void adjust(char direction) {
    
  }
};