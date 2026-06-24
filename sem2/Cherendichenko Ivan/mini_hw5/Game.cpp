#include "Game.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

namespace {
std::mt19937& rng() {
  static std::mt19937 engine(std::random_device{}());
  return engine;
}
}  // namespace

Game::Game()
    : window(sf::VideoMode(kWindowWidth, kWindowHeight), L"Запоминашки",
             sf::Style::Titlebar | sf::Style::Close),
      first_index(-1),
      second_index(-1),
      moves(0),
      found_pairs(0),
      consecutive_errors(0),
      waiting(false),
      reveal_delay(sf::seconds(0.85f)),
      game_over(false) {
  window.setFramerateLimit(60);
  if (!loadResources()) {
    std::cerr << "Не удалось загрузить ресурсы из папки assets." << std::endl;
  }
  createBackTexture();
  setupBoard();
}

bool Game::loadResources() {
  bool ok = true;

  if (!font.loadFromFile("assets/font.ttf")) {
    ok = false;
  }

  if (background_texture.loadFromFile("assets/background.jpg")) {
    background_texture.setSmooth(true);
    background_sprite.setTexture(background_texture);
    sf::Vector2u size = background_texture.getSize();
    float scale_x = static_cast<float>(kWindowWidth) / size.x;
    float scale_y = static_cast<float>(kWindowHeight) / size.y;
    float scale = std::max(scale_x, scale_y);
    background_sprite.setScale(scale, scale);
    float offset_x = (kWindowWidth - size.x * scale) / 2.f;
    float offset_y = (kWindowHeight - size.y * scale) / 2.f;
    background_sprite.setPosition(offset_x, offset_y);
  } else {
    ok = false;
  }

  for (int i = 0; i < kPairCount; ++i) {
    std::string path = "assets/card" + std::to_string(i + 1) + ".png";
    if (face_textures[i].loadFromFile(path)) {
      face_textures[i].setSmooth(true);
    } else {
      ok = false;
    }
  }
  return ok;
}

void Game::createBackTexture() {
  const unsigned int s = 256;
  sf::RenderTexture render_texture;
  render_texture.create(s, s);
  render_texture.clear(sf::Color(38, 48, 78));

  sf::RectangleShape inner(sf::Vector2f(s - 24.f, s - 24.f));
  inner.setPosition(12.f, 12.f);
  inner.setFillColor(sf::Color(58, 72, 116));
  inner.setOutlineThickness(6.f);
  inner.setOutlineColor(sf::Color(205, 214, 235));
  render_texture.draw(inner);

  sf::Text question("?", font, 150);
  question.setStyle(sf::Text::Bold);
  question.setFillColor(sf::Color(222, 228, 245));
  sf::FloatRect b = question.getLocalBounds();
  question.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
  question.setPosition(s / 2.f, s / 2.f);
  render_texture.draw(question);

  render_texture.display();
  back_texture = render_texture.getTexture();
  back_texture.setSmooth(true);
}

void Game::setupBoard() {
  std::vector<int> symbols;
  for (int i = 0; i < kPairCount; ++i) {
    symbols.push_back(i);
    symbols.push_back(i);
  }
  std::shuffle(symbols.begin(), symbols.end(), rng());

  const float grid_width = kGridSize * kCardSize + (kGridSize - 1) * kGap;
  const float left = (kWindowWidth - grid_width) / 2.f;

  for (int i = 0; i < kCardCount; ++i) {
    int row = i / kGridSize;
    int col = i % kGridSize;
    float x = left + col * (kCardSize + kGap);
    float y = kTopMargin + row * (kCardSize + kGap);
    cards[i].setSymbol(symbols[i]);
    cards[i].setState(CardState::kHidden);
    cards[i].setBounds(x, y, static_cast<float>(kCardSize));
  }
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    update();
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::MouseButtonPressed &&
               event.mouseButton.button == sf::Mouse::Left) {
      handleClick(static_cast<float>(event.mouseButton.x),
                  static_cast<float>(event.mouseButton.y));
    }
  }
}

int Game::findCardAt(float x, float y) const {
  for (int i = 0; i < kCardCount; ++i) {
    if (cards[i].contains(x, y)) {
      return i;
    }
  }
  return -1;
}

void Game::handleClick(float x, float y) {
  if (game_over || waiting) {
    return;
  }

  int index = findCardAt(x, y);
  if (index < 0 || cards[index].getState() != CardState::kHidden) {
    return;
  }

  cards[index].setState(CardState::kRevealed);

  if (first_index < 0) {
    first_index = index;
  } else if (index != first_index) {
    second_index = index;
    ++moves;
    waiting = true;
    reveal_clock.restart();
  }
}

void Game::update() {
  if (waiting && reveal_clock.getElapsedTime() >= reveal_delay) {
    resolveTurn();
    waiting = false;
  }
}

void Game::resolveTurn() {
  Card& first = cards[first_index];
  Card& second = cards[second_index];

  if (first.getSymbol() == second.getSymbol()) {
    first.setState(CardState::kMatched);
    second.setState(CardState::kMatched);
    ++found_pairs;
    consecutive_errors = 0;
  } else {
    first.setState(CardState::kHidden);
    second.setState(CardState::kHidden);
    ++consecutive_errors;
    if (consecutive_errors >= 2) {
      shuffleHidden();
      consecutive_errors = 0;
    }
  }

  first_index = -1;
  second_index = -1;

  if (isWin()) {
    game_over = true;
  }
}

void Game::shuffleHidden() {
  std::vector<int> hidden_indices;
  std::vector<int> hidden_symbols;
  for (int i = 0; i < kCardCount; ++i) {
    if (cards[i].getState() == CardState::kHidden) {
      hidden_indices.push_back(i);
      hidden_symbols.push_back(cards[i].getSymbol());
    }
  }
  std::shuffle(hidden_symbols.begin(), hidden_symbols.end(), rng());
  for (std::size_t i = 0; i < hidden_indices.size(); ++i) {
    cards[hidden_indices[i]].setSymbol(hidden_symbols[i]);
  }
}

bool Game::isWin() const { return found_pairs == kPairCount; }

sf::String Game::toSfmlString(const std::string& utf8_text) {
  return sf::String::fromUtf8(utf8_text.begin(), utf8_text.end());
}

void Game::drawHud() {
  sf::Text info("", font, 28);
  info.setFillColor(sf::Color::White);
  info.setStyle(sf::Text::Bold);
  info.setString(toSfmlString("Ходы: " + std::to_string(moves) +
                              "      Пары: " + std::to_string(found_pairs) +
                              " / " + std::to_string(kPairCount)));
  info.setPosition(36.f, kWindowHeight - 110.f);

  // Тёмная подложка под текстом для читаемости.
  sf::FloatRect bounds = info.getLocalBounds();
  sf::RectangleShape backdrop(
      sf::Vector2f(bounds.width + 24.f, bounds.height + 24.f));
  backdrop.setPosition(info.getPosition().x - 12.f,
                       info.getPosition().y - 6.f);
  backdrop.setFillColor(sf::Color(0, 0, 0, 150));
  window.draw(backdrop);
  window.draw(info);

  if (game_over) {
    sf::Text win("", font, 40);
    win.setStyle(sf::Text::Bold);
    win.setFillColor(sf::Color(120, 230, 140));
    win.setString(
        toSfmlString("Победа! Ходов: " + std::to_string(moves)));
    sf::FloatRect wb = win.getLocalBounds();
    win.setOrigin(wb.left + wb.width / 2.f, wb.top + wb.height / 2.f);
    win.setPosition(kWindowWidth / 2.f, kWindowHeight - 55.f);

    sf::RectangleShape win_backdrop(
        sf::Vector2f(wb.width + 40.f, wb.height + 28.f));
    win_backdrop.setOrigin(win_backdrop.getSize().x / 2.f,
                           win_backdrop.getSize().y / 2.f);
    win_backdrop.setPosition(win.getPosition());
    win_backdrop.setFillColor(sf::Color(0, 0, 0, 170));
    window.draw(win_backdrop);
    window.draw(win);
  }
}

void Game::render() {
  window.clear(sf::Color(20, 24, 34));
  window.draw(background_sprite);

  // Полупрозрачная вуаль, чтобы карточки были контрастнее фона.
  sf::RectangleShape veil(
      sf::Vector2f(static_cast<float>(kWindowWidth),
                   static_cast<float>(kWindowHeight)));
  veil.setFillColor(sf::Color(0, 0, 0, 90));
  window.draw(veil);

  for (int i = 0; i < kCardCount; ++i) {
    cards[i].draw(window, back_texture, face_textures[cards[i].getSymbol()]);
  }

  drawHud();
  window.display();
}
