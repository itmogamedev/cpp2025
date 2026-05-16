#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>
#include <string>
#include <optional>
#include <memory>

class Game {
 public:
  Game();
  ~Game();

  void run();

 private:
  void initWindow();
  void initFont();
  void initVariables();
  char generateRandomChar();
  void handleInput();
  void update(float delta_time);
  void updateTimer(float delta_time);
  void processKeyPress(sf::Keyboard::Scancode scancode);
  void resetGame();
  void render();

  sf::RenderWindow* window_;
  sf::Font font_;
  
  std::unique_ptr<sf::Text> current_char_text_;
  std::unique_ptr<sf::Text> score_text_;
  std::unique_ptr<sf::Text> timer_text_;
  std::unique_ptr<sf::Text> game_over_text_;
  std::unique_ptr<sf::Text> restart_text_;
  
  char current_char_;
  int score_;
  float time_remaining_;
  bool game_active_;
  
  std::random_device random_device_;
  std::mt19937 random_engine_;
  
  const float INITIAL_TIME = 10.0f;
  const float TIME_PENALTY = 1.0f;
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;
};

#endif  // GAME_H_