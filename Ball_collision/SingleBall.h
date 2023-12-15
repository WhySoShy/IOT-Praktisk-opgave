#ifndef SingleBall_h
#define SingleBall_h

#include "Arduino.h"

class SingleBall {
  public:
    SingleBall();
    SingleBall( bool startActive );
    SingleBall( bool startActive, float start_x, float start_y );
    void updatePosition( bool atRight );
    void transfer();
    float posX;
    float posY;
    int dir[2];
    bool shouldTransfer;
    bool isOnScreen;
  private:
};

#endif