#include "Board.hpp"

#include <algorithm>
#include <random>
#include <vector>

namespace {

const sf::String kSymbols[8] = {
    sf::String(U"♠"), sf::String(U"♥"), sf::String(U"♦"), sf::String(U"♣"),
    sf::String(U"★"), sf::String(U"☀"), sf::String(U"♪"), sf::String(U"✿")
};

const sf::Color kBackFill    {70,  130, 180};
const sf::Color kBackOutline {40,   80, 120};
const sf::Color kFaceFill    {245, 240, 232};
const sf::Color kFaceOutline {180, 160, 120};
const sf::Color kSymbolColor {50,   50,  50};

}  // namespace

Board::Board(const sf::Font& font)
    : card_shape_({Card::kSize, Card::kSize}),
      card_text_(font, {}, 52) {
  card_shape_.setOutlineThickness(2.f);
  card_text_.setFillColor(kSymbolColor);

  std::array<sf::String, kTotal> deck;
  for (int i = 0; i < 8; ++i) {
    deck[i * 2] = kSymbols[i];
    deck[i * 2 + 1] = kSymbols[i];
  }

  std::mt19937 rng(std::random_device{}());
  std::shuffle(deck.begin(), deck.end(), rng);

  for (int i = 0; i < kTotal; ++i) {
    cards_[i].symbol = deck[i];
    cards_[i].position = CardPos(i);
    cards_[i].state = Card::State::kFaceDown;
  }
}

sf::Vector2f Board::CardPos(int index) const {
  return {
      kOriginX + static_cast<float>(index % kCols) * (Card::kSize + kGap),
      kOriginY + static_cast<float>(index / kCols) * (Card::kSize + kGap)
  };
}

int Board::CardAt(sf::Vector2f point) const {
  for (int i = 0; i < kTotal; ++i)
    if (cards_[i].Contains(point))
      return i;
  return -1;
}

void Board::FlipCard(int index) {
  if (cards_[index].state == Card::State::kFaceDown)
    cards_[index].state = Card::State::kFaceUp;
}

void Board::HideFlipped() {
  for (auto& c : cards_)
    if (c.state == Card::State::kFaceUp)
      c.state = Card::State::kFaceDown;
}

void Board::MatchFlipped() {
  for (auto& c : cards_)
    if (c.state == Card::State::kFaceUp)
      c.state = Card::State::kMatched;
}

void Board::ShuffleUnmatched() {
  std::vector<int> idx;
  for (int i = 0; i < kTotal; ++i)
    if (cards_[i].state == Card::State::kFaceDown)
      idx.push_back(i);

  std::vector<sf::String> syms;
  syms.reserve(idx.size());
  for (int i : idx)
    syms.push_back(cards_[i].symbol);

  std::mt19937 rng(std::random_device{}());
  std::shuffle(syms.begin(), syms.end(), rng);

  for (int i = 0; i < static_cast<int>(idx.size()); ++i)
    cards_[idx[i]].symbol = syms[i];
}

bool Board::AllMatched() const {
  for (const auto& c : cards_)
    if (c.state != Card::State::kMatched)
      return false;
  return true;
}

void Board::Draw(sf::RenderWindow& window) const {
  for (const auto& card : cards_)
    DrawCard(window, card);
}

void Board::DrawCard(sf::RenderWindow& window, const Card& card) const {
  if (card.state == Card::State::kMatched) return;

  card_shape_.setPosition(card.position);

  if (card.state == Card::State::kFaceDown) {
    card_shape_.setFillColor(kBackFill);
    card_shape_.setOutlineColor(kBackOutline);
  } else {
    card_shape_.setFillColor(kFaceFill);
    card_shape_.setOutlineColor(kFaceOutline);
  }
  window.draw(card_shape_);

  if (card.state == Card::State::kFaceUp) {
    card_text_.setString(card.symbol);
    sf::FloatRect b = card_text_.getLocalBounds();
    card_text_.setOrigin({b.position.x + b.size.x * 0.5f,
                          b.position.y + b.size.y * 0.5f});
    card_text_.setPosition(card.position +
                           sf::Vector2f{Card::kSize * 0.5f, Card::kSize * 0.5f});
    window.draw(card_text_);
  }
}
