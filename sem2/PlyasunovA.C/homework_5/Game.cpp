#include "Game.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

Game::Game()
    : window(sf::VideoMode(kWindowWidth, kWindowHeight), "Cosmic Shooter",
             sf::Style::Close),
      score(0),
      lives(3),
      reload_cooldown(kInitReload),
      asteroid_base_speed(100.f),
      asteroid_spawn_timer(0.f),
      asteroid_spawn_delay(1.f),
      is_game_over(false),
      invincibility_timer(0.f) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  if (!font.loadFromFile("arial.ttf") && !font.loadFromFile("OpenSans.ttf")) {
    // Ўрифт не загружен Ч текст будет пустым, но игра работает
  }

  score_text.setFont(font);
  score_text.setCharacterSize(24);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(10.f, 10.f);

  lives_text.setFont(font);
  lives_text.setCharacterSize(24);
  lives_text.setFillColor(sf::Color::White);
  lives_text.setPosition(10.f, 40.f);

  game_over_text.setFont(font);
  game_over_text.setCharacterSize(48);
  game_over_text.setFillColor(sf::Color::Red);
  game_over_text.setString("GAME OVER");
  game_over_text.setPosition(kWindowWidth / 2 - 120.f,
                             kWindowHeight / 2 - 80.f);

  final_score_text.setFont(font);
  final_score_text.setCharacterSize(30);
  final_score_text.setFillColor(sf::Color::Yellow);
  final_score_text.setPosition(kWindowWidth / 2 - 100.f,
                               kWindowHeight / 2 + 10.f);
}

void Game::run() {
  sf::Clock delta_clock;
  while (window.isOpen()) {
    sf::Time dt = delta_clock.restart();
    processEvents();
    if (!is_game_over) update(dt);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();
  }

  if (!is_game_over) {
    ship.handleInput();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      if (last_shot_clock.getElapsedTime().asSeconds() >= reload_cooldown) {
        sf::Vector2f bullet_pos = ship.getBounds().getPosition();
        bullet_pos.x += ship.getBounds().width / 2.f - 2.f;
        bullet_pos.y -= 10.f;
        bullets.emplace_back(bullet_pos);
        last_shot_clock.restart();
      }
    }
  }
}

void Game::update(sf::Time delta_time) {
  float dt = delta_time.asSeconds();

  ship.update(delta_time);

  if (invincibility_timer > 0.f) invincibility_timer -= dt;

  for (auto it = bullets.begin(); it != bullets.end();) {
    it->update(delta_time);
    if (!it->isActive() || it->getBounds().top + it->getBounds().height < 0) {
      it = bullets.erase(it);
    } else {
      ++it;
    }
  }

  for (auto it = asteroids.begin(); it != asteroids.end();) {
    it->update(delta_time);
    if (it->isOutOfBounds(kWindowHeight)) {
      it = asteroids.erase(it);
    } else {
      ++it;
    }
  }

  asteroid_spawn_timer += dt;
  if (asteroid_spawn_timer >= asteroid_spawn_delay) {
    asteroid_spawn_timer = 0.f;
    spawnAsteroid();
  }

  static float speed_timer = 0.f;
  speed_timer += dt;
  if (speed_timer >= 5.f) {
    speed_timer = 0.f;
    asteroid_base_speed += 20.f;
    if (asteroid_base_speed > 500.f) asteroid_base_speed = 500.f;
  }

  handleCollisions();

  score_text.setString("Score: " + std::to_string(score));
  lives_text.setString("Lives: " + std::to_string(lives));

  if (lives <= 0) {
    is_game_over = true;
    final_score_text.setString("Final score: " + std::to_string(score));
  }
}

void Game::render() {
  window.clear(sf::Color::Black);

  ship.draw(window);
  for (auto& bullet : bullets) bullet.draw(window);
  for (auto& asteroid : asteroids) asteroid.draw(window);
  window.draw(score_text);
  window.draw(lives_text);

  if (is_game_over) {
    window.draw(game_over_text);
    window.draw(final_score_text);
  }

  window.display();
}

void Game::spawnAsteroid() {
  float radius = 15.f + std::rand() % 20;
  float x = std::rand() % static_cast<int>(kWindowWidth - radius * 2) + radius;
  sf::Vector2f pos(x, -radius);
  Asteroid asteroid(pos, asteroid_base_speed);
  asteroid.setSize(radius);
  asteroids.push_back(asteroid);
}

void Game::handleCollisions() {
  // ѕули против астероидов
  for (auto b_it = bullets.begin(); b_it != bullets.end();) {
    bool hit = false;
    for (auto a_it = asteroids.begin(); a_it != asteroids.end();) {
      if (b_it->getBounds().intersects(a_it->getBounds())) {
        hit = true;
        a_it = asteroids.erase(a_it);
        ++score;
        updateReloadCooldown();
        break;
      } else {
        ++a_it;
      }
    }
    if (hit) {
      b_it = bullets.erase(b_it);
    } else {
      ++b_it;
    }
  }

  //  орабль против астероидов
  if (invincibility_timer <= 0.f) {
    for (auto a_it = asteroids.begin(); a_it != asteroids.end();) {
      if (ship.getBounds().intersects(a_it->getBounds())) {
        --lives;
        invincibility_timer = kInvincibleDuration;
        a_it = asteroids.erase(a_it);
        if (lives <= 0) break;
      } else {
        ++a_it;
      }
    }
  }
}

void Game::updateReloadCooldown() {
  int reduction_steps = score / 5;
  float new_cooldown = kInitReload - reduction_steps * 0.05f;
  if (new_cooldown < kMinReload) new_cooldown = kMinReload;
  reload_cooldown = new_cooldown;
}
