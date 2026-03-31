#pragma once

#include "SFML/Graphics.hpp"
#include "BouncingCircleShape.h"
#include <vector>

void invokeLoop();

namespace GameLoopRequirements {
  void update();
  void draw();

  void generateCircleShapes(std::vector<BouncingCircleShape>& sh);

  void handleMouseClick(const sf::Vector2i& clickPos);
  void handleGameOver();
  void handleRestart();

  void centerText(sf::Text& text, const sf::Vector2f& position);
}