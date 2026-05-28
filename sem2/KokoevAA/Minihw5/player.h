#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>

class Player {
 public:
  Player();

  void update(float delta_time);
  void draw(sf::RenderWindow& window) const;
  void resetPosition();

  sf::Vector2f getGunPosition() const;
  sf::Vector2f getPosition() const;
  sf::FloatRect getBounds() const;

 private:
  sf::ConvexShape shape;
};

#endif  // PLAYER_H_
