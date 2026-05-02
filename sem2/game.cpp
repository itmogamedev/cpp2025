#include "Game.h"

#include <cctype>
#include <ctime>
#include <iostream>
#include <sstream>

#include "Constants.h"
#include "Utils.h"

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
             "Typing Trainer - Uppercase Only"),
      gameActive(true),
      score(0),
      timeRemaining(INITIAL_TIME),
      currentChar(getRandomChar()) {
  window.setFramerateLimit(FRAMERATE_LIMIT);

  if (!font.openFromFile("arial.ttf")) {
    std::runtime_error("ты патрик");
  }

  scoreText = std::make_unique<sf::Text>(font);
  timerText = std::make_unique<sf::Text>(font);
  charText = std::make_unique<sf::Text>(font);
  gameOverText = std::make_unique<sf::Text>(font);
  restartText = std::make_unique<sf::Text>(font);

  scoreText->setCharacterSize(SCORE_FONT_SIZE);
  scoreText->setFillColor(COLOR_SCORE);
  scoreText->setPosition({SCORE_POS_X, SCORE_POS_Y});

  timerText->setCharacterSize(TIMER_FONT_SIZE);
  timerText->setFillColor(COLOR_TIMER);
  timerText->setPosition({TIMER_POS_X, TIMER_POS_Y});

  charText->setCharacterSize(CHAR_FONT_SIZE);
  charText->setFillColor(COLOR_CHAR);

  gameOverText->setCharacterSize(GAME_OVER_FONT_SIZE);
  gameOverText->setFillColor(COLOR_GAME_OVER);
  gameOverText->setString("GAME OVER");

  restartText->setCharacterSize(RESTART_FONT_SIZE);
  restartText->setFillColor(COLOR_RESTART);
  restartText->setString("Press R to restart, ESC to quit");

  std::srand(static_cast<unsigned>(std::time(nullptr)));

  updateTexts();
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    update(clock.restart());
    render();
  }
}

void Game::processEvents() {
  while (const auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (gameActive) {
      if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
        if (textEntered->unicode < 32) continue;

        char inputChar = static_cast<char>(textEntered->unicode);
        inputChar = static_cast<char>(
            std::toupper(static_cast<unsigned char>(inputChar)));
        handleTextInput(inputChar);
      }
    } else {
      if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::R) {
          resetGame();
        } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }
    }
  }
}

void Game::handleTextInput(char inputChar) {
  if (inputChar >= 'A' && inputChar <= 'Z') {
    if (inputChar == currentChar) {
      score++;
    } else {
      timeRemaining -= PENALTY_TIME;
    }
  } else {
    timeRemaining -= PENALTY_TIME;
  }

  if (timeRemaining < 0.0f) {
    timeRemaining = 0.0f;
    gameActive = false;
  }

  currentChar = getRandomChar();
  updateTexts();
}

void Game::update(sf::Time dt) {
  if (gameActive) {
    timeRemaining -= dt.asSeconds();
    if (timeRemaining <= 0.0f) {
      timeRemaining = 0.0f;
      gameActive = false;
    }
    updateTexts();
  }
}

void Game::render() {
  window.clear(CLEAR_COLOR);

  if (gameActive) {
    window.draw(*scoreText);
    window.draw(*timerText);
    window.draw(*charText);
  } else {
    sf::FloatRect goBounds = gameOverText->getLocalBounds();
    gameOverText->setOrigin({goBounds.position.x + goBounds.size.x / 2.0f,
                             goBounds.position.y + goBounds.size.y / 2.0f});
    gameOverText->setPosition({GAME_OVER_POS_X, GAME_OVER_POS_Y});
    window.draw(*gameOverText);

    sf::Text finalScoreText(font);
    finalScoreText.setCharacterSize(FINAL_SCORE_FONT_SIZE);
    finalScoreText.setFillColor(COLOR_FINAL_SCORE);
    std::ostringstream finalScoreStr;
    finalScoreStr << "Final Score: " << score;
    finalScoreText.setString(finalScoreStr.str());
    sf::FloatRect fsBounds = finalScoreText.getLocalBounds();
    finalScoreText.setOrigin({fsBounds.position.x + fsBounds.size.x / 2.0f,
                              fsBounds.position.y + fsBounds.size.y / 2.0f});
    finalScoreText.setPosition({FINAL_SCORE_POS_X, FINAL_SCORE_POS_Y});
    window.draw(finalScoreText);

    sf::FloatRect rBounds = restartText->getLocalBounds();
    restartText->setOrigin({rBounds.position.x + rBounds.size.x / 2.0f,
                            rBounds.position.y + rBounds.size.y / 2.0f});
    restartText->setPosition({RESTART_POS_X, RESTART_POS_Y});
    window.draw(*restartText);
  }

  window.display();
}

void Game::resetGame() {
  gameActive = true;
  score = 0;
  timeRemaining = INITIAL_TIME;
  currentChar = getRandomChar();
  updateTexts();
}

void Game::updateTexts() {
  std::ostringstream scoreStr;
  scoreStr << "Score: " << score;
  scoreText->setString(scoreStr.str());

  std::ostringstream timerStr;
  timerStr << "Time: ";
  timerStr.precision(1);
  timerStr << std::fixed << timeRemaining;
  timerText->setString(timerStr.str());

  charText->setString(std::string(1, currentChar));
  sf::FloatRect charBounds = charText->getLocalBounds();
  charText->setOrigin({charBounds.position.x + charBounds.size.x / 2.0f,
                       charBounds.position.y + charBounds.size.y / 2.0f});
  charText->setPosition({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f});
}
