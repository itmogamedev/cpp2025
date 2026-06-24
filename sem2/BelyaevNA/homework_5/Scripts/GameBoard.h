#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>

#include "Card.h"

class GameBoard {
 private:
  std::vector<Card> cards;
  std::vector<int> symbols;
  std::map<int, std::shared_ptr<sf::Texture>> iconTextures;
  std::shared_ptr<sf::Texture> coverTexture;
  sf::Font font;
  int pairsFound;
  int consecutiveErrors;

  void initCards();
  void shuffleHiddenCards();
  bool loadTextures();

 public:
  GameBoard();
  int handleClick(sf::Vector2i mousePos);
  bool checkMatch(int firstCard, int secondCard);
  int getPairsFound() const;
  bool isGameWon() const;
  void draw(sf::RenderWindow& window) const;
  void drawBackground(sf::RenderWindow& window) const;
};

#endif
