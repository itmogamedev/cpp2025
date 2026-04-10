#include "Game.h"

#include <cmath>
#include <iostream>

Game::Game()
    : window(sf::VideoMode({800, 600}), "OSUuuu.."),
      ui(font)
      ,
      gen(rd()),
      disX(50, 750),
      disY(50, 550),
      score(0),
      radius(50),
      timeLeft(30.0f),
      gameActive(true) {

  if (!font.openFromFile("TAWOGTheSpoon-Regular.otf")) {
    std::cerr << "Error loading font!" << std::endl;
  }

  initGame();
}

void Game::run() {
  while (window.isOpen()) {
    float deltaTime = clock.restart().asSeconds();

    processEvents();
    update(deltaTime);
    render();
  }
}

void Game::initGame() {
  circles.clear();
  for (int i = 0; i < 5; i++) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition(sf::Vector2f(disX(gen) - radius, disY(gen) - radius));
    circles.push_back(circle);
  }

  score = 0;
  timeLeft = 30.0f;
  gameActive = true;

  ui.updateScore(score);
  ui.updateTimer(timeLeft);
  ui.hideGameOver();
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
        initGame();
      }
    }

    if (gameActive) {
      if (const auto* mousePressed =
              event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left) {
          handleMouseClick(mousePressed->position);
        }
      }
    }
  }
}

void Game::update(float deltaTime) {
  if (gameActive) {
    timeLeft -= deltaTime;
    ui.updateTimer(timeLeft);

    if (timeLeft <= 0) {
      gameActive = false;
      ui.showGameOver(score);
    }
  }
}

void Game::render() {
  window.clear(sf::Color::Black);

  // –исуем круги
  for (const auto& circle : circles) {
    window.draw(circle);
  }

  // –исуем UI
  ui.draw(window);

  window.display();
}

void Game::handleMouseClick(const sf::Vector2i& mousePos) {
  bool hit = false;

  for (auto& circle : circles) {
    float circleX = circle.getPosition().x + radius;
    float circleY = circle.getPosition().y + radius;

    float dx = mousePos.x - circleX;
    float dy = mousePos.y - circleY;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < radius) {
      hit = true;
      score++;
      ui.updateScore(score);

      circle.setPosition(sf::Vector2f(disX(gen) - radius, disY(gen) - radius));

      // —брос цветов
      for (auto& c : circles) {
        c.setFillColor(sf::Color::Cyan);
      }
      break;
    }
  }

  if (!hit) {
    for (auto& circle : circles) {
      circle.setFillColor(sf::Color::Red);
    }
    timeLeft -= 2.0f;
    ui.updateTimer(timeLeft);
  }
}
