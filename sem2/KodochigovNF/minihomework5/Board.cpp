#include "Board.h"

#include <algorithm>
#include <random>

Board::Board(float startX, float startY, float cardWidth, float cardHeight,
             float spacing)
    : font_(nullptr),
      card_width_(cardWidth),
      card_height_(cardHeight),
      spacing_(spacing),
      start_x_(startX),
      start_y_(startY),
      first_revealed_row_(-1),
      first_revealed_col_(-1),
      second_revealed_row_(-1),
      second_revealed_col_(-1),
      waiting_for_delay_(false),
      delay_duration_(0.5f),
      consecutive_mistakes_(0),
      score_(0),
      moves_(0) {
  initCards();
}

void Board::setFont(sf::Font& font) {
  font_ = &font;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      cards_[i][j].text.setFont(*font_);
      updateCardAppearance(i, j);
    }
  }
}

void Board::initCards() {
  std::vector<char> symbols;
  for (char c = 'A'; c <= 'H'; ++c) {
    symbols.push_back(c);
    symbols.push_back(c);
  }
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(symbols.begin(), symbols.end(), g);

  int idx = 0;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      cards_[i][j].symbol = symbols[idx++];
      cards_[i][j].state = HIDDEN;
      cards_[i][j].shape.setSize(sf::Vector2f(card_width_, card_height_));
      cards_[i][j].shape.setPosition(start_x_ + j * (card_width_ + spacing_),
                                     start_y_ + i * (card_height_ + spacing_));
      cards_[i][j].shape.setFillColor(sf::Color(100, 100, 200));
      cards_[i][j].shape.setOutlineThickness(2.f);
      cards_[i][j].shape.setOutlineColor(sf::Color::Black);
      cards_[i][j].text.setCharacterSize(36);
      cards_[i][j].text.setFillColor(sf::Color::White);
      if (font_) {
        cards_[i][j].text.setFont(*font_);
      }
      updateCardAppearance(i, j);
    }
  }
}

void Board::shuffleRemainingCards() {
  std::vector<char> remaining_symbols;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (cards_[i][j].state != MATCHED) {
        remaining_symbols.push_back(cards_[i][j].symbol);
      }
    }
  }
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(remaining_symbols.begin(), remaining_symbols.end(), g);

  size_t idx = 0;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (cards_[i][j].state != MATCHED) {
        setCardSymbolAndText(i, j, remaining_symbols[idx++]);
      }
    }
  }
}

void Board::resetRevealed() {
  first_revealed_row_ = -1;
  first_revealed_col_ = -1;
  second_revealed_row_ = -1;
  second_revealed_col_ = -1;
}

bool Board::checkMatchAndUpdate() {
  char sym1 = cards_[first_revealed_row_][first_revealed_col_].symbol;
  char sym2 = cards_[second_revealed_row_][second_revealed_col_].symbol;
  if (sym1 == sym2) {
    cards_[first_revealed_row_][first_revealed_col_].state = MATCHED;
    cards_[second_revealed_row_][second_revealed_col_].state = MATCHED;
    score_++;
    consecutive_mistakes_ = 0;
    return true;
  } else {
    cards_[first_revealed_row_][first_revealed_col_].state = HIDDEN;
    cards_[second_revealed_row_][second_revealed_col_].state = HIDDEN;
    consecutive_mistakes_++;
    if (consecutive_mistakes_ >= 2) {
      shuffleRemainingCards();
      consecutive_mistakes_ = 0;
    }
    return false;
  }
}

void Board::hideNonMatched() {
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (cards_[i][j].state == REVEALED) {
        cards_[i][j].state = HIDDEN;
        updateCardAppearance(i, j);
      }
    }
  }
}

void Board::revealCard(int row, int col) {
  if (cards_[row][col].state == HIDDEN) {
    cards_[row][col].state = REVEALED;
    updateCardAppearance(row, col);
  }
}

bool Board::isCardClickable(int row, int col) const {
  return cards_[row][col].state == HIDDEN;
}

void Board::updateCardAppearance(int row, int col) {
  Card& card = cards_[row][col];
  if (card.state == HIDDEN) {
    card.shape.setFillColor(sf::Color(100, 100, 200));
    card.text.setString("?");
  } else if (card.state == REVEALED) {
    card.shape.setFillColor(sf::Color(200, 200, 100));
    card.text.setString(std::string(1, card.symbol));
  } else if (card.state == MATCHED) {
    card.shape.setFillColor(sf::Color::Transparent);
    card.text.setString("");
  }
  sf::FloatRect rect = card.shape.getGlobalBounds();
  sf::FloatRect textRect = card.text.getLocalBounds();
  card.text.setPosition(rect.left + (rect.width - textRect.width) / 2.0f,
                        rect.top + (rect.height - textRect.height) / 2.0f);
}

void Board::setCardSymbolAndText(int row, int col, char symbol) {
  cards_[row][col].symbol = symbol;
  if (cards_[row][col].state == HIDDEN) {
    cards_[row][col].text.setString("?");
  } else if (cards_[row][col].state == REVEALED) {
    cards_[row][col].text.setString(std::string(1, symbol));
  }
  sf::FloatRect rect = cards_[row][col].shape.getGlobalBounds();
  sf::FloatRect textRect = cards_[row][col].text.getLocalBounds();
  cards_[row][col].text.setPosition(
      rect.left + (rect.width - textRect.width) / 2.0f,
      rect.top + (rect.height - textRect.height) / 2.0f);
}

void Board::handleClick(sf::Vector2i mousePos) {
  if (waiting_for_delay_ || isFinished()) return;

  int row = -1, col = -1;
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (cards_[i][j].shape.getGlobalBounds().contains(mousePos.x,
                                                        mousePos.y)) {
        row = i;
        col = j;
        break;
      }
    }
  }
  if (row == -1 || !isCardClickable(row, col)) return;

  if (first_revealed_row_ == -1) {
    revealCard(row, col);
    first_revealed_row_ = row;
    first_revealed_col_ = col;
  } else if (second_revealed_row_ == -1 &&
             (row != first_revealed_row_ || col != first_revealed_col_)) {
    revealCard(row, col);
    second_revealed_row_ = row;
    second_revealed_col_ = col;
    moves_++;
    waiting_for_delay_ = true;
    delay_clock_.restart();
  }
}

void Board::update(float /*deltaTime*/) {
  if (waiting_for_delay_ &&
      delay_clock_.getElapsedTime().asSeconds() >= delay_duration_) {
    waiting_for_delay_ = false;
    checkMatchAndUpdate();
    resetRevealed();
    for (int i = 0; i < SIZE; ++i)
      for (int j = 0; j < SIZE; ++j) updateCardAppearance(i, j);
  }
}

void Board::draw(sf::RenderWindow& window) {
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (cards_[i][j].state != MATCHED) {
        window.draw(cards_[i][j].shape);
        window.draw(cards_[i][j].text);
      }
    }
  }
}

bool Board::isFinished() const {
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (cards_[i][j].state != MATCHED) return false;
    }
  }
  return true;
}

int Board::getScore() const { return score_; }
int Board::getMoves() const { return moves_; }

void Board::reset() {
  score_ = 0;
  moves_ = 0;
  consecutive_mistakes_ = 0;
  waiting_for_delay_ = false;
  resetRevealed();
  initCards();
}
