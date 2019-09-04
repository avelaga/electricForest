#include "Arduino.h"
#include "ledstrip.h"
#define NUM_LEDS    70
#define fastLower    1
#define fastUpper    2
#define slowLower    1
#define slowUpper    3
#define lowerCol 150
#define upperCol 200

ledstrip::ledstrip() {
  pos = random(0, NUM_LEDS);
  pause = random(5, 10);
  spedUp = false;
  speed = 2;
  col = random(lowerCol, upperCol);
}

int ledstrip::update(int frames, boolean motionDetected) {

  // new motion detected
  if (!spedUp && motionDetected) {

    pause = random(fastLower, fastUpper);
    spedUp = true;
  }

  // motion just ended
  if (spedUp && !motionDetected) {
    pause = random(slowLower, slowUpper);
    spedUp = false;
  }


  if (frames % pause == 0) {
    pos -= 1;

    //    Serial.print("current object pos "); Serial.println(pos);
    if (pos < -5) {

      pos = NUM_LEDS;
      col = random(lowerCol, upperCol);

      if (!spedUp) {
        pause = random(slowLower, slowUpper);
      }

    }
  }

  return pos;

}

int ledstrip::getColor() {
  return col;
}
