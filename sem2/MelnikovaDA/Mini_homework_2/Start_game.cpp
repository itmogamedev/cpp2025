#include "Start_game.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <string>
#include <vector>

int Game::runGame() {
  int score = 0;
  auto desktop = sf::VideoMode::getDesktopMode();

  sf::Vector2u windowSize(desktop.size.x - 100, desktop.size.y - 100);

  sf::RenderWindow window(sf::VideoMode(windowSize), "OSU home",
                          sf::State::Windowed);

  window.setPosition({static_cast<int>((desktop.size.x - windowSize.x) / 2),
                      static_cast<int>((desktop.size.y - windowSize.y) / 2)});

  sf::Font font;
  if (!font.openFromFile("C:/Users/Diana/Desktop/c++/Sem2/Mini_homework_2/"
                         "Mini_hw_2/arial.ttf"))
    return -1;

  sf::Text timerText(font);
  sf::Text scoreText(font);
  sf::Text gameOverText(font);
  scoreText.setCharacterSize(30);
  scoreText.setFillColor(sf::Color::Black);
  scoreText.setPosition({10.f, 50.f});
  timerText.setCharacterSize(30);
  timerText.setFillColor(sf::Color::Black);
  timerText.setPosition({10.f, 10.f});
  gameOverText.setString("GAME OVER");
  gameOverText.setCharacterSize(60);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setPosition(
      {windowSize.x / 2.f - 150.f, windowSize.y / 2.f - 50.f});

  sf::Clock clock;
  const int TIME_LIMIT = 60;
  bool gameOver = false;
  int penaltyTime = 0;

  std::mt19937 rng(std::random_device{}());

  std::vector<sf::CircleShape> circles(5, sf::CircleShape(75.f));
  for (auto& circle : circles) {
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(3.f);

    circle.setOrigin({circle.getRadius(), circle.getRadius()});
  }

  auto spawnAllCircles = [&]() {
    for (auto& circle : circles) {
      float radius = circle.getRadius();

      std::uniform_real_distribution<float> distX(radius,
                                                  windowSize.x - radius);
      std::uniform_real_distribution<float> distY(radius,
                                                  windowSize.y - radius);

      circle.setPosition({distX(rng), distY(rng)});
    }
  };

  spawnAllCircles();

  while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) window.close();
      if (!gameOver && event->is<sf::Event::MouseButtonPressed>()) {
        auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();

        if (mouseEvent->button == sf::Mouse::Button::Left) {
          sf::Vector2f mousePos = window.mapPixelToCoords(mouseEvent->position);

          bool hit = false;

          for (auto& circle : circles) {
            if (circle.getGlobalBounds().contains(mousePos)) {
              score += 5;

              float radius = circle.getRadius();

              std::uniform_real_distribution<float> distX(
                  radius, windowSize.x - radius);
              std::uniform_real_distribution<float> distY(
                  radius, windowSize.y - radius);

              circle.setPosition({distX(rng), distY(rng)});

              hit = true;
              break;
            }
          }

          if (!hit) {
            penaltyTime += 5;
          }
        }
      }

      int timeLeft = TIME_LIMIT -
                     static_cast<int>(clock.getElapsedTime().asSeconds()) -
                     penaltyTime;

      if (timeLeft <= 0) {
        gameOver = true;
        timeLeft = 0;
      }

      timerText.setString("Time: " + std::to_string(timeLeft));
      scoreText.setString("Score: " + std::to_string(score));
      window.clear(sf::Color(255, 105, 180));

      if (!gameOver) {
        for (auto& circle : circles) {
          window.draw(circle);
        }
      } else {
        window.draw(gameOverText);

        sf::Text finalScoreText(font);
        finalScoreText.setString("Final Score: " + std::to_string(score));
        finalScoreText.setCharacterSize(40);
        finalScoreText.setFillColor(sf::Color::Black);

        finalScoreText.setPosition(
            {windowSize.x / 2.f - 150.f, windowSize.y / 2.f + 20.f});

        window.draw(finalScoreText);
      }

      window.draw(timerText);
      window.draw(scoreText);
      window.display();
    }
  }
}
