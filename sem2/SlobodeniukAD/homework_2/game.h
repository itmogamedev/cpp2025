#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "circle.h"
#include "config.h"

class Game {
 public:
  Game();
  void run();

 private:
  void handleEvents();
  void update(float dt);
  void draw();
  void checkClick(const sf::Vector2i& mouse_pos);

  sf::RenderWindow window;
  std::vector<Circle> circles;
  sf::Font font;
  sf::Text score_text;
  sf::Text timer_text;
  sf::Text game_over_text;

  float remaining_time;
  int score;
  bool is_game_over;
};

#endif