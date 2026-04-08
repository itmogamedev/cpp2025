#include "game.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <string>

char getRandomSymbol(std::mt19937& generator) {
  const std::string symbols =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789"
      "!@#$%^&*()-_=+?";

  std::uniform_int_distribution<int> dist(0,
                                          static_cast<int>(symbols.size()) - 1);
  return symbols[dist(generator)];
}

void runGame(float width, float height, float timeLeft, const float wrongTime) {
  unsigned int intWidth = static_cast<unsigned int>(width);
  unsigned int intHeight = static_cast<unsigned int>(height);

  sf::RenderWindow window(sf::VideoMode({intWidth, intHeight}),
                          sf::String(L"Тайпинг-тренажер"));
  window.setFramerateLimit(60);

  sf::Font font;
  if (!font.openFromFile("arial.ttf")) return;

  sf::Text symbolText(font, "", 180);
  symbolText.setPosition({width / 2 - 45.0f, height / 2 - 90.0f});
  symbolText.setFillColor(sf::Color::White);

  sf::Text scoreText(font, "", 36);
  scoreText.setPosition({10.0f, 10.0f});
  scoreText.setFillColor(sf::Color::White);

  sf::Text timerText(font, "", 36);
  timerText.setPosition({width - 180.0f, 10.0f});
  timerText.setFillColor(sf::Color::White);

  sf::Text gameOverText(font, "", 64);
  gameOverText.setPosition({width / 2 - 200.0f, height / 2 - 130.0f});
  gameOverText.setFillColor(sf::Color::White);

  std::random_device rd;
  std::mt19937 generator(rd());

  char currentSymbol = getRandomSymbol(generator);
  int score = 0;
  bool gameOver = false;

  sf::Clock clock;

  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();

    if (!gameOver) {
      timeLeft -= deltaTime;

      if (timeLeft <= 0.0f) {
        timeLeft = 0.0f;
        gameOver = true;
      }
    }

    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();

      if (!gameOver) {
        if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
          char32_t entered = textEntered->unicode;

          if (entered >= 32 &&
              entered <= 126)  // диапозон обычных печатных символов ASCII
          {
            if (entered == static_cast<char32_t>(currentSymbol)) {
              score++;
              currentSymbol = getRandomSymbol(generator);
            } else {
              timeLeft -= wrongTime;

              if (timeLeft <= 0.f) {
                timeLeft = 0.f;
                gameOver = true;
              }
            }
          }
        }
      }
    }

    symbolText.setString(std::string(1, currentSymbol));
    scoreText.setString(sf::String(L"Счёт: ") + std::to_string(score));
    timerText.setString(sf::String(L"Время: ") +
                        std::to_string(static_cast<int>(std::ceill(timeLeft))));

    if (gameOver) {
      gameOverText.setString(sf::String(L"Игра окончена\n"
                                        L"Финальный счёт: ") +
                             std::to_string(score) +
                             sf::String(L"\nМожете закрыть данное окно"));
    } else {
      gameOverText.setString("");
    }

    window.clear(sf::Color(20, 20, 20));

    if (!gameOver) window.draw(symbolText);

    window.draw(scoreText);
    window.draw(timerText);

    if (gameOver) window.draw(gameOverText);

    window.display();
  }
}
