#include "game.h"

#include <algorithm>
#include <random>
#include <sstream>

#include "resource_manager.h"

namespace {

std::mt19937& randomEngine() {
  static std::random_device rd;
  static std::mt19937 engine(rd());
  return engine;
}

}  // namespace

Game::Game()
    : window(sf::VideoMode(kWindowWidth, kWindowHeight), "Space Shooter",
             sf::Style::Titlebar | sf::Style::Close),
      score(0),
      asteroid_spawn_timer(0.f),
      asteroid_spawn_interval(1.4f),
      asteroid_base_speed(140.f),
      game_time(0.f),
      game_over(false) {
  window.setFramerateLimit(60);

  asteroid_textures = {
      "assets/asteroid1.png", "assets/asteroid2.png", "assets/asteroid3.png",
      "assets/asteroid4.png", "assets/asteroid5.png",
  };

  setupBackground();
  setupHudTexts();

  player = std::make_unique<Player>(static_cast<float>(kWindowWidth),
                                    static_cast<float>(kWindowHeight));
}

void Game::setupBackground() {
  sf::Texture& bg_texture =
      ResourceManager::getInstance().getTexture("assets/background.png");
  sf::Vector2u tex_size = bg_texture.getSize();
  if (tex_size.x > 0 && tex_size.y > 0) {
    background_sprite.setTexture(bg_texture, true);
    background_sprite.setScale(
        static_cast<float>(kWindowWidth) / static_cast<float>(tex_size.x),
        static_cast<float>(kWindowHeight) / static_cast<float>(tex_size.y));
    // Чуть притемним фон, чтобы спрайты и HUD читались лучше.
    background_sprite.setColor(sf::Color(170, 170, 200));
  }
}

void Game::setupHudTexts() {
  sf::Font& font = ResourceManager::getInstance().getFont();

  score_text.setFont(font);
  score_text.setCharacterSize(22);
  score_text.setFillColor(sf::Color::White);
  score_text.setOutlineColor(sf::Color::Black);
  score_text.setOutlineThickness(2.f);
  score_text.setPosition(12.f, 8.f);

  lives_text.setFont(font);
  lives_text.setCharacterSize(22);
  lives_text.setFillColor(sf::Color::White);
  lives_text.setOutlineColor(sf::Color::Black);
  lives_text.setOutlineThickness(2.f);
  lives_text.setPosition(static_cast<float>(kWindowWidth) - 170.f, 8.f);

  game_over_text.setFont(font);
  game_over_text.setCharacterSize(64);
  game_over_text.setFillColor(sf::Color(255, 60, 60));
  game_over_text.setOutlineColor(sf::Color::Black);
  game_over_text.setOutlineThickness(3.f);
  game_over_text.setString("GAME OVER");

  final_score_text.setFont(font);
  final_score_text.setCharacterSize(28);
  final_score_text.setFillColor(sf::Color::White);
  final_score_text.setOutlineColor(sf::Color::Black);
  final_score_text.setOutlineThickness(2.f);

  restart_text.setFont(font);
  restart_text.setCharacterSize(20);
  restart_text.setFillColor(sf::Color(220, 220, 220));
  restart_text.setOutlineColor(sf::Color::Black);
  restart_text.setOutlineThickness(2.f);
  restart_text.setString("Press R to restart   |   Esc to quit");

  hud_overlay.setSize(sf::Vector2f(static_cast<float>(kWindowWidth), 40.f));
  hud_overlay.setFillColor(sf::Color(0, 0, 0, 120));
  hud_overlay.setPosition(0.f, 0.f);

  game_over_overlay.setSize(sf::Vector2f(static_cast<float>(kWindowWidth),
                                         static_cast<float>(kWindowHeight)));
  game_over_overlay.setFillColor(sf::Color(0, 0, 0, 160));
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    float delta_time = clock.restart().asSeconds();
    // Защита от больших скачков (например, окно тащили):
    // ограничиваем dt сверху, чтобы коллизии не «перепрыгивали».
    if (delta_time > 0.05f) {
      delta_time = 0.05f;
    }
    processEvents();
    if (!game_over) {
      update(delta_time);
    }
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
      if (game_over && event.key.code == sf::Keyboard::R) {
        resetGame();
      }
      if (!game_over && event.key.code == sf::Keyboard::Space) {
        if (player->canShoot()) {
          sf::Vector2f pos = player->getPosition();
          bullets.emplace_back(pos.x, pos.y);
          player->shoot();
        }
      }
    }
  }
}

void Game::update(float delta_time) {
  game_time += delta_time;

  // Непрерывный ввод движения — лучше пуллингом, чем по событиям.
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player->moveLeft(delta_time);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player->moveRight(delta_time);
  }

  player->update(delta_time);
  player->updateReloadTime(score);

  for (auto& bullet : bullets) {
    bullet.update(delta_time);
  }
  bullets.erase(
      std::remove_if(bullets.begin(), bullets.end(),
                     [](const Bullet& b) { return b.isOffScreen(); }),
      bullets.end());

  // Спавн астероидов: интервал постепенно уменьшается со временем.
  asteroid_spawn_timer += delta_time;
  asteroid_spawn_interval = std::max(0.35f, 1.4f - game_time * 0.012f);
  if (asteroid_spawn_timer >= asteroid_spawn_interval) {
    asteroid_spawn_timer = 0.f;
    spawnAsteroid();
  }

  for (auto& asteroid : asteroids) {
    asteroid.update(delta_time);
  }
  asteroids.erase(
      std::remove_if(asteroids.begin(), asteroids.end(),
                     [this](const Asteroid& a) {
                       return a.isOffScreen(static_cast<float>(kWindowHeight));
                     }),
      asteroids.end());

  checkCollisions();

  if (!player->isAlive()) {
    game_over = true;
  }
}

void Game::spawnAsteroid() {
  std::uniform_int_distribution<std::size_t> tex_dist(
      0, asteroid_textures.size() - 1);
  std::uniform_real_distribution<float> x_dist(60.f, kWindowWidth - 60.f);
  std::uniform_real_distribution<float> speed_jitter(0.85f, 1.25f);

  // Базовая скорость растёт со временем, плюс случайный множитель.
  float current_base = asteroid_base_speed + game_time * 6.f;
  float speed = current_base * speed_jitter(randomEngine());

  asteroids.emplace_back(x_dist(randomEngine()), speed,
                         asteroid_textures[tex_dist(randomEngine())]);
}

void Game::checkCollisions() {
  // Снаряды против астероидов.
  for (auto bullet_it = bullets.begin(); bullet_it != bullets.end();) {
    bool hit = false;
    for (auto asteroid_it = asteroids.begin();
         asteroid_it != asteroids.end();) {
      if (bullet_it->getBounds().intersects(asteroid_it->getBounds())) {
        asteroid_it = asteroids.erase(asteroid_it);
        hit = true;
        ++score;
        break;
      }
      ++asteroid_it;
    }
    if (hit) {
      bullet_it = bullets.erase(bullet_it);
    } else {
      ++bullet_it;
    }
  }

  // Игрок против астероидов.
  for (auto it = asteroids.begin(); it != asteroids.end();) {
    if (it->getBounds().intersects(player->getBounds())) {
      it = asteroids.erase(it);
      player->loseLife();
    } else {
      ++it;
    }
  }
}

void Game::resetGame() {
  score = 0;
  game_time = 0.f;
  asteroid_spawn_timer = 0.f;
  asteroid_spawn_interval = 1.4f;
  asteroids.clear();
  bullets.clear();
  player = std::make_unique<Player>(static_cast<float>(kWindowWidth),
                                    static_cast<float>(kWindowHeight));
  game_over = false;
}

void Game::drawHud() {
  window.draw(hud_overlay);

  std::stringstream score_stream;
  score_stream << "Score: " << score;
  score_text.setString(score_stream.str());

  std::stringstream lives_stream;
  lives_stream << "Lives: " << player->getLives();
  lives_text.setString(lives_stream.str());

  window.draw(score_text);
  window.draw(lives_text);
}

void Game::drawGameOver() {
  window.draw(game_over_overlay);

  sf::FloatRect go_bounds = game_over_text.getLocalBounds();
  game_over_text.setOrigin(go_bounds.left + go_bounds.width / 2.f,
                           go_bounds.top + go_bounds.height / 2.f);
  game_over_text.setPosition(static_cast<float>(kWindowWidth) / 2.f,
                             static_cast<float>(kWindowHeight) / 2.f - 70.f);

  std::stringstream fs;
  fs << "Final Score: " << score;
  final_score_text.setString(fs.str());
  sf::FloatRect fs_bounds = final_score_text.getLocalBounds();
  final_score_text.setOrigin(fs_bounds.left + fs_bounds.width / 2.f,
                             fs_bounds.top + fs_bounds.height / 2.f);
  final_score_text.setPosition(static_cast<float>(kWindowWidth) / 2.f,
                               static_cast<float>(kWindowHeight) / 2.f + 10.f);

  sf::FloatRect r_bounds = restart_text.getLocalBounds();
  restart_text.setOrigin(r_bounds.left + r_bounds.width / 2.f,
                         r_bounds.top + r_bounds.height / 2.f);
  restart_text.setPosition(static_cast<float>(kWindowWidth) / 2.f,
                           static_cast<float>(kWindowHeight) / 2.f + 60.f);

  window.draw(game_over_text);
  window.draw(final_score_text);
  window.draw(restart_text);
}

void Game::render() {
  window.clear(sf::Color(15, 15, 30));
  window.draw(background_sprite);

  for (const auto& asteroid : asteroids) {
    asteroid.draw(window);
  }
  for (const auto& bullet : bullets) {
    bullet.draw(window);
  }
  player->draw(window);

  drawHud();

  if (game_over) {
    drawGameOver();
  }

  window.display();
}
