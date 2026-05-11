#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <string>

class TypingGame {
 private:
  sf::RenderWindow window;
  sf::Font font;

  // Игровые переменные
  char current_char;
  int score;
  float time_left;
  bool game_active;
  const float game_time = 30.0f;

  // Текстовые элементы
  std::unique_ptr<sf::Text> target_char_text;
  std::unique_ptr<sf::Text> score_text;
  std::unique_ptr<sf::Text> timer_text;
  std::unique_ptr<sf::Text> game_over_text;
  std::unique_ptr<sf::Text> final_score_text;
  std::unique_ptr<sf::Text> instruction_text;

  // Генератор случайных символов
  std::random_device random_device;
  std::mt19937 generator;
  std::uniform_int_distribution<> char_distribution;

  sf::Clock game_clock;

  // Приватные методы
  void setupText();
  void generateNewChar();
  void updateUI();
  void resetGame();

 public:
  TypingGame();
  void run();
  void handleInput();
  void update();
  void render();
};
