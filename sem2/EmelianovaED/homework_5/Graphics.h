#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SFML/Graphics.hpp>

#include "Game.h"
class Graphics {
  sf::RenderWindow window_game;
  sf::Font font_game;
  float wait_timer;
  void handEvents(Game& logic, float dt);
  void renderWindow(const Game& logic);
  void showEndScreen(const Game& logic);
  int getCardClick(int x, int y) const;

 public:
  Graphics();
  void runGame(Game& logic);
};
#endif  // !GRAPHICS_H
