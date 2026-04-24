#include "utils.h"

float Utility::getRandomFloat(int min, int max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(min, max);
  return dis(gen);
}
sf::Vector2f Utility::newCirclePosition() {
  float X = Utility::getRandomFloat(100, Constants::SCREEN_WIDTH - 100);
  float Y = Utility::getRandomFloat(100, Constants::SCREEN_HEIGHT - 100);
  return sf::Vector2f(X, Y);
}
