#include <SFML/Graphics.hpp>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "CircleTarget.h"
#include "Utils.h"

int main() {
  const unsigned int windowWidth = 1000;
  const unsigned int windowHeight = 700;

  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}),
                          "OSU Mini Game");
  window.setFramerateLimit(60);

  std::cout << "Current path: " << std::filesystem::current_path() << "\n";

  sf::Font font;
  if (!font.openFromFile("arial.ttf")) {
    std::cout << "Font not found!\n";
    std::cin.get();
    return 1;
  }

  sf::Text scoreText(font, "", 28);
  scoreText.setPosition({20.f, 20.f});
  scoreText.setFillColor(sf::Color::Black);

  sf::Text timerText(font, "", 28);
  timerText.setPosition({20.f, 60.f});
  timerText.setFillColor(sf::Color::Black);

  sf::Text endText(font, "", 40);
  endText.setPosition({250.f, 300.f});
  endText.setFillColor(sf::Color::Black);

  const int circleCount = 5;
  const float radius = 35.f;
  std::vector<CircleTarget> circles;

  for (int i = 0; i < circleCount; i++) {
    CircleTarget target;
    target.shape.setRadius(radius);
    target.shape.setFillColor(sf::Color::Red);
    target.shape.setPosition(RandomPosition(radius,
                                            static_cast<float>(windowWidth),
                                            static_cast<float>(windowHeight)));
    target.velocity = {RandomFloat(-250.f, 250.f), RandomFloat(-250.f, 250.f)};
    circles.push_back(target);
  }

  int score = 0;
  float timeLeft = 20.f;
  bool gameOver = false;

  sf::Clock deltaClock;

  while (window.isOpen()) {
    float dt = deltaClock.restart().asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      if (!gameOver) {
        if (const auto* mousePressed =
                event->getIf<sf::Event::MouseButtonPressed>()) {
          if (mousePressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(
                {mousePressed->position.x, mousePressed->position.y});

            bool hit = false;

            for (auto& circle : circles) {
              if (IsMouseInsideCircle(circle.shape, mousePos)) {
                score++;

                circle.shape.setPosition(
                    RandomPosition(radius, static_cast<float>(windowWidth),
                                   static_cast<float>(windowHeight)));

                circle.velocity = {RandomFloat(-250.f, 250.f),
                                   RandomFloat(-250.f, 250.f)};

                hit = true;
                break;
              }
            }

            if (!hit) {
              timeLeft -= 1.5f;
              if (timeLeft < 0.f) {
                timeLeft = 0.f;
              }
            }
          }
        }
      }
    }

    if (!gameOver) {
      timeLeft -= dt;
      if (timeLeft <= 0.f) {
        timeLeft = 0.f;
        gameOver = true;
      }

      for (auto& circle : circles) {
        sf::Vector2f pos = circle.shape.getPosition();
        pos += circle.velocity * dt;
        circle.shape.setPosition(pos);

        if (pos.x <= 0.f || pos.x + radius * 2.f >= windowWidth) {
          circle.velocity.x *= -1.f;
        }

        if (pos.y <= 0.f || pos.y + radius * 2.f >= windowHeight) {
          circle.velocity.y *= -1.f;
        }
      }
    }

    scoreText.setString("Score: " + std::to_string(score));
    timerText.setString("Time: " + std::to_string((int)std::ceil(timeLeft)));

    if (gameOver) {
      endText.setString("Game Over\nFinal score: " + std::to_string(score));
    }

    window.clear(sf::Color::White);

    if (!gameOver) {
      for (auto& circle : circles) {
        window.draw(circle.shape);
      }
      window.draw(scoreText);
      window.draw(timerText);
    } else {
      window.draw(scoreText);
      window.draw(timerText);
      window.draw(endText);
    }

    window.display();
  }

  return 0;
}