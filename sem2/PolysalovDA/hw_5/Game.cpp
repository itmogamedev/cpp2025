#include "Game.h"

#include <iostream>

sf::Texture loadTexture(const std::string& path) {
  sf::Texture texture;
  if (!texture.loadFromFile(path)) {
    std::cerr << "Failed to load texture: " << path << std::endl;
  }
  return texture;
}

Game::Game()
    : spaceship_texture(loadTexture(SPACESHIP_TEXTURE)),
      bullet_texture(loadTexture(BULLET_TEXTURE)),
      window(sf::VideoMode(WINDOW_SIZE), WINDOW_TITLE,
             sf::Style::Titlebar | sf::Style::Close),
      handler(window),
      renderer(window),
      ui(),
      spaceship(spaceship_texture, bullet_texture),
      enemy_system(),
      bullet_system() {
  window.setFramerateLimit(FRAMERATE_LIMIT);
  window.requestFocus();
  auto ship_size = spaceship.getSize();
  spaceship.setScale(SPACESHIP_WIDTH / ship_size.x,
                     SPACESHIP_HEIGHT / ship_size.y);
  spaceship.setPosition(SPACESHIP_START_POS_X, SPACESHIP_START_POS_Y);

  game_clock.restart();
}

void Game::run() {
  while (window.isOpen()) {
    InputState input = handler.pollActions();
    float delta_time = game_clock.restart().asSeconds();

    if (!game_over) {
      handleActions(input, delta_time);
      update(delta_time);
    }
    draw();
  }
}

void Game::handleActions(const InputState& input, float delta_time) {
  for (const auto& action : input.actions) {
    if (action == Actions::MoveLeft) {
      spaceship.moveLeft(delta_time);
    } else if (action == Actions::MoveRight) {
      spaceship.moveRight(delta_time);
    }
  }
  if (input.shooting) {
    handleShoot();
  }
}

void Game::handleShoot() {
  if (!game_over) {
    auto bullet = spaceship.tryShoot();
    if (bullet.has_value()) {
      bullet_system.addBullet(bullet.value());
    }
  }
}

void Game::update(float delta_time) {
  spaceship.update(delta_time);
  bullet_system.update(delta_time);

  spawn_timer += delta_time;

  float current_spawn_interval =
      std::max(ASTEROID_SPAWN_INTERVAL - ASTEROID_SPAWN_DECREASE * score,
               MIN_SPAWN_INTERVAL);

  if (spawn_timer >= current_spawn_interval) {
    spawnEnemy();
    spawn_timer = 0;
  }

  enemy_system.update(
      delta_time,
      ASTEROID_BASE_SPEED + ASTEROID_SPEED_INCREASE * score * SPEED_MULTIPLER);
  checkCollisions();

  spaceship.reduceCooldown(COOLDOWN_REDUCTION_PER_SCORE * score);

  ui.updateScore(score);
  ui.updateLives(lives);

  if (lives <= 0) {
    game_over = true;
    ui.setGameOver(true, score);
  }
}

void Game::spawnEnemy() {
  float x = rand() % (WINDOW_SIZE.x - ASTEROID_WIDTH) + ASTEROID_SPAWN_MARGIN;
  enemy_system.spawnEnemy({x, ASTEROID_SPAWN_Y});
}

void Game::checkCollisions() {
  auto& enemies = enemy_system.getEnemies();
  auto& bullets = bullet_system.getBullets();

  for (auto bullet_it = bullets.begin(); bullet_it != bullets.end();) {
    bool bullet_hit = false;

    for (auto enemy_it = enemies.begin(); enemy_it != enemies.end();) {
      if (bullet_it->getGlobalBounds()
              .findIntersection(enemy_it->getGlobalBounds())
              .has_value()) {
        enemy_it = enemies.erase(enemy_it);
        score++;
        bullet_hit = true;
        break;
      } else {
        ++enemy_it;
      }
    }

    if (bullet_hit) {
      bullet_it = bullets.erase(bullet_it);
    } else {
      ++bullet_it;
    }
  }

  sf::FloatRect ship_bounds = spaceship.getGlobalBounds();
  for (auto it = enemies.begin(); it != enemies.end();) {
    if (ship_bounds.findIntersection(it->getGlobalBounds()).has_value()) {
      it = enemies.erase(it);
      lives--;
    } else {
      ++it;
    }
  }
}

void Game::resetGame() {
  score = START_SCORE;
  lives = MAX_LIVES;
  game_over = false;
  bullet_system.clear();
  enemy_system.clear();
  spaceship.setPosition(SPACESHIP_START_POS_X, SPACESHIP_START_POS_Y);
  ui.setGameOver(false, START_SCORE);
  game_clock.restart();
}

void Game::draw() {
  renderer.clear();
  renderer.draw(spaceship);

  for (const auto& bullet : bullet_system.getBullets()) {
    renderer.draw(bullet);
  }

  enemy_system.draw(renderer);
  renderer.draw(ui);
  renderer.display();
}