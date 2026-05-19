#include "game.h"

#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <ctime>
#include <string>

#include "constants.h"

namespace {

bool areCirclesIntersecting(sf::Vector2f first_position, float first_radius,
                            sf::Vector2f second_position, float second_radius) {
  const float delta_x = first_position.x - second_position.x;
  const float delta_y = first_position.y - second_position.y;
  const float distance_squared = delta_x * delta_x + delta_y * delta_y;
  const float radius_sum = first_radius + second_radius;
  return distance_squared <= radius_sum * radius_sum;
}

}  // namespace

Game::Game()
    : window(sf::VideoMode(constants::kWindowWidth, constants::kWindowHeight),
             "Space Shooter"),
      random_engine(static_cast<unsigned int>(std::time(nullptr))),
      score(0),
      lives(constants::kStartLives),
      elapsed_time(0.0F),
      asteroid_spawn_timer(0.0F),
      is_game_over(false),
      is_font_loaded(false) {
  window.setFramerateLimit(60);
  is_font_loaded = font.loadFromFile("arial.ttf") ||
                   font.loadFromFile("C:/Windows/Fonts/arial.ttf");
}

void Game::run() {
  while (window.isOpen()) {
    processEvents();
    const float delta_time = clock.restart().asSeconds();
    update(delta_time);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) {
        window.close();
      }

      if (event.key.code == sf::Keyboard::Space) {
        shoot();
      }

      if (event.key.code == sf::Keyboard::Enter && is_game_over) {
        restart();
      }
    }
  }
}

void Game::update(float delta_time) {
  if (is_game_over) {
    return;
  }

  elapsed_time += delta_time;
  player.update(delta_time);
  spawnAsteroid(delta_time);
  updateObjects(delta_time);
  handleCollisions();
  removeInactiveObjects();
}

void Game::render() {
  window.clear(sf::Color(10, 12, 25));

  player.draw(window);

  for (const Bullet& bullet : bullets) {
    bullet.draw(window);
  }

  for (const Asteroid& asteroid : asteroids) {
    asteroid.draw(window);
  }

  drawHud();

  if (is_game_over) {
    drawGameOver();
  }

  window.display();
}

void Game::shoot() {
  if (is_game_over ||
      shoot_clock.getElapsedTime().asSeconds() < getReloadDelay()) {
    return;
  }

  bullets.emplace_back(player.getGunPosition());
  shoot_clock.restart();
}

void Game::spawnAsteroid(float delta_time) {
  asteroid_spawn_timer += delta_time;

  const float spawn_delay = std::max(0.35F, 1.05F - elapsed_time * 0.01F);
  if (asteroid_spawn_timer < spawn_delay) {
    return;
  }

  const float radius = getRandomFloat(constants::kAsteroidMinRadius,
                                      constants::kAsteroidMaxRadius);
  const float x_position =
      getRandomFloat(radius, constants::kWindowWidth - radius);
  const float speed = getAsteroidSpeed() + getRandomFloat(0.0F, 70.0F);

  asteroids.emplace_back(sf::Vector2f{x_position, -radius}, radius, speed);
  asteroid_spawn_timer = 0.0F;
}

void Game::updateObjects(float delta_time) {
  for (Bullet& bullet : bullets) {
    bullet.update(delta_time);
  }

  for (Asteroid& asteroid : asteroids) {
    asteroid.update(delta_time);
  }
}

void Game::handleCollisions() {
  for (std::size_t bullet_index = 0; bullet_index < bullets.size();
       ++bullet_index) {
    for (std::size_t asteroid_index = 0; asteroid_index < asteroids.size();
         ++asteroid_index) {
      if (!bullets[bullet_index].getBounds().intersects(
              asteroids[asteroid_index].getBounds())) {
        continue;
      }

      bullets.erase(bullets.begin() +
                    static_cast<std::ptrdiff_t>(bullet_index));
      asteroids.erase(asteroids.begin() +
                      static_cast<std::ptrdiff_t>(asteroid_index));
      ++score;
      return;
    }
  }

  for (std::size_t asteroid_index = 0; asteroid_index < asteroids.size();
       ++asteroid_index) {
    if (areCirclesIntersecting(player.getPosition(), constants::kPlayerRadius,
                               asteroids[asteroid_index].getPosition(),
                               asteroids[asteroid_index].getRadius())) {
      handlePlayerHit(asteroid_index);
      return;
    }
  }
}

void Game::handlePlayerHit(std::size_t asteroid_index) {
  asteroids.erase(asteroids.begin() +
                  static_cast<std::ptrdiff_t>(asteroid_index));
  --lives;
  player.resetPosition();

  if (lives <= 0) {
    is_game_over = true;
  }
}

void Game::removeInactiveObjects() {
  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](const Bullet& bullet) {
                                 return bullet.isOutOfWindow();
                               }),
                bullets.end());

  asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                 [](const Asteroid& asteroid) {
                                   return asteroid.isOutOfWindow();
                                 }),
                  asteroids.end());
}

void Game::drawHud() {
  if (!is_font_loaded) {
    return;
  }

  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setPosition({20.0F, 16.0F});
  text.setString("Score: " + std::to_string(score) +
                 "   Lives: " + std::to_string(lives));
  window.draw(text);
}

void Game::drawGameOver() {
  if (!is_font_loaded) {
    return;
  }

  sf::RectangleShape overlay({static_cast<float>(constants::kWindowWidth),
                              static_cast<float>(constants::kWindowHeight)});
  overlay.setFillColor(sf::Color(0, 0, 0, 150));
  window.draw(overlay);

  sf::Text title;
  title.setFont(font);
  title.setCharacterSize(48);
  title.setFillColor(sf::Color::White);
  title.setString("Game over");
  title.setPosition({310.0F, 280.0F});
  window.draw(title);

  sf::Text score_text;
  score_text.setFont(font);
  score_text.setCharacterSize(28);
  score_text.setFillColor(sf::Color(255, 230, 120));
  score_text.setString("Final score: " + std::to_string(score) +
                       "\nPress Enter to restart");
  score_text.setPosition({305.0F, 350.0F});
  window.draw(score_text);
}

void Game::restart() {
  bullets.clear();
  asteroids.clear();
  score = 0;
  lives = constants::kStartLives;
  elapsed_time = 0.0F;
  asteroid_spawn_timer = 0.0F;
  is_game_over = false;
  player.resetPosition();
  clock.restart();
  shoot_clock.restart();
}

float Game::getReloadDelay() const {
  return std::max(0.12F, 0.45F - static_cast<float>(score) * 0.015F);
}

float Game::getAsteroidSpeed() const {
  return constants::kAsteroidBaseSpeed +
         elapsed_time * constants::kAsteroidSpeedGrowth;
}

float Game::getRandomFloat(float min_value, float max_value) {
  std::uniform_real_distribution<float> distribution(min_value, max_value);
  return distribution(random_engine);
}
