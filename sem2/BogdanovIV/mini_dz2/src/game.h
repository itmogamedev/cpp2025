#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>
#include <string>

class TypingGame {
 public:
  TypingGame();
  void Run();

 private:
  sf::RenderWindow window_;

  sf::Font font_;

  sf::Text target_char_text_;
  sf::Text score_text_;
  sf::Text timer_text_;
  sf::Text game_over_text_;
  sf::Text final_score_text_;
  sf::Text instruction_text_;

  char current_char_;
  int score_;
  float time_remaining_;
  float game_time_;
  bool game_active_;

  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_int_distribution<> char_dist_;

  sf::Clock game_clock_;

  sf::Color background_color_;
  sf::Color text_color_;
  sf::Color timer_color_;

  char GenerateRandomChar();
  void UpdateDisplay();
  void CenterTargetChar();
  void CorrectPress();
  void WrongPress();
  void EndGame();
  void RestartGame();
};

#endif
