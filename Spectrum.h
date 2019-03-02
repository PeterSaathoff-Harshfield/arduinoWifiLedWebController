#include "Mode.h"

class Spectrum: public Mode {
private:
  int rate;
  
public:
	Spectrum() : Mode() {
	  rate = 20;
	}
  
  void get(long now, int rgb[]) {
    int step = (now/rate) % 768;

    int s = step % 256;
    if (step >= 0 && step < 256) {
      rgb[0] = 255 - s;
      rgb[1] = s;
      rgb[2] = 0;
    }
    else if (step >= 256 && step < 512) {
      rgb[0] = 0;
      rgb[1] = 255 - s;
      rgb[2] = s;
    }
    else if (step >= 512 && step < 768) {
      rgb[0] = s;
      rgb[1] = 0;
      rgb[2] = 255 - s;
    }
  }
  
  void adjust(char direction) {
    if (direction == 'l') {
      rate += 10;
    }
    else if (direction == 'r') {
      rate -= 10;
    }
  
    if (rate < 5) {
      rate = 5;
    }
    else if (rate > 500) {
      rate = 500;
    }
  
    Serial.print("spectrum rate: ");
    Serial.println(rate);
  }
};