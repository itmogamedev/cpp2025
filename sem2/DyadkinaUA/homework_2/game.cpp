#include "game.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <ctime>
#include <optional>
#include <string>
#include <vector>

namespace {

constexpr bool kDigitMasks[10][7] = {
    {true, true, true, false, true, true, true},
    {false, false, true, false, false, true, false},
    {true, false, true, true, true, false, true},
    {true, false, true, true, false, true, true},
    {false, true, true, true, false, true, false},
    {true, true, false, true, false, true, true},
    {true, true, false, true, true, true, true},
    {true, false, true, false, false, true, false},
    {true, true, true, true, true, true, true},
    {true, true, true, true, false, true, true},
};

float distSq(const sf::Vector2f& a, const sf::Vector2f& b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

}  // namespace

// ---- SevenSegmentDigit ----

SevenSegmentDigit::SevenSegmentDigit()
    : position(0.0f, 0.0f),
      width(22.0f),
      height(38.0f),
      thickness(4.0f),
      color(sf::Color::White),
      value(0) {
  updateGeometry();
  setValue(0);
}

void SevenSegmentDigit::setPosition(const sf::Vector2f& p) {
  position = p;
  updateGeometry();
}

void SevenSegmentDigit::setSize(float w, float h, float t) {
  width = w;
  height = h;
  thickness = t;
  updateGeometry();
}

void SevenSegmentDigit::setColor(const sf::Color& c) {
  color = c;
  setValue(value);
}

void SevenSegmentDigit::setValue(int v) {
  value = std::clamp(v, 0, 9);
  for (int i = 0; i < 7; ++i) {
    segments[i].setFillColor(kDigitMasks[value][i] ? color
                                                   : sf::Color(50, 50, 50));
  }
}

void SevenSegmentDigit::draw(sf::RenderWindow& w) const {
  for (const sf::RectangleShape& s : segments) {
    w.draw(s);
  }
}

void SevenSegmentDigit::updateGeometry() {
  const float hl = width - 2.0f * thickness;
  const float vl = (height - 3.0f * thickness) / 2.0f;

  segments[0].setSize({hl, thickness});
  segments[0].setPosition({position.x + thickness, position.y});

  segments[1].setSize({thickness, vl});
  segments[1].setPosition({position.x, position.y + thickness});

  segments[2].setSize({thickness, vl});
  segments[2].setPosition(
      {position.x + width - thickness, position.y + thickness});

  segments[3].setSize({hl, thickness});
  segments[3].setPosition(
      {position.x + thickness, position.y + height / 2.0f - thickness / 2.0f});

  segments[4].setSize({thickness, vl});
  segments[4].setPosition(
      {position.x, position.y + height / 2.0f + thickness / 2.0f});

  segments[5].setSize({thickness, vl});
  segments[5].setPosition({position.x + width - thickness,
                           position.y + height / 2.0f + thickness / 2.0f});

  segments[6].setSize({hl, thickness});
  segments[6].setPosition(
      {position.x + thickness, position.y + height - thickness});
}

// ---- NumberDisplay ----

NumberDisplay::NumberDisplay(int cnt, float dw, float dh, float dt, float sp)
    : digits(cnt),
      position(0.0f, 0.0f),
      digit_width(dw),
      digit_height(dh),
      segment_thickness(dt),
      spacing(sp),
      value(0) {
  setPosition(position);
  setValue(0);
}

void NumberDisplay::setPosition(const sf::Vector2f& p) {
  position = p;
  for (std::size_t i = 0; i < digits.size(); ++i) {
    digits[i].setSize(digit_width, digit_height, segment_thickness);
    digits[i].setPosition(
        {position.x + static_cast<float>(i) * (digit_width + spacing),
         position.y});
  }
}

void NumberDisplay::setColor(const sf::Color& c) {
  for (SevenSegmentDigit& d : digits) {
    d.setColor(c);
  }
}

void NumberDisplay::setValue(int v) {
  value = std::max(0, v);
  int cur = value;
  for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
    digits[i].setValue(cur % 10);
    cur /= 10;
  }
}

void NumberDisplay::draw(sf::RenderWindow& w) const {
  for (const SevenSegmentDigit& d : digits) {
    d.draw(w);
  }
}

// ---- Game ----

Game::Game()
    : window(sf::VideoMode({static_cast<unsigned int>(kWindowWidth),
                            static_cast<unsigned int>(kWindowHeight)}),
             "OSU Home Edition"),
      random_engine(static_cast<unsigned int>(std::time(nullptr))),
      remaining_time_seconds(static_cast<float>(kGameDurationSeconds)),
      score(0),
      is_game_over(false),
      score_display(3, 22.0f, 38.0f, 4.0f, 5.0f),
      time_display(2, 22.0f, 38.0f, 4.0f, 5.0f) {
  window.setFramerateLimit(60);

  const std::array<sf::Color, kTargetsCount> colors = {
      sf::Color(255, 99, 132), sf::Color(54, 162, 235), sf::Color(255, 205, 86),
      sf::Color(75, 192, 192), sf::Color(153, 102, 255)};

  for (int i = 0; i < kTargetsCount; ++i) {
    targets.emplace_back(kTargetRadius, colors[i]);
  }

  time_display.setPosition({125.0f, 18.0f});
  time_display.setColor(sf::Color::White);
  score_display.setPosition({840.0f, 18.0f});
  score_display.setColor(sf::Color::White);

  restart();
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    update();
    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    if (const auto* m = event->getIf<sf::Event::MouseButtonPressed>()) {
      if (m->button == sf::Mouse::Button::Left) {
        handleLeftClick(m->position.x, m->position.y);
      }
    }

    if (const auto* k = event->getIf<sf::Event::KeyPressed>()) {
      if (k->code == sf::Keyboard::Key::R) {
        restart();
      }
    }
  }
}

void Game::update() {
  const float dt = frame_clock.restart().asSeconds();

  if (!is_game_over) {
    remaining_time_seconds -= dt;
    if (remaining_time_seconds <= 0.0f) {
      remaining_time_seconds = 0.0f;
      is_game_over = true;
    }
  }

  score_display.setValue(score);
  time_display.setValue(static_cast<int>(std::ceil(remaining_time_seconds)));
}

void Game::render() {
  window.clear(sf::Color(12, 12, 18));

  for (const CircleTarget& t : targets) {
    t.draw(window);
  }

  drawHud();

  if (is_game_over) {
    drawGameOverScreen();
  }

  window.display();
}

void Game::handleLeftClick(int x, int y) {
  if (is_game_over) {
    return;
  }

  const sf::Vector2f click(static_cast<float>(x), static_cast<float>(y));

  for (int i = 0; i < static_cast<int>(targets.size()); ++i) {
    if (targets[i].contains(click)) {
      ++score;
      randomizeTargetPosition(i);
      return;
    }
  }

  remaining_time_seconds -= static_cast<float>(kMissPenaltySeconds);
  if (remaining_time_seconds <= 0.0f) {
    remaining_time_seconds = 0.0f;
    is_game_over = true;
  }
}

void Game::restart() {
  score = 0;
  remaining_time_seconds = static_cast<float>(kGameDurationSeconds);
  is_game_over = false;
  frame_clock.restart();

  for (int i = 0; i < static_cast<int>(targets.size()); ++i) {
    randomizeTargetPosition(i);
  }
}

void Game::randomizeTargetPosition(int index) {
  const sf::Vector2f old_pos = targets[index].getPosition();

  for (int attempt = 0; attempt < 200; ++attempt) {
    const sf::Vector2f np = generateRandomPosition(index);
    if (distSq(old_pos, np) > 130.0f * 130.0f) {
      targets[index].setPosition(np);
      return;
    }
  }

  targets[index].setPosition(generateRandomPosition(index));
}

sf::Vector2f Game::generateRandomPosition(int ignore_index) {
  std::uniform_real_distribution<float> xd(
      kTargetRadius, static_cast<float>(kWindowWidth) - kTargetRadius);
  std::uniform_real_distribution<float> yd(
      120.0f + kTargetRadius,
      static_cast<float>(kWindowHeight) - kTargetRadius);

  const float min_dist = kTargetRadius * 2.2f;

  for (int attempt = 0; attempt < 100; ++attempt) {
    const sf::Vector2f c(xd(random_engine), yd(random_engine));
    bool ok = true;

    for (int i = 0; i < static_cast<int>(targets.size()); ++i) {
      if (i == ignore_index) {
        continue;
      }

      if (distSq(c, targets[i].getPosition()) < min_dist * min_dist) {
        ok = false;
        break;
      }
    }

    if (ok) {
      return c;
    }
  }

  return {xd(random_engine), yd(random_engine)};
}

void Game::drawHud() {
  drawLabel({28.0f, 20.0f}, "TIME", 1.0f, sf::Color::White);
  drawLabel({720.0f, 20.0f}, "SCORE", 1.0f, sf::Color::White);
  drawLabel({28.0f, 68.0f}, "MISS -2 SEC", 0.85f, sf::Color(220, 140, 140));

  time_display.draw(window);
  score_display.draw(window);

  sf::RectangleShape line({static_cast<float>(kWindowWidth) - 30.0f, 2.0f});
  line.setPosition({15.0f, 108.0f});
  line.setFillColor(sf::Color(60, 60, 80));
  window.draw(line);
}

void Game::drawLabel(const sf::Vector2f& pos, const std::string& text,
                     float scale, const sf::Color& color) {
  float ox = 0.0f;

  for (char c : text) {
    if (c == ' ') {
      ox += 12.0f * scale;
    } else {
      drawLetter({pos.x + ox, pos.y}, c, scale, color);
      ox += 22.0f * scale;
    }
  }
}

void Game::drawLetter(const sf::Vector2f& pos, char letter, float scale,
                      const sf::Color& color) {
  std::vector<std::string> p;

  switch (letter) {
    case 'A':
      p = {"01110", "10001", "11111", "10001", "10001"};
      break;
    case 'C':
      p = {"01111", "10000", "10000", "10000", "01111"};
      break;
    case 'E':
      p = {"11111", "11000", "11110", "11000", "11111"};
      break;
    case 'G':
      p = {"01111", "10000", "10111", "10001", "01110"};
      break;
    case 'I':
      p = {"11111", "00100", "00100", "00100", "11111"};
      break;
    case 'M':
      p = {"10001", "11011", "10101", "10001", "10001"};
      break;
    case 'O':
      p = {"01110", "10001", "10001", "10001", "01110"};
      break;
    case 'P':
      p = {"11110", "10001", "11110", "10000", "10000"};
      break;
    case 'R':
      p = {"11110", "10001", "11110", "10100", "10010"};
      break;
    case 'S':
      p = {"01111", "10000", "01110", "00001", "11110"};
      break;
    case 'T':
      p = {"11111", "00100", "00100", "00100", "00100"};
      break;
    case 'V':
      p = {"10001", "10001", "10001", "01010", "00100"};
      break;
    case '-':
      p = {"00000", "00000", "11111", "00000", "00000"};
      break;
    case '2':
      p = {"01110", "00001", "00110", "01000", "11111"};
      break;
    default:
      return;
  }

  const float pixel_size = 3.0f * scale;
  const float pixel_step = 4.0f * scale;

  for (int row = 0; row < static_cast<int>(p.size()); ++row) {
    for (int col = 0; col < static_cast<int>(p[row].size()); ++col) {
      if (p[row][col] == '1') {
        sf::RectangleShape pixel({pixel_size, pixel_size});
        pixel.setPosition({pos.x + static_cast<float>(col) * pixel_step,
                           pos.y + static_cast<float>(row) * pixel_step});
        pixel.setFillColor(color);
        window.draw(pixel);
      }
    }
  }
}

void Game::drawGameOverScreen() {
  sf::RectangleShape overlay(
      {static_cast<float>(kWindowWidth), static_cast<float>(kWindowHeight)});
  overlay.setFillColor(sf::Color(0, 0, 0, 160));
  window.draw(overlay);

  sf::RectangleShape panel({420.0f, 160.0f});
  panel.setPosition({290.0f, 250.0f});
  panel.setFillColor(sf::Color(28, 28, 40));
  panel.setOutlineThickness(2.0f);
  panel.setOutlineColor(sf::Color(180, 180, 220));
  window.draw(panel);

  drawLabel({359.0f, 272.0f}, "GAME OVER", 1.5f, sf::Color::White);
  drawLabel({345.0f, 330.0f}, "SCORE", 1.0f, sf::Color(180, 210, 255));

  NumberDisplay final_score(3, 22.0f, 38.0f, 4.0f, 5.0f);
  final_score.setPosition({460.0f, 323.0f});
  final_score.setColor(sf::Color::White);
  final_score.setValue(score);
  final_score.draw(window);

  drawLabel({322.0f, 378.0f}, "PRESS R TO RESTART", 0.85f,
            sf::Color(160, 160, 160));
}
