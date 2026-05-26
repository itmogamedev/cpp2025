#include "laser.h"

Laser::Laser(float x, float y, float speed) : speed(speed) {
  shape.setSize({6.f, 20.f});
  shape.setFillColor(sf::Color(255, 255, 0));
  shape.setPosition({x - 3.f, y - 20.f});
}

void Laser::tick(std::shared_ptr<sf::RenderWindow> rend, float dt) {
  auto pos = shape.getPosition();
  pos.y -= speed * dt;
  shape.setPosition(pos);
  rend->draw(shape);
}

bool Laser::isOutOfBounds() const { return shape.getPosition().y + shape.getSize().y < 0.f; }
