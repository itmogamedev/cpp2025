#include "Utils.h"

#include <random>

float RandomFloat(float min, float max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(min, max);
  return dist(gen);
}

sf::Vector2f RandomPosition(float radius, float windowW, float windowH) {
  return {RandomFloat(radius, windowW - radius * 2.f),
          RandomFloat(radius, windowH - radius * 2.f)};
}

bool IsMouseInsideCircle(const sf::CircleShape& circle, sf::Vector2f mousePos) {
  sf::Vector2f center = circle.getPosition() +
                        sf::Vector2f(circle.getRadius(), circle.getRadius());

  float dx = mousePos.x - center.x;
  float dy = mousePos.y - center.y;
  float distSq = dx * dx + dy * dy;
  float r = circle.getRadius();

  return distSq <= r * r;
}