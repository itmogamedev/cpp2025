#include "game.h"

#include <algorithm>


MemoryGame::MemoryGame()
    : window_(
          sf::VideoMode({constants::kWindowWidth, constants::kWindowHeight}),
          ""),
      random_engine_(std::random_device{}()) {
  window_.setFramerateLimit(60);
  Reset();
}

void MemoryGame::Run() {
  while (window_.isOpen()) {
    while (const auto event = window_.pollEvent()) {
      HandleEvent(*event);
    }

    Update();
    Draw();
  }
}

void MemoryGame::Reset() {
  std::vector<int> ids;
  ids.reserve(constants::kCardCount);

  for (int id = 0; id < constants::kPairCount; ++id) {
    ids.push_back(id);
    ids.push_back(id);
  }

  std::shuffle(ids.begin(), ids.end(), random_engine_);

  for (int i = 0; i < constants::kCardCount; ++i) {
    cards_[i].pair_id = ids[i];
    cards_[i].is_open = false;
    cards_[i].is_matched = false;
  }

  open_cards_.clear();
  moves_ = 0;
  score_ = 0;
  consecutive_errors_ = 0;
  state_ = GameState::kPlaying;
}

void MemoryGame::HandleEvent(const sf::Event& event) {
  if (event.is<sf::Event::Closed>()) {
    window_.close();
    return;
  }

  const auto* mouse_event = event.getIf<sf::Event::MouseButtonPressed>();
  if (mouse_event == nullptr) {
    return;
  }

  if (mouse_event->button != sf::Mouse::Button::Left) {
    return;
  }

  const sf::Vector2f mouse_position(
      static_cast<float>(mouse_event->position.x),
      static_cast<float>(mouse_event->position.y));

  HandleClick(mouse_position);
}

void MemoryGame::HandleClick(sf::Vector2f mouse_position) {
  if (state_ != GameState::kPlaying) {
    return;
  }

  const int index = CardIndexAt(mouse_position);
  if (index < 0) {
    return;
  }

  Card& card = cards_[index];

  if (card.is_open || card.is_matched) {
    return;
  }

  card.is_open = true;
  open_cards_.push_back(index);

  if (open_cards_.size() == 2) {
    ++moves_;
    check_clock_.restart();
    state_ = GameState::kCheckingPair;
  }
}

void MemoryGame::Update() {
  if (state_ != GameState::kCheckingPair) {
    return;
  }

  if (check_clock_.getElapsedTime().asSeconds() <
      constants::kRevealDelaySeconds) {
    return;
  }

  const int first_index = open_cards_[0];
  const int second_index = open_cards_[1];

  Card& first_card = cards_[first_index];
  Card& second_card = cards_[second_index];

  if (first_card.pair_id == second_card.pair_id) {
    first_card.is_open = false;
    second_card.is_open = false;
    first_card.is_matched = true;
    second_card.is_matched = true;

    ++score_;
    consecutive_errors_ = 0;

    if (score_ == constants::kPairCount) {
      open_cards_.clear();
      state_ = GameState::kWon;
      return;
    }
  } else {
    first_card.is_open = false;
    second_card.is_open = false;
    ++consecutive_errors_;

    if (consecutive_errors_ >= 2) {
      ShuffleHiddenCards();
      consecutive_errors_ = 0;
    }
  }

  open_cards_.clear();
  state_ = GameState::kPlaying;
}

void MemoryGame::Draw() {
  window_.clear(constants::kBackgroundColor);
  DrawHud();

  for (int i = 0; i < constants::kCardCount; ++i) {
    if (cards_[i].is_matched) {
      continue;
    }

    if (cards_[i].is_open) {
      DrawCardFace(i);
    } else {
      DrawCardBack(i);
    }
  }

  if (state_ == GameState::kWon) {
    DrawWinOverlay();
  }

  window_.display();
}

sf::Vector2f MemoryGame::CardPosition(int index) const {
  const int row = index / constants::kGridSize;
  const int column = index % constants::kGridSize;

  return {
      constants::kBoardLeft +
          static_cast<float>(column) *
              (constants::kCardSize + constants::kCardGap),
      constants::kBoardTop +
          static_cast<float>(row) *
              (constants::kCardSize + constants::kCardGap),
  };
}

int MemoryGame::CardIndexAt(sf::Vector2f position) const {
  for (int i = 0; i < constants::kCardCount; ++i) {
    const sf::Vector2f card_position = CardPosition(i);

    const bool inside_x =
        position.x >= card_position.x &&
        position.x <= card_position.x + constants::kCardSize;
    const bool inside_y =
        position.y >= card_position.y &&
        position.y <= card_position.y + constants::kCardSize;

    if (inside_x && inside_y) {
      return i;
    }
  }

  return -1;
}

void MemoryGame::DrawHud() {
  drawing::DrawNumber(window_, moves_, {28.0f, 30.0f}, 4.0f,
             constants::kHudActiveColor);

  constexpr float kProgressLeft = 182.0f;
  constexpr float kProgressTop = 34.0f;
  constexpr float kCellSize = 18.0f;
  constexpr float kCellGap = 8.0f;

  for (int i = 0; i < constants::kPairCount; ++i) {
    sf::RectangleShape box({kCellSize, kCellSize});
    box.setPosition(
        {kProgressLeft + static_cast<float>(i) * (kCellSize + kCellGap),
         kProgressTop});
    box.setOutlineThickness(2.0f);
    box.setOutlineColor(constants::kHudMutedColor);
    box.setFillColor(i < score_ ? constants::kHudActiveColor
                                : sf::Color(0, 0, 0, 0));
    window_.draw(box);
  }

  for (int i = 0; i < 2; ++i) {
    sf::CircleShape dot(8.0f);
    dot.setPosition({468.0f + static_cast<float>(i) * 24.0f, 35.0f});
    dot.setFillColor(i < consecutive_errors_ ? constants::kErrorColor
                                             : constants::kHudMutedColor);
    window_.draw(dot);
  }
}

void MemoryGame::DrawCardBack(int index) {
  const sf::Vector2f position = CardPosition(index);

  sf::RectangleShape card({constants::kCardSize, constants::kCardSize});
  card.setPosition(position);
  card.setFillColor(constants::kCardBackColor);
  card.setOutlineThickness(3.0f);
  card.setOutlineColor(sf::Color(180, 210, 255));
  window_.draw(card);

  drawing::DrawRectangle(window_, position + sf::Vector2f(24.0f, 26.0f),
                {48.0f, 8.0f}, constants::kCardBackPatternColor);
  drawing::DrawRectangle(window_, position + sf::Vector2f(18.0f, 44.0f),
                {60.0f, 8.0f}, constants::kCardBackPatternColor);
  drawing::DrawRectangle(window_, position + sf::Vector2f(24.0f, 62.0f),
                {48.0f, 8.0f}, constants::kCardBackPatternColor);
}

void MemoryGame::DrawCardFace(int index) {
  const sf::Vector2f position = CardPosition(index);

  sf::RectangleShape card({constants::kCardSize, constants::kCardSize});
  card.setPosition(position);
  card.setFillColor(constants::kCardFaceColor);
  card.setOutlineThickness(3.0f);
  card.setOutlineColor(constants::kCardOutlineColor);
  window_.draw(card);

  drawing::DrawSymbol(window_, cards_[index].pair_id, position);
}

void MemoryGame::DrawWinOverlay() {
  sf::RectangleShape dark_layer(
      {static_cast<float>(constants::kWindowWidth),
       static_cast<float>(constants::kWindowHeight)});
  dark_layer.setFillColor(sf::Color(0, 0, 0, 170));
  window_.draw(dark_layer);

  sf::RectangleShape panel({410.0f, 210.0f});
  panel.setPosition({65.0f, 215.0f});
  panel.setFillColor(sf::Color(28, 32, 45));
  panel.setOutlineThickness(4.0f);
  panel.setOutlineColor(constants::kHudActiveColor);
  window_.draw(panel);

  DrawTrophy({270.0f, 280.0f});

  constexpr float kDigitUnit = 7.0f;
  const float width = drawing::GetNumberWidth(moves_, kDigitUnit);
  drawing::DrawNumber(window_, moves_, {270.0f - width / 2.0f, 335.0f}, kDigitUnit,
             constants::kHudActiveColor);
}

void MemoryGame::DrawTrophy(sf::Vector2f center) {
  drawing::DrawRectangle(window_, center + sf::Vector2f(-34.0f, -42.0f),
                {68.0f, 46.0f}, constants::kHudActiveColor);
  drawing::DrawRectangle(window_, center + sf::Vector2f(-12.0f, 4.0f),
                {24.0f, 32.0f}, constants::kHudActiveColor);
  drawing::DrawRectangle(window_, center + sf::Vector2f(-34.0f, 36.0f),
                {68.0f, 10.0f}, constants::kHudActiveColor);
  drawing::DrawRectangle(window_, center + sf::Vector2f(-58.0f, -30.0f),
                {20.0f, 12.0f}, constants::kHudActiveColor);
  drawing::DrawRectangle(window_, center + sf::Vector2f(38.0f, -30.0f),
                {20.0f, 12.0f}, constants::kHudActiveColor);
}

void MemoryGame::ShuffleHiddenCards() {
  std::vector<int> positions;
  std::vector<int> values;

  for (int i = 0; i < constants::kCardCount; ++i) {
    if (!cards_[i].is_matched && !cards_[i].is_open) {
      positions.push_back(i);
      values.push_back(cards_[i].pair_id);
    }
  }

  std::shuffle(values.begin(), values.end(), random_engine_);

  for (std::size_t i = 0; i < positions.size(); ++i) {
    cards_[positions[i]].pair_id = values[i];
  }
}
