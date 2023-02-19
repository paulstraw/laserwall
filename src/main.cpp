#include <Arduino.h>

#include "Laser.h"

// Create laser instance (with laser pointer connected to digital pin 5)
Laser laser(6);

void setup()
{
  laser.init();

  laser.setScale(1);
  laser.setOffset(0, 0);

  // Serial.begin(115200);
  Serial.begin(250000, SERIAL_8E2);
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

// void loop()
// {
//   circle();
// }

// // https://derivative.ca/UserGuide/Arduino
// // Parse incoming messages consisting of three decimal values followed by a carriage return
// // Example "12 34 56\n"
// // In TouchDesigner: op('serial1').send("12 34 56", terminator="\n")

char buffer[16]; // maximum expected length
int len = 0;

void loop()
{
  if (Serial.available() > 0)
  {
    int incomingByte = Serial.read();
    buffer[len++] = incomingByte;
    // check for overflow
    if (len >= 16)
    {
      // overflow, resetting
      Serial.println("OVERFLOW!");
      len = 0;
      memset(buffer, 32, sizeof(buffer));
    }

    // Serial.print((char)incomingByte);

    // check for newline (end of message)
    if (incomingByte == '\n')
    {
      // Serial.println("end");
      int x, y, r;
      int n = sscanf(buffer, "%d %d %d", &x, &y, &r);
      if (n == 3)
      {
        // valid message received
        // char buf[64];
        // sprintf(buf, "GOTDAT x: %d, y: %d, r: %d", x, y, r);
        // Serial.println(buf);
        // char buf2[64];
        // sprintf(buf2, "GOTDATRAW %s", buffer);
        // Serial.println(buf2);

        if (r)
        {
          laser.on();
        }
        else
        {
          laser.off();
        }

        laser.sendto(x, y);
      }
      else
      {
        Serial.println("Badmsg!!");
        // invalid message received
      }

      len = 0; // reset buffer counter

      memset(buffer, 32, sizeof(buffer)); // reset buffer to all ASCII spaces (decimal 32)
    }
  }
}
