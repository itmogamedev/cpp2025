#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

const int kAsteroidRadius = 32;
const int kWindowX = 800;
const int kWindowY = 600;
const int kFrameRate = 60;
const float kShipSpeed = 400.f;
const float kProjectileSpeed = 600.f;
const float kAsteroidSpeedBase = 20.f;
const float kAsteroidSpeedIncrease = 10.f;
const float kSpawnRateBase = 1.2f;
const float kSpawnRateMin = 0.4f;
const float kSpawnRateDecrease = 0.1f;
const float kCooldownBase = 0.4f;
const float kCooldownMin = 0.12f;
const float kCooldownReduction = 0.004f;
const int kMaxLives = 3;
const float kInvisTime = 1.5f;
const float kShipX = 112.f;
const float kShipY = 64.f;
const float KProjectileX = 4.f;
const float kProjectileY = 12.f;
const std::string kAsteroidFile = "asteroid.png";
const std::string kFontFile = "pixel.ttf";
const std::string kShipFile = "ship.png";
const sf::Color kTransparent = sf::Color(255, 255, 255, 128);

std::vector<int> kTextFont = {24, 48, 32, 24};
;
std::vector<float> kTextX = {10.f, kWindowX / 2.f, kWindowX / 2.f,
                             kWindowX / 2.f};
std::vector<float> kTextY = {10.f, kWindowY / 2.f - 40.f, kWindowY / 2.f + 20.f,
                             kWindowY / 2.f + 70.f};
std::vector<sf::Color> kTextColor = {sf::Color::White, sf::Color::Red,
                                     sf::Color::Yellow, sf::Color::White};
static sf::Texture asteroid_texture;
static sf::Texture ship_texture;

enum GameState { Playing, GameOver };
enum GameText { UIText, GameOverText, FinalScoreText, RestartText, TextAmount };

struct Projectile {
  sf::RectangleShape shape_;

  Projectile(const sf::Vector2f& position) {
    shape_.setSize({KProjectileX, kProjectileY});
    shape_.setFillColor(sf::Color::Yellow);
    shape_.setPosition(position);
  }
};

struct Asteroid {
  sf::Sprite sprite_;
  sf::Vector2f velocity_;

  Asteroid(float game_time) : sprite_(sf::Sprite(asteroid_texture)) {
    sprite_.setOrigin({kAsteroidRadius, kAsteroidRadius});
    float x = static_cast<float>(rand() % (kWindowX - 2 * kAsteroidRadius) +
                                 kAsteroidRadius);
    sprite_.setPosition({x, -kAsteroidRadius});
    float speed = kAsteroidSpeedBase + kAsteroidSpeedIncrease * game_time;
    velocity_ = sf::Vector2f(0.f, speed);
  }
};

struct Ship {
  sf::Sprite sprite_;

  Ship() : sprite_(sf::Sprite(ship_texture)) {
    sprite_.setOrigin({kShipX / 2.f, kShipY / 2.f});
    sprite_.setPosition({(kWindowX - kShipX) / 2.f, kWindowY - kShipY});
  }
};

template <typename T1, typename T2>
bool checkCollision(const T1& a, const T2& b) {
  return a.getGlobalBounds().findIntersection(b.getGlobalBounds()) !=
         std::nullopt;
}

int main() {
  if (!asteroid_texture.loadFromFile(kAsteroidFile)) {
    std::cerr << "No asteroid file :(" << std::endl;
  }

  if (!ship_texture.loadFromFile(kShipFile)) {
    std::cerr << "No ship file :(" << std::endl;
  }

  sf::RenderWindow window(sf::VideoMode({kWindowX, kWindowY}), "Space Shooter");
  window.setFramerateLimit(kFrameRate);
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  sf::Font font;
  if (!font.openFromFile(kFontFile)) {
    return EXIT_FAILURE;
  }

  Ship ship;
  std::vector<Projectile> projectiles;
  std::vector<Asteroid> asteroids;
  std::vector<sf::Text> text;
  for (int i = 0; i < TextAmount; ++i) {
    text.push_back(sf::Text(font));
    text[i].setFillColor(kTextColor[i]);
    text[i].setCharacterSize(kTextFont[i]);
  }

  int score = 0;
  int lives = kMaxLives;
  bool invincible = false;
  float invincible_timer = 0.f;
  float shot_cooldown = kCooldownBase;
  float shot_timer = 0.f;
  float spawn_timer = 0.f;
  float game_time = 0.f;

  sf::Clock clock;
  GameState state = Playing;

  while (window.isOpen()) {
    float dt = clock.restart().asSeconds();
    while (auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      else if (event->is<sf::Event::KeyPressed>()) {
        auto* keyEvent = event->getIf<sf::Event::KeyPressed>();
        if (state == GameOver && keyEvent->code == sf::Keyboard::Key::R) {
          score = 0;
          lives = kMaxLives;
          invincible = false;
          invincible_timer = 0.f;
          shot_cooldown = kCooldownBase;
          shot_timer = 0.f;
          spawn_timer = 0.f;
          game_time = 0.f;
          projectiles.clear();
          asteroids.clear();
          ship = Ship();
          state = Playing;
        }
      }
    }

    if (state == Playing) {
      sf::Vector2f move(0.f, 0.f);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        move.x -= kShipSpeed * dt;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        move.x += kShipSpeed * dt;
      }
      sf::Vector2f new_pos = ship.sprite_.getPosition() + move;
      new_pos.x =
          std::max(0.f, std::min(new_pos.x, static_cast<float>(kWindowX)));
      ship.sprite_.setPosition(new_pos);

      shot_timer += dt;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) &&
          shot_timer >= shot_cooldown) {
        sf::Vector2f ship_pos = ship.sprite_.getPosition();
        sf::Vector2f proj_pos(ship_pos.x - KProjectileX / 2.f,
                              ship_pos.y - kProjectileY);
        projectiles.push_back(Projectile(proj_pos));
        shot_timer = 0.f;
      }

      shot_cooldown =
          std::max(kCooldownMin, kCooldownBase - score * kCooldownReduction);
      float curr_spawn_rate = std::max(
          kSpawnRateMin, kSpawnRateBase - kSpawnRateDecrease * game_time);
      spawn_timer += dt;
      while (spawn_timer >= curr_spawn_rate) {
        asteroids.push_back(Asteroid(game_time));
        spawn_timer -= curr_spawn_rate;
      }

      for (auto& p : projectiles) {
        p.shape_.move({0.f, -kProjectileSpeed * dt});
      }
      for (auto& a : asteroids) {
        a.sprite_.move(a.velocity_ * dt);
      }

      auto proj_out = [](const Projectile& p) {
        return p.shape_.getPosition().y + kProjectileY < 0.f;
      };
      std::erase_if(projectiles, proj_out);

      auto ast_out = [](const Asteroid& a) {
        return a.sprite_.getPosition().y - kAsteroidRadius > kWindowY;
      };
      std::erase_if(asteroids, ast_out);

      for (auto p = projectiles.begin(); p != projectiles.end();) {
        bool hit = false;
        for (auto a = asteroids.begin(); a != asteroids.end(); ++a) {
          if (checkCollision<sf::Shape, sf::Sprite>(p->shape_, a->sprite_)) {
            a = asteroids.erase(a);
            p = projectiles.erase(p);
            score++;
            hit = true;
            break;
          }
        }

        if (!hit) ++p;
      }

      if (!invincible) {
        for (auto a = asteroids.begin(); a != asteroids.end();) {
          if (checkCollision<sf::Sprite, sf::Sprite>(ship.sprite_,
                                                     a->sprite_)) {
            a = asteroids.erase(a);
            lives--;
            if (lives <= 0) {
              state = GameOver;
              break;
            }

            invincible = true;
            invincible_timer = kInvisTime;
            break;
          } else {
            ++a;
          }
        }
      }

      if (invincible) {
        invincible_timer -= dt;
        if (invincible_timer <= 0.f) {
          invincible = false;
        }
      }

      game_time += dt;
    }

    window.clear();

    if (state == Playing) {
      if (invincible) {
        ship.sprite_.setColor(kTransparent);
        window.draw(ship.sprite_);
        ship.sprite_.setColor(sf::Color::White);
      } else {
        window.draw(ship.sprite_);
      }

      for (const auto& p : projectiles) window.draw(p.shape_);

      for (const auto& asteroid : asteroids) {
        window.draw(asteroid.sprite_);
      }

      text[UIText].setPosition({kTextX[UIText], kTextX[UIText]});
      text[UIText].setString("Score: " + std::to_string(score) +
                             "   Lives: " + std::to_string(lives));
      window.draw(text[UIText]);
    } else if (state == GameOver) {
      text[GameOverText].setString("GAME OVER");
      text[FinalScoreText].setString("Final Score: " + std::to_string(score));
      text[RestartText].setString("Press R to restart");

      for (int i = GameOverText; i < TextAmount; ++i) {
        sf::FloatRect bounds = text[i].getLocalBounds();
        text[i].setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        text[i].setPosition({kTextX[i], kTextY[i]});
        window.draw(text[i]);
      }
    }

    window.display();
  }

  return EXIT_SUCCESS;
}