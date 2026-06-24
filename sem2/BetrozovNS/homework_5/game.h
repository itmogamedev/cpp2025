#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "card.h"

class Game {
 public:
  Game();

  void run();

 private:
  void processEvents();
  void update();
  void render();

  void initializeCards();
  void handleMouseClick(sf::Vector2f mouse_position);

  void checkOpenedCards();
  void shuffleHiddenCards();

  bool allCardsRemoved() const;

  sf::RenderWindow window_;

  sf::Font font_;

  std::vector<Card> cards_;
  std::vector<int> opened_indices_;

  int attempts_count_;
  int score_;
  int mistakes_in_row_;

  bool is_waiting_;
  bool is_game_over_;

  sf::Clock delay_clock_;

  sf::Text attempts_text_;
  sf::Text score_text_;
  sf::Text game_over_text_;

  std::mt19937 random_engine_;
};

#endif  // GAME_H_
