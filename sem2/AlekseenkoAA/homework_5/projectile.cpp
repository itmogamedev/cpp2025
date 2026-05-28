#include "projectile.h"

#include "constants.h"

Projectile::Projectile(sf::Vector2f point) {
  shape.setSize({shotWidth, shotHeight});
  shape.setFillColor(sf::Color(120, 255, 255));
  shape.setPosition(point);
}

void Projectile::update(float time) {
  shape.move({0.0f, -shotSpeed * time});
  if (shape.getPosition().y + shotHeight < 0.0f) {
    active = false;
  }
}

void Projectile::draw(sf::RenderWindow& window) const {
  if (active) {
    window.draw(shape);
  }
}

sf::FloatRect Projectile::bounds() const { return shape.getGlobalBounds(); }

bool Projectile::isActive() const { return active; }

void Projectile::stop() { active = false; }
