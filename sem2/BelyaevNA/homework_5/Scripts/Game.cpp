#include "Game.h"

#include "Constants.h"

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Memory"), ui(font) {
  bool fontOk = font.openFromFile("C:/Windows/Fonts/arial.ttf");
  if (!fontOk) {
    fontOk = font.openFromFile("arial.ttf");
  }
}

void Game::handleInput() {
  while (const auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) window.close();
    if (!logic.isWaiting() && !logic.isGameWon()) {
      if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouse->button == sf::Mouse::Button::Left) {
          int c = board.handleClick(sf::Mouse::getPosition(window));
          if (c != -1) {
            if (logic.getFirstCard() == -1)
              logic.setFirstCard(c);
            else if (logic.getSecondCard() == -1) {
              logic.setSecondCard(c);
              logic.incrementMoves();
              logic.startDelay();
            }
          }
        }
      }
    }
  }
}

void Game::update() {
  logic.updateChain();
  if (logic.shouldResolve()) {
    if (board.checkMatch(logic.getFirstCard(), logic.getSecondCard())) {
      logic.startChain();
      logic.addScore(SCORE_PER_PAIR);
      if (board.isGameWon()) {
        logic.setGameWon();
        ui.showWinScreen(logic.getMoves(), logic.getScore());
      }
    } else {
      logic.resetChain();
    }
    logic.resetSelection();
  }
  ui.updateMoves(logic.getMoves());
  ui.updateScore(logic.getScore());
  ui.updateChain(logic.getChainMultiplier(), logic.isChainActive());
}

void Game::render() {
  window.clear(sf::Color(COLOR_SKY_R, COLOR_SKY_G, COLOR_SKY_B));
  board.drawBackground(window);
  board.draw(window);
  ui.draw(window);
  window.display();
}

void Game::run() {
  while (window.isOpen()) {
    handleInput();
    update();
    render();
  }
}
