#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Asteroid.h"
#include "Bullet.h"
#include "Ship.h"

class Game {
 public:
  Game();
  void run();

 private:
  void processEvents();
  void update(sf::Time delta_time);
  void render();
  void spawnAsteroid();
  void handleCollisions();
  void updateReloadCooldown();

  sf::RenderWindow window;
  Ship ship;
  std::vector<Bullet> bullets;
  std::vector<Asteroid> asteroids;
  sf::Font font;
  sf::Text score_text;
  sf::Text lives_text;
  sf::Text game_over_text;
  sf::Text final_score_text;

  int score;
  int lives;
  float reload_cooldown;
  sf::Clock last_shot_clock;
  float asteroid_base_speed;
  float asteroid_spawn_timer;
  float asteroid_spawn_delay;
  sf::Clock game_clock;
  bool is_game_over;
  float invincibility_timer;

  static constexpr float kInvincibleDuration = 1.0f;
  static constexpr float kInitReload = 0.5f;
  static constexpr float kMinReload = 0.1f;
  static constexpr float kWindowWidth = 800.f;
  static constexpr float kWindowHeight = 600.f;
};

#endif
