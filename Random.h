#include "Mode.h"

class Random: public Mode {
private:
  int rate;
  
public:
  Random() : Mode() {
    rate = 32;
  }
  
  void get(long now, int rgb[]) {
    int step = (now/20) % rate;
    if (step == 0) {
      rgb[0] = random() % 256;
      rgb[1] = random() % 256;
      rgb[2] = random() % 256;
    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      rate -= 2;
    }
    else if (direction == 'r') {
      rate += 2;
    }
    
    if (rate <= 4) {
      rate = 4;
    }
    else if (rate >= 1000) {
      rate = 1000;
    }
  }
};