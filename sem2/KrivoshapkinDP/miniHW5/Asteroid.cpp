#include "Asteroid.h"

#include <cstdlib>

#include "Constants.h"

Asteroid::Asteroid(float x, float y, float speed) : speed(speed) {
  float radius =
      kAsteroidMinRadius +
      static_cast<float>(rand() % static_cast<int>(kAsteroidMaxRadius -
                                                   kAsteroidMinRadius + 1));
  shape.setRadius(radius);
  shape.setFillColor(kAsteroidColor);
  shape.setOrigin({radius, radius});
  shape.setPosition({x, y});
}

void Asteroid::update(float dt) { shape.move({0.0f, speed * dt}); }

void Asteroid::draw(sf::RenderWindow& window) const { window.draw(shape); }

sf::FloatRect Asteroid::getBounds() const { return shape.getGlobalBounds(); }

bool Asteroid::isOffScreen(float windowHeight) const {
  return shape.getPosition().y - shape.getRadius() > windowHeight;
}
