#include "Game.h"

#include <iostream>

Game::Game()
    : window(sf::VideoMode(WINDOW_SIZE), WINDOW_TITLE,
             sf::Style::Titlebar | sf::Style::Close),
      circles(window.getSize()),
      handler(window),
      renderer(window),
      ui(),
      time_left(START_TIME),
      game_time(START_TIME),
      game_running(true) {
  window.setFramerateLimit(25);
  circles.initialize(CIRCLES_COUNT);
  last_time = std::chrono::steady_clock::now();
}

void Game::resetGame() {
  circles.reset();
  time_left = game_time;
  game_running = true;
  ui.setGameOver(false, START_SCORE);
  ui.updateTimer(time_left);
}

void Game::run() {
  while (window.isOpen()) {
    handleActions(handler.pollActions());
    update();
    draw();
  }
}

void Game::handleActions(const std::vector<Actions>& actions) {
  for (const auto& action : actions) {
    if (action == Actions::LeftClick && game_running) {
      sf::Vector2i mousePos = handler.getLastMousePosition();
      bool hit = circles.checkHit(mousePos);

      if (hit) {
        ui.updateScore(circles.getScore());
      } else {
        time_left -= TIME_FINE;
        if (time_left < 0) time_left = 0;
        ui.updateTimer(time_left);
      }
    }
  }
}

void Game::update() {
  auto now = std::chrono::steady_clock::now();
  float delta_time = std::chrono::duration<float>(now - last_time).count();
  last_time = now;

  if (game_running) {
    time_left -= delta_time;
    ui.updateTimer(time_left);
    circles.update(delta_time, window.getSize());
    if (time_left <= 0) {
      game_running = false;
      ui.setGameOver(true, circles.getScore());
    }
  }
}

void Game::draw() {
  renderer.clear();
  renderer.draw(circles);
  renderer.draw(ui);
  renderer.display();
}