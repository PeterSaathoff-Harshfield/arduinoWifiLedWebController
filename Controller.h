#pragma once
// #include "Mode.h"
#include "White.h"
#include "Spectrum.h"
#include "SolidColors.h"
#include "Gradient.h"
#include "Random.h"
#include "Flow.h"
#include "RedPulse.h"

class Controller {
private:
  bool logging = true;
  
  Mode* modes[7];
  
  // String modes[7] = {"white", "spectrum", "solidcolors", "gradient", "random", "flow", "redPulse"};
  const int numberOfModes = sizeof(modes) / sizeof(modes[0]);
  int currentMode;
  
  int rgb[3];
  
  void putColors() {
    r = rgb[0];
    g = rgb[1];
    b = rgb[2];
  }
  
public:
  int r;
  int g;
  int b;
  
	Controller() {
	  r = 1;
    g = 1;
    b = 1;
    
    currentMode = 0;
    
    modes[0] = new White();
    modes[1] = new Spectrum();
    modes[2] = new SolidColors();
    modes[3] = new Gradient();
    modes[4] = new Random();
    modes[5] = new Flow();
    modes[6] = new RedPulse();
	}
  
  void update(long now) {  
    modes[currentMode]->get(now, rgb);
    putColors();
  }
  
  void setMode(int modeIndex) {
    if (modeIndex >= 0 && modeIndex < 7) {
      currentMode = modeIndex;
    }
  }
  
  void switchMode(char direction) {
    if (direction == 'u') {
      currentMode += 1;
    }
    else if (direction == 'd') {
      currentMode -= 1;
    }

    int n = numberOfModes;
    if (currentMode < 0) {
      currentMode = n + currentMode;
    }
    else if (currentMode > 0) {
      currentMode = currentMode % n;
    }
    else {
      currentMode = 0;
    }
  
  }
  
  void adjustMode(char direction) {
    modes[currentMode]->adjust(direction);
  }
  
};

