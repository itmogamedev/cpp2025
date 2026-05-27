#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Game {
 public:
  Game();
  void run();

 private:
  enum CardState { HIDDEN, REVEALED, REMOVED };
  struct Card {
    char symbol;
    CardState state;
    sf::RectangleShape shape;
    sf::Text text;
  };

  void init();
  void handleEvents();
  void update(float dt);
  void render();
  void shuffleAllCards();
  void shuffleRemainingCards();
  int getCardIndex(const sf::Vector2f& mousePos) const;
  void openCard(int idx);
  void closeBothCards();
  void checkMatch();
  void removeMatchedPair();
  void resetTurn();
  void checkGameOver();

  sf::RenderWindow window;
  sf::Font font;
  std::vector<Card> cards;

  int grid_width;
  int grid_height;
  float card_width;
  float card_height;
  float margin_x;
  float margin_y;
  float start_x;
  float start_y;

  int score;
  int moves;
  int consecutive_errors;

  enum GameState { WAITING, DELAY };
  GameState state;
  sf::Clock delay_clock;
  float delay_duration;

  int first_index;
  int second_index;
  bool waiting_for_second;
};
