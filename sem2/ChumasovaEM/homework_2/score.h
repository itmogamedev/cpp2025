#pragma once
#include <SFML/Graphics.hpp>

class Score {
 public:
  int increase(int score);
  void updateText(sf::Text& scoreText, int score);
};
