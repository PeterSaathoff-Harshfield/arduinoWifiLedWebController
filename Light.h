class Light {
private:
  bool logging = false;
  
  int redPin;
  int greenPin;
  int bluePin;
  
public:
  
  int currentColor[3];
  
  bool primed;  
  
  Light(int rPin, int gPin, int bPin) {
    redPin = rPin;
    greenPin = gPin;
    bluePin = bPin;
    
    for (int i = 0; i < 3; i++) {
      currentColor[i] = 100;
    }
    
    primed = true;
  }
  
  void set(int r, int g, int b) {
    if (currentColor[0] == r && currentColor[1] == g && currentColor[2] == b) {
      primed = false;
    }
    else {
      primed = true;
    }
    
    currentColor[0] = r;
    currentColor[1] = g;
    currentColor[2] = b;
    
  }
  
  int brightness(int raw) {
    if (raw < 0) {
      raw = 0;
    }
    if (raw > 255) {
      raw = 255;
    }

    float scale = 0.00025;
    float expo = 2.4493;
  
    float y = scale * pow((29 + raw), expo);
    if (y < 0) {
      y = 0;
    }

    return y;
  }


  void display() {
    if (primed) {
      
      int r1 = brightness(currentColor[0]);
      int g1 = brightness(currentColor[1]);
      int b1 = brightness(currentColor[2]);
  
      analogWrite(redPin, r1);
      analogWrite(greenPin, g1);
      analogWrite(bluePin, b1);
      
      primed = false;
      
      if (logging) {
        char v[64];
        sprintf(v, "actual: %03d %03d %03d virtual: %03d %03d %03d", r1, g1, b1, currentColor[0], currentColor[1], currentColor[2]);
         Serial.println(v);
      }
    }
    
    
  
    // monitor color levels
    // char buffer[64];
    // sprintf(buffer, "%03d %s", brightness, String(y).c_str());
    // Serial.println(buffer);
  }
  
};

