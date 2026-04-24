#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Constants.h"

class UI : public sf::Drawable {
 private:
  sf::Font font;
  sf::Text score_text;
  sf::Text timer_text;
  sf::Text game_over_text;
  bool game_over;

 public:
  UI();
  void updateScore(int score);
  void updateTimer(float time_left);
  void setGameOver(bool over, int final_score);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};