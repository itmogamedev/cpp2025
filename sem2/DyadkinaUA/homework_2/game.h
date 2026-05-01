#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include <array>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "target.h"

class SevenSegmentDigit {
 public:
  SevenSegmentDigit();

  void setPosition(const sf::Vector2f& position);
  void setSize(float width, float height, float thickness);
  void setColor(const sf::Color& color);
  void setValue(int value);
  void draw(sf::RenderWindow& window) const;

 private:
  void updateGeometry();

  std::array<sf::RectangleShape, 7> segments;
  sf::Vector2f position;
  float width;
  float height;
  float thickness;
  sf::Color color;
  int value;
};

class NumberDisplay {
 public:
  NumberDisplay(int digits_count, float digit_width, float digit_height,
                float segment_thickness, float spacing);

  void setPosition(const sf::Vector2f& position);
  void setColor(const sf::Color& color);
  void setValue(int value);
  void draw(sf::RenderWindow& window) const;

 private:
  std::vector<SevenSegmentDigit> digits;
  sf::Vector2f position;
  float digit_width;
  float digit_height;
  float segment_thickness;
  float spacing;
  int value;
};

class Game {
 public:
  Game();
  void run();

 private:
  static constexpr int kWindowWidth = 1000;
  static constexpr int kWindowHeight = 700;
  static constexpr int kTargetsCount = 5;
  static constexpr int kGameDurationSeconds = 30;
  static constexpr int kMissPenaltySeconds = 2;
  static constexpr float kTargetRadius = 32.0f;

  void processEvents();
  void update();
  void render();
  void handleLeftClick(int x, int y);
  void restart();
  void randomizeTargetPosition(int index);
  sf::Vector2f generateRandomPosition(int ignore_index = -1);

  void drawHud();
  void drawLabel(const sf::Vector2f& pos, const std::string& text, float scale,
                 const sf::Color& color);
  void drawLetter(const sf::Vector2f& pos, char letter, float scale,
                  const sf::Color& color);
  void drawGameOverScreen();

  sf::RenderWindow window;
  sf::Clock frame_clock;
  std::vector<CircleTarget> targets;
  std::mt19937 random_engine;
  float remaining_time_seconds;
  int score;
  bool is_game_over;
  NumberDisplay score_display;
  NumberDisplay time_display;
};

#endif  // GAME_H_
