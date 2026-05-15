#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <SFML/Graphics.hpp>

#include "GameModel.h"

class GameView {
 public:
  explicit GameView(sf::RenderWindow& window);

  bool loadFont(const std::string& path, const std::string& fallback_path);
  void render(const GameModel& model);

 private:
  void drawBackground();
  void drawCircles(const GameModel& model);
  void drawHud(const GameModel& model);
  void drawGameOver(const GameModel& model);

  sf::RenderWindow& window_;
  sf::Font font_;
};

#endif  // GAME_VIEW_H_
