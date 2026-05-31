#include "asteroid.h"

Asteroid::Asteroid(float x, float speed, float size) : speed(speed) {
  shape.setSize({size, size});
  shape.setFillColor(sf::Color(130, 130, 130));
  shape.setPosition({x, -size});
}

void Asteroid::tick(std::shared_ptr<sf::RenderWindow> rend, float dt) {
  auto pos = shape.getPosition();
  pos.y += speed * dt;
  shape.setPosition(pos);
  rend->draw(shape);
}

bool Asteroid::isOutOfBounds(float windowHeight) const { return shape.getPosition().y > windowHeight; }
