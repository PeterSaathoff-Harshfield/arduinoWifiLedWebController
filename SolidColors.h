#include "Mode.h"

class SolidColors: public Mode {
private:
  enum {numberOfColors = 13};
  int colors[numberOfColors][3] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {128, 0, 128},
    {64, 0, 128},
    {32, 0, 64},
    {0, 128, 96},
    {0, 128, 128},
    {32, 128, 192},
    {128, 128, 0},
    {160, 120, 0},
    {160, 150, 0},
    {70, 160, 70}
  };
  
  int colorState;
  
public:
  SolidColors() : Mode() {
    colorState = 0;
  } 
 
  void get(long now, int rgb[]) {
    for (int i = 0; i < 3; i++) {
      rgb[i] = colors[colorState][i];
    }
  }
 
  void adjust(char direction) {
    if (direction == 'l') {
      colorState -= 1;
    }
    else if (direction == 'r') {
      colorState += 1;
    }
   
    if (colorState < 0) {
      colorState = colorState + numberOfColors;
    }
    else if (colorState > 0) {
      colorState = colorState % numberOfColors;
    } 
  }
};