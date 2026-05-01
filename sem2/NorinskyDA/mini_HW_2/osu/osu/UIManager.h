#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iomanip>

class UIManager {
 public:
  UIManager(sf::Font& font);

  void updateScore(int score);
  void updateTimer(float timeLeft);

  void showGameOver(int finalScore);
  void hideGameOver();
  bool isGameOverVisible() const { return gameOverVisible; }

  void draw(sf::RenderWindow& window) const;

 private:
  sf::Text scoreText;
  sf::Text timerText;
  sf::Text gameOverText;
  sf::Text finalScoreText;
  sf::Text restartText;

  bool gameOverVisible;
};

