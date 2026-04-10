#include "TypingGame.h"

#include <cctype>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

TypingGame::TypingGame()
    : window(sf::VideoMode(800, 600), "Typing Trainer", sf::Style::Close),
      font(),
      current_char(' '),
      score(0),
      time_left(31.0f),
      game_active(true) {
  if (!font.loadFromFile("Images/Roboto-Regular.ttf")) {
    if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/"
                           "LiberationSans-Regular.ttf")) {
      std::cerr << "Could not load font. Please provide a valid font file."
                << std::endl;
    }
  }
  setupText();
  generateRandomChar();
}

void TypingGame::run() {
  sf::Clock delta_clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (game_active and event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 and event.text.unicode > 31) {
          handleInput(static_cast<char>(event.text.unicode));
        }
      }

      if (event.type == sf::Event::KeyPressed and
          event.key.code == sf::Keyboard::Enter) {
        resetGame();
      }
    }

    if (game_active) {
      float dt = delta_clock.restart().asSeconds();
      time_left -= dt;
      if (time_left <= 0.0f) {
        time_left = 0.0f;
        game_active = false;
      }
    }

    updateText();
    window.clear(sf::Color::Black);
    window.draw(title_text);
    window.draw(char_text);
    window.draw(score_text);
    window.draw(timer_text);
    if (!game_active) {
      window.draw(game_over_text);
      window.draw(restart_text);
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
}

void TypingGame::setupText() {
  char_text.setFont(font);
  char_text.setCharacterSize(200);
  char_text.setFillColor(sf::Color::Red);

  score_text.setFont(font);
  score_text.setCharacterSize(36);
  score_text.setFillColor(sf::Color::Green);
  score_text.setPosition(20, 10);

  timer_text.setFont(font);
  timer_text.setCharacterSize(36);
  timer_text.setFillColor(sf::Color::White);
  timer_text.setPosition(200, 10);

  game_over_text.setFont(font);
  game_over_text.setCharacterSize(48);
  game_over_text.setFillColor(sf::Color::Red);
  game_over_text.setPosition(400 - 150, 400);
  game_over_text.setString("GAME OVER");

  restart_text.setFont(font);
  restart_text.setCharacterSize(24);
  restart_text.setFillColor(sf::Color::White);
  restart_text.setPosition(400 - 150, 500);
  restart_text.setString("Press Enter to restart");
}

void TypingGame::generateRandomChar() {
  const std::string allowedChars =
      "abcdefghjklmnopqrstuvwxyz"
      "0123456789";

  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> dist(0, allowedChars.size() - 1);

  current_char = allowedChars[dist(gen)];
  char_text.setString(std::string(1, current_char));

  sf::FloatRect bounds = char_text.getLocalBounds();
  char_text.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
  char_text.setPosition(380, 200);
}

void TypingGame::handleInput(char input) {
  if (!game_active) return;

  char inputLower = std::tolower(static_cast<unsigned char>(input));
  char currentLower = std::tolower(static_cast<unsigned char>(current_char));

  if (inputLower == currentLower) {
    score++;
    generateRandomChar();
  } else {
    time_left -= 1.0f;
    if (time_left < 0.0f) time_left = 0.0f;
  }
}

void TypingGame::updateText() {
  score_text.setString("Score: " + std::to_string(score));
  timer_text.setString("Time: " + std::to_string(static_cast<int>(time_left)) +
                       " s");
  timer_text.setFillColor(time_left < 5.0f ? sf::Color::Red : sf::Color::White);
}

void TypingGame::resetGame() {
  score = 0;
  time_left = 31.0f;
  game_active = true;
  generateRandomChar();
  updateText();
}
