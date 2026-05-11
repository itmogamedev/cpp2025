#include "game.h"

Game::Game()
    : screen(sf::VideoMode({800, 450}), "Typing Trainer"),
      type("abcdefghijklmnopqrstuvwxyz0123456789") {
  screen.setFramerateLimit(60);
}

void Game::Run() {
  sf::Clock clock;
  while (screen.isOpen()) {
    float dt = clock.restart().asSeconds();
    ProcessEvents();
    Update(dt);
    Render();
  }
}

void Game::ProcessEvents() {
  while (const std::optional event = screen.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      screen.close();
    }
    if (const auto* text = event->getIf<sf::Event::TextEntered>()) {
      type.CheckInput(text->unicode);
    }
  }
}

void Game::Update(float dt) { type.Update(dt); }

void Game::Render() {
  screen.clear(sf::Color(40, 40, 40));
  render.Draw(screen, type);
  screen.display();
}