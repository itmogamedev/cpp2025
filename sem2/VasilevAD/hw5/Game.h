#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include "Card.h"

class Game {
  private:
  void initCards();
  void shuffleRemaining();
  void handleInput();
  void update();
  void render();

  sf::RenderWindow window;
  sf::Font font;
  std::vector<Card> cards;
  std::vector<int> selected_indices;

  int total_turns;
  int consecutive_errors;
  int matches_found;
  bool is_waiting;
  sf::Clock wait_clock;
  bool game_over;

public:
  Game();
  void run();
};

#endif