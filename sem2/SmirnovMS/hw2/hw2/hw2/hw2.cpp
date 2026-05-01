#include <sstream>
#include <string>

#include "hw2.h"

Game::Game()
    : window(sf::VideoMode({900, 600}), "Typing Trainer"),
      rng(std::random_device{}()),
      dist(33, 126),
      targetText(font, "", 120),
      scoreText(font, "", 30),
      timeText(font, "", 30),
      endText(font, "", 40) {
  font.openFromFile("arial.ttf");
}

void Game::run() {
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    processEvents();
    update(dt);
    render();
  }
}

void Game::reset() {
  score = 0;
  timeLeft = 20.f;
  penalty = 1.5f;
  isGameOver = false;
  newChar();
}

void Game::newChar() { currentChar = static_cast<char>(dist(rng)); }

void Game::handleInput(char c) {
  if (isGameOver) return;

  if (c == currentChar) {
    score++;
    newChar();
  } else {
    timeLeft -= penalty;
    if (timeLeft < 0) timeLeft = 0;
  }
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) window.close();

    if (const auto* txt = event->getIf<sf::Event::TextEntered>()) {
      char c = static_cast<char>(txt->unicode);
      if (c >= 33 && c <= 126) handleInput(c);
    }

    if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
      if (isGameOver && key->code == sf::Keyboard::Key::Enter) reset();
    }
  }
}

void Game::update(float dt) {
  if (!isGameOver) {
    timeLeft -= dt;
    if (timeLeft <= 0) {
      timeLeft = 0;
      isGameOver = true;
    }
  }

  targetText.setString(std::string(1, currentChar));
  targetText.setPosition({400, 200});

  scoreText.setString("Score: " + std::to_string(score));
  scoreText.setPosition({20, 550});

  std::ostringstream ss;
  ss << "Time: " << (int)timeLeft;
  timeText.setString(ss.str());
  timeText.setPosition({750, 550});

  if (isGameOver) {
    endText.setString("Game Over\nScore: " + std::to_string(score) +
                      "\nPress Enter");
    endText.setPosition({300, 200});
  }
}

void Game::render() {
  window.clear(sf::Color(30, 30, 40));

  window.draw(targetText);
  window.draw(scoreText);
  window.draw(timeText);

  if (isGameOver) window.draw(endText);

  window.display();
}