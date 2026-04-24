#include "Game.h"

#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <iostream>

#define MAX_TIME 60.0F
#define REDUCE_TIME 2.0f
#define WINDOW_WIDHT 1280
#define WINDOW_HEIGHT 720
#define WINDOW_CLEAR_COLOR {245, 245, 245}
#define POINT 1

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDHT, WINDOW_HEIGHT}), "Typing Trainer"),
      timer_game(MAX_TIME),
      renderer_game(window, font),
      isGameOver(false) {
  if (!font.openFromFile("D:\\MiniHW2\\x64\\Debug\\durik.ttf")) {
    std::cerr << "Font not found at: " << std::filesystem::current_path()
              << std::endl;
    std::exit(EXIT_FAILURE);
  } else {
    std::cout << "Font loaded successfully!" << std::endl;
  }
  generateNewSymbol();
};
void Game::run() {
  sf::Clock delta_clock;
  while (window.isOpen()) {
    float delta_time = delta_clock.restart().asSeconds();
    processEvents();
    if (!isGameOver) {
      updateTime(delta_time);
    }
    renderGame();
  }
}
void Game::processEvents() {
  while (auto event_game = window.pollEvent()) {
    if (event_game->is<sf::Event::Closed>()) {
      window.close();
    } else if (auto text_entered =
                   event_game->getIf<sf::Event::TextEntered>()) {
      char typed_char = static_cast<char>(text_entered->unicode);
      if (std::isalnum(static_cast<unsigned char>(typed_char))) {
        if (!isGameOver) {
          if (typed_char == symbol_current) {
            counter_game.updateCounter(POINT);
            generateNewSymbol();
          } else {
            timer_game.reduceTimer(REDUCE_TIME);
          }
        }
      }
    } else if (auto key_pressed = event_game->getIf<sf::Event::KeyPressed>()) {
      if (isGameOver) {
        if (key_pressed->code == sf::Keyboard::Key::R) {
          restartGame();
        } else if (key_pressed->code == sf::Keyboard::Key::Escape) {
          window.close();
        }
      }
    }
  }
}
void Game::updateTime(float delta_time) {
  timer_game.updateTimer(delta_time);
  if (timer_game.isExpired()) {
    isGameOver = true;
  }
}
void Game::renderGame() {
  window.clear(WINDOW_CLEAR_COLOR);
  if (isGameOver) {
    renderer_game.drawGameOver(counter_game.getPoints());
  } else {
    renderer_game.drawGame(symbol_current, counter_game.getPoints(),
                           timer_game.getRemainingTime());
  }
  window.display();
}
void Game::generateNewSymbol() {
  symbol_current = rand_symbol.getRandomSymbol();
}
void Game::restartGame() {
  timer_game.resetTimer(MAX_TIME);
  counter_game.resetCounter();
  generateNewSymbol();
  isGameOver = false;
}
