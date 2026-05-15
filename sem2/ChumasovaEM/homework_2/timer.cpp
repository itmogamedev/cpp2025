#include "timer.h"

#include <string>

#include "constants.h"

float Timer::update(float timeLeft, float deltaTime) {
  timeLeft -= deltaTime;
  if (timeLeft < Constants::START_POSITION) {
    return 0;
  }
  return timeLeft;
}

float Timer::penalty(float timeLeft, float penaltyAmount) {
  timeLeft -= penaltyAmount;
  if (timeLeft < Constants::START_POSITION) {
    return 0;
  }
  return timeLeft;
}

bool Timer::isExpired(float timeLeft) {
  return timeLeft <= Constants::START2_POSITION;
}

void Timer::updateText(sf::Text& timerText, float timeLeft) {
  timerText.setString("Time: " + std::to_string(static_cast<int>(timeLeft)));
}
