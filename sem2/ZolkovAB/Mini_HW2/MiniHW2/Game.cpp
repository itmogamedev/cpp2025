#include "Game.h"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>

#include "Utils.h"

Game::Game()
    : window(sf::VideoMode({windowWidth, windowHeight}), "OSU Mini Game"),
      scoreText(font, "", 28),
      timerText(font, "", 28),
      endText(font, "", 40) {
  InitWindow();

  std::cout << "Current path: " << std::filesystem::current_path() << "\n";

  if (!InitFont()) {
    window.close();
    return;
  }

  InitText();
  InitCircles();
}

void Game::InitWindow() { window.setFramerateLimit(60); }

bool Game::InitFont() {
  if (!font.openFromFile("arial.ttf")) {
    std::cout << "Font not found!\n";
    std::cin.get();
    return false;
  }
  return true;
}

void Game::InitText() {
  scoreText.setPosition({20.f, 20.f});
  scoreText.setFillColor(sf::Color::Black);

  timerText.setPosition({20.f, 60.f});
  timerText.setFillColor(sf::Color::Black);

  endText.setPosition({250.f, 300.f});
  endText.setFillColor(sf::Color::Black);
}

void Game::InitCircles() {
  circles.clear();

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
}

void Game::ProcessEvents() {
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
          HandleMouseClick(mousePos);
        }
      }
    }
  }
}

void Game::HandleMouseClick(sf::Vector2f mousePos) {
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

void Game::Update(float deltaTime) {
  if (gameOver) {
    UpdateText();
    return;
  }

  timeLeft -= deltaTime;
  if (timeLeft <= 0.f) {
    timeLeft = 0.f;
    gameOver = true;
  }

  UpdateCircles(deltaTime);
  UpdateText();
}

void Game::UpdateCircles(float deltaTime) {
  for (auto& circle : circles) {
    sf::Vector2f pos = circle.shape.getPosition();
    pos += circle.velocity * deltaTime;
    circle.shape.setPosition(pos);

    if (pos.x <= 0.f || pos.x + radius * 2.f >= windowWidth) {
      circle.velocity.x *= -1.f;
    }

    if (pos.y <= 0.f || pos.y + radius * 2.f >= windowHeight) {
      circle.velocity.y *= -1.f;
    }
  }
}

void Game::UpdateText() {
  scoreText.setString("Score: " + std::to_string(score));
  timerText.setString("Time: " + std::to_string((int)std::ceil(timeLeft)));

  if (gameOver) {
    endText.setString("Game Over\nFinal score: " + std::to_string(score));
  }
}

void Game::Render() {
  window.clear(sf::Color::White);

  if (!gameOver) {
    for (auto& circle : circles) {
      window.draw(circle.shape);
    }
  }

  window.draw(scoreText);
  window.draw(timerText);

  if (gameOver) {
    window.draw(endText);
  }

  window.display();
}

void Game::Run() {
  while (window.isOpen()) {
    float deltaTime = deltaClock.restart().asSeconds();

    ProcessEvents();
    Update(deltaTime);
    Render();
  }
}