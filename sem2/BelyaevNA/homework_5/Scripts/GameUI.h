#ifndef GAMEUI_H
#define GAMEUI_H

#include <SFML/Graphics.hpp>

class GameUI {
 private:
  sf::Text movesText;
  sf::Text scoreText;
  sf::Text chainText;
  sf::Text winText;
  sf::RectangleShape winPanel;

 public:
  GameUI(const sf::Font& font);
  void updateMoves(int moves);
  void updateScore(int score);
  void updateChain(int multiplier, bool active);
  void showWinScreen(int moves, int score);
  void draw(sf::RenderWindow& window) const;
};

#endif
