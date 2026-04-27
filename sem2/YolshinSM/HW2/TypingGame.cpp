#include "TypingGame.h"

#include <iostream>

TypingGame::TypingGame()
    : window(sf::VideoMode({800, 600}), "Typing Game"),
      score(0),
      time_left(game_time),
      game_active(true),
      generator(random_device()),
      char_distribution(33, 126) {
  if (!font.openFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
    if (!font.openFromFile("arial.ttf")) {
      std::cerr
          << "Warning: Could not load font. Text may not display correctly."
          << std::endl;
    }
  }

  target_char_text = std::make_unique<sf::Text>(font);
  score_text = std::make_unique<sf::Text>(font);
  timer_text = std::make_unique<sf::Text>(font);
  game_over_text = std::make_unique<sf::Text>(font);
  final_score_text = std::make_unique<sf::Text>(font);
  instruction_text = std::make_unique<sf::Text>(font);

  setupText();
  generateNewChar();
}

void TypingGame::setupText() {
  target_char_text->setCharacterSize(200);
  target_char_text->setFillColor(sf::Color::White);
  target_char_text->setStyle(sf::Text::Bold);

  score_text->setCharacterSize(30);
  score_text->setFillColor(sf::Color::Green);
  score_text->setPosition({20, 20});

  timer_text->setCharacterSize(30);
  timer_text->setFillColor(sf::Color::Yellow);
  timer_text->setPosition({20, 60});

  game_over_text->setCharacterSize(50);
  game_over_text->setFillColor(sf::Color::Red);
  game_over_text->setStyle(sf::Text::Bold);
  game_over_text->setString("GAME OVER!");
  game_over_text->setPosition({300, 200});

  final_score_text->setCharacterSize(40);
  final_score_text->setFillColor(sf::Color::White);
  final_score_text->setStyle(sf::Text::Bold);
  final_score_text->setPosition({300, 300});

  instruction_text->setCharacterSize(20);
  instruction_text->setFillColor(sf::Color(150, 150, 150));
  instruction_text->setString(
      "Press the matching key as fast as you can!\nWrong key = -2 seconds");
  instruction_text->setPosition({20, 550});
}

void TypingGame::generateNewChar() {
  current_char = static_cast<char>(char_distribution(generator));
  target_char_text->setString(std::string(1, current_char));

  sf::FloatRect text_rect = target_char_text->getLocalBounds();
  target_char_text->setOrigin({text_rect.position.x + text_rect.size.x / 2.0f,
                               text_rect.position.y + text_rect.size.y / 2.0f});
  target_char_text->setPosition(
      {window.getSize().x / 2.0f, window.getSize().y / 2.0f});
}

void TypingGame::updateUI() {
  score_text->setString("Score: " + std::to_string(score));
  timer_text->setString(
      "Time: " + std::to_string(static_cast<int>(time_left * 10) / 10.0f) +
      "s");

  if (time_left < 5.0f) {
    timer_text->setFillColor(sf::Color::Red);
  } else {
    timer_text->setFillColor(sf::Color::Yellow);
  }
}

void TypingGame::handleInput() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* text_event = event->getIf<sf::Event::TextEntered>()) {
      if (game_active && text_event->unicode < 128) {
        char input_char = static_cast<char>(text_event->unicode);

        if (input_char == current_char) {
          score++;
          time_left += 0.5f;
          if (time_left > game_time) time_left = game_time;
          generateNewChar();
        } else if (input_char >= 32 && input_char <= 126) {
          time_left -= 2.0f;
          target_char_text->setFillColor(sf::Color::Red);

          if (time_left <= 0) {
            time_left = 0;
            game_active = false;
            final_score_text->setString("Final Score: " +
                                        std::to_string(score));
          }
        }
        updateUI();
      }
    }
  }

  if (!game_active) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
      resetGame();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
      window.close();
    }
  }
}

void TypingGame::update() {
  if (game_active) {
    float delta_time = game_clock.restart().asSeconds();
    time_left -= delta_time;

    if (time_left <= 0) {
      time_left = 0;
      game_active = false;
      final_score_text->setString("Final Score: " + std::to_string(score));
    }

    updateUI();

    static float error_timer = 0;
    if (target_char_text->getFillColor() != sf::Color::White) {
      error_timer += delta_time;
      if (error_timer > 0.2f) {
        target_char_text->setFillColor(sf::Color::White);
        error_timer = 0;
      }
    }
  } else {
    game_clock.restart();
  }
}

void TypingGame::render() {
  window.clear(sf::Color::Black);

  window.draw(*target_char_text);
  window.draw(*score_text);
  window.draw(*timer_text);
  window.draw(*instruction_text);

  if (!game_active) {
    window.draw(*game_over_text);
    window.draw(*final_score_text);

    sf::Text restart_text(font);
    restart_text.setCharacterSize(25);
    restart_text.setFillColor(sf::Color(150, 150, 150));
    restart_text.setString("Press R to restart or ESC to exit");
    restart_text.setPosition({300, 400});
    window.draw(restart_text);
  }

  window.display();
}

void TypingGame::resetGame() {
  score = 0;
  time_left = game_time;
  game_active = true;
  generateNewChar();
  updateUI();
  target_char_text->setFillColor(sf::Color::White);
  game_clock.restart();
  final_score_text->setString("Final Score: 0");
}

void TypingGame::run() {
  while (window.isOpen()) {
    handleInput();
    update();
    render();
    sf::sleep(sf::milliseconds(10));
  }
}
