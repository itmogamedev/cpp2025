#include "Game.h"

// #include<SFML / Graphics.hpp>

Game::Game()
    : window(sf::RenderWindow(sf::VideoMode({1280, 720}), "Header")),
      boardModel(),
      boardView(boardModel),
      boardController(BoardController(boardModel, boardView)) {}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      else {
        boardController.handleEvent(event);
      }
    }

    boardModel.update(dt);

    window.clear();

    boardView.render(window);

    window.display();
  }
}
