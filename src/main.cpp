#include <Arduino.h>

#include "Laser.h"
#include "Drawing.h"

#include "weirdcurve.h"
#include "wc2.h"
#include "Objects.h"
#include "Logo.h"
#include "smileylaserweb.h"
#include "skull.h"
#include "ghost.h"
#include "safetythird.h"
#include "dnc.h"
#include "sidedoor.h"
#include "amongus.h"
#include "foxfriend.h"
#include "dogfriend.h"
#include "subscribe.h"

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
  Serial.setTimeout(5);
}

void circle()
{
  laser.setScale(1);
  laser.setOffset(2048, 2048);
  const int scale = 12;
  laser.sendto(SIN(0) / scale, COS(0) / scale);
  laser.on();
  for (int r = 5; r <= 360; r += 5)
  {
    laser.sendto(SIN(r) / scale, COS(r) / scale);
  }
  laser.off();
}

void drawHelloWorld()
{
  laser.setScale(0.7f);
  laser.setOffset(0, 0);
  Drawing::drawString("LASER", 700, 3500);
  Drawing::drawString("WALL", 1100, 2000);
}

void drawLogo()
{
  long centerX, centerY, w, h;
  Drawing::calcObjectBox(draw_logo, sizeof(draw_logo) / 4, centerX, centerY, w, h);

  int count = 200;
  laser.setScale(4096 / (float)h);
  laser.setOffset(2048, 2048);

  long maxMove = 0;
  for (int i = 0; i < count; i++)
  {
    laser.setMaxMove(maxMove);
    maxMove += 400;
    Drawing::drawObject(draw_logo, sizeof(draw_logo) / 4, -centerX, -centerY);
    if (laser.maxMoveReached())
    {
      long x, y;
      laser.getMaxMoveFinalPosition(x, y);
      laser.resetMaxMove();
      laser.off();
      laser.sendtoRaw(x, y);
      laser.on();
      laser.sendtoRaw(2047, 0);
    }
  }
  laser.resetMaxMove();
  long pos = 0;
  while (pos < 4095)
  {
    laser.setClipArea(pos, 0, 4095, 4095);
    pos += 100;
    Drawing::drawObject(draw_logo, sizeof(draw_logo) / 4, -centerX, -centerY);
  }
  laser.resetClipArea();
}

void drawAmongButt()
{
  laser.setScale(1);
  laser.setOffset(0, 0);

  for (int i = 0; i < 2; i++)
  {
    Drawing::drawObject(draw_amongus1, sizeof(draw_amongus1) / 4, 0, 0);
  }

  for (int i = 0; i < 2; i++)
  {
    Drawing::drawObject(draw_amongus2, sizeof(draw_amongus2) / 4, 0, 0);
  }

  for (int i = 0; i < 2; i++)
  {
    Drawing::drawObject(draw_amongus3, sizeof(draw_amongus3) / 4, 0, 0);
  }

  for (int i = 0; i < 2; i++)
  {
    Drawing::drawObject(draw_amongus4, sizeof(draw_amongus4) / 4, 0, 0);
  }

  for (int i = 0; i < 2; i++)
  {
    Drawing::drawObject(draw_amongus5, sizeof(draw_amongus5) / 4, 0, 0);
  }

  for (int i = 0; i < 2; i++)
  {
    Drawing::drawObject(draw_amongus6, sizeof(draw_amongus6) / 4, 0, 0);
  }
}

char messageBuffer[5]; // 2 bytes x, 2 bytes y, 1 byte meta
char prog = '0';

void loop()
{
  if (Serial.available() > 0)
  {
    Serial.readBytes(messageBuffer, 1);
    Serial.readString();
    prog = messageBuffer[0];
    Serial.println(prog);

    // Serial.readBytes(messageBuffer, 5);
    // unsigned int targetX = (messageBuffer[0] << 8) | messageBuffer[1];
    // unsigned int targetY = (messageBuffer[2] << 8) | messageBuffer[3];
    // laser.sendto(targetX, targetY);
    // Serial.println("targetX");
    // Serial.println(targetX);
    // Serial.println(targetY);
  }

  switch (prog)
  {
  case '0':
    break;
  case '1':
    circle();
    break;
  case '2':
    laser.setScale(4);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_heart, sizeof(draw_heart) / 4, 0, 0);
    break;
  case '3':
    laser.setScale(3.5f);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_island, sizeof(draw_island) / 4, 0, 0);
    break;
  case '4':
    drawLogo();
    break;
  case '5':
    laser.setScale(5);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_bike, sizeof(draw_bike) / 4, 0, 0);
    break;
  case '6':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_smileylaserweb, sizeof(draw_smileylaserweb) / 4, 0, 0);
    break;
  case '7':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_skull, sizeof(draw_skull) / 4, 0, 0);
    break;
  case '8':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_ghost, sizeof(draw_ghost) / 4, 0, 0);
    break;
  case '9':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_safetythird, sizeof(draw_safetythird) / 4, 0, 0);
    break;
  case 'a':
    laser.setScale(1);
    laser.setOffset(0, 0);
    drawAmongButt();
    break;
  case 'b':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_sidedoor, sizeof(draw_sidedoor) / 4, 0, 0);
    break;
  case 'c':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_dnc, sizeof(draw_dnc) / 4, 0, 0);
    break;
  case 'd':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_foxfriend, sizeof(draw_foxfriend) / 4, 0, 0);
    break;
  case 'e':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawString("12:42", 0, 0);
    break;
  case 'f':
    laser.setScale(1);
    laser.setOffset(0, 0);
    Drawing::drawObject(draw_dogfriend, sizeof(draw_dogfriend) / 4, 0, 0);
    break;
  case 'g':
    drawHelloWorld();
    break;
  case 'h':
    laser.setScale(0.5);
    laser.setOffset(0, 0);
    Drawing::drawString("SUBSCRIBE", 0, 2800);
    // Drawing::drawObject(draw_subscribe, sizeof(draw_subscribe) / 4, 0, 0);
    break;
  }
}
