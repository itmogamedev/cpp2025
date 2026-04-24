#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <string>

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(sf::Time deltaTime);
  void render();
  void handlePlayerInput(sf::Keyboard::Key code);
  void generateNewCharacter();
  void addScore(int points);
  void reduceTime(float seconds);
  void updateScoreDisplay();
  void updateTimerDisplay();

  sf::RenderWindow window;
  sf::Font font;
  sf::Text current_char_text;
  sf::Text score_text;
  sf::Text timer_text;
  sf::Text game_over_text;

  std::mt19937 rng;
  std::uniform_int_distribution<int> char_dist;
  static const std::string kAllowedChars;

  char current_char;
  int score;
  float time_left;
  bool is_game_over;

  static constexpr float kInitialTime = 30.0f;
  static constexpr float kWrongPenalty = 2.0f;
  static constexpr int kScoreIncrement = 1;
};
