#include "BodyMotion.h"
#include <Avatar.h>

using namespace m5avatar;

BodyMotion body; 
Avatar avatar;


const char *random_words[] = {
    "こんにちは",
    "おはよう",
    "こんばんは",
    "おやすみ",
    "ありがとう",
    "さようなら",
    "またね",
    "よろしく",
    "すごい",
    "いいね"
};
const int NUM_RANDOM_WORDS = sizeof(random_words) / sizeof(random_words[0]);


static unsigned long lastSpeakTime = 0;
static int speakInterval = 5000;  // 5秒おきにしゃべる
// loopの中で
static unsigned long lastSpeak = 0;
static bool showing = false;

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
    avatar.addTask(servo, "servo");
    avatar.setSpeechFont(&fonts::efontJA_16);

    body.begin();

    delay(1000);
}

void loop() {
  M5.update();

  unsigned long now = millis();
  if (!showing && now - lastSpeak > 5000) {
    int idx = random(NUM_RANDOM_WORDS);
    avatar.setExpression(Expression::Happy);
    avatar.setSpeechText(random_words[idx]);
    lastSpeak = now;
    showing = true;
  } else if (showing && now - lastSpeak > 7000) {
    avatar.setSpeechText(""); // 2秒表示して消す
    avatar.setExpression(Expression::Neutral);
    showing = false;
  }
}
