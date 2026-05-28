#ifndef SPACE_SHOOTER_ASTEROID_H
#define SPACE_SHOOTER_ASTEROID_H

#include <SFML/Graphics.hpp>
#include <string>

class Asteroid {
 public:
  Asteroid(float x, float speed, const std::string& texture_path);

  void update(float delta_time);
  void draw(sf::RenderWindow& window) const;

  sf::FloatRect getBounds() const;
  bool isOffScreen(float window_height) const;

 private:
  sf::Sprite sprite;
  float speed;
};

#endif  // SPACE_SHOOTER_ASTEROID_H
