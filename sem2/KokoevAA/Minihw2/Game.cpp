#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <optional>
#include <string>

Game::Game()
    : window(sf::VideoMode({1000, 700}), "Osu"),
      score(0),
      time_left(20.0f),
      game_over(false) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  if (!font.openFromFile("arial.ttf")) {
    std::cout << "FONT NOT FOUND\n";
  }
  score_text.setCharacterSize(28);
  score_text.setPosition({20, 20});

  timer_text.setCharacterSize(28);
  timer_text.setPosition({20, 60});

  end_text.setCharacterSize(36);
  end_text.setPosition({350, 300});

  createCircles();
  updateText();
}

void Game::run() {
  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();

    processEvents();
    update(dt);
    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) window.close();

    if (game_over) continue;

    if (const auto* e = event->getIf<sf::Event::MouseButtonPressed>()) {
      if (e->button == sf::Mouse::Button::Left) {
        handleClick(e->position.x, e->position.y);
      }
    }
  }
}

void Game::update(float dt) {
  if (game_over) return;

  time_left -= dt;

  if (time_left <= 0) {
    time_left = 0;
    game_over = true;
  }

  for (size_t i = 0; i < circles.size(); i++) {
    circles[i].update(window, dt);
  }

  updateText();
}

void Game::render() {
  window.clear();

  for (size_t i = 0; i < circles.size(); i++) {
    circles[i].draw(window);
  }

  window.draw(score_text);
  window.draw(timer_text);

  if (game_over) window.draw(end_text);

  window.display();
}

void Game::handleClick(int x, int y) {
  sf::Vector2f pos(static_cast<float>(x), static_cast<float>(y));

  bool hit = false;

  for (size_t i = 0; i < circles.size(); i++) {
    if (circles[i].containsPoint(pos)) {
      score++;
      circles[i].setRandomPosition(window);
      circles[i].setRandomVelocity();
      hit = true;
      break;
    }
  }

  if (!hit) {
    time_left -= 1.5f;
    if (time_left < 0) time_left = 0;
  }

  updateText();
}

void Game::createCircles() {
  for (int i = 0; i < 5; i++) {
    CircleTarget c;
    c.setRandomPosition(window);
    circles.push_back(c);
  }
}

void Game::updateText() {
  score_text.setString("Score: " + std::to_string(score));
  timer_text.setString("Time: " + std::to_string((int)time_left));
  end_text.setString("Game Over: " + std::to_string(score));
}
