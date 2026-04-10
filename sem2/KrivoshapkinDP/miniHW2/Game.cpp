#include "Game.h"

#include <iostream>
#include <string>

#include "Constants.h"

Game::Game()
    : window(sf::VideoMode({constants::kWindowWidth, constants::kWindowHeight}),
             "OSU"),
      timerText(font, "", constants::kTimerText),
      scoreText(font, "", constants::kScoreText),
      gameOverText(font, "Game Over!", constants::kGameOverText),
      finalScoreText(font, "", constants::kFinalScoreText),
      rng(std::random_device{}()),
      distX(constants::kCircleRadius,
            constants::kWindowWidth - constants::kCircleRadius),
      distY(constants::kCircleRadius,
            constants::kWindowHeight - constants::kCircleRadius),
      distVel(-constants::kCircleSpeed, constants::kCircleSpeed),
      timeLeft(constants::kInitialTime),
      score(0),
      gameOver(false) {
  if (!font.openFromFile("fonts/arial.ttf")) {
    std::cerr << "Error: can't open font! \n";
  }

  timerText.setFillColor(sf::Color::White);
  timerText.setPosition({constants::kTimerTextPosX, constants::kTimerTextPosY});
  timerText.setString("Time: 30s");

  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({constants::kScoreTextPosX, constants::kScoreTextPosY});
  scoreText.setString("Score: 0");

  gameOverText.setFillColor(sf::Color::Red);
  sf::FloatRect boundsGo = gameOverText.getLocalBounds();
  gameOverText.setOrigin({boundsGo.size.x / constants::kSizeDelX,
                          boundsGo.size.y / constants::kSizeDelY});
  gameOverText.setPosition({constants::kWindowWidth / constants::kSetPosDelX,
                            constants::kWindowHeight / constants::kSetPosDelY -
                                constants::kSetPosDelYm});

  finalScoreText.setFillColor(sf::Color::White);
  finalScoreText.setPosition(
      {constants::kWindowWidth / constants::kSetPosDelX,
       constants::kWindowHeight / constants::kSetPosDelY +
           constants::kSetPosDelYp});

  for (int i = 0; i < constants::kCircleCount; ++i) {
    sf::Color color =
        (i % 2 == 0) ? sf::Color(255, 201, 14) : sf::Color(181, 230, 29);
    circles.emplace_back(constants::kCircleRadius, color, randomPosition(),
                         randomVelocity());
  }
  clock.restart();
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    float deltaTime = clock.restart().asSeconds();
    if (!gameOver) {
      update(deltaTime);
    }
    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (const auto* mouseButton =
                   event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mouseButton->button == sf::Mouse::Button::Left) {
        sf::Vector2f mousePos(static_cast<float>(mouseButton->position.x),
                              static_cast<float>(mouseButton->position.y));
        handleClick(mousePos);
      }
    }
  }
}

void Game::update(float deltaTime) {
  if (gameOver) return;
  timeLeft -= deltaTime;
  if (timeLeft <= 0.0f) {
    timeLeft = 0.0f;
    gameOver = true;
    finalScoreText.setString("Score: " + std::to_string(score));
    sf::FloatRect bounds = finalScoreText.getLocalBounds();
    finalScoreText.setOrigin({bounds.size.x / constants::kSizeDelX,
                              bounds.size.y / constants::kSizeDelY});
  }

  for (auto& circle : circles) {
    circle.update(deltaTime, window.getSize());
  }

  timerText.setString("Time: " + std::to_string(static_cast<int>(timeLeft)) +
                      "s");
  scoreText.setString("Score: " + std::to_string(score));
}

void Game::render() {
  window.clear(sf::Color(133, 162, 230));
  for (const auto& circle : circles) {
    circle.draw(window);
  }
  window.draw(timerText);
  window.draw(scoreText);
  if (gameOver) {
    window.draw(gameOverText);
    window.draw(finalScoreText);
  }
  window.display();
}

void Game::handleClick(const sf::Vector2f& mousePos) {
  if (gameOver) return;

  bool hit = false;
  for (auto& circle : circles) {
    if (circle.contains(mousePos)) {
      hit = true;
      resetCircle(circle);
      score++;
      break;
    }
  }

  if (!hit) {
    timeLeft -= constants::kMissTimePenalty;
    if (timeLeft < constants::kTimeLeft) {
      timeLeft = constants::kTimeLeft;
      gameOver = true;
      finalScoreText.setString("Score: " + std::to_string(score));
      sf::FloatRect bounds = finalScoreText.getLocalBounds();
      finalScoreText.setOrigin({bounds.size.x / constants::kSizeDelX,
                                bounds.size.y / constants::kSizeDelY});
    }
  }
}

void Game::resetCircle(Circle& circle) { circle.setPosition(randomPosition()); }

sf::Vector2f Game::randomPosition() { return {distX(rng), distY(rng)}; }

sf::Vector2f Game::randomVelocity() { return {distVel(rng), distVel(rng)}; }
