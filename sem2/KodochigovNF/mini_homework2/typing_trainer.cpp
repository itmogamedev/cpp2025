#include "typing_trainer.h"

#include <sstream>
#include <string>

TypingTrainer::TypingTrainer()
    : window_(sf::VideoMode(800, 600), "Typing Trainer", sf::Style::Close),
      time_left_(30.0f),
      score_(0),
      game_active_(true),
      rng_(std::chrono::steady_clock::now().time_since_epoch().count()),
      char_dist_(33, 126) {
  window_.setFramerateLimit(60);

  if (!font_.loadFromFile("arial.ttf")) {
    window_.close();
    return;
  }

  charText_.setFont(font_);
  charText_.setCharacterSize(200);
  charText_.setFillColor(sf::Color::White);
  charText_.setStyle(sf::Text::Bold);
  current_char_ = generateRandomChar();
  charText_.setString(std::string(1, current_char_));
  centerText(charText_);
  charText_.setPosition(400.0f, 250.0f);

  scoreText_.setFont(font_);
  scoreText_.setCharacterSize(36);
  scoreText_.setFillColor(sf::Color::Cyan);
  scoreText_.setPosition(20.0f, 20.0f);

  timerText_.setFont(font_);
  timerText_.setCharacterSize(36);
  timerText_.setFillColor(sf::Color::Yellow);
  timerText_.setPosition(600.0f, 20.0f);

  gameOverText_.setFont(font_);
  gameOverText_.setCharacterSize(48);
  gameOverText_.setFillColor(sf::Color::Red);
  gameOverText_.setStyle(sf::Text::Bold);
  gameOverText_.setString("GAME OVER\nPress R to restart\nPress ESC to exit");
  centerText(gameOverText_);
  gameOverText_.setPosition(400.0f, 380.0f);
}

void TypingTrainer::run() {
  sf::Clock deltaClock;
  while (window_.isOpen()) {
    float deltaTime = deltaClock.restart().asSeconds();
    processEvents();
    update(deltaTime);
    render();
  }
}

void TypingTrainer::processEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
    }

    if (event.type == sf::Event::TextEntered && game_active_) {
      char entered = static_cast<char>(event.text.unicode);
      if (entered == current_char_) {
        ++score_;
        current_char_ = generateRandomChar();
        charText_.setString(std::string(1, current_char_));
        centerText(charText_);
      } else {
        time_left_ -= 1.0f;
        if (time_left_ < 0.0f) time_left_ = 0.0f;
      }
    }

    if (!game_active_ && event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::R) {
        resetGame();
      } else if (event.key.code == sf::Keyboard::Escape) {
        window_.close();
      }
    }
  }
}

void TypingTrainer::update(float deltaTime) {
  if (!game_active_) return;

  time_left_ -= deltaTime;
  if (time_left_ <= 0.0f) {
    time_left_ = 0.0f;
    game_active_ = false;
  }

  std::ostringstream scoreStream;
  scoreStream << "Score: " << score_;
  scoreText_.setString(scoreStream.str());

  std::ostringstream timerStream;
  timerStream << "Time: " << std::max(0.0f, time_left_);
  timerText_.setString(timerStream.str());
}

void TypingTrainer::render() {
  window_.clear(sf::Color::Black);
  window_.draw(scoreText_);
  window_.draw(timerText_);
  if (game_active_) {
    window_.draw(charText_);
  } else {
    window_.draw(gameOverText_);
    sf::Text finalScore;
    finalScore.setFont(font_);
    finalScore.setCharacterSize(36);
    finalScore.setFillColor(sf::Color::White);
    finalScore.setString("Your score: " + std::to_string(score_));
    centerText(finalScore);
    finalScore.setPosition(400.0f, 250.0f);
    window_.draw(finalScore);
  }
  window_.display();
}

char TypingTrainer::generateRandomChar() {
  return static_cast<char>(char_dist_(rng_));
}

void TypingTrainer::centerText(sf::Text& text) {
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(bounds.left + bounds.width / 2.0f,
                 bounds.top + bounds.height / 2.0f);
}

void TypingTrainer::resetGame() {
  time_left_ = 30.0f;
  score_ = 0;
  current_char_ = generateRandomChar();
  charText_.setString(std::string(1, current_char_));
  centerText(charText_);
  game_active_ = true;
}
