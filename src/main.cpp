#include <Arduino.h>

// https://derivative.ca/UserGuide/Arduino
// Parse incoming messages consisting of three decimal values followed by a carriage return
// Example "12 34 56\n"
// In TouchDesigner: op('serial1').send("12 34 56", terminator="\n")

char buffer[16]; // maximum expected length
int len = 0;

void setup()
{
  Serial.begin(115200);
}

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
      len = 0;
    }
    // check for newline (end of message)
    if (incomingByte == '\n')
    {
      int x, y, r;
      int n = sscanf(buffer, "%d %d %d", &x, &y, &r);
      if (n == 3)
      {
        // valid message received
        char buf[255];
        sprintf(buf, "GOTDAT x: %d, y: %d, r: %d", x, y, r);

        Serial.println(buf);
      }
      else
      {
        // invalid message received
      }
      len = 0; // reset buffer counter
    }
  }
}
