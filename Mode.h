#pragma once

class Mode {
public:
  
  Mode() {
    
  }
  
  virtual ~Mode() {}
  
  virtual void get(long now, int rgb[]) = 0;
  
  virtual void adjust(char direction) = 0;
};