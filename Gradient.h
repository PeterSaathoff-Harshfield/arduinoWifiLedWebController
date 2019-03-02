#include "Mode.h"

class Gradient: public Mode {
private:
  int gradientState;
  int rate;
  int numberOfGradients;
  
public:
  Gradient() : Mode() {
    gradientState = 0;
    rate = 100;
    numberOfGradients = 3;
  }
  
  void get(long now, int rgb[]) {
    int step = (now/rate) % 512;
    
    int x;
    int y;
    if (step < 256) {
      x = 255 - step;
      y = step;
    }
    else if (step >= 256) {
      x = step - 256;
      y = 512 - step;
    }
    
    if (gradientState == 0) {
      rgb[0] = 0;
      rgb[1] = x;
      rgb[2] = y;
    }
    else if (gradientState == 1) {
      rgb[0] = y;
      rgb[1] = 0;
      rgb[2] = x;
    }
    else if (gradientState == 2) {
      rgb[0] = x;
      rgb[1] = y;
      rgb[2] = 0;
    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      gradientState -= 1;
    }
    else if (direction == 'r') {
      gradientState += 1;
    }
    
    if (gradientState < 0) {
      gradientState = gradientState + numberOfGradients;
    }
    else if (gradientState >= numberOfGradients) {
      gradientState = gradientState % numberOfGradients;
    }
  }
};