#include "game.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

Game::Game()
    : window_(sf::VideoMode(600, 700), "Memory Game"),
      rng_(std::random_device{}()),
      first_selected_row_(-1),
      first_selected_col_(-1),
      second_selected_row_(-1),
      second_selected_col_(-1),
      waiting_for_second_(false),
      waiting_for_flip_back_(false),
      consecutive_mistakes_(0),
      moves_count_(0),
      pairs_found_(0),
      pending_shuffle_(false),
      game_over_(false) {
  if (!font_.loadFromFile("arial.ttf")) {
    std::cerr << "Failed to load font. Using default system font." << std::endl;
  }

  moves_text_.setFont(font_);
  moves_text_.setCharacterSize(24);
  moves_text_.setFillColor(sf::Color::White);
  moves_text_.setPosition(20.0f, 20.0f);

  // Score counter
  points_text_.setFont(font_);
  points_text_.setCharacterSize(24);
  points_text_.setFillColor(sf::Color::White);
  points_text_.setPosition(20.0f, 50.0f);

  end_game_text_.setFont(font_);
  end_game_text_.setCharacterSize(36);
  end_game_text_.setFillColor(sf::Color::Yellow);
  end_game_text_.setStyle(sf::Text::Bold);

  InitializeCards();
}

void Game::InitializeCards() {
  std::vector<int> symbols;
  for (int i = 0; i < kTotalPairs; ++i) {
    symbols.push_back(i);
    symbols.push_back(i);
  }
  std::shuffle(symbols.begin(), symbols.end(), rng_);

  int symbol_index = 0;
  for (int row = 0; row < kGridSize; ++row) {
    for (int col = 0; col < kGridSize; ++col) {
      Card& card = cards_[row][col];
      card.symbol_id = symbols[symbol_index++];
      card.is_matched = false;
      card.is_revealed = false;

      float x = kOffsetX + col * (kCardWidth + kCardSpacing);
      float y = kOffsetY + row * (kCardHeight + kCardSpacing);

      card.shape.setSize(sf::Vector2f(kCardWidth, kCardHeight));
      card.shape.setPosition(x, y);
      card.shape.setFillColor(sf::Color(70, 130, 180));
      card.shape.setOutlineThickness(2.0f);
      card.shape.setOutlineColor(sf::Color::White);
    }
  }

  consecutive_mistakes_ = 0;
  moves_count_ = 0;
  pairs_found_ = 0;
  pending_shuffle_ = false;
  game_over_ = false;
  end_game_text_.setString("");
}

void Game::ShuffleRemainingCards() {
  std::vector<Card*> remaining_cards;
  for (int row = 0; row < kGridSize; ++row) {
    for (int col = 0; col < kGridSize; ++col) {
      if (!cards_[row][col].is_matched) {
        cards_[row][col].is_revealed = false;
        remaining_cards.push_back(&cards_[row][col]);
      }
    }
  }

  if (remaining_cards.size() < 2) {
    return;
  }

  std::vector<int> symbols;
  symbols.reserve(remaining_cards.size());
  for (Card* card : remaining_cards) {
    symbols.push_back(card->symbol_id);
  }

  std::shuffle(remaining_cards.begin(), remaining_cards.end(), rng_);
  for (size_t i = 0; i < remaining_cards.size(); ++i) {
    remaining_cards[i]->symbol_id = symbols[i];
  }

  consecutive_mistakes_ = 0;
}

void Game::HandleMouseClick(const sf::Vector2i& mouse_position) {
  if (waiting_for_flip_back_) {
    return;
  }

  sf::Vector2f world_pos = window_.mapPixelToCoords(mouse_position);

  for (int row = 0; row < kGridSize; ++row) {
    for (int col = 0; col < kGridSize; ++col) {
      Card& card = cards_[row][col];

      if (card.is_matched || card.is_revealed) {
        continue;
      }

      if (card.shape.getGlobalBounds().contains(world_pos)) {
        card.is_revealed = true;

        if (!waiting_for_second_) {
          first_selected_row_ = row;
          first_selected_col_ = col;
          waiting_for_second_ = true;
        } else {
          if (row == first_selected_row_ && col == first_selected_col_) {
            return;
          }

          second_selected_row_ = row;
          second_selected_col_ = col;
          waiting_for_second_ = false;
          moves_count_++;

          CheckMatch();
        }
        return;
      }
    }
  }
}

void Game::CheckMatch() {
  Card& first = cards_[first_selected_row_][first_selected_col_];
  Card& second = cards_[second_selected_row_][second_selected_col_];

  if (first.symbol_id == second.symbol_id) {
    first.is_matched = true;
    second.is_matched = true;
    pairs_found_++;
    consecutive_mistakes_ = 0;
    pending_shuffle_ = false;

    if (pairs_found_ == kTotalPairs) {
      game_over_ = true;
      std::string end_message =
          "You Win!\nMoves: " + std::to_string(moves_count_) +
          "\nScore: " + std::to_string(pairs_found_);
      end_game_text_.setString(end_message);

      sf::FloatRect text_rect = end_game_text_.getLocalBounds();
      end_game_text_.setOrigin(text_rect.left + text_rect.width / 2.0f,
                               text_rect.top + text_rect.height / 2.0f);
      end_game_text_.setPosition(window_.getSize().x / 2.0f,
                                 window_.getSize().y / 2.0f);
    }

    ResetSelection();
  } else {
    waiting_for_flip_back_ = true;
    flip_back_clock_.restart();
    consecutive_mistakes_++;

    if (consecutive_mistakes_ >= 2) {
      pending_shuffle_ = true;
    }
  }
}

void Game::UpdateCardVisuals() {
  for (int row = 0; row < kGridSize; ++row) {
    for (int col = 0; col < kGridSize; ++col) {
      Card& card = cards_[row][col];

      if (card.is_matched) {
        card.shape.setFillColor(sf::Color::Transparent);
        card.shape.setOutlineColor(sf::Color::Transparent);
      } else if (card.is_revealed) {
        card.shape.setFillColor(sf::Color::White);
        card.shape.setOutlineColor(sf::Color::Yellow);
      } else {
        card.shape.setFillColor(sf::Color(70, 130, 180));
        card.shape.setOutlineColor(sf::Color::White);
      }
    }
  }
}

void Game::DrawGame() {
  window_.clear(sf::Color(30, 30, 30));

  for (int row = 0; row < kGridSize; ++row) {
    for (int col = 0; col < kGridSize; ++col) {
      Card& card = cards_[row][col];
      window_.draw(card.shape);

      if (card.is_revealed && !card.is_matched) {
        sf::Text symbol_text;
        symbol_text.setFont(font_);
        symbol_text.setString(std::to_string(card.symbol_id));
        symbol_text.setCharacterSize(40);
        symbol_text.setFillColor(sf::Color::Black);

        sf::FloatRect text_rect = symbol_text.getLocalBounds();
        symbol_text.setOrigin(text_rect.left + text_rect.width / 2.0f,
                              text_rect.top + text_rect.height / 2.0f);

        sf::Vector2f card_pos = card.shape.getPosition();
        sf::Vector2f card_size = card.shape.getSize();
        symbol_text.setPosition(card_pos.x + card_size.x / 2.0f,
                                card_pos.y + card_size.y / 2.0f);

        window_.draw(symbol_text);
      }
    }
  }

  moves_text_.setString("Moves: " + std::to_string(moves_count_));
  points_text_.setString("Points: " + std::to_string(pairs_found_));
  window_.draw(moves_text_);
  window_.draw(points_text_);

  if (game_over_) {
    sf::RectangleShape overlay(
        sf::Vector2f(window_.getSize().x, window_.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window_.draw(overlay);
    window_.draw(end_game_text_);
  }

  window_.display();
}

void Game::ResetSelection() {
  first_selected_row_ = -1;
  first_selected_col_ = -1;
  second_selected_row_ = -1;
  second_selected_col_ = -1;
  waiting_for_second_ = false;
}

void Game::Run() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        if (!game_over_) {
          HandleMouseClick(sf::Mouse::getPosition(window_));
        }
      }
    }

    if (waiting_for_flip_back_) {
      if (flip_back_clock_.getElapsedTime().asSeconds() >= kRevealDelay) {
        cards_[first_selected_row_][first_selected_col_].is_revealed = false;
        cards_[second_selected_row_][second_selected_col_].is_revealed = false;
        waiting_for_flip_back_ = false;
        ResetSelection();

        if (pending_shuffle_) {
          ShuffleRemainingCards();
          pending_shuffle_ = false;
        }
      }
    }

    UpdateCardVisuals();
    DrawGame();
  }
}
