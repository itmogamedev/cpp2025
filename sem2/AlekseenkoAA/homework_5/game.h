#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>

#include "asteroid.h"
#include "constants.h"
#include "player.h"
#include "projectile.h"
#include "randomsystem.h"

enum class GameState { play, over };

class Game {
 public:
  bool load();
  int run();

 private:
  void restart();
  void readEvents(sf::RenderWindow& window);
  void update(float time, bool readKeyboard);
  void readKeyboard(float time);
  void moveShots(float time);
  void moveAsteroids(float time);
  void checkHits();
  void draw(sf::RenderWindow& window) const;
  void drawBackground(sf::RenderWindow& window) const;
  void drawUi(sf::RenderWindow& window) const;
  void drawText(sf::RenderWindow& window, const std::string& text,
                unsigned int size, sf::Vector2f point, sf::Color color) const;
  void drawCenterText(sf::RenderWindow& window, const std::string& text,
                      unsigned int size, float y, sf::Color color) const;
  void shoot();
  void clearShots();
  float reloadTime() const;
  float asteroidSpeed() const;
  void makeStars();
  std::string findAsset(const std::string& path) const;
  bool loadTexture(sf::Texture& texture, const std::string& path) const;
  bool loadFont(sf::Font& target, const std::string& path) const;
  std::string numberText(int number) const;

  RandomSystem random;
  sf::Texture player_texture;
  std::array<sf::Texture, 5> alien_textures;
  sf::Font font;
  Player player;
  std::vector<Asteroid> asteroids;
  std::vector<Projectile> shots;
  std::vector<sf::Vector2f> stars;
  GameState state = GameState::play;
  int score = 0;
  int lives = startLives;
  float game_time = 0.0f;
  float reload = 0.0f;
};
