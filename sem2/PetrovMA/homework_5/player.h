
#ifndef MININHWLAST_PLAYER_H
#define MININHWLAST_PLAYER_H
#include <cmath>
#include <memory>


#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Keyboard.hpp"

struct PlayerStats {
  sf::RectangleShape render;
  int health = 3;
  int score = 0;
};

class Player {
public:
  PlayerStats stats;

  Player();
  void reset(const sf::Vector2f &windowSize);
  void tick(std::shared_ptr<sf::RenderWindow> rend, double_t dt);
};

#endif // MININHWLAST_PLAYER_H
