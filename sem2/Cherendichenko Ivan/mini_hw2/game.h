#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "target.h"

class Game {
 public:
  Game();
  void run();

 private:
  enum class State { Playing, GameOver };

  sf::RenderWindow window_;
  sf::Font font_;
  sf::Clock clock_;

  sf::Texture bg_texture_;
  sf::Sprite bg_sprite_;
  bool bg_loaded_ = false;

  std::vector<sf::Texture> sticker_textures_;
  std::vector<std::unique_ptr<Target>> targets_;

  float time_remaining_;
  int score_;
  float miss_flash_timer_;
  State state_;

  void loadAssets();
  void loadStickers();
  void initTargets();

  void handleEvents();
  void onMouseClick(sf::Vector2f pos);
  void update(float dt);

  void render();
  void renderHUD();
  void renderMissFlash();
  void renderGameOver();

  void drawCentred(const std::string& str, unsigned int size, sf::Color fill,
                   float y_offset);
};
