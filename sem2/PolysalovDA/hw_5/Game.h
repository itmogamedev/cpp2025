#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "BulletSystem.h"
#include "Constants.h"
#include "EnemySystem.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "Spaceship.h"
#include "UI.h"

class Game {
 private:
  sf::Texture spaceship_texture;
  sf::Texture bullet_texture;
  sf::RenderWindow window;
  InputHandler handler;
  Renderer renderer;
  UI ui;

  Spaceship spaceship;
  EnemySystem enemy_system;
  BulletSystem bullet_system;

  int score = START_SCORE;
  int lives = MAX_LIVES;
  bool game_over = false;
  float spawn_timer = 0;

  sf::Clock game_clock;

  void handleActions(const InputState& input, float delta_time);
  void update(float delta_time);
  void draw();
  void resetGame();

  void checkCollisions();
  void spawnEnemy();
  void handleShoot();

 public:
  Game();
  void run();
};