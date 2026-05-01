#include "Game.h"

#include <cmath>
#include <iostream>

Game::Game()
    : window(sf::VideoMode({800, 600}), "OSUuuu.."),
      ui(font),
      gen(rd()),
      disX(radius, windowWidth - radius),
      disY(radius, windowHeight - radius),
      disSpeed(30, 80),
      score(0),
      timeLeft(30.0f),
      gameActive(true) {
  if (!font.openFromFile("font.otf")) {
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
    MovingCircle mc;
    mc.shape = sf::CircleShape(radius);
    mc.shape.setFillColor(sf::Color::Cyan);
    mc.shape.setPosition(getRandomPosition());
    mc.velocity = getRandomVelocity();
    circles.push_back(mc);
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
  for (auto& circle : circles) {
    circle.shape.move(circle.velocity * deltaTime);

    wrapAround(circle);
  }
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

  // Рисуем круги
  for (const auto& circle : circles) {
    window.draw(circle.shape);
  }

  // Рисуем UI
  ui.draw(window);

  window.display();
}

void Game::handleMouseClick(const sf::Vector2i& mousePos) {
  bool hit = false;

  for (auto& circle : circles) {
    sf::Vector2f circleCenter =
        circle.shape.getPosition() + sf::Vector2f(radius, radius);

    float dx = mousePos.x - circleCenter.x;
    float dy = mousePos.y - circleCenter.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < radius) {
      hit = true;
      score++;
      ui.updateScore(score);

      circle.shape.setPosition(getRandomPosition());
      circle.velocity = getRandomVelocity();

      // Сброс цветов
      for (auto& c : circles) {
        c.shape.setFillColor(sf::Color::Cyan);
      }
      break;
    }
  }

  if (!hit) {
    for (auto& circle : circles) {
      circle.shape.setFillColor(sf::Color::Red);
    }
    timeLeft -= 2.0f;
    ui.updateTimer(timeLeft);
  }
}

sf::Vector2f Game::getRandomPosition() {
  return sf::Vector2f(disX(gen) - radius, disY(gen) - radius);
}

sf::Vector2f Game::getRandomVelocity() {
  float speed = disSpeed(gen);
  int direction = gen() % 8;  // 8 направлений

  switch (direction) {
    case 0:
      return sf::Vector2f(speed, speed);
    case 1:
      return sf::Vector2f(speed, -speed);
    case 2:
      return sf::Vector2f(-speed, speed);
    case 3:
      return sf::Vector2f(-speed, -speed);
    case 4:
      return sf::Vector2f(speed, 0);
    case 5:
      return sf::Vector2f(-speed, 0);
    case 6:
      return sf::Vector2f(0, speed);
    default:
      return sf::Vector2f(0, -speed);
  }
}

void Game::wrapAround(MovingCircle& circle) {
  sf::Vector2f pos = circle.shape.getPosition();

  // Горизонтальная телепортация
  if (pos.x + radius * 2 < 0) {
    circle.shape.setPosition(sf::Vector2f((float)windowWidth, pos.y));
  } else if (pos.x > windowWidth) {
    circle.shape.setPosition(sf::Vector2f(-radius * 2, pos.y));
  }

  // Вертикальная телепортация
  if (pos.y + radius * 2 < 0) {
    circle.shape.setPosition(sf::Vector2f(pos.x, (float)windowHeight));
  } else if (pos.y > windowHeight) {
    circle.shape.setPosition(sf::Vector2f(pos.x, -radius * 2));
  }
}
