#include "game.h"

#include <iostream>
#include <string>

#include "constants.h"

Game::Game()
    : window(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}),
             "Typing Game"),
      playing(true),
      timeLeft(Constants::START_TIME),
      score(Constants::START_POSITION),
      currentSymbol('a') {
  window.setFramerateLimit(Constants::FPS_LIMIT);

  if (!font.openFromFile("arial.ttf")) {
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
      std::cout << "Font not loaded!" << std::endl;
    }
  }

  symbolText = std::make_unique<sf::Text>(font);
  scoreText = std::make_unique<sf::Text>(font);
  timerText = std::make_unique<sf::Text>(font);
  gameOverText = std::make_unique<sf::Text>(font);

  currentSymbol = symbolGenerator.generate();
  initTexts();
}

void Game::initTexts() {
  symbolText->setString(std::string(Constants::START_ONE, currentSymbol));
  symbolText->setCharacterSize(Constants::SYMBOL_SIZE);
  symbolText->setFillColor(Constants::TEXT_COLOR);
  symbolText->setPosition({Constants::LET_POS_X, Constants::LET_POS_Y});

  scoreText->setString("Score: 0");
  scoreText->setCharacterSize(Constants::SCORE_SIZE);
  scoreText->setFillColor(Constants::TEXT_COLOR);
  scoreText->setPosition({Constants::SCORE_POS_X, Constants::SCORE_POS_Y});

  timerText->setString("Time: " +
                       std::to_string(static_cast<int>(Constants::START_TIME)));
  timerText->setCharacterSize(Constants::TIMER_SIZE);
  timerText->setFillColor(Constants::TEXT_COLOR);
  timerText->setPosition({Constants::TIMER_POS_X, Constants::TIMER_POS_Y});

  gameOverText->setString("GAME OVER!\nYour score: 0\nPress ESC to exit");
  gameOverText->setCharacterSize(Constants::GAMEOVER_SIZE);
  gameOverText->setFillColor(Constants::TEXT2_COLOR);
  gameOverText->setPosition({Constants::OV_POS_X, Constants::OV_POS_Y});
}

void Game::newSymbol() {
  currentSymbol = symbolGenerator.generate();
  symbolText->setString(std::string(Constants::START_ONE, currentSymbol));
}

void Game::processEvents() {
  while (const std::optional<sf::Event> event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (playing) {
        char pressed = inputHandler.getPressedChar(keyPressed->code);

        if (pressed == currentSymbol) {
          score = scoreManager.increase(score);
          scoreManager.updateText(*scoreText, score);
          newSymbol();
        } else if (pressed != '\0') {
          timeLeft = timer.penalty(timeLeft, Constants::PENALTY_TIME);
        }
      } else {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }
    }
  }
}

void Game::update(float deltaTime) {
  if (!playing) return;

  timeLeft = timer.update(timeLeft, deltaTime);
  timer.updateText(*timerText, timeLeft);

  if (timer.isExpired(timeLeft)) {
    playing = false;
    gameOverText->setString("GAME OVER!\nYour score: " + std::to_string(score) +
                            "\nPress ESC to exit");
  }
}

void Game::render() {
  window.clear(Constants::BACKGROUND_COLOR);

  window.draw(*symbolText);
  window.draw(*scoreText);
  window.draw(*timerText);

  if (!playing) {
    window.draw(*gameOverText);
  }

  window.display();
}

void Game::run() {
  while (window.isOpen()) {
    float deltaTime = deltaClock.restart().asSeconds();

    processEvents();
    update(deltaTime);
    render();
  }
}
