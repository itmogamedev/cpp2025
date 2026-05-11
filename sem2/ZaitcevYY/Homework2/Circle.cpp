#include "Circle.h"

#include <cstdlib>

static float randFloat(float min, float max) {
  return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                   (max - min);
}

Circle::Circle(float radius) {
  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Transparent);
  shape.setOutlineColor(sf::Color::Cyan);
  shape.setOutlineThickness(6.f);
}

void Circle::setRandomPosition(int maxX, int maxY) {
  int x = rand() % maxX;
  int y = rand() % maxY;
  shape.setPosition((float)x, (float)y);
}

void Circle::setRandomVelocity(float minSpeed, float maxSpeed) {
  float vx = randFloat(minSpeed, maxSpeed);
  float vy = randFloat(minSpeed, maxSpeed);

  if (rand() % 2) vx = -vx;
  if (rand() % 2) vy = -vy;

  velocity = {vx, vy};
}

void Circle::update(float dt, int maxX, int maxY) {
  shape.move(velocity * dt);

  auto pos = shape.getPosition();
  float r = shape.getRadius();

  if (pos.x <= 0 || pos.x + 2 * r >= maxX) {
    velocity.x = -velocity.x;
  }
  if (pos.y <= 0 || pos.y + 2 * r >= maxY) {
    velocity.y = -velocity.y;
  }
}

void Circle::draw(sf::RenderWindow& window) { window.draw(shape); }

bool Circle::isClicked(sf::Vector2i mousePos) {
  return shape.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
}
