#pragma once
#include <SFML/Graphics.hpp>

#include "model.h"

class View {
 public:
  View(sf::RenderWindow& window, Model& model);
  void draw();

 private:
  sf::RenderWindow& window;
  Model& model;
  sf::Font font;
  std::optional<sf::Text> scoreText;
  std::optional<sf::Text> timerText;
  std::optional<sf::Text> gameOverText;
  // в SFML 3 нет конструктора sf::Text(), поэтому надо объявлять ссылку. с
  // std::optional можно работать как с умным указателем, но он хранится на
  // стеке
  void loadFont();
  void updateTexts();
};
