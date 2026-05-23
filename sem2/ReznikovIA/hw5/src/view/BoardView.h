#pragma once

#include <SFML/Graphics.hpp>

#include "../model/BoardModel.h"

class BoardView {
 public:
  BoardView(const BoardModel& boardModel);
  void render(sf::RenderWindow& window);

 private:
  const BoardModel& boardModel;
  sf::Texture tileset;
  sf::Font font;
};
