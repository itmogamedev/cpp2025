#include "game.h"

#include <iostream>

TypingGame::TypingGame()
    : window_(sf::VideoMode(800, 600), "Typing Speed Game"),
      gen_(rd_()),
      char_dist_(33, 126),
      score_(0),
      game_time_(30.0f),
      time_remaining_(30.0f),
      game_active_(true),
      background_color_(30, 30, 45),
      text_color_(255, 255, 255),
      timer_color_(100, 255, 100) {
  if (!font_.loadFromFile("font/arialmt.ttf")) {
    if (!font_.loadFromFile("../font/arialmt.ttf"))
        if(!font_.loadFromFile("../../font/arialmt.ttf"))
      std::cerr << "Error loading font!" << std::endl;
  }

  target_char_text_.setFont(font_);
  target_char_text_.setCharacterSize(200);
  target_char_text_.setFillColor(text_color_);
  target_char_text_.setStyle(sf::Text::Bold);

  score_text_.setFont(font_);
  score_text_.setCharacterSize(30);
  score_text_.setFillColor(text_color_);
  score_text_.setPosition(20, 20);

  timer_text_.setFont(font_);
  timer_text_.setCharacterSize(30);
  timer_text_.setFillColor(timer_color_);
  timer_text_.setPosition(window_.getSize().x - 150, 20);

  instruction_text_.setFont(font_);
  instruction_text_.setCharacterSize(20);
  instruction_text_.setFillColor(sf::Color(150, 150, 150));
  instruction_text_.setString("Press the matching key as fast as you can!");
  instruction_text_.setPosition(
      window_.getSize().x / 2.0f -
          instruction_text_.getLocalBounds().width / 2.0f,
      window_.getSize().y - 50);

  game_over_text_.setFont(font_);
  game_over_text_.setCharacterSize(60);
  game_over_text_.setFillColor(sf::Color::Red);
  game_over_text_.setStyle(sf::Text::Bold);

  final_score_text_.setFont(font_);
  final_score_text_.setCharacterSize(40);
  final_score_text_.setFillColor(text_color_);
  final_score_text_.setStyle(sf::Text::Bold);

  current_char_ = GenerateRandomChar();
  UpdateDisplay();
  CenterTargetChar();
}

void TypingGame::Run() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }

      if (event.type == sf::Event::TextEntered && game_active_) {
        if (event.text.unicode >= 32 && event.text.unicode <= 126) {
          char pressed_char = static_cast<char>(event.text.unicode);

          if (pressed_char == current_char_) {
            CorrectPress();
            CenterTargetChar();
          } else {
            WrongPress();
          }

          if (time_remaining_ <= 0 && game_active_) {
            EndGame();
          }
        }
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::R && !game_active_) {
          RestartGame();
        }
      }
    }

    if (game_active_) {
      float delta_time = game_clock_.restart().asSeconds();
      time_remaining_ -= delta_time;

      if (time_remaining_ <= 0) {
        time_remaining_ = 0;
        EndGame();
      }

      UpdateDisplay();
    }

    window_.clear(background_color_);

    window_.draw(target_char_text_);
    window_.draw(score_text_);
    window_.draw(timer_text_);
    window_.draw(instruction_text_);

    if (!game_active_) {
      window_.draw(game_over_text_);
      window_.draw(final_score_text_);
    }

    window_.display();
  }
}

char TypingGame::GenerateRandomChar() {
  return static_cast<char>(char_dist_(gen_));
}

void TypingGame::UpdateDisplay() {
  target_char_text_.setString(std::string(1, current_char_));
  score_text_.setString("Score: " + std::to_string(score_));

  if (time_remaining_ < game_time_ * 0.2f) {
    timer_text_.setFillColor(sf::Color::Red);
  } else if (time_remaining_ < game_time_ * 0.5f) {
    timer_text_.setFillColor(sf::Color::Yellow);
  } else {
    timer_text_.setFillColor(timer_color_);
  }

  timer_text_.setString(
      "Time: " + std::to_string(static_cast<int>(time_remaining_ + 0.5f)));
}

void TypingGame::CenterTargetChar() {
  sf::FloatRect text_bounds = target_char_text_.getLocalBounds();
  target_char_text_.setPosition(
      window_.getSize().x / 2.0f - text_bounds.width / 2.0f,
      window_.getSize().y / 2.0f - text_bounds.height / 2.0f);
}

void TypingGame::CorrectPress() {
  score_++;
  current_char_ = GenerateRandomChar();
  UpdateDisplay();
}

void TypingGame::WrongPress() {
  time_remaining_ -= 1.0f;
  if (time_remaining_ < 0) time_remaining_ = 0;
  UpdateDisplay();

  target_char_text_.setFillColor(sf::Color::Red);
  sf::sleep(sf::milliseconds(100));
  target_char_text_.setFillColor(text_color_);
}

void TypingGame::EndGame() {
  game_active_ = false;
  game_over_text_.setString("GAME OVER!");

  sf::FloatRect game_over_bounds = game_over_text_.getLocalBounds();
  game_over_text_.setPosition(
      window_.getSize().x / 2.0f - game_over_bounds.width / 2.0f,
      window_.getSize().y / 2.0f - 120);

  final_score_text_.setString("Final Score: " + std::to_string(score_));
  sf::FloatRect final_score_bounds = final_score_text_.getLocalBounds();
  final_score_text_.setPosition(
      window_.getSize().x / 2.0f - final_score_bounds.width / 2.0f,
      window_.getSize().y / 2.0f - 30);
}

void TypingGame::RestartGame() {
  score_ = 0;
  time_remaining_ = game_time_;
  game_active_ = true;
  current_char_ = GenerateRandomChar();

  UpdateDisplay();
  CenterTargetChar();

  target_char_text_.setFillColor(text_color_);

  game_clock_.restart();
}
