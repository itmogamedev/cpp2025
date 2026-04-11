// Game.h
// Основной класс игры: владеет окном SFML, списком кругов, таймером и счётом.
// Обрабатывает ввод, обновляет состояние и отрисовывает кадр.

#ifndef HOMEWORK_2_GAME_H
#define HOMEWORK_2_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Circle.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(float dt);
  void render();
  void handleClick(float mx, float my);
  void reset();
  void loadTextures();

  static constexpr unsigned int window_width = 800;
  static constexpr unsigned int window_height = 600;
  static constexpr float top_offset = 60.f;
  static constexpr int circle_count = 5;
  static constexpr float circle_radius = 40.f;
  static constexpr float start_time = 30.f;
  static constexpr float miss_penalty = 1.5f;
  static constexpr float hit_bonus = 0.2f;

  sf::RenderWindow window;
  sf::Font font;
  bool font_loaded;
  std::vector<sf::Texture> textures;
  sf::Texture game_over_texture;
  bool game_over_texture_loaded;
  sf::Sprite game_over_sprite;
  std::vector<Circle> circles;
  sf::Text score_text;
  sf::Text timer_text;
  sf::Text game_over_text;
  sf::Text hint_text;
  float time_left;
  int score;
  bool game_over;
};

#endif  // HOMEWORK_2_GAME_H
