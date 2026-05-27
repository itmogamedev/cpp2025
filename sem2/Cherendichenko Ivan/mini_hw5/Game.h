#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <string>

#include "Card.h"

// Игра "Запоминашки": поле 4x4, нужно найти все 8 пар.
class Game {
 public:
  Game();
  void run();

 private:
  // Главный цикл.
  void processEvents();
  void update();
  void render();

  // Игровая логика.
  void handleClick(float x, float y);
  void resolveTurn();
  void shuffleHidden();
  bool isWin() const;
  int findCardAt(float x, float y) const;

  // Инициализация ресурсов и поля.
  bool loadResources();
  void createBackTexture();
  void setupBoard();
  void drawHud();

  static sf::String toSfmlString(const std::string& utf8_text);

  static const int kGridSize = 4;
  static const int kCardCount = 16;
  static const int kPairCount = 8;
  static const int kWindowWidth = 720;
  static const int kWindowHeight = 820;
  static const int kCardSize = 150;
  static const int kGap = 16;
  static const int kTopMargin = 30;

  sf::RenderWindow window;
  sf::Font font;
  sf::Texture background_texture;
  sf::Texture back_texture;
  std::array<sf::Texture, kPairCount> face_textures;
  sf::Sprite background_sprite;
  std::array<Card, kCardCount> cards;

  int first_index;
  int second_index;
  int moves;
  int found_pairs;
  int consecutive_errors;

  bool waiting;
  sf::Clock reveal_clock;
  sf::Time reveal_delay;

  bool game_over;
};
