#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

const float INITIAL_TIME = 30.0f;
const float PENALTY_TIME = 2.0f;
const int SCORE_PER_HIT = 1;
const int MIN_PRINTABLE = 97;
const int MAX_PRINTABLE = 122;

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Typing Monkey");
  window.setFramerateLimit(60u);

  sf::Font font;
  font.openFromFile("/System/Library/Fonts/Helvetica.ttc");

  sf::Text targetCharText(font);
  targetCharText.setCharacterSize(200u);
  targetCharText.setFillColor(sf::Color::White);
  targetCharText.setStyle(sf::Text::Bold);
  targetCharText.setPosition(
      {window.getSize().x / 2.0f, window.getSize().y / 2.0f});

  sf::Text scoreText(font);
  scoreText.setCharacterSize(36u);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({20.0f, 20.0f});

  sf::Text timerText(font);
  timerText.setCharacterSize(36u);
  timerText.setFillColor(sf::Color::White);
  timerText.setPosition({window.getSize().x - 150.0f, 20.0f});

  sf::Text gameOverText(font);
  gameOverText.setCharacterSize(48u);
  gameOverText.setStyle(sf::Text::Bold);
  gameOverText.setPosition(
      {window.getSize().x / 2.0f - 130.0f, window.getSize().y / 2.0f - 100.0f});

  sf::Text finalScoreText(font);
  finalScoreText.setCharacterSize(36u);
  finalScoreText.setFillColor(sf::Color::White);
  finalScoreText.setPosition(
      {window.getSize().x / 2.0f, window.getSize().y / 2.0f + 20.0f});

  auto centerText = [](sf::Text& text) {
    sf::FloatRect bounds = text.getGlobalBounds();
    text.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});
  };
  centerText(targetCharText);
  centerText(gameOverText);
  centerText(finalScoreText);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(MIN_PRINTABLE, MAX_PRINTABLE);

  int score = 0;
  float remainingTime = INITIAL_TIME;
  bool isGameActive = true;
  char currentChar = static_cast<char>(dist(gen));

  sf::Clock gameClock;
  float lastTime = gameClock.getElapsedTime().asSeconds();

  auto updateTargetChar = [&]() {
    targetCharText.setString(std::string(1, currentChar));
    centerText(targetCharText);
  };
  updateTargetChar();

  auto updateScoreText = [&]() {
    scoreText.setString("Score: " + std::to_string(score));
  };
  updateScoreText();

  auto updateTimerText = [&]() {
    std::ostringstream ss;
    ss << "Time: " << std::fixed << std::setprecision(1) << remainingTime;
    timerText.setString(ss.str());
  };
  updateTimerText();

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();

      if (isGameActive) {
        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
          uint32_t codepoint = textEvent->unicode;
          if (codepoint >= MIN_PRINTABLE && codepoint <= MAX_PRINTABLE) {
            char enteredChar = static_cast<char>(codepoint);
            if (enteredChar == currentChar) {
              score += SCORE_PER_HIT;
              updateScoreText();
              currentChar = static_cast<char>(dist(gen));
              updateTargetChar();
            } else {
              remainingTime -= PENALTY_TIME;
              if (remainingTime < 0) remainingTime = 0;
              updateTimerText();
            }
          }
        }
      }
    }

    float currentTime = gameClock.getElapsedTime().asSeconds();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (isGameActive) {
      remainingTime -= deltaTime;
      if (remainingTime <= 0) {
        remainingTime = 0;
        isGameActive = false;
        finalScoreText.setString("Final score: " + std::to_string(score));
        centerText(finalScoreText);
        if (score > 20) {
          gameOverText.setString("GREAT JOB!");
          gameOverText.setFillColor(sf::Color::Green);
        } else {
          gameOverText.setString("TRY AGAIN");
          gameOverText.setFillColor(sf::Color::Red);
        }
      }
      updateTimerText();
    }

    window.clear(sf::Color::Black);
    if (isGameActive) {
      window.draw(targetCharText);
      window.draw(scoreText);
      window.draw(timerText);
    } else {
      window.draw(gameOverText);
      window.draw(finalScoreText);
    }
    window.display();
  }

  return 0;
}
