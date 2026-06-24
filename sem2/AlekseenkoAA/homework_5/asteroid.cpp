#include "asteroid.h"

#include "constants.h"

Asteroid::Asteroid(const sf::Texture& texture) {
  shape.setSize({asteroidWidth, asteroidHeight});
  shape.setTexture(&texture);
  shape.setFillColor(sf::Color::White);
}

void Asteroid::respawn(RandomSystem& random, float base_speed,
                       bool above_window) {
  float max_x = float(windowWidth) - asteroidWidth;
  float min_y = above_window ? -280.0f : -560.0f;
  float max_y = above_window ? -40.0f : 80.0f;
  shape.setPosition(
      {random.randomFloat(0.0f, max_x), random.randomFloat(min_y, max_y)});
  speed = base_speed + random.randomFloat(0.0f, 90.0f);
}

void Asteroid::update(float time) { shape.move({0.0f, speed * time}); }

void Asteroid::draw(sf::RenderWindow& window) const { window.draw(shape); }

sf::FloatRect Asteroid::bounds() const { return shape.getGlobalBounds(); }
