#include "UI.h"

#include <string>

UI::UI() : m_fontLoaded(false) {}

bool UI::init() {
  if (m_font.openFromFile("BitcountGridDouble_Cursive-Regular.ttf"))
    m_fontLoaded = true;
  else if (m_font.openFromFile("C:/Windows/Fonts/Arial.ttf"))
    m_fontLoaded = true;
  else if (m_font.openFromFile("C:/Windows/Fonts/Consolas.ttf"))
    m_fontLoaded = true;

  if (m_fontLoaded) {
    m_scoreText = std::make_unique<sf::Text>(m_font, "Score: 0", 36);
    m_scoreText->setFillColor(sf::Color::White);
    m_scoreText->setPosition({15.f, 15.f});

    m_timerText = std::make_unique<sf::Text>(m_font, "Time: 30", 36);
    m_timerText->setFillColor(sf::Color::White);
    m_timerText->setPosition({600.f, 15.f});

    m_gameOverText = std::make_unique<sf::Text>(m_font, "GAME OVER", 60);
    m_gameOverText->setFillColor(sf::Color::Red);
    m_gameOverText->setPosition({250.f, 200.f});

    m_finalScoreText = std::make_unique<sf::Text>(m_font, "Final Score: 0", 45);
    m_finalScoreText->setFillColor(sf::Color::Yellow);
    m_finalScoreText->setPosition({280.f, 280.f});

    m_restartText =
        std::make_unique<sf::Text>(m_font, "Press R to restart", 25);
    m_restartText->setFillColor(sf::Color::White);
    m_restartText->setPosition({310.f, 360.f});

    m_exitText = std::make_unique<sf::Text>(m_font, "Press Q to exit", 25);
    m_exitText->setFillColor(sf::Color::White);
    m_exitText->setPosition({280.f, 400.f});
  }

  return m_fontLoaded;
}

void UI::update(int score, float remainingTime) {
  if (!m_fontLoaded) return;

  if (m_scoreText) m_scoreText->setString("Score: " + std::to_string(score));

  if (m_timerText) {
    int timeInt = static_cast<int>(remainingTime);
    m_timerText->setString("Time: " + std::to_string(timeInt));

    if (remainingTime <= 5.f && remainingTime > 0.f) {
      m_timerText->setFillColor(sf::Color::Red);
    } else {
      m_timerText->setFillColor(sf::Color::White);
    }
  }
}

void UI::draw(sf::RenderWindow& window) {
  if (!m_fontLoaded) return;
  if (m_scoreText) window.draw(*m_scoreText);
  if (m_timerText) window.draw(*m_timerText);
}
void UI::showGameOver(sf::RenderWindow& window, int finalScore) {
  if (!m_fontLoaded) return;

  if (m_finalScoreText) {
    m_finalScoreText->setString("Final Score: " + std::to_string(finalScore));
    window.draw(*m_gameOverText);
    window.draw(*m_finalScoreText);
    window.draw(*m_restartText);
    window.draw(*m_exitText);
  }
}
