#include "Arduino.h"
#include "SCHLTR.h"

SCHLTR::SCHLTR()
{
 S1 = ?;
 S2 = ?;
 S3 = ?;
 S4 = ?;
 pinMode(S1, INPUT_PULLUP);
 pinMode(S2, INPUT_PULLUP);
 pinMode(S3, INPUT_PULLUP);
 pinMode(S4, INPUT_PULLUP);
}

int SCHLTR::s1()
{
 if (digitalRead(S1) == 1)
 {
  return 0;
 }
 else
 {
  return 1;
 }
}

int SCHLTR::s2()
{
 if (digitalRead(S2) == 1)
 {
  return 0;
 }
 else
 {
  return 1;
 }
}

int SCHLTR::s3()
{
 if (digitalRead(S3) == 1)
 {
  return 0;
 }
 else
 {
  return 1;
 }
}

int SCHLTR::s4()
{
 if (digitalRead(S4) == 1)
 {
  return 0;
 }
 else
 {
  return 1;
 }
}
