#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "OSU at home!"),
      score(0),
      timeLeft(30.f),
      isGameOver(false) {
  font.loadFromFile("minecraft.ttf");

  scoreText.setFont(font);
  scoreText.setCharacterSize(24);
  scoreText.setPosition(10, 10);

  timerText.setFont(font);
  timerText.setCharacterSize(24);
  timerText.setPosition(10, 40);

  gameOverText.setFont(font);
  gameOverText.setCharacterSize(40);
  gameOverText.setPosition(150, 250);

  for (int i = 0; i < 5; i++) {
    Circle c(30.f);
    c.setRandomPosition(750, 550);
    c.setRandomVelocity(50.f, 250.f);
    circles.push_back(c);
  }
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    update();
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();

    if (!isGameOver && event.type == sf::Event::MouseButtonPressed) {
      handleClick(sf::Mouse::getPosition(window));
    }
  }
}

void Game::handleClick(sf::Vector2i mousePos) {
  bool hit = false;

  for (auto& circle : circles) {
    if (circle.isClicked(mousePos)) {
      score++;
      circle.setRandomPosition(750, 550);
      circle.setRandomVelocity(50.f, 150.f);
      hit = true;
      break;
    }
  }

  if (!hit) {
    timeLeft -= 1.f;
  }
}

void Game::update() {
  float dt = clock.restart().asSeconds();

  if (!isGameOver) {
    timeLeft -= dt;

    for (auto& circle : circles) {
      circle.update(dt, 800, 600);
    }

    if (timeLeft <= 0) {
      isGameOver = true;
      gameOverText.setString("Game Over! Score: " + std::to_string(score));
    }

    scoreText.setString("Score: " + std::to_string(score));
    timerText.setString("Time: " + std::to_string((int)timeLeft));
  }
}

void Game::render() {
  window.clear(sf::Color(20, 20, 20));

  for (auto& circle : circles) {
    circle.draw(window);
  }

  window.draw(scoreText);
  window.draw(timerText);

  if (isGameOver) {
    window.draw(gameOverText);
  }

  window.display();
}
