#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>
#include <vector>

class Circle;

class Game {
 public:
  Game();
  ~Game();
  void run();

 private:
  void processEvents();
  void update(float deltaTime);
  void render();
  void respawnCircle(Circle* circle);
  void endGame();

  sf::RenderWindow m_window;
  sf::Font m_font;
  std::optional<sf::Text> m_scoreText;
  std::optional<sf::Text> m_timerText;
  std::optional<sf::Text> m_gameOverText;
  std::vector<std::unique_ptr<Circle>> m_circles;
  int m_score;
  float m_remainingTime;
  bool m_isGameOver;
  sf::Clock m_clock;
};
