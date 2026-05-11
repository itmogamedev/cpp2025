#include "Game.h"

#include <cstdlib>
#include <ctime>

Game::Game()
    : mWindow(sf::VideoMode({800, 600}), "Typing Trainer"),
      mTargetText(mFont),
      mScoreText(mFont),
      mTargetChar(' '),
      mScore(0),
      mTimeLeft(15.0f),
      mIsGameOver(false) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  if (!mFont.openFromFile("arial.ttf")) {
    // Font loading failed – handle error (e.g., log or exit)
  }

  mTargetText.setCharacterSize(150);
  mTargetText.setFillColor(sf::Color(0, 255, 150));

  mScoreText.setCharacterSize(30);
  mScoreText.setFillColor(sf::Color::White);
  mScoreText.setPosition({20.f, 20.f});

  generateNewTarget();
}

void Game::generateNewTarget() {
  mTargetChar = static_cast<char>(33 + (std::rand() % 94));
  mTargetText.setString(std::string(1, mTargetChar));

  sf::FloatRect textRect = mTargetText.getLocalBounds();
  mTargetText.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                         textRect.position.y + textRect.size.y / 2.0f});
  mTargetText.setPosition({400.0f, 300.0f});
}

void Game::run() {
  sf::Clock clock;
  while (mWindow.isOpen()) {
    sf::Time deltaTime = clock.restart();
    processEvents();
    if (!mIsGameOver) {
      update(deltaTime);
    }
    render();
  }
}

void Game::processEvents() {
  while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      mWindow.close();
    }

    if (!mIsGameOver) {
      if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
        if (textEvent->unicode < 128) {
          char entered = static_cast<char>(textEvent->unicode);
          if (entered == mTargetChar) {
            mScore++;
            mTimeLeft += 1.0f;
            generateNewTarget();
          } else {
            mTimeLeft -= 2.0f;
          }
        }
      }
    }
  }
}

void Game::update(sf::Time deltaTime) {
  mTimeLeft -= deltaTime.asSeconds();
  if (mTimeLeft <= 0.0f) {
    mTimeLeft = 0.0f;
    mIsGameOver = true;
  }

  mScoreText.setString("Score: " + std::to_string(mScore) +
                       " | Time: " + std::to_string(static_cast<int>(mTimeLeft)) + "s");
}

void Game::render() {
  mWindow.clear(sf::Color(40, 44, 52));

  if (!mIsGameOver) {
    mWindow.draw(mScoreText);
    mWindow.draw(mTargetText);
  } else {
    sf::Text gameOverText(mFont,
                          "GAME OVER\nFinal Score: " + std::to_string(mScore), 50);
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect rect = gameOverText.getLocalBounds();
    gameOverText.setOrigin({rect.size.x / 2.0f, rect.size.y / 2.0f});
    gameOverText.setPosition({400.0f, 300.0f});
    mWindow.draw(gameOverText);
  }

  mWindow.display();
}
