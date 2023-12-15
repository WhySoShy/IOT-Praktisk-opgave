#include <Arduino.h>
#include "SingleBall.h"

#ifndef SCREEN_WIDTH
  #define SCREEN_WIDTH 128
  #define SCREEN_HEIGHT 64
#endif

SingleBall::SingleBall() {
  isOnScreen = false;
  posX = SCREEN_WIDTH / 2;
  posY = SCREEN_HEIGHT / 2;
  dir[0] = 25;
  dir[1] = 10;
}
SingleBall::SingleBall( bool startActive ) {
  isOnScreen = startActive;
  posX = SCREEN_WIDTH / 2;
  posY = SCREEN_HEIGHT / 2;
  dir[0] = 25;
  dir[1] = 10;
}
SingleBall::SingleBall( bool startActive, float start_x, float start_y) {
  isOnScreen = startActive;
  posX = start_x;
  posY = start_y;
  dir[0] = 25; // X
  dir[1] = 10; // Y
}


void SingleBall::updatePosition( bool atRight )
{
  posX += (float)dir[0] / 100;
  posY += (float)dir[1] / 100;
 
  if(posY <= 0 || posY >= 63) {
    dir[0] += (rand() % 7 - 3);
    dir[1] = -dir[1];
    posY += (float)dir[1] / 100;
  }
  if((posX > 127 && atRight) || (!atRight && posX <= 0)) {
    dir[1] += (rand() % 7 - 3);
    dir[0] = -dir[0];
    posX += (float)dir[0] / 100;
  }

  if(isOnScreen && ((posX <= 0 && atRight) || (!atRight && posX >= SCREEN_WIDTH))) { // The wall it should collide with
    shouldTransfer = true;
  }
}

void SingleBall::transfer()
{
  shouldTransfer = false;
  isOnScreen = false;
}