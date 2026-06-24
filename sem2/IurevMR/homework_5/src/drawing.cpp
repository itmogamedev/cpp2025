#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

#include "game.h"

namespace drawing {

namespace {

sf::Vector2f Add(sf::Vector2f vector, float x, float y) {
  return {vector.x + x, vector.y + y};
}

sf::Color GetSymbolColor(int pair_id) {
  static const std::array<sf::Color, constants::kPairCount> kColors = {
      sf::Color(240, 111, 105), sf::Color(245, 180, 85),
      sf::Color(240, 220, 105), sf::Color(115, 205, 130),
      sf::Color(95, 190, 220),  sf::Color(120, 150, 245),
      sf::Color(185, 125, 235), sf::Color(235, 125, 185),
  };

  return kColors[pair_id];
}

void DrawDigit(sf::RenderWindow& window,
               int digit,
               sf::Vector2f position,
               float unit,
               sf::Color color) {
  static constexpr std::array<std::uint8_t, 10> kSegments = {
      0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
      0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111,
  };

  const std::uint8_t mask = kSegments[digit];

  const auto draw_segment = [&](int bit,
                                sf::Vector2f offset,
                                sf::Vector2f size) {
    if ((mask & (1 << bit)) != 0) {
      DrawRectangle(window, position + offset, size, color);
    }
  };

  draw_segment(0, {unit, 0.0f}, {4.0f * unit, unit});
  draw_segment(1, {5.0f * unit, unit}, {unit, 3.0f * unit});
  draw_segment(2, {5.0f * unit, 5.0f * unit}, {unit, 3.0f * unit});
  draw_segment(3, {unit, 8.0f * unit}, {4.0f * unit, unit});
  draw_segment(4, {0.0f, 5.0f * unit}, {unit, 3.0f * unit});
  draw_segment(5, {0.0f, unit}, {unit, 3.0f * unit});
  draw_segment(6, {unit, 4.0f * unit}, {4.0f * unit, unit});
}

void DrawCircleSymbol(sf::RenderWindow& window,
                      sf::Vector2f center,
                      sf::Color color) {
  sf::CircleShape circle(28.0f);
  circle.setPosition(Add(center, -28.0f, -28.0f));
  circle.setFillColor(color);
  window.draw(circle);
}

void DrawTriangleSymbol(sf::RenderWindow& window,
                        sf::Vector2f center,
                        sf::Color color) {
  sf::ConvexShape triangle;
  triangle.setPointCount(3);
  triangle.setPoint(0, Add(center, 0.0f, -34.0f));
  triangle.setPoint(1, Add(center, 34.0f, 28.0f));
  triangle.setPoint(2, Add(center, -34.0f, 28.0f));
  triangle.setFillColor(color);
  window.draw(triangle);
}

void DrawDiamondSymbol(sf::RenderWindow& window,
                       sf::Vector2f center,
                       sf::Color color) {
  sf::ConvexShape diamond;
  diamond.setPointCount(4);
  diamond.setPoint(0, Add(center, 0.0f, -36.0f));
  diamond.setPoint(1, Add(center, 36.0f, 0.0f));
  diamond.setPoint(2, Add(center, 0.0f, 36.0f));
  diamond.setPoint(3, Add(center, -36.0f, 0.0f));
  diamond.setFillColor(color);
  window.draw(diamond);
}

void DrawCrossSymbol(sf::RenderWindow& window,
                     sf::Vector2f center,
                     sf::Color color) {
  DrawRectangle(window, Add(center, -8.0f, -34.0f), {16.0f, 68.0f}, color);
  DrawRectangle(window, Add(center, -34.0f, -8.0f), {68.0f, 16.0f}, color);
}

void DrawDoubleCircleSymbol(sf::RenderWindow& window,
                            sf::Vector2f center,
                            sf::Color color) {
  sf::CircleShape left_circle(22.0f);
  left_circle.setPosition(Add(center, -42.0f, -22.0f));
  left_circle.setFillColor(color);
  window.draw(left_circle);

  sf::CircleShape right_circle(22.0f);
  right_circle.setPosition(Add(center, -2.0f, -22.0f));
  right_circle.setFillColor(color);
  window.draw(right_circle);
}

void DrawBarsSymbol(sf::RenderWindow& window,
                    sf::Vector2f center,
                    sf::Color color) {
  DrawRectangle(window, Add(center, -30.0f, -8.0f), {14.0f, 38.0f}, color);
  DrawRectangle(window, Add(center, -7.0f, -28.0f), {14.0f, 58.0f}, color);
  DrawRectangle(window, Add(center, 16.0f, -18.0f), {14.0f, 48.0f}, color);
}

void DrawTargetSymbol(sf::RenderWindow& window,
                      sf::Vector2f center,
                      sf::Color color) {
  sf::CircleShape outer(34.0f);
  outer.setPosition(Add(center, -34.0f, -34.0f));
  outer.setFillColor(color);
  window.draw(outer);

  sf::CircleShape inner(21.0f);
  inner.setPosition(Add(center, -21.0f, -21.0f));
  inner.setFillColor(constants::kCardFaceColor);
  window.draw(inner);

  sf::CircleShape dot(10.0f);
  dot.setPosition(Add(center, -10.0f, -10.0f));
  dot.setFillColor(color);
  window.draw(dot);
}

void DrawHouseSymbol(sf::RenderWindow& window,
                     sf::Vector2f center,
                     sf::Color color) {
  sf::ConvexShape house;
  house.setPointCount(5);
  house.setPoint(0, Add(center, 0.0f, -36.0f));
  house.setPoint(1, Add(center, 34.0f, -8.0f));
  house.setPoint(2, Add(center, 25.0f, 34.0f));
  house.setPoint(3, Add(center, -25.0f, 34.0f));
  house.setPoint(4, Add(center, -34.0f, -8.0f));
  house.setFillColor(color);
  window.draw(house);
}

}  // namespace

void DrawRectangle(sf::RenderWindow& window,
                   sf::Vector2f position,
                   sf::Vector2f size,
                   sf::Color color) {
  sf::RectangleShape shape(size);
  shape.setPosition(position);
  shape.setFillColor(color);
  window.draw(shape);
}

float GetNumberWidth(int number, float unit) {
  int digits = 1;

  while (number >= 10) {
    number /= 10;
    ++digits;
  }

  return static_cast<float>(digits) * 6.0f * unit +
         static_cast<float>(digits - 1) * 2.0f * unit;
}

void DrawNumber(sf::RenderWindow& window,
                int number,
                sf::Vector2f position,
                float unit,
                sf::Color color) {
  std::vector<int> digits;

  do {
    digits.push_back(number % 10);
    number /= 10;
  } while (number > 0);

  std::reverse(digits.begin(), digits.end());

  for (int digit : digits) {
    DrawDigit(window, digit, position, unit, color);
    position.x += 8.0f * unit;
  }
}

void DrawSymbol(sf::RenderWindow& window,
                int pair_id,
                sf::Vector2f card_position) {
  const sf::Vector2f center = Add(card_position, 48.0f, 48.0f);
  const sf::Color color = GetSymbolColor(pair_id);

  switch (pair_id) {
    case 0:
      DrawCircleSymbol(window, center, color);
      break;
    case 1:
      DrawTriangleSymbol(window, center, color);
      break;
    case 2:
      DrawDiamondSymbol(window, center, color);
      break;
    case 3:
      DrawCrossSymbol(window, center, color);
      break;
    case 4:
      DrawDoubleCircleSymbol(window, center, color);
      break;
    case 5:
      DrawBarsSymbol(window, center, color);
      break;
    case 6:
      DrawTargetSymbol(window, center, color);
      break;
    case 7:
      DrawHouseSymbol(window, center, color);
      break;
    default:
      break;
  }
}

}  // namespace drawing
