#include "Game.h"

#include <sstream>

Game::Game()
    : window_(sf::VideoMode(800, 600), "Game"),
      score_(0),
      timeLeft_(30.f),
      gameOver_(false) {
  window_.setFramerateLimit(60);

  for (int i = 0; i < 5; ++i) {
    circles_.emplace_back(25.f, window_.getSize());
  }

  font_.loadFromFile("arial.ttf");

  scoreText_.setFont(font_);
  scoreText_.setCharacterSize(24);
  scoreText_.setPosition(10, 10);

  timeText_.setFont(font_);
  timeText_.setCharacterSize(24);
  timeText_.setFillColor(sf::Color::Red);
  timeText_.setPosition(650, 10);
}

void Game::run() {
  sf::Clock clock;

  while (window_.isOpen()) {
    float dt = clock.restart().asSeconds();
    processEvents();
    update(dt);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;

  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
    }

    if (!gameOver_ &&
        event.type == sf::Event::MouseButtonPressed) {
      sf::Vector2f pos = window_.mapPixelToCoords(
          sf::Mouse::getPosition(window_));
      handleClick(pos);
    }
  }
}

void Game::handleClick(sf::Vector2f pos) {
  bool hit = false;

  for (auto& circle : circles_) {
    if (circle.contains(pos)) {
      circle.respawn(window_.getSize());
      score_++;
      hit = true;
      break;
    }
  }

  if (!hit) {
    timeLeft_ -= 2.f;
  }
}

void Game::update(float dt) {
  if (gameOver_) {
    return;
  }

  timeLeft_ -= dt;

  if (timeLeft_ <= 0) {
    gameOver_ = true;
    timeLeft_ = 0;
    return;
  }

  for (auto& circle : circles_) {
    circle.update(dt);
  }

  std::stringstream scoreStream;
  scoreStream << "Score: " << score_;
  scoreText_.setString(scoreStream.str());

  std::stringstream timeStream;
  timeStream << "Time: " << static_cast<int>(timeLeft_);
  timeText_.setString(timeStream.str());
}

void Game::render() {
  window_.clear();

  for (auto& circle : circles_) {
    circle.draw(window_);
  }

  window_.draw(scoreText_);
  window_.draw(timeText_);

  if (gameOver_) {
    sf::Text over;
    over.setFont(font_);
    over.setCharacterSize(40);
    over.setFillColor(sf::Color::White);
    over.setString("GAME OVER\nScore: " +
                   std::to_string(score_));
    over.setPosition(200, 250);
    window_.draw(over);
  }

  window_.display();
}