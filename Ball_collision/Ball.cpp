#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <stdlib.h>

#include "SingleBall.h"

#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels
#define BALL_UPDATE_SPEED 15    // How fast the OLED Updates
#define BACKEND_UPDATE_SPEED 1  // How fast we do some calculations
 
#define OLED_RESET -1
#define NUM_BALLS 15

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void readNewValue();
void drawBalls();
void updatePositions();
void updateBalls();

bool atRight = true;          // Is on the right? In this context, right also acts as the "master".
bool debug = false;           // Output debug messages
bool ballCollision = false;   // The balls should be able to collide with each other, and change direction
unsigned long lastDrawn = 0;  // Millis since the OLED was last updated.

SingleBall balls[NUM_BALLS]; // Array of balls. Size is defined by NUM_BALLS.

void setupBalls() {
  if (!Serial1) {
    Serial1.begin(9600);
    if (debug && !Serial) {
      Serial.begin(9600);
    }
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Enable and connect to the OLED.

  // The "master" starts all the balls.
  if(atRight) {
    for(int i = 0;i<NUM_BALLS;i++)
    {
      Serial.println(String("Setup ball: ") + i);
      balls[i].posX = 50 + (i*4);
      balls[i].posY = 50;
      balls[i].isOnScreen = true; 
    }
  }

  Serial.println(F("Setup completed"));
}

void updateBalls() {
  //Serial.println(F("Start of loop"));
  // Update balls based on Serial.
  readNewValue();

  // Draw the individual balls on the OLED.
  drawBalls();

  // Delay position updates. Multiplier for the velocity of the balls. Less delay = faster balls.
  delay(BACKEND_UPDATE_SPEED);

  // Run through the balls and handle their positioning.
  updatePositions();
}

void drawBalls() {
  if(millis()-lastDrawn >= BALL_UPDATE_SPEED)
  {
    display.clearDisplay();
 
    display.drawLine(0,0,127,0,WHITE); // Top wall
    if (!atRight)
      display.drawLine(0,0,0,63,WHITE); // Left wall
    else
      display.drawLine(127,0,127,63,WHITE); // Right wall
    
    display.drawLine(0,63,127,63,WHITE); // Bottom wall

    for(int i = 0;i<NUM_BALLS;i++)
    {
      if(balls[i].isOnScreen) {
        display.drawCircle(balls[i].posX, balls[i].posY, 2, WHITE);
      }
    }

    display.display();
 
    lastDrawn = millis();
  }
}

void readNewValue() {
  if (Serial1.available() >= 4) // Data is sent in 4 pieces. Wait until there are 4 pieces available.
  {
    if (debug)
      Serial.println("Reading..");
    
    int index = Serial1.read(); // First is the index of the ball, in the balls array.

    balls[index].posY = (int)Serial1.read(); // Second is the Y position on the screen.
    balls[index].dir[0] = Serial1.read() - 128; // Third is the X velocity of the ball.
    balls[index].dir[1] = Serial1.read() - 128; // Fourth is the Y velocity of the ball.

    balls[index].posX = atRight ? 1 : SCREEN_WIDTH - 1; // Then we reset the X position to the proper position;
    balls[index].isOnScreen = true; // Lastly, we notify the ball that it is now on the screen.

    if (debug) {
      Serial.println(index);
      Serial.println(balls[index].posX);
      Serial.println(balls[index].posY);
      Serial.println(balls[index].dir[0]);
      Serial.println(balls[index].dir[1]);
    }
  }
}


void updatePositions()
{
  for(int i = 0;i<NUM_BALLS;i++)
  {
    if(balls[i].isOnScreen) // If the balls is on the screen, it should be updated. Otherwise not.
    {
      balls[i].updatePosition(atRight); // Handle ball movement.

      if(balls[i].shouldTransfer) // If the ball has touched the connecting wall, it should be transferred to the other side.
      {
        Serial1.write(i); // Index of the ball in the array.
        Serial1.write(balls[i].posY); // Y position of the ball.
        Serial1.write(balls[i].dir[0] + 128); // X velocity of the ball.
        Serial1.write(balls[i].dir[1] + 128); // Y velocity of the ball.

        balls[i].transfer(); // Raise flag to notify that the ball is now transferred.
      }
    }
  }
}