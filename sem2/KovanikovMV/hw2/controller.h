#pragma once
#include <SFML/Graphics.hpp>

#include "model.h"
#include "view.h"

class Controller {
 public:
  Controller(unsigned int width, unsigned int height, const std::string& title);
  void run();

 private:
  sf::RenderWindow window;
  Model model;
  View view;
  sf::Clock clock;

  void processEvents();
  void update(float deltaTime);
  void handleMouseClick(const sf::Vector2i& mousePos);
};
