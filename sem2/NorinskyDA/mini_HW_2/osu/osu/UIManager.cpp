#include "UIManager.h"

#include <string>


UIManager::UIManager(sf::Font& font)
    : scoreText(font, "Score: 0", 30),
      timerText(font, "Time: 30.0", 30),
      gameOverText(font, "GAME OVER!", 30),
      finalScoreText(font, "", 20),
      restartText(font, "Press SPACE to restart", 20),
      gameOverVisible(false) {
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(sf::Vector2f(10, 20));

  timerText.setFillColor(sf::Color::White);
  timerText.setPosition(sf::Vector2f(400, 20));

  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setPosition(sf::Vector2f(200, 200));

  finalScoreText.setFillColor(sf::Color::Yellow);
  finalScoreText.setPosition(sf::Vector2f(200, 280));

  restartText.setFillColor(sf::Color::White);
  restartText.setPosition(sf::Vector2f(200, 350));
}

void UIManager::updateScore(int score) {
  scoreText.setString("Score: " + std::to_string(score));
}

void UIManager::updateTimer(float timeLeft) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << timeLeft;
    timerText.setString("Time: " + stream.str());
}

void UIManager::showGameOver(int finalScore) {
  gameOverVisible = true;
  finalScoreText.setString("Final Score: " + std::to_string(finalScore));
}

void UIManager::hideGameOver() { gameOverVisible = false; }

void UIManager::draw(sf::RenderWindow& window) const {
  window.draw(scoreText);
  window.draw(timerText);

  if (gameOverVisible) {
    window.draw(gameOverText);
    window.draw(finalScoreText);
    window.draw(restartText);
  }
}

