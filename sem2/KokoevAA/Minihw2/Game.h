#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "CircleTarget.h"

class Game {
 public:
  Game();
  void run();

 private:
  sf::RenderWindow window;
  sf::Clock clock;

  std::vector<CircleTarget> circles;

  sf::Font font;
  sf::Text score_text{font};
  sf::Text timer_text{font};
  sf::Text end_text{font};

  int score;
  float time_left;
  bool game_over;

  void processEvents();
  void update(float dt);
  void render();

  void handleClick(int x, int y);
  void createCircles();
  void updateText();
};

#endif
