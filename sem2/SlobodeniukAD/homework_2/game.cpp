#include "game.h"

#include <cstdlib>
#include <ctime>
#include <optional>
#include <string>


static sf::Font loadDefaultFont() {
  sf::Font font;
  if (!font.openFromFile("C:/Windows/Fonts/Arial.ttf")) {
    if (!font.openFromFile("C:/Windows/Fonts/Tahoma.ttf")) {
      if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
      }
    }
  }
  return font;
}

Game::Game(): 
  window(sf::VideoMode({static_cast<unsigned int>(WINDOW_WIDTH), static_cast<unsigned int>(WINDOW_HEIGHT)}), WINDOW_TITLE),
  font(loadDefaultFont()),
  score_text(font, "Score: 0", FONT_SIZE_SCORE),
  timer_text(font, "Time: " + std::to_string(static_cast<int>(INITIAL_TIME)),FONT_SIZE_TIMER),
  game_over_text(font, "Game Over!", FONT_SIZE_GAME_OVER),
  remaining_time(INITIAL_TIME),
  score(0),
  is_game_over(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < CIRCLES_COUNT; ++i) {
      circles.emplace_back(WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    score_text.setFillColor(TEXT_COLOR);
    score_text.setPosition({TEXT_POSITION_X, TEXT_POSITION_Y_SCORE});

    timer_text.setFillColor(TEXT_COLOR);
    timer_text.setPosition({TEXT_POSITION_X, TEXT_POSITION_Y_TIMER});

    game_over_text.setFillColor(GAME_OVER_TEXT_COLOR);
    game_over_text.setPosition({TEXT_POSITION_X_GAME_OVER, TEXT_POSITION_Y_GAME_OVER});
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    handleEvents();

    if (!is_game_over) {
      float dt = clock.restart().asSeconds();
      remaining_time -= dt;
      if (remaining_time <= 0.0f) {
        is_game_over = true;
        remaining_time = 0.0f;
      }
      update(dt);
    }

    draw();
  }
}

void Game::handleEvents() {
  while (const std::optional<sf::Event> event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (event->is<sf::Event::MouseButtonPressed>() && !is_game_over) {
      if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouse->button == sf::Mouse::Button::Left) {
          sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
          checkClick(mouse_pos);
        }
      }
    }
  }
}

void Game::update(float dt) {
  for (auto& circle : circles) {
    circle.update(dt, WINDOW_WIDTH, WINDOW_HEIGHT);
  }
}

void Game::draw() {
  window.clear(BACKGROUND_COLOR);

  for (const auto& circle : circles) {
    circle.draw(window);
  }

  score_text.setString("Score: " + std::to_string(score));
  timer_text.setString("Time: " + std::to_string(static_cast<int>(remaining_time)));

  window.draw(score_text);
  window.draw(timer_text);

  if (is_game_over) {
    game_over_text.setString("Game Over!\nScore: " + std::to_string(score));
    window.draw(game_over_text);
  }

  window.display();
}

void Game::checkClick(const sf::Vector2i& mouse_pos) {
  bool hit = false;
  for (auto& circle : circles) {
    if (circle.isClicked(mouse_pos)) {
      circle.reposition(WINDOW_WIDTH, WINDOW_HEIGHT);
      score += SCORE_INCREMENT;
      hit = true;
      break;
    }
  }
  if (!hit) {
    remaining_time -= TIME_PENALTY;
    if (remaining_time < 0.0f) remaining_time = 0.0f;
  }
}
