#define NUM_BALLS 3

#include "Ball.h"

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);

  debug = true;
  atRight = false;
  

  setupBalls();
}
 
void loop()
{
  //Serial.println(F("Start loop"));
  updateBalls(); // Run this every loop.
}