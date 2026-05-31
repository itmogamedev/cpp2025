#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
 private:
  sf::RectangleShape shape;
  float speed;

 public:
  Player();

  void update(float dt);

  void draw(sf::RenderWindow& window);

  sf::Vector2f getPosition() const;

  sf::FloatRect getBounds() const;
};

#endif
