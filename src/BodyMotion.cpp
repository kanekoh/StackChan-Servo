#include "BodyMotion.h"
#include <ServoEasing.hpp> // https://github.com/ArminJo/ServoEasing       

ServoEasing servo_x;
ServoEasing servo_y;

BodyMotion::BodyMotion()
{}

void BodyMotion::begin() {
  if (servo_x.attach(SERVO_PIN_X, START_DEGREE_VALUE_X, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE) == INVALID_SERVO) {
    Serial.print("Error attaching servo x");
  }
  if (servo_y.attach(SERVO_PIN_Y, START_DEGREE_VALUE_Y, DEFAULT_MICROSECONDS_FOR_0_DEGREE, DEFAULT_MICROSECONDS_FOR_180_DEGREE) == INVALID_SERVO) {
    Serial.print("Error attaching servo y");
  }
  servo_x.setEasingType(EASE_QUADRATIC_IN_OUT);
  servo_y.setEasingType(EASE_QUADRATIC_IN_OUT);
  setSpeedForAllServos(30);

  servo_x.setEaseTo(START_DEGREE_VALUE_X); 
  servo_y.setEaseTo(START_DEGREE_VALUE_Y);
  synchronizeAllServosStartAndWaitForAllServosToStop();
}

void BodyMotion::moveHomePosition()
{
  moveTo(START_DEGREE_VALUE_X, START_DEGREE_VALUE_Y);
}

void BodyMotion::moveTo(int x, int y)
{
  if (!servo_x.attached() || !servo_y.attached()) {
    Serial.println("Servo not attached!");
    return;
  }
  servo_x.setEaseTo(x);
  servo_y.setEaseTo(y);
  synchronizeAllServosStartAndWaitForAllServosToStop();
}

