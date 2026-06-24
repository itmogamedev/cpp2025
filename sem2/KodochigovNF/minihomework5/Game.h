#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Board.h"

class Game {
 public:
  Game();
  void run();

 private:
  sf::RenderWindow window_;
  sf::Font font_;
  Board board_;
  sf::Text score_text_;
  sf::Text moves_text_;
  sf::Text game_over_text_;
  bool game_over_;

  void processEvents();
  void update(float deltaTime);
  void render();
  void updateUIText();
};

#endif
