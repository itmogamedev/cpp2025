#include "Game.h"

#include <cstdlib>
#include <ctime>

#include "constants.h"

Game::Game()
    : screen_width(SCREEN_WIDTH_F),
      screen_height(SCREEN_HEIGHT_F),
      window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Shooter",
             sf::Style::Close),
      model(SCREEN_WIDTH_F, SCREEN_HEIGHT_F),
      view(SCREEN_WIDTH_F, SCREEN_HEIGHT_F) {
  window.setFramerateLimit(FRAMERATE_LIMIT);
  srand(static_cast<unsigned int>(time(0)));
  view.loadResources();
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    float delta_time = clock.restart().asSeconds();
    processEvents();
    handleInput(delta_time);
    update(delta_time);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) window.close();
    }
  }
}

void Game::handleInput(float delta_time) {
  if (model.getState() != GameState::Playing) return;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    model.moveShipLeft(delta_time);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    model.moveShipRight(delta_time);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    model.shoot();
  }
}

void Game::update(float delta_time) { model.update(delta_time); }

void Game::render() { view.render(window, model); }
