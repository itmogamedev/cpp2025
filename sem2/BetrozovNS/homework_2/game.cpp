#include "Game.h"

#include <SFML/Window/Keyboard.hpp>
#include <string>

const std::string Game::kAllowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
Game::Game()
    : window(sf::VideoMode(800, 600), "TapTapClerk"),
      rng(std::random_device{}()),
      char_dist(0, static_cast<int>(kAllowedChars.size()) - 1),
      current_char('A'),
      score(0),
      time_left(kInitialTime),
      is_game_over(false) {
  if (!font.loadFromFile("arial.ttf")) {
    // в случае ошибки можно использовать дефолтный шрифт или выйти
    throw std::runtime_error("Failed to load font");
  }

  current_char_text.setFont(font);
  current_char_text.setCharacterSize(120);
  current_char_text.setFillColor(sf::Color::White);
  current_char_text.setStyle(sf::Text::Bold);
  sf::FloatRect text_rect = current_char_text.getLocalBounds();
  current_char_text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                              text_rect.top + text_rect.height / 2.0f);
  current_char_text.setPosition(window.getSize().x / 2.0f,
                                window.getSize().y / 2.0f - 30.0f);

  // здеся у нас СЧЁТ
  score_text.setFont(font);
  score_text.setCharacterSize(30);
  score_text.setFillColor(sf::Color::Green);
  score_text.setPosition(20.0f, 20.0f);

  // тут таймер
  timer_text.setFont(font);
  timer_text.setCharacterSize(30);
  timer_text.setFillColor(sf::Color::Red);
  timer_text.setPosition(window.getSize().x - 150.0f, 20.0f);

  // а тут мы кончаем
  game_over_text.setFont(font);
  game_over_text.setCharacterSize(50);
  game_over_text.setFillColor(sf::Color::Yellow);
  game_over_text.setString("GAME OVER\nPress ESC to exit");
  sf::FloatRect go_rect = game_over_text.getLocalBounds();
  game_over_text.setOrigin(go_rect.left + go_rect.width / 2.0f,
                           go_rect.top + go_rect.height / 2.0f);
  game_over_text.setPosition(window.getSize().x / 2.0f,
                             window.getSize().y / 2.0f + 50.0f);

  generateNewCharacter();
  updateScoreDisplay();
  updateTimerDisplay();
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    sf::Time dt = clock.restart();
    processEvents();
    if (!is_game_over) {
      update(dt);
    }
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      if (is_game_over) {
        if (event.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      } else {
        handlePlayerInput(event.key.code);
      }
    }
  }
}

void Game::update(sf::Time deltaTime) {
  time_left -= deltaTime.asSeconds();
  if (time_left <= 0.0f) {
    time_left = 0.0f;
    is_game_over = true;
  }
  updateTimerDisplay();
}

void Game::render() {
  window.clear(sf::Color::Black);
  window.draw(current_char_text);
  window.draw(score_text);
  window.draw(timer_text);
  if (is_game_over) {
    window.draw(game_over_text);
  }
  window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key code) {
  char pressed = '\0';
  if (code >= sf::Keyboard::A && code <= sf::Keyboard::Z) {
    pressed = 'A' + (code - sf::Keyboard::A);
  } else if (code >= sf::Keyboard::Num0 && code <= sf::Keyboard::Num9) {
    pressed = '0' + (code - sf::Keyboard::Num0);
  } else if (code == sf::Keyboard::Space) {
    pressed = ' ';
  } else {
    return;
  }

  if (pressed == current_char) {
    addScore(kScoreIncrement);
    generateNewCharacter();
  } else {
    reduceTime(kWrongPenalty);
  }
}

void Game::generateNewCharacter() {
  current_char = kAllowedChars[char_dist(rng)];
  current_char_text.setString(std::string(1, current_char));
  sf::FloatRect text_rect = current_char_text.getLocalBounds();
  current_char_text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                              text_rect.top + text_rect.height / 2.0f);
}

void Game::addScore(int points) {
  score += points;
  updateScoreDisplay();
}

void Game::reduceTime(float seconds) {
  time_left -= seconds;
  if (time_left < 0.0f) {
    time_left = 0.0f;
    is_game_over = true;
  }
  updateTimerDisplay();
}

void Game::updateScoreDisplay() {
  score_text.setString("Score: " + std::to_string(score));
}

void Game::updateTimerDisplay() {
  int seconds = static_cast<int>(time_left);
  timer_text.setString("Time: " + std::to_string(seconds));
}
