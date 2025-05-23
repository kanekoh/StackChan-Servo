#include "BodyMotion.h"
#include <Avatar.h>

using namespace m5avatar;

BodyMotion body; 
Avatar avatar;

void servo(void *args)
{
  float gazeX, gazeY;
  int targetX, targetY;
  DriveContext *ctx = (DriveContext *)args;
  Avatar *avatar = ctx->getAvatar();
  for (;;)
  {
    avatar->getGaze(&gazeY, &gazeX);
    targetX = body.getStartDegreeX() + (int)(15.0 * gazeX);
    if(gazeY < 0) {
      int tmp = (int)(10.0 * gazeY);
      if(tmp > 10) tmp = 10;
      targetY = body.getStartDegreeY() + tmp;
    } else {
      targetY = body.getStartDegreeY()  + (int)(10.0 * gazeY);
    }

    body.moveTo(targetX, targetY);
    delay(50);
  }
}

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    avatar.init();
    avatar.setSpeechFont(&fonts::efontJA_16);

    body.begin();

    delay(1000);
}

void loop() {
  M5.update();

  // start from the home position
  body.moveHomePosition();
  delay(1000);

  // move to the left
  body.moveTo(body.getStartDegreeX()+15, body.getStartDegreeY());
  delay(1000);

  // move to the right
  body.moveTo(body.getStartDegreeX()-15, body.getStartDegreeY());
  delay(1000);

  body.moveHomePosition();
  delay(1000);

  // move to the down
  body.moveTo(body.getStartDegreeX(), body.getStartDegreeY()+10);
  delay(1000);

  // move to the up
  body.moveTo(body.getStartDegreeX(), body.getStartDegreeY()-10);
  delay(2000);
}
