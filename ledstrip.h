#ifndef ledstrip_h
#define ledstrip_h

#include "Arduino.h"

class ledstrip
{
  public:
    ledstrip();
    int update(int frames, boolean motionDetected);
    int getColor();
  private:
//    int bright[50];
    int pos;
    int col;
    int pause;
    int speed;
    boolean spedUp;
};

#endif
