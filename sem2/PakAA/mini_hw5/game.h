#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

#include "asteroid.h"
#include "bullet.h"
#include "player.h"

class Game {
 public:
  Game();
  void run();

 private:
  static constexpr int kWindowWidth = 800;
  static constexpr int kWindowHeight = 600;

  void processEvents();
  void update(float delta_time);
  void render();

  void spawnAsteroid();
  void checkCollisions();
  void resetGame();

  void drawHud();
  void drawGameOver();
  void setupHudTexts();
  void setupBackground();

  sf::RenderWindow window;
  sf::Sprite background_sprite;
  sf::Text score_text;
  sf::Text lives_text;
  sf::Text game_over_text;
  sf::Text final_score_text;
  sf::Text restart_text;
  // Полупрозрачная плашка под HUD, чтобы текст был читаем поверх фона.
  sf::RectangleShape hud_overlay;
  // Затемнение фона на экране Game Over.
  sf::RectangleShape game_over_overlay;

  std::unique_ptr<Player> player;
  std::vector<Bullet> bullets;
  std::vector<Asteroid> asteroids;
  std::vector<std::string> asteroid_textures;

  int score;
  float asteroid_spawn_timer;
  float asteroid_spawn_interval;
  float asteroid_base_speed;
  float game_time;
  bool game_over;
};

#endif  // SPACE_SHOOTER_GAME_H
