#include "game.h"

#include <algorithm>
#include <filesystem>
#include <iostream>

Game::Game()
    : window_(sf::VideoMode(520, 620), "WHEN THE DEMENTIA IS KICKING IN"),
      attempts_count_(0),
      score_(0),
      mistakes_in_row_(0),
      is_waiting_(false),
      is_game_over_(false),
      random_engine_(std::random_device{}()) {
  std::cout << std::filesystem::current_path() << std::endl;
  if (!font_.loadFromFile("arial.ttf")) {
    window_.close();
  }

  attempts_text_.setFont(font_);
  attempts_text_.setCharacterSize(28);
  attempts_text_.setFillColor(sf::Color::White);
  attempts_text_.setPosition(20.0f, 520.0f);

  score_text_.setFont(font_);
  score_text_.setCharacterSize(28);
  score_text_.setFillColor(sf::Color::White);
  score_text_.setPosition(20.0f, 560.0f);

  game_over_text_.setFont(font_);
  game_over_text_.setCharacterSize(36);
  game_over_text_.setFillColor(sf::Color::Green);
  game_over_text_.setPosition(40.0f, 250.0f);

  initializeCards();
}

void Game::run() {
  while (window_.isOpen()) {
    processEvents();
    update();
    render();
  }
}

void Game::processEvents() {
  sf::Event event;

  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left && !is_waiting_ &&
        !is_game_over_) {
      sf::Vector2f mouse_position =
          window_.mapPixelToCoords(sf::Mouse::getPosition(window_));

      handleMouseClick(mouse_position);
    }
  }
}

void Game::update() {
  attempts_text_.setString("Attempts: " + std::to_string(attempts_count_));

  score_text_.setString("Pairs: " + std::to_string(score_));

  if (is_waiting_ && delay_clock_.getElapsedTime().asSeconds() >= 1.0f) {
    checkOpenedCards();
    is_waiting_ = false;
  }

  if (allCardsRemoved()) {
    is_game_over_ = true;

    game_over_text_.setString("Such a smart lil fella! Attempts: " +
                              std::to_string(attempts_count_));
  }
}

void Game::render() {
  window_.clear(sf::Color(30, 30, 30));

  for (const Card& card : cards_) {
    card.draw(window_);
  }

  window_.draw(attempts_text_);
  window_.draw(score_text_);

  if (is_game_over_) {
    window_.draw(game_over_text_);
  }

  window_.display();
}

void Game::initializeCards() {
  std::vector<int> values;

  for (int i = 1; i <= 8; ++i) {
    values.push_back(i);
    values.push_back(i);
  }

  std::shuffle(values.begin(), values.end(), random_engine_);

  cards_.resize(16);

  int index = 0;

  for (int row = 0; row < 4; ++row) {
    for (int column = 0; column < 4; ++column) {
      float x = 20.0f + column * 120.0f;
      float y = 20.0f + row * 120.0f;

      cards_[index].initialize(x, y, values[index], font_);

      ++index;
    }
  }
}

void Game::handleMouseClick(sf::Vector2f mouse_position) {
  if (opened_indices_.size() >= 2) {
    return;
  }

  for (int i = 0; i < static_cast<int>(cards_.size()); ++i) {
    Card& card = cards_[i];

    if (card.contains(mouse_position) && !card.isRemoved() &&
        !card.isRevealed()) {
      card.reveal();

      opened_indices_.push_back(i);

      if (opened_indices_.size() == 2) {
        ++attempts_count_;

        is_waiting_ = true;

        delay_clock_.restart();
      }

      break;
    }
  }
}

void Game::checkOpenedCards() {
  int first_index = opened_indices_[0];
  int second_index = opened_indices_[1];

  Card& first_card = cards_[first_index];
  Card& second_card = cards_[second_index];

  if (first_card.getValue() == second_card.getValue()) {
    first_card.remove();
    second_card.remove();

    ++score_;

    mistakes_in_row_ = 0;
  } else {
    first_card.hide();
    second_card.hide();

    ++mistakes_in_row_;

    if (mistakes_in_row_ >= 2) {
      shuffleHiddenCards();

      mistakes_in_row_ = 0;
    }
  }

  opened_indices_.clear();
}

void Game::shuffleHiddenCards() {
  std::vector<sf::Vector2f> positions;
  std::vector<int> hidden_indices;

  for (int i = 0; i < static_cast<int>(cards_.size()); ++i) {
    if (!cards_[i].isRemoved() && !cards_[i].isRevealed()) {
      positions.push_back(cards_[i].getPosition());

      hidden_indices.push_back(i);
    }
  }

  std::shuffle(positions.begin(), positions.end(), random_engine_);

  for (int i = 0; i < static_cast<int>(hidden_indices.size()); ++i) {
    cards_[hidden_indices[i]].setPosition(positions[i].x, positions[i].y);
  }
}

bool Game::allCardsRemoved() const {
  for (const Card& card : cards_) {
    if (!card.isRemoved()) {
      return false;
    }
  }

  return true;
}
