#include "Game.hpp"

#include <cstring>
#include <stdexcept>
#include <string>

namespace {

const char* kFontPaths[] = {
    "/Library/Fonts/Arial Unicode.ttf",
    "/System/Library/Fonts/Supplemental/Arial Unicode.ttf"
};

const sf::Color kBgColor      {30,  30,  40};
const sf::Color kHudColor     {210, 210, 220};
const sf::Color kOverlayColor {0,   0,   0, 190};

sf::String ToSfString(const char* utf8) {
  return sf::String::fromUtf8(utf8, utf8 + std::strlen(utf8));
}

bool LoadFont(sf::Font& font) {
  for (const char* path : kFontPaths)
    if (font.openFromFile(path))
      return true;
  return false;
}

}  // namespace

Game::Game()
    : window_(sf::VideoMode({520u, 570u}), "Grayjack"),
      board_(font_),
      hud_text_(font_, {}, 22),
      game_over_text_(font_, {}, 44) {
  if (!LoadFont(font_))
    throw std::runtime_error("Font not found. Set path in Game.cpp -> kFontPaths");

  window_.setFramerateLimit(60);
  hud_text_.setFillColor(kHudColor);
  game_over_text_.setFillColor(sf::Color::White);
}

void Game::Run() {
  while (window_.isOpen()) {
    while (std::optional<sf::Event> event = window_.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window_.close();
      HandleEvent(*event);
    }
    Update();
    Render();
  }
}

void Game::HandleEvent(const sf::Event& event) {
  if (state_ == GameState::kGameOver) {
    if (event.is<sf::Event::KeyPressed>() ||
        event.is<sf::Event::MouseButtonPressed>())
      window_.close();
    return;
  }

  if (state_ != GameState::kWaitingFirst && state_ != GameState::kWaitingSecond)
    return;

  if (const auto* mp = event.getIf<sf::Event::MouseButtonPressed>())
    if (mp->button == sf::Mouse::Button::Left)
      OnCardClick(sf::Vector2f(mp->position));
}

void Game::OnCardClick(sf::Vector2f pos) {
  int idx = board_.CardAt(pos);
  if (idx < 0) return;

  if (state_ == GameState::kWaitingFirst) {
    board_.FlipCard(idx);
    first_card_ = idx;
    state_ = GameState::kWaitingSecond;
  } else if (state_ == GameState::kWaitingSecond) {
    if (idx == first_card_) return;
    board_.FlipCard(idx);
    second_card_ = idx;
    delay_clock_.restart();
    state_ = GameState::kShowingPair;
  }
}

void Game::Update() {
  if (state_ != GameState::kShowingPair) return;
  if (delay_clock_.getElapsedTime().asSeconds() < kShowDelay) return;

  ++moves_;

  if (board_.GetCard(first_card_).symbol == board_.GetCard(second_card_).symbol) {
    board_.MatchFlipped();
    ++score_;
    consec_misses_ = 0;
    if (board_.AllMatched()) {
      state_ = GameState::kGameOver;
      return;
    }
  } else {
    board_.HideFlipped();
    ++consec_misses_;
    if (consec_misses_ >= 2) {
      board_.ShuffleUnmatched();
      consec_misses_ = 0;
    }
  }

  first_card_ = -1;
  second_card_ = -1;
  state_       = GameState::kWaitingFirst;
}

void Game::Render() {
  window_.clear(kBgColor);

  board_.Draw(window_);

  hud_text_.setString(ToSfString("Ходы: ") + sf::String(std::to_string(moves_)));
  hud_text_.setPosition({15.f, 18.f});
  window_.draw(hud_text_);

  hud_text_.setString(ToSfString("Пары: ") + sf::String(std::to_string(score_)) +
                      sf::String(U"/8"));
  {
    sf::FloatRect b = hud_text_.getLocalBounds();
    hud_text_.setPosition({520.f - b.position.x - b.size.x - 15.f, 18.f});
  }
  window_.draw(hud_text_);

  if (state_ == GameState::kGameOver) {
    sf::RectangleShape overlay({520.f, 570.f});
    overlay.setFillColor(kOverlayColor);
    window_.draw(overlay);

    game_over_text_.setCharacterSize(44);
    game_over_text_.setString(ToSfString("Победа!"));
    {
      sf::FloatRect b = game_over_text_.getLocalBounds();
      game_over_text_.setOrigin({b.position.x + b.size.x * 0.5f,
                                 b.position.y + b.size.y * 0.5f});
    }
    game_over_text_.setPosition({260.f, 220.f});
    window_.draw(game_over_text_);

    game_over_text_.setCharacterSize(28);
    game_over_text_.setString(ToSfString("Ходов: ") +
                              sf::String(std::to_string(moves_)));
    {
      sf::FloatRect b = game_over_text_.getLocalBounds();
      game_over_text_.setOrigin({b.position.x + b.size.x * 0.5f,
                                 b.position.y + b.size.y * 0.5f});
    }
    game_over_text_.setPosition({260.f, 290.f});
    window_.draw(game_over_text_);

    game_over_text_.setCharacterSize(16);
    game_over_text_.setFillColor({180, 180, 180});
    game_over_text_.setString(ToSfString("Нажмите любую кнопку для выхода"));
    {
      sf::FloatRect b = game_over_text_.getLocalBounds();
      game_over_text_.setOrigin({b.position.x + b.size.x * 0.5f,
                                 b.position.y + b.size.y * 0.5f});
    }
    game_over_text_.setPosition({260.f, 350.f});
    window_.draw(game_over_text_);

    game_over_text_.setCharacterSize(44);
    game_over_text_.setFillColor(sf::Color::White);
    game_over_text_.setOrigin({0.f, 0.f});
  }

  window_.display();
}
