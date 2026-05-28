#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "meteor.h"

constexpr unsigned int k_window_width = 1280;
constexpr unsigned int k_window_height = 920;
constexpr float k_player_speed = 550.f;
constexpr float k_bullet_speed = 900.f;
constexpr float k_min_shoot_cooldown = 0.12f;
constexpr float k_base_shoot_cooldown = 0.45f;
constexpr float k_shoot_cooldown_reduction = 0.015f;
constexpr int k_meteor_count = 7;
constexpr int k_start_lives = 3;
constexpr float k_damage_cooldown = 1.0f;
constexpr float k_background_scroll_speed = 120.f;

struct Bullet {
  sf::RectangleShape shape;
};

static bool LoadFont(sf::Font& font) {
  return font.loadFromFile("C:/Users/Admin/Desktop/meow/cpp2sem/miniHw5/Fonts/tuffy.ttf");
}

static float CalculateShootCooldown(int score) {
  return std::max(k_min_shoot_cooldown,
                  k_base_shoot_cooldown - static_cast<float>(score) * k_shoot_cooldown_reduction);
}

static void CenterText(sf::Text& text, float x, float y) {
  const auto bounds = text.getLocalBounds();
  text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
  text.setPosition(x, y);
}

int main() {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  sf::RenderWindow window(sf::VideoMode(k_window_width, k_window_height), "Space Shooter");
  window.setFramerateLimit(60);

  sf::Texture space_texture;
  sf::Texture player_texture;
  sf::Font font;

  if (!space_texture.loadFromFile("C:/Users/Admin/Desktop/meow/cpp2sem/miniHw5/Images/newkos1.jpg") ||
      !player_texture.loadFromFile("C:/Users/Admin/Desktop/meow/cpp2sem/miniHw5/Images/player.png") ||
      !LoadFont(font)) {
    std::cerr << "Failed to load game resources." << std::endl;
    return 1;
  }

  sf::RectangleShape background(
      sf::Vector2f(static_cast<float>(k_window_width), static_cast<float>(k_window_height)));
  background.setTexture(&space_texture);

  sf::RectangleShape background_top = background;
  background_top.setPosition(0.f, -static_cast<float>(k_window_height));

  sf::RectangleShape player(sf::Vector2f(80.f, 70.f));
  player.setTexture(&player_texture);
  player.setPosition(k_window_width / 2.f - player.getSize().x / 2.f,
                     k_window_height - 140.f);

  std::vector<Meteor> meteors;
  meteors.reserve(k_meteor_count);
  for (int meteor_index = 0; meteor_index < k_meteor_count; ++meteor_index) {
    meteors.emplace_back(static_cast<float>(k_window_width), static_cast<float>(k_window_height));
  }

  std::vector<Bullet> bullets;
  int score = 0;
  int lives = k_start_lives;
  bool game_over = false;
  float shoot_timer = CalculateShootCooldown(score);
  float damage_cooldown_timer = 0.f;
  float elapsed_game_time = 0.f;

  sf::Text hud_text("", font, 32);
  hud_text.setFillColor(sf::Color::White);
  hud_text.setPosition(20.f, 16.f);

  sf::Text game_over_text("Game Over", font, 74);
  game_over_text.setFillColor(sf::Color(255, 120, 120));
  CenterText(game_over_text, k_window_width / 2.f, k_window_height / 2.f - 90.f);

  sf::Text final_score_text("", font, 38);
  final_score_text.setFillColor(sf::Color::White);

  sf::Text exit_hint_text("Close the window to exit", font, 28);
  exit_hint_text.setFillColor(sf::Color(220, 220, 220));
  CenterText(exit_hint_text, k_window_width / 2.f, k_window_height / 2.f + 80.f);

  sf::Clock delta_clock;
  while (window.isOpen()) {
    const float delta_time = delta_clock.restart().asSeconds();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        window.close();
      }
    }

    if (!game_over) {
      elapsed_game_time += delta_time;
      shoot_timer += delta_time;
      damage_cooldown_timer = std::max(0.f, damage_cooldown_timer - delta_time);

      float horizontal_input = 0.f;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        horizontal_input -= 1.f;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        horizontal_input += 1.f;
      }

      player.move(horizontal_input * k_player_speed * delta_time, 0.f);
      const float max_player_x = k_window_width - player.getSize().x;
      const float clamped_player_x = std::clamp(player.getPosition().x, 0.f, max_player_x);
      player.setPosition(clamped_player_x, player.getPosition().y);

      const float current_shoot_cooldown = CalculateShootCooldown(score);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
          shoot_timer >= current_shoot_cooldown) {
        Bullet bullet;
        bullet.shape.setSize(sf::Vector2f(8.f, 24.f));
        bullet.shape.setFillColor(sf::Color(255, 230, 120));
        bullet.shape.setPosition(player.getPosition().x + player.getSize().x / 2.f -
                                     bullet.shape.getSize().x / 2.f,
                                 player.getPosition().y - bullet.shape.getSize().y);
        bullets.push_back(bullet);
        shoot_timer = 0.f;
      }

      for (auto& bullet : bullets) {
        bullet.shape.move(0.f, -k_bullet_speed * delta_time);
      }
      bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                   [](const Bullet& bullet) {
                                     return bullet.shape.getPosition().y +
                                                bullet.shape.getSize().y < 0.f;
                                   }),
                    bullets.end());

      background.move(0.f, k_background_scroll_speed * delta_time);
      background_top.move(0.f, k_background_scroll_speed * delta_time);
      if (background.getPosition().y >= static_cast<float>(k_window_height)) {
        background.setPosition(0.f, background_top.getPosition().y - k_window_height);
      }
      if (background_top.getPosition().y >= static_cast<float>(k_window_height)) {
        background_top.setPosition(0.f, background.getPosition().y - k_window_height);
      }

      const float meteor_speed_boost = elapsed_game_time * 6.f;
      for (auto& meteor : meteors) {
        meteor.Move(delta_time, meteor_speed_boost);
      }

      for (auto bullet_it = bullets.begin(); bullet_it != bullets.end();) {
        bool bullet_destroyed = false;

        for (auto& meteor : meteors) {
          if (meteor.Collision(bullet_it->shape.getGlobalBounds())) {
            meteor.Restart();
            ++score;
            bullet_it = bullets.erase(bullet_it);
            bullet_destroyed = true;
            break;
          }
        }

        if (!bullet_destroyed) {
          ++bullet_it;
        }
      }

      if (damage_cooldown_timer <= 0.f) {
        for (auto& meteor : meteors) {
          if (meteor.Collision(player.getGlobalBounds())) {
            --lives;
            meteor.Restart();
            damage_cooldown_timer = k_damage_cooldown;

            if (lives <= 0) {
              lives = 0;
              game_over = true;
            }
            break;
          }
        }
      }
    }

    player.setFillColor(damage_cooldown_timer > 0.f ? sf::Color(255, 255, 255, 180)
                                                    : sf::Color::White);

    std::ostringstream hud_stream;
    hud_stream << "Score: " << score << "    Lives: " << lives;
    hud_text.setString(hud_stream.str());

    std::ostringstream final_score_stream;
    final_score_stream << "Final score: " << score;
    final_score_text.setString(final_score_stream.str());
    CenterText(final_score_text, k_window_width / 2.f, k_window_height / 2.f + 5.f);

    window.clear();
    window.draw(background);
    window.draw(background_top);

    for (const auto& bullet : bullets) {
      window.draw(bullet.shape);
    }

    for (auto& meteor : meteors) {
      meteor.Draw(window);
    }

    window.draw(player);
    window.draw(hud_text);

    if (game_over) {
      sf::RectangleShape overlay(
          sf::Vector2f(static_cast<float>(k_window_width), static_cast<float>(k_window_height)));
      overlay.setFillColor(sf::Color(0, 0, 0, 170));
      window.draw(overlay);
      window.draw(game_over_text);
      window.draw(final_score_text);
      window.draw(exit_hint_text);
    }

    window.display();
  }

  return 0;
}
