#pragma once

#include <SFML/Graphics.hpp>

#include "board.h"

class Game {
 public:
  Game();

  void run();

 private:
  static constexpr unsigned int kWindowWidth = 600;
  static constexpr unsigned int kWindowHeight = 700;
  static constexpr float kCardSize = 120.f;
  static constexpr float kGap = 24.f;
  static constexpr float kPadding = 24.f;
  static constexpr float kTopBarHeight = 100.f;
  static constexpr float kRevealDelaySeconds = 1.0f;

  sf::RenderWindow window;
  sf::Font font;
  bool font_ready;
  Board board;

  int first_card;
  int second_card;
  bool waiting_for_close;
  sf::Clock reveal_clock;

  int moves;
  int matches;
  int consecutive_errors;
  bool game_won;

  bool loadFont();

  void processEvents();
  void handleClick(int mouse_x, int mouse_y);

  void update();
  void resolvePair();

  void render();
  void drawStatusBar();
  void drawWinBanner();
};
