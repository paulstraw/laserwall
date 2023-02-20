#include <Arduino.h>

#include "Laser.h"
#include "Drawing.h"

#include "weirdcurve.h"
#include "wc2.h"
#include "Objects.h"
#include "smileylaserweb.h"
#include "skull.h"
#include "ghost.h"
#include "safetythird.h"
#include "dnc.h"

// Create laser instance (with laser pointer connected to digital pin 5)
Laser laser(5);

void setup()
{
  laser.init();

  laser.setScale(1);
  laser.setOffset(0, 0);

  // Serial.begin(115200);
  // Serial.begin(115200, SERIAL_8N2);
  // Serial.begin(250000, SERIAL_8N2);
  // Serial.begin(500000, SERIAL_8N2);
  Serial.begin(1000000, SERIAL_8N2);
}

// draw a circle using sin/cos
void circle()
{
  laser.setScale(1);
  laser.setOffset(2048, 2048);
  const int scale = 12;
  laser.sendto(SIN(0) / scale, COS(0) / scale);
  laser.on();
  for (int r = 5; r <= 360; r += 5)
  {
    Serial.println(SIN(r) / scale);
    laser.sendto(SIN(r) / scale, COS(r) / scale);
  }
  laser.off();
}

char messageBuffer[5]; // 2 bytes x, 2 bytes y, 1 byte meta

void loop()
{
  // if (Serial.available() > 0)
  // {
  //   Serial.readBytes(messageBuffer, 5);
  //   unsigned int targetX = (messageBuffer[0] << 8) | messageBuffer[1];
  //   unsigned int targetY = (messageBuffer[2] << 8) | messageBuffer[3];
  //   laser.sendto(targetX, targetY);
  //   // Serial.println("targetX");
  //   // Serial.println(targetX);
  //   // Serial.println(targetY);
  // }

  // circle();
  // laser.setOffset(2048, 2048);
  // laser.setScale(4);
  // Drawing::drawObject(draw_heart, sizeof(draw_hefart) / 4, 0, 0);
  // laser.setScale(3.5f);
  // laser.setScale(1);
  // Drawing::drawObject(draw_island, sizeof(draw_island) / 4, 0, 0);
  // laser.setScale(5);
  // Drawing::drawObject(draw_bike, sizeof(draw_bike) / 4, 0, 0);
  // laser.setScale(0.4f);
  // laser.setOffset(0, 0);
  // Drawing::drawObject(draw_smileylaserweb, sizeof(draw_smileylaserweb) / 4, 0, 0);
  Drawing::drawObject(draw_skull, sizeof(draw_skull) / 4, 0, 0);
  // Drawing::drawObject(draw_ghost, sizeof(draw_ghost) / 4, 0, 0);
  // Drawing::drawObject(draw_safetythird, sizeof(draw_safetythird) / 4, 0, 0);
  // Drawing::drawObject(draw_dnc, sizeof(draw_dnc) / 4, 0, 0);

  // long centerX, centerY, w, h;
  // Drawing::calcObjectBox(draw_wc2, sizeof(draw_wc2) / 4, centerX, centerY, w, h);
  // laser.setScale(4096 / (float)h);
  // laser.setOffset(2048, 2048);
  // for (int i = 0; i < 1000; i++)
  // {
  //   Drawing::drawObject(draw_wc2, sizeof(draw_wc2) / 4, -centerX, -centerY);
  // }
}
