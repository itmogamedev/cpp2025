#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>

#include "game.h"

class Draw {
  sf::RenderWindow game_window;
  sf::Font game_font;
  float wait_accumulator;
  bool font_ready;

  void processEvents(Game& current_game, float delta_time);
  void renderField(const Game& current_game);
  void renderFinalScreen(const Game& current_game);
  int detectCardClick(int mouse_x, int mouse_y) const;

 public:
  Draw();
  void startGame(Game& current_game);
};

#endif