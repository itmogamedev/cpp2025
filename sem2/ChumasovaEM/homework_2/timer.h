#pragma once
#include <SFML/Graphics.hpp>

class Timer {
 public:
  float update(float timeLeft, float deltaTime);
  float penalty(float timeLeft, float penaltyAmount);
  bool isExpired(float timeLeft);
  void updateText(sf::Text& timerText, float timeLeft);
};
