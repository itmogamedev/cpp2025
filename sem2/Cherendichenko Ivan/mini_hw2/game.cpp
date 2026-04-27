#include "game.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "game_config.h"

Game::Game()
    : window_(
          sf::VideoMode(GameConfig::kWindowWidth, GameConfig::kWindowHeight),
          GameConfig::kWindowTitle, sf::Style::Close),
      time_remaining_(GameConfig::kGameDuration),
      score_(0),
      miss_flash_timer_(0.f),
      state_(State::Playing) {
  window_.setFramerateLimit(GameConfig::kFrameRateLimit);
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
  loadAssets();
  initTargets();
}

void Game::run() {
  while (window_.isOpen()) {
    const float dt = clock_.restart().asSeconds();
    handleEvents();
    update(dt);
    render();
  }
}

void Game::loadAssets() {
  const std::string font_path =
      GameConfig::kAssetsFolder + GameConfig::kFontFilename;
  if (!font_.loadFromFile(font_path)) {
    std::cerr << "[Game] Font not found at: " << font_path
              << " — text will not render. Put font.ttf into assets/\n";
  }

  const std::string bg_path =
      GameConfig::kAssetsFolder + GameConfig::kBackgroundFilename;
  if (bg_texture_.loadFromFile(bg_path)) {
    bg_texture_.setSmooth(true);
    bg_sprite_.setTexture(bg_texture_);
    const sf::Vector2u sz = bg_texture_.getSize();
    bg_sprite_.setScale(
        static_cast<float>(GameConfig::kWindowWidth) / static_cast<float>(sz.x),
        static_cast<float>(GameConfig::kWindowHeight) /
            static_cast<float>(sz.y));
    bg_loaded_ = true;
    std::cout << "[Game] Background loaded: " << bg_path << "\n";
  } else {
    std::cerr << "[Game] Background not found: " << bg_path << "\n";
  }

  loadStickers();
}

void Game::loadStickers() {
  namespace fs = std::filesystem;

  const std::string folder = GameConfig::kAssetsFolder;
  if (!fs::exists(folder)) {
    std::cerr << "[Game] assets/ folder not found next to the executable!\n";
    return;
  }

  std::vector<std::string> paths;
  for (const auto& entry : fs::directory_iterator(folder)) {
    if (!entry.is_regular_file()) continue;

    std::string ext = entry.path().extension().string();
    for (char& c : ext)
      c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (ext != ".png" && ext != ".jpg" && ext != ".jpeg" && ext != ".bmp" &&
        ext != ".tga")
      continue;

    const std::string stem = entry.path().stem().string();

    const std::string& prefix = GameConfig::kStickerPrefix;
    if (stem.size() >= prefix.size() &&
        stem.substr(0, prefix.size()) == prefix) {
      paths.push_back(entry.path().string());
    }
  }

  std::sort(paths.begin(), paths.end());

  for (const auto& p : paths) {
    sf::Texture tex;
    tex.setSmooth(true);
    if (tex.loadFromFile(p)) {
      sticker_textures_.push_back(std::move(tex));
      std::cout << "[Game] Sticker loaded: " << p << "\n";
    } else {
      std::cerr << "[Game] Failed to load sticker: " << p << "\n";
    }
  }

  std::cout << "[Game] Total stickers: " << sticker_textures_.size() << "\n";
}

void Game::initTargets() {
  targets_.clear();
  for (int i = 0; i < GameConfig::kTargetCount; ++i) {
    auto t =
        std::make_unique<Target>(GameConfig::kTargetRadius, sticker_textures_);
    t->randomize(GameConfig::kWindowWidth, GameConfig::kWindowHeight);
    targets_.push_back(std::move(t));
  }
}

void Game::handleEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
      return;
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) {
        window_.close();
        return;
      }

      if (state_ == State::GameOver && event.key.code == sf::Keyboard::R) {
        time_remaining_ = GameConfig::kGameDuration;
        score_ = 0;
        miss_flash_timer_ = 0.f;
        state_ = State::Playing;
        initTargets();
      }
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
      onMouseClick({static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y)});
    }
  }
}

void Game::onMouseClick(sf::Vector2f pos) {
  if (state_ != State::Playing) return;

  for (auto& t : targets_) {
    if (t->isClicked(pos)) {
      t->randomize(GameConfig::kWindowWidth, GameConfig::kWindowHeight);
      ++score_;
      return;
    }
  }

  time_remaining_ -= GameConfig::kMissPenalty;
  miss_flash_timer_ = GameConfig::kMissFlashDuration;
  if (time_remaining_ <= 0.f) {
    time_remaining_ = 0.f;
    state_ = State::GameOver;
  }
}

void Game::update(float dt) {
  if (state_ != State::Playing) return;

  miss_flash_timer_ = std::max(0.f, miss_flash_timer_ - dt);

  time_remaining_ -= dt;
  if (time_remaining_ <= 0.f) {
    time_remaining_ = 0.f;
    state_ = State::GameOver;
    return;
  }

  for (auto& t : targets_)
    t->update(dt, GameConfig::kWindowWidth, GameConfig::kWindowHeight);
}

void Game::render() {
  window_.clear(sf::Color(30, 30, 40));

  if (bg_loaded_) window_.draw(bg_sprite_);

  if (state_ == State::Playing) {
    for (const auto& t : targets_) t->draw(window_);
    renderMissFlash();
    renderHUD();
  } else {
    renderGameOver();
  }

  window_.display();
}

void Game::renderHUD() {
  std::ostringstream oss;
  oss << "Time: " << std::fixed << std::setprecision(1) << time_remaining_;

  sf::Text timer_text;
  timer_text.setFont(font_);
  timer_text.setCharacterSize(GameConfig::kFontSizeHud);
  timer_text.setFillColor(time_remaining_ <= GameConfig::kLowTimeWarn
                              ? sf::Color::Red
                              : sf::Color::White);
  timer_text.setOutlineColor(sf::Color::Black);
  timer_text.setOutlineThickness(GameConfig::kTextOutline);
  timer_text.setString(oss.str());
  timer_text.setPosition(GameConfig::kHudPadding, GameConfig::kHudPadding);
  window_.draw(timer_text);

  sf::Text score_text;
  score_text.setFont(font_);
  score_text.setCharacterSize(GameConfig::kFontSizeHud);
  score_text.setFillColor(sf::Color::White);
  score_text.setOutlineColor(sf::Color::Black);
  score_text.setOutlineThickness(GameConfig::kTextOutline);
  score_text.setString("Score: " + std::to_string(score_));

  const sf::FloatRect sb = score_text.getLocalBounds();
  score_text.setPosition(static_cast<float>(GameConfig::kWindowWidth) -
                             sb.width - sb.left - GameConfig::kHudPadding,
                         GameConfig::kHudPadding);
  window_.draw(score_text);
}

void Game::renderMissFlash() {
  if (miss_flash_timer_ <= 0.f) return;

  const float ratio = miss_flash_timer_ / GameConfig::kMissFlashDuration;
  sf::RectangleShape flash(
      sf::Vector2f(static_cast<float>(GameConfig::kWindowWidth),
                   static_cast<float>(GameConfig::kWindowHeight)));
  flash.setFillColor(sf::Color(
      255, 0, 0, static_cast<sf::Uint8>(GameConfig::kMissFlashAlpha * ratio)));
  window_.draw(flash);
}

void Game::drawCentred(const std::string& str, unsigned int size,
                       sf::Color fill, float y_offset) {
  sf::Text text;
  text.setFont(font_);
  text.setCharacterSize(size);
  text.setFillColor(fill);
  text.setOutlineColor(sf::Color::Black);
  text.setOutlineThickness(size >= GameConfig::kFontSizeTitle
                               ? GameConfig::kTitleOutline
                               : GameConfig::kTextOutline);
  text.setString(str);
  const sf::FloatRect b = text.getLocalBounds();
  text.setPosition(
      static_cast<float>(GameConfig::kWindowWidth) / 2.f -
          (b.width + b.left) / 2.f,
      static_cast<float>(GameConfig::kWindowHeight) / 2.f + y_offset);
  window_.draw(text);
}

void Game::renderGameOver() {
  sf::RectangleShape overlay(
      sf::Vector2f(static_cast<float>(GameConfig::kWindowWidth),
                   static_cast<float>(GameConfig::kWindowHeight)));
  overlay.setFillColor(sf::Color(0, 0, 0, GameConfig::kOverlayAlpha));
  window_.draw(overlay);

  drawCentred("GAME OVER", GameConfig::kFontSizeTitle, sf::Color::Yellow,
              -90.f);
  drawCentred("Your score: " + std::to_string(score_),
              GameConfig::kFontSizeBody, sf::Color::White, -5.f);
  drawCentred("R - restart          ESC - quit", GameConfig::kFontSizeBody,
              sf::Color(180, 180, 255), 60.f);
}
