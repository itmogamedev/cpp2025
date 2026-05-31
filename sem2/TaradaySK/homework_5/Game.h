#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Card {
  sf::RectangleShape shape;
  int id;
  bool isOpened;
  bool isMatched;
};

class Game {
 private:
  sf::RenderWindow window;
  std::vector<Card> cards;

  int firstSelectedIdx;
  int secondSelectedIdx;

  int score;
  int totalMoves;
  int consecutiveErrors;
  bool isWaiting;

  sf::Clock delayClock;
  sf::Font font;
  sf::Text statusText;
  sf::Text symbolText;

  void initCards();
  void shuffleRemainingCards();
  void handleCellClick(int index);
  void checkMatches();
  void updateText();

 public:
  Game();
  void run();
};

#endif