#ifndef TYPING_TRAINER_H_
#define TYPING_TRAINER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <random>

class TypingTrainer {
 public:
  TypingTrainer();
  void run();

 private:
  void processEvents();
  void update(float deltaTime);
  void render();
  char generateRandomChar();
  void centerText(sf::Text& text);
  void resetGame();

  sf::RenderWindow window_;
  sf::Font font_;

  sf::Text charText_;
  sf::Text scoreText_;
  sf::Text timerText_;
  sf::Text gameOverText_;

  float time_left_;
  int score_;
  char current_char_;
  bool game_active_;

  std::mt19937 rng_;
  std::uniform_int_distribution<int> char_dist_;
};

#endif
