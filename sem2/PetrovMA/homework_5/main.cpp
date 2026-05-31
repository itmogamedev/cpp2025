#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"

#include "asteroid.h"
#include "laser.h"
#include "player.h"

enum class GameState { kPlaying, kGameOver };

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode({900, 600}), "SHOOTER");
  window->setFramerateLimit(60);

  Player player;
  std::vector<Asteroid> asteroids;
  std::vector<Laser> lasers;

  GameState state = GameState::kPlaying;

  float spawner = 0.f;
  float smooth_cd = 0.f;
  float game_time = 0.f;

  sf::Font font;
  bool has_font = font.openFromFile("C:/Windows/Fonts/arial.ttf");
  if (!has_font) {
    return 0;
  }

  sf::Text hud_text(font, "", 20);
  hud_text.setFillColor(sf::Color::White);
  hud_text.setPosition({15.f, 15.f});

  sf::Text game_over_txt(font, "GAME OVER", 50);
  game_over_txt.setFillColor(sf::Color(255, 0, 0));

  auto bounds = game_over_txt.getLocalBounds();
  game_over_txt.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
  game_over_txt.setPosition({900.f / 2.f, 220.f});

  sf::Text restart_txt(font, "", 20);
  restart_txt.setFillColor(sf::Color(200, 200, 200));

  sf::Clock clock;

  while (window->isOpen()) {
    while (const std::optional event = window->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window->close();
      }

      if (const auto *kp = event->getIf<sf::Event::KeyPressed>()) {
        if (kp->code == sf::Keyboard::Key::Escape) {
          window->close();
        }
        if (state == GameState::kGameOver && kp->code == sf::Keyboard::Key::R) {
          player.reset({900.f, 600.f});
          asteroids.clear();
          lasers.clear();
          state = GameState::kPlaying;
          spawner = 0.f;
          smooth_cd = 0.f;
          game_time = 0.f;
          clock.restart();
        }
      }
    }

    if (!window->isOpen()) {
      break;
    }

    float dt = clock.restart().asSeconds();

    window->clear();

    if (state == GameState::kPlaying) {
      game_time += dt;
      float current_asteroid_speed = 150.f + game_time * 4.f;

      if (smooth_cd > 0.f) {
        smooth_cd -= dt;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && smooth_cd <= 0.f) {
        auto player_pos = player.stats.render.getPosition();
        auto playerSize = player.stats.render.getSize();
        float laserX = player_pos.x + playerSize.x / 2.f;
        float laserY = player_pos.y;
        lasers.emplace_back(laserX, laserY, 600.f);

        float base_cd = 0.6f;
        float speedup = 0.015f;
        float min_cd = 0.08f;
        float activeCooldown = base_cd - player.stats.score * speedup;
        if (activeCooldown < min_cd) {
          activeCooldown = min_cd;
        }
        smooth_cd = activeCooldown;
      }

      spawner -= dt;
      if (spawner <= 0.f) {
        float size = 25.f + static_cast<float>(std::rand() % 26);
        float x = static_cast<float>(std::rand() % static_cast<int>(900.f - size));
        asteroids.emplace_back(x, current_asteroid_speed, size);

        spawner = 0.5f + static_cast<float>(std::rand() % 100) / 100.f * 0.7f;
      }

      player.tick(window, dt);

      for (auto it = lasers.begin(); it != lasers.end();) {
        it->tick(window, dt);
        if (it->isOutOfBounds()) {
          it = lasers.erase(it);
        } else {
          ++it;
        }
      }

      for (auto it = asteroids.begin(); it != asteroids.end();) {
        it->speed = current_asteroid_speed;
        it->tick(window, dt);
        if (it->isOutOfBounds(600.f)) {
          it = asteroids.erase(it);
        } else {
          ++it;
        }
      }

      for (auto las = lasers.begin(); las != lasers.end();) {
        bool las_dest = false;
        for (auto ast = asteroids.begin(); ast != asteroids.end();) {
          if (las->shape.getGlobalBounds().findIntersection(ast->shape.getGlobalBounds())) {
            ast = asteroids.erase(ast);
            player.stats.score += 1;
            las_dest = true;
            break;
          } else {
            ++ast;
          }
        }
        if (las_dest) {
          las = lasers.erase(las);
        } else {
          ++las;
        }
      }

      for (auto ast = asteroids.begin(); ast != asteroids.end();) {
        if (player.stats.render.getGlobalBounds().findIntersection(ast->shape.getGlobalBounds())) {
          ast = asteroids.erase(ast);
          player.stats.health -= 1;
          if (player.stats.health <= 0) {
            state = GameState::kGameOver;
            break;
          }
        } else {
          ++ast;
        }
      }

      hud_text.setString("Score: " + std::to_string(player.stats.score) +
                         "   HP: " + std::to_string(player.stats.health));
      window->draw(hud_text);
    } else {
      window->draw(game_over_txt);

      restart_txt.setString("Score: " + std::to_string(player.stats.score) + "\n\nR to restart");
      auto restart_rect = restart_txt.getLocalBounds();
      restart_txt.setOrigin({restart_rect.size.x / 2.f, restart_rect.size.y / 2.f});
      restart_txt.setPosition({900.f / 2.f, 320.f});

      window->draw(restart_txt);
    }

    window->display();
  }

  return 0;
}
